#include <iostream>
#include "ReceiveException.h"
#include "eFriendStatus.h"
#include "eFriendRequestType.h"
#include "PacketHelper.h"
#include "BabelServer.h"
#include "eCommandId.h"
#include "eErrorCode.h"
#include "FileSerializer.h"
#include "RequestMaker.h"
#include "Serializer.hpp"
#include "StandardInput.h"
#include "Debug.h"
#include "constant.h"


BabelServer::BabelServer(int port) : _port(port), _running(true), _userFound(false), _strangerFound(false)
{
	FileSerializer fileSerializer(DEFAULT_SERVER_DB_FILE);
	std::string data = fileSerializer.readFromFile();
	if (data.size() > 0)
		this->_database.deserialize(data);
}


BabelServer::~BabelServer()
{
	FileSerializer fileSerializer(DEFAULT_SERVER_DB_FILE);
	fileSerializer.writeToFile(this->_database.serialize());
}


void					BabelServer::start()
{
	Debug::Log("> Server started.");
	this->_server.start();
	this->loop();
	this->_server.stop();
}



// ---------- Timeout Methods ---------- //

void					BabelServer::setTimeout()
{
	unsigned long long int timeout = (unsigned long long int)-1;
	for (std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator it = this->_strangers.begin(); it != this->_strangers.end(); ++it)
	{
		if (it->second < timeout)
			timeout = it->second;
	}
	if (timeout == (unsigned long long int)-1)
	{
		this->_lastTimeout = 0;
		this->_select.setTimeout(-1, -1);
	}
	else
	{
		this->_lastTimeout = timeout;
		this->_select.setTimeout((long)(timeout / SEC_IN_USEC), (long)(timeout % SEC_IN_USEC));
	}
}

void					BabelServer::updateTimeout()
{
	if (this->_lastTimeout != 0)
	{
		long sec;
		long usec;
		this->_select.getRemainingTime(sec, usec);
		unsigned long long int timeDiff = this->_lastTimeout - sec * SEC_IN_USEC - usec;
		for (std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator it = this->_strangers.begin(); it != this->_strangers.end(); ++it)
		{
			if (it->second <= timeDiff)
				it->second = 0;
			else
				it->second -= timeDiff;
		}
	}
}

// ---------- End of Timeout Methods ---------- //



// ---------- Kicking Methods ---------- //

void					BabelServer::kickIfRequired(ITCPRemoteClient* client)
{
	std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator, std::string> >::iterator* strangerToRemove = NULL;
	for (std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator, std::string> >::iterator it = this->_strangersToKick.begin(); client != NULL && it != this->_strangersToKick.end(); ++it)
	{
		if ((it->first)->first == client)
		{
			this->kickStranger(it->first, it->second);
			strangerToRemove = new std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator, std::string> >::iterator(it);
			client = NULL;
		}
	}
	if (strangerToRemove != NULL)
	{
		this->_strangersToKick.erase(*strangerToRemove);
		delete strangerToRemove;
	}

	std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator, std::string> >::iterator* clientToRemove = NULL;
	for (std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator, std::string> >::iterator it = this->_usersToKick.begin(); client != NULL && it != this->_usersToKick.end(); ++it)
	{
		if ((it->first)->first == client)
		{
			this->kickUser(it->first, it->second);
			clientToRemove = new std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator, std::string> >::iterator(it);
			client = NULL;
		}
	}
	if (clientToRemove != NULL)
	{
		this->_usersToKick.erase(*clientToRemove);
		delete clientToRemove;
	}
}

void					BabelServer::kickStranger(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator& stranger, std::string const& reason)
{
	Debug::Log("Guest kicked: '" + stranger->first->getIp() + "' (" + reason + ")");
	this->_select.removeReadFd(stranger->first);
	delete stranger->first;
	this->_strangers.erase(stranger);
}

void					BabelServer::kickUser(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator& client, std::string const& reason)
{
	Debug::Log("Client kicked: '" + client->second.getName() + "' from " + client->first->getIp() + " (" + reason + ")");
	client->second.setOnlineStatus(Offline);
	this->notifyFriends(client->second, Offline);
	this->_select.removeReadFd(client->first);
	this->_select.removeWriteFd(client->first);
	delete client->first;
	this->_users.erase(client);
}

void					BabelServer::kickUser(ITCPRemoteClient* client, std::string const& reason)
{
	std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator* toRemove = NULL;
	for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator it = this->_users.begin(); toRemove == NULL && it != this->_users.end(); ++it)
	{
		if (it->first == client)
		{
			*toRemove = it;
		}
	}
	if (toRemove != NULL)
	{
		this->kickUser(*toRemove, reason);
	}
}

void					BabelServer::kickStrangers()
{
	for (std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator it = this->_strangers.begin(); it != this->_strangers.end(); ++it)
	{
		if (it->first->mustBeClosed() == false && it->second == 0)
		{
			std::string message;
			PacketHelper::writeTcpHeader(message, KO);
			message += Serializer::serialize<int>(AuthentificationTimeOut);
			PacketHelper::writeTcpHeaderSize(message);

			it->first->prepareMsg(message, message.length());
			this->_select.addWriteFd(it->first);
			it->first->prepareClose();

			this->_strangersToKick.push_front(std::pair<std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator, std::string>(it, "authentification timeout"));
		}
	}
}

// ---------- End of Kicking Methods ---------- //



// ---------- Client Getters Methods ---------- //

bool										BabelServer::isStranger(ITCPRemoteClient* stranger)
{
	this->_strangerFound = false;
	for (std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator it = this->_strangers.begin(); this->_strangerFound == false && it != this->_strangers.end(); ++it)
	{
		if (stranger == it->first)
		{
			this->_soughtStranger = std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator(it);
			this->_strangerFound = true;
		}
	}
	return this->_strangerFound;
}

bool										BabelServer::isAuthentified(ITCPRemoteClient* client)
{
	this->_userFound = false;
	for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator it = this->_users.begin(); this->_userFound == false && it != this->_users.end(); ++it)
	{
		if (client == it->first)
		{
			this->_soughtUser = std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator(it);
			this->_userFound = true;
		}
	}
	return this->_userFound;
}

std::list<std::pair<ITCPRemoteClient*,
	unsigned long long int > > ::iterator&	BabelServer::getStranger()
{
	if (this->_strangerFound == false)
		throw std::runtime_error("BabelServer: getStranger when no stranger has been sought.");
	return this->_soughtStranger;
}

std::list<std::pair<ITCPRemoteClient*,
	UserData& > > ::iterator&				BabelServer::getAuthentified()
{
	if (this->_userFound == false)
		throw std::runtime_error("BabelServer: getClient when client has been sought.");
	return this->_soughtUser;
}

// ---------- End of Client Getters Methods ---------- //



// ---------- IO Handling Methods ---------- //

void					BabelServer::process()
{
	std::list<IWritable*> const& writeReady = this->_select.getReadyWrite();
	for (std::list<IWritable*>::const_iterator it = writeReady.begin(); it != writeReady.end(); ++it)
	{
		(*it)->send();
		this->_select.removeWriteFd(*it);
		this->kickIfRequired(static_cast<ITCPRemoteClient*>(*it));
	}

	std::list<IObservable*> const& readReady = this->_select.getReadyRead();
	for (std::list<IObservable*>::const_iterator it = readReady.begin(); it != readReady.end(); ++it)
	{
		// Input on stdin
		if ((*it)->getReadFd() == 0)
		{
			this->_running = false;
			Debug::Log("> Input detected. Stopping the server.");
		}
		// A new client connected to the server
		else if (*it == &this->_server)
		{
			ITCPRemoteClient* newClient = this->_server.acceptClient();
			this->_strangers.push_front(std::pair<ITCPRemoteClient*, unsigned long long int>(newClient, AUTH_TIMEOUT));
			Debug::Log("Guest connection: " + newClient->getIp());
			this->_select.addReadFd(newClient);

			// Authentification Request
			std::string authRequest;
			PacketHelper::writeTcpHeader(authRequest, RequestAuth);
			PacketHelper::writeTcpHeaderSize(authRequest);
			newClient->prepareMsg(authRequest, authRequest.length());
			this->_select.addWriteFd(newClient);
		}
		// A message has been received
		else
		{
			ITCPRemoteClient* client = static_cast<ITCPRemoteClient*>(*it);
			if (client != NULL)
			{
				this->processMessage(client);
			}
			else
			{
				throw std::runtime_error("Input received on server from an unknown origin.");
			}
		}
	}
}

void					BabelServer::disconnectUser(ITCPRemoteClient* client, std::string const& kickMessage)
{
	// Client is an unauthentified guest
	if (this->isStranger(client))
	{
		this->kickStranger(this->getStranger(), kickMessage);
	}
	// Client is an authentified user
	else if (this->isAuthentified(client))
	{
		this->kickUser(this->getAuthentified(), kickMessage);
	}
	// Unknown origin
	else
	{
		Debug::Log("Unknown client kicked: '" + client->getIp() + " (" + kickMessage + ")");
		this->_select.removeReadFd(client);
		this->_select.removeWriteFd(client);
		delete client;
	}
}

void					BabelServer::processMessage(ITCPRemoteClient* client)
{
	std::string message;
	try
	{
		if (client->receiveMsg(message) == 0)
		{
			this->disconnectUser(client, "has disconnected");
			return;
		}
	}
	catch (ReceiveException&)
	{
		this->disconnectUser(client, "has improperly and suddenly disconnected.");
		return;
	}

	std::istringstream iss(message);
	TCPPacketHeader header;
	int length = PacketHelper::getUnreadSize(iss);

	while (iss.good() && length > 0)
	{
		// Invalid TCP header
		if (length < (int)TCP_HEADER_SIZE || PacketHelper::readTcpHeader(iss, header) == false)
		{
			this->disconnectUser(client, "invalid TCP header");
			return;
		}
		// Valid TCP header
		else
		{
			// Client is an unauthentified guest
			if (this->isStranger(client))
			{
				this->processStrangerMessage(this->getStranger(), header, iss);
			}
			// Client is an authentified user
			else if (this->isAuthentified(client))
			{
				this->processUserMessage(this->getAuthentified(), header, iss);
			}
			// Unknown origin
			else
			{
				Debug::Log("Message received from an unknown client");
			}
		}
		length = PacketHelper::getUnreadSize(iss);
	}
}

// ---------- End of IO Handling Methods ---------- //



// ---------- Social-related Methods ---------- //

void					BabelServer::notifyFriends(UserData& user, eFriendStatus status)
{
	std::list<UserData*> friendsList = user.getListFriend();
	for (std::list<UserData*>::iterator it = friendsList.begin(); it != friendsList.end(); ++it)
	{
		if ((*it)->getOnlineStatus() == Online)
		{
			std::string request = RequestMaker::FriendStatusUpdateRequest(status, user.getName());
			ITCPRemoteClient* soughtFriend = NULL;
			for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator j = this->_users.begin(); soughtFriend == NULL && j != this->_users.end(); ++j)
			{
				if (**it == j->second)
				{
					soughtFriend = j->first;
				}
			}
			if (soughtFriend != NULL)
			{
				Debug::Log("FriendStatusUpdate: notifying '" + (*it)->getName() + "' (" + soughtFriend->getIp() + ") that '" + user.getName() + "' just " + (status == Online ? "connected." : "disconnected."));
				soughtFriend->prepareMsg(request, request.length());
				this->_select.addWriteFd(soughtFriend);
			}
		}
	}
}

void					BabelServer::processFriendRequest(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator& client, int payloadSize, std::istringstream& iss)
{
	bool failed = false;
	int dataSize = PacketHelper::getUnreadSize(iss);
	if (dataSize < payloadSize || payloadSize < 7)
		failed = true;
	else
	{
		eFriendRequestType requestType = (eFriendRequestType)Serializer::deserialize<char>(iss);
		std::string asker = Serializer::deserialize<std::string>(iss);
		std::string asked = Serializer::deserialize<std::string>(iss);
		if (iss.good() == false || dataSize - PacketHelper::getUnreadSize(iss) != payloadSize || asker.compare(client->second.getName()) != 0 ||
			(requestType != Addition && requestType != Removal))
			failed = true;
		else
		{
			eErrorCode status;
			// Friend Addition Request 
			if (requestType == Addition)
			{
				status = this->_database.addFriendRequest(client->second, asked);
			}
			// Friend Removal Request
			else
			{
				status = this->_database.removeFriend(client->second, asked);
			}
			if (status != Success)
			{
				Debug::LogErrorCode("-FriendRequest request: '" + asker + "' (" + client->first->getIp() + (requestType == Addition ? ") wanted to add '" : ") wanted to remove '") + asked + "' as a friend: ", status);
				std::string request = RequestMaker::KORequest(status);
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
			}
			else
			{
				Debug::Log("-> '" + asker + "' (" + client->first->getIp() + (requestType == Addition ? ") asked '" : ") removed '") + asked + "' as a friend");
				std::string request = RequestMaker::OKRequest(FriendRequest);
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
				UserData* askedUser = this->_database.getUser(asked);
				if (askedUser == NULL)
					throw std::runtime_error("User '" + asked + "' could not be loaded in memory from the database.");
				if (askedUser->getOnlineStatus() == Online)
				{
					for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator it = this->_users.begin(); askedUser != NULL && it != this->_users.end(); ++it)
					{
						if (it->second == *askedUser)
						{
							std::string notification = RequestMaker::FriendsRequest((char)requestType, asker, asked);
							it->first->prepareMsg(notification, notification.length());
							this->_select.addWriteFd(it->first);
							askedUser = NULL;
						}
					}
				}
			}
		}
	}
	if (failed)
	{
		Debug::Log("-FriendRequest request: invalid request (from '" + client->second.getName() + "' (" + client->first->getIp() + "))");
		std::string request = RequestMaker::KORequest(UnknownCommand);
		client->first->prepareMsg(request, request.length());
		this->_select.addWriteFd(client->first);
	}
}

void					BabelServer::processFriendValidation(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator& client, int payloadSize, std::istringstream& iss)
{
	bool failed = false;
	int dataSize = PacketHelper::getUnreadSize(iss);
	if (dataSize < payloadSize || payloadSize < 7)
		failed = true;
	else
	{
		char accepted = (eFriendRequestType)Serializer::deserialize<char>(iss);
		std::string asker = Serializer::deserialize<std::string>(iss);
		std::string asked = Serializer::deserialize<std::string>(iss);
		if (iss.good() == false || dataSize - PacketHelper::getUnreadSize(iss) != payloadSize || asked.compare(client->second.getName()) != 0 || (accepted != 0 && accepted != 1))
			failed = true;
		else
		{
			eErrorCode status;
			// FriendRequest Denied
			if (accepted == 0)
			{
				status = this->_database.refuseFriendRequest(client->second, asker);
			}
			// FriendRequest Accepted
			else
			{
				status = this->_database.validateFriendRequest(client->second, asker);
			}
			if (status != Success)
			{
				Debug::LogErrorCode("-FriendValidation request: '" + asked + "' (" + client->first->getIp() + (accepted == 0 ? ") wanted to refuse '" : ") wanted to accept '") + asker + "' as a friend: ", status);
				std::string request = RequestMaker::KORequest(status);
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
			}
			else
			{
				Debug::Log("-> '" + asked + "' (" + client->first->getIp() + (accepted == 0 ? ") refused '" : ") accepted '") + asker + "' as a friend");
				UserData* askerUser = this->_database.getUser(asker);
				if (askerUser == NULL)
					throw std::runtime_error("User '" + asker + "' could not be loaded in memory from the database.");
				std::string request;
				if (askerUser->getOnlineStatus() == Online)
				{
					ITCPRemoteClient* askerClient = NULL;
					std::string notification;
					for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator it = this->_users.begin(); askerClient == NULL && it != this->_users.end(); ++it)
					{
						if (it->second == *askerUser)
							askerClient = it->first;
					}
					if (accepted == 0)
					{
						request = RequestMaker::OKRequest(FriendValidation);
						notification = RequestMaker::FriendStatusUpdateRequest((char)Offline, asked);
					}
					else
					{
						request = RequestMaker::FriendStatusUpdateRequest((char)Online, asker);
						notification = RequestMaker::FriendStatusUpdateRequest((char)Online, asked);
					}
					if (askerClient != NULL)
					{
						askerClient->prepareMsg(notification, notification.length());
						this->_select.addWriteFd(askerClient);
					}
				}
				else
				{
					request = RequestMaker::FriendStatusUpdateRequest((char)Offline, asker);
				}
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
			}
		}
	}
	if (failed)
	{
		Debug::Log("-FriendValidation request: invalid request (from '" + client->second.getName() + "' (" + client->first->getIp() + "))");
		std::string request = RequestMaker::KORequest(UnknownCommand);
		client->first->prepareMsg(request, request.length());
		this->_select.addWriteFd(client->first);
	}
}

// ---------- End of Social-related Methods ---------- //



// ---------- Account-related Methods ---------- //

void					BabelServer::signInUser(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator& client, UserData* user)
{
	Debug::Log("-> " + client->first->getIp() + " signed in as " + user->getName());
	user->setOnlineStatus(Online);

	std::list<std::pair<std::string, char> > friendsList;
	std::list<UserData*> friends = user->getListFriend();
	for (std::list<UserData*>::iterator it = friends.begin(); it != friends.end(); ++it)
	{
		friendsList.push_front(std::pair<std::string, char>((*it)->getName(), (char)((*it)->getOnlineStatus())));
	}
	friends = user->getListFriendRequest();
	for (std::list<UserData*>::iterator it = friends.begin(); it != friends.end(); ++it)
	{
		friendsList.push_front(std::pair<std::string, char>((*it)->getName(), (char)(FriendRequestPending)));
	}

	std::string request = RequestMaker::SendFriendList(friendsList);
	client->first->prepareMsg(request, request.length());
	this->_select.addWriteFd(client->first);

	this->_users.push_front(std::pair<ITCPRemoteClient*, UserData&>(client->first, *user));
	this->_strangers.erase(client);
}

void					BabelServer::processSignIn(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator& client, int payloadSize, std::istringstream& iss)
{
	bool failed = false;
	int dataSize = PacketHelper::getUnreadSize(iss);
	if (dataSize < payloadSize || payloadSize < 6)
		failed = true;
	else
	{
		std::string username;
		std::string password;
		username = Serializer::deserialize<std::string>(iss);
		password = Serializer::deserialize<std::string>(iss);
		if (iss.good() == false || dataSize - PacketHelper::getUnreadSize(iss) != payloadSize)
			failed = true;
		else
		{
			if (this->_database.checkCredentials(username, password) == UnknownUser)
			{
				Debug::Log("-SignIn request: invalid credentials (from " + client->first->getIp() + ")");
				std::string request = RequestMaker::KORequest(InvalidCredentials);
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
				client->second = AUTH_TIMEOUT;
			}
			else
			{
				UserData* user = this->_database.getUser(username);
				if (user == NULL)
					throw std::runtime_error("User '" + username + "' could not be loaded in memory from the database.");
				if (user->getOnlineStatus() == Online)
				{
					Debug::Log("-SignIn request: user already connected: '" + username + "' (from " + client->first->getIp() + ")");
					std::string request = RequestMaker::KORequest(UserAlreadyConnected);
					client->first->prepareMsg(request, request.length());
					this->_select.addWriteFd(client->first);
					client->second = AUTH_TIMEOUT;
				}
				else
				{
					this->signInUser(client, user);
					this->notifyFriends(*user, Online);
				}
			}
		}
	}
	if (failed)
	{
		Debug::Log("-SignIn request: invalid request (from " + client->first->getIp() + ")");
		std::string request = RequestMaker::KORequest(UnknownCommand);
		client->first->prepareMsg(request, request.length());
		this->_select.addWriteFd(client->first);
	}
}

bool					BabelServer::validUsername(std::string const& username) const
{
	return username.length() >= MIN_USERNAME_SIZE && username.length() <= MAX_USERNAME_SIZE && username.find_first_not_of(USERNAME_CHAR_SET) == std::string::npos;
}

bool					BabelServer::validPassword(std::string const& password) const
{
	return password.length() >= MIN_PASSWORD_SIZE && password.length() <= MAX_PASSWORD_SIZE && password.find_first_not_of(PASSWORD_CHAR_SET) == std::string::npos;
}

void					BabelServer::processSignUp(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator& client, int payloadSize, std::istringstream& iss)
{
	bool failed = false;
	int dataSize = PacketHelper::getUnreadSize(iss);
	if (dataSize < payloadSize || payloadSize < 6)
		failed = true;
	else
	{
		std::string username;
		std::string password;
		username = Serializer::deserialize<std::string>(iss);
		password = Serializer::deserialize<std::string>(iss);
		if (iss.good() == false || dataSize - PacketHelper::getUnreadSize(iss) != payloadSize)
			failed = true;
		else
		{
			if (this->validUsername(username) == false)
			{
				Debug::Log("-SignUp request: invalid username: '" + username + "' (from " + client->first->getIp() + ")");
				std::string request = RequestMaker::KORequest(InvalidUsername);
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
				client->second = AUTH_TIMEOUT;
			}
			else if (this->validPassword(password) == false)
			{
				Debug::Log("-SignUp request: invalid password: '" + password + "' (from " + client->first->getIp() + ")");
				std::string request = RequestMaker::KORequest(InvalidPassword);
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
				client->second = AUTH_TIMEOUT;
			}
			else
			{

				if (this->_database.addUser(username, password) == UnavailableUsername)
				{
					Debug::Log("-SignUp request: unavailable username: '" + username + "' (from " + client->first->getIp() + ")");
					std::string request = RequestMaker::KORequest(UnavailableUsername);
					client->first->prepareMsg(request, request.length());
					this->_select.addWriteFd(client->first);
					client->second = AUTH_TIMEOUT;
				}
				else
				{
					UserData* user = this->_database.getUser(username);
					Debug::Log("-> '" + username + "' (" + client->first->getIp() + ") just created an account");
					if (user == NULL)
						throw std::runtime_error("User '" + username + "' could not be loaded in memory from the database.");
					this->signInUser(client, user);
					this->notifyFriends(*user, Online);
				}
			}
		}
	}
	if (failed)
	{
		Debug::Log("-SignUp request: invalid request (from " + client->first->getIp() + ")");
		std::string request = RequestMaker::KORequest(UnknownCommand);
		client->first->prepareMsg(request, request.length());
		this->_select.addWriteFd(client->first);
	}
}

// ---------- End of Account-related Methods ---------- //



// ---------- Call-related Methods ---------- //

void					BabelServer::processAddToCall(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator& client, int payloadSize, std::istringstream& iss)
{
	bool failed = false;
	int dataSize = PacketHelper::getUnreadSize(iss);
	if (dataSize < payloadSize || payloadSize < 7)
		failed = true;
	else
	{
		std::string calleeName = Serializer::deserialize<std::string>(iss);
		std::list<std::string> callers = Serializer::deserialize<std::list<std::string> >(iss);
		if (iss.good() == false || dataSize - PacketHelper::getUnreadSize(iss) != payloadSize)
			failed = true;
		else
		{
			if (client->second.isFriend(calleeName) == false)
			{
				Debug::Log("-AddToCall request: '" + client->second.getName() + "' (" + client->first->getIp() + ") wanted to call an unknown user: '" + calleeName + "'");
				std::string request = RequestMaker::KORequest(UnknownUser);
				client->first->prepareMsg(request, request.length());
				this->_select.addWriteFd(client->first);
			}
			else
			{
				UserData* callee = this->_database.getUser(calleeName);
				if (callee == NULL)
					throw std::runtime_error("User '" + calleeName + "' could not be loaded in memory from the database.");
				if (callee->getOnlineStatus() == Offline)
				{
					Debug::Log("-AddToCall request: '" + client->second.getName() + "' (" + client->first->getIp() + "): friend offline: '" + calleeName + "'");
					std::string request = RequestMaker::KORequest(UserOffline);
					client->first->prepareMsg(request, request.length());
					this->_select.addWriteFd(client->first);
				}
				else
				{
					Debug::Log("-> '" + client->second.getName() + "' (" + client->first->getIp() + ") invited '" + calleeName + "' in a call");
					std::string request = RequestMaker::OKRequest(AddToCall);
					client->first->prepareMsg(request, request.length());
					this->_select.addWriteFd(client->first);
					for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator it = this->_users.begin(); callee != NULL && it != this->_users.end(); ++it)
					{
						if (it->second == *callee)
						{
							std::string notification = RequestMaker::AddToCallRequest(client->second.getName(), callers);
							it->first->prepareMsg(notification, notification.length());
							this->_select.addWriteFd(it->first);
							callee = NULL;
						}
					}
				}
			}
		}
	}
	if (failed)
	{
		Debug::Log("-AddToCall request: invalid request (from '" + client->second.getName() + "' (" + client->first->getIp() + "))");
		std::string request = RequestMaker::KORequest(UnknownCommand);
		client->first->prepareMsg(request, request.length());
		this->_select.addWriteFd(client->first);
	}
}

void					BabelServer::processAnswerCall(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator& client, int payloadSize, std::istringstream& iss)
{
	bool failed = false;
	int dataSize = PacketHelper::getUnreadSize(iss);
	if (dataSize < payloadSize || payloadSize < 4)
		failed = true;
	else
	{
		char accepted = Serializer::deserialize<char>(iss);
		std::string callerName = Serializer::deserialize<std::string>(iss);
		if (iss.good() == false || dataSize - PacketHelper::getUnreadSize(iss) != payloadSize || (accepted != 0 && accepted != 1))
			failed = true;
		else
		{
			if (client->second.isFriend(callerName) == true)
			{
				UserData* caller = this->_database.getUser(callerName);
				if (caller == NULL)
					throw std::runtime_error("User '" + callerName + "' could not be loaded in memory from the database.");
				if (caller->getOnlineStatus() == Online)
				{
					ITCPRemoteClient* callerClient = NULL;
					for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator it = this->_users.begin(); callerClient == NULL && it != this->_users.end(); ++it)
					{
						if (it->second == *caller)
						{
							callerClient = it->first;
						}
					}
					if (callerClient == NULL)
						throw std::runtime_error("User '" + callerName + "' could not be loaded in memory from the list of online users.");
					Debug::Log("-> '" + client->second.getName() + "' (" + client->first->getIp() + (accepted == 0 ? ") refused to join '" : ") accepted to join '") + callerName + "' in a call");
					std::string request;
					if (accepted == 0)
					{
						request = RequestMaker::CallDroppedRequest(client->second.getName());
					}
					else
					{
						request = RequestMaker::HostRequest(client->first->getIp(), client->second.getName());
					}
					callerClient->prepareMsg(request, request.length());
					this->_select.addWriteFd(callerClient);
				}
			}
		}
	}
	if (failed)
	{
		Debug::Log("-AnswerCall request: invalid request (from '" + client->second.getName() + "' (" + client->first->getIp() + "))");
		std::string request = RequestMaker::KORequest(UnknownCommand);
		client->first->prepareMsg(request, request.length());
		this->_select.addWriteFd(client->first);
	}
}

void					BabelServer::processHostReady(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator& client, int payloadSize, std::istringstream& iss)
{
	bool failed = false;
	int dataSize = PacketHelper::getUnreadSize(iss);
	if (dataSize < payloadSize || payloadSize < 7)
		failed = true;
	else
	{
		int port = Serializer::deserialize<int>(iss);
		std::string calleeName = Serializer::deserialize<std::string>(iss);
		if (iss.good() == false || dataSize - PacketHelper::getUnreadSize(iss) != payloadSize)
			failed = true;
		else
		{
			if (client->second.isFriend(calleeName) == true)
			{
				UserData* callee = this->_database.getUser(calleeName);
				if (callee == NULL)
					throw std::runtime_error("User '" + calleeName + "' could not be loaded in memory from the database.");
				if (callee->getOnlineStatus() == Online)
				{
					ITCPRemoteClient* calleeClient = NULL;
					for (std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator it = this->_users.begin(); calleeClient == NULL && it != this->_users.end(); ++it)
					{
						if (it->second == *callee)
						{
							calleeClient = it->first;
						}
					}
					if (calleeClient == NULL)
						throw std::runtime_error("User '" + calleeName + "' could not be loaded in memory from the list of online users.");
					Debug::Log("-> '" + client->second.getName() + "' (" + client->first->getIp() + ") became host for a call with '" + calleeName + "'");
					std::string request = RequestMaker::ConnectToPeerRequest(port, client->first->getIp(), client->second.getName());
					calleeClient->prepareMsg(request, request.length());
					this->_select.addWriteFd(calleeClient);
				}
			}
		}
	}
	if (failed)
	{
		Debug::Log("-HostReady request: invalid request (from '" + client->second.getName() + "' (" + client->first->getIp() + "))");
		std::string request = RequestMaker::KORequest(UnknownCommand);
		client->first->prepareMsg(request, request.length());
		this->_select.addWriteFd(client->first);
	}
}

// ---------- Requests Handling Methods ---------- //



// ---------- Requests Handling Methods ---------- //

void					BabelServer::processStrangerMessage(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator& client, TCPPacketHeader const& header, std::istringstream& iss)
{
	std::string request;
	Debug::LogCommandId("Request received from '" + client->first->getIp() + "' (guest): ", (int)(header.commandId));
	switch (header.commandId)
	{
		case SignUp:
			this->processSignUp(client, header.payloadSize, iss);
			;
			break;
		case SignIn:
			this->processSignIn(client, header.payloadSize, iss);
			break;
		default:
		  request = RequestMaker::KORequest(UnknownCommand);
			client->first->prepareMsg(request, request.length());
			this->_select.addWriteFd(client->first);
			break;
	}
}

void					BabelServer::processUserMessage(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator& client, TCPPacketHeader const& header, std::istringstream& iss)
{
	std::string request;
	Debug::LogCommandId("Request received from user '" + client->second.getName() + "' (ip: " + client->first->getIp() + "): ", (int)(header.commandId));
	switch (header.commandId)
	{
		case FriendRequest:
			this->processFriendRequest(client, header.payloadSize, iss);
			break;
		case FriendValidation:
			this->processFriendValidation(client, header.payloadSize, iss);
			break;
		case AddToCall:
			this->processAddToCall(client, header.payloadSize, iss);
			break;
		case AnswerCall:
			this->processAnswerCall(client, header.payloadSize, iss);
			break;
		case HostReady:
			this->processHostReady(client, header.payloadSize, iss);
			break;
		case OK:
			;
			break;
		case KO:
			;
			break;
		default:
		  request = RequestMaker::KORequest(UnknownCommand);
		  client->first->prepareMsg(request, request.length());
		  this->_select.addWriteFd(client->first);
		  break;
	}
}

// ---------- End of Requests Handling Methods ---------- //




void					BabelServer::updateData()
{
	// Remove every guest clients who have taken too long to authentify.
	this->kickStrangers();
}


void					BabelServer::loop()
{
	StandardInput standardInput;
	this->_select.addReadFd(&this->_server);
	this->_select.addReadFd(&standardInput);
	while (this->_running)
	{
		this->setTimeout();
		this->_select.start();
		this->updateTimeout();
		this->process();
		this->updateData();
	}
}

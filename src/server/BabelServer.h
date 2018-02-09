#pragma once

#include <list>
#include <sstream>
#include <utility>
#include "constant.h"
#include "Database.h"
#include "UserData.h"
#include "mySelect.h"
#include "myTCPServer.h"
#include "TCPPacketHeader.h"
#include "ITCPRemoteClient.h"


class BabelServer
{
public:
	BabelServer(int = DEFAULT_SERVER_PORT);
	~BabelServer();

public:
	void							start();


private:
	void							loop();

	void							setTimeout();
	void							updateTimeout();

	void							process();
	void							updateData();

	void							processMessage(ITCPRemoteClient*);

	bool										isStranger(ITCPRemoteClient*);
	bool										isAuthentified(ITCPRemoteClient*);
	std::list<std::pair<ITCPRemoteClient*,
		unsigned long long int> >::iterator&		getStranger();
	std::list<std::pair<ITCPRemoteClient*,
		UserData& > > ::iterator&				getAuthentified();


	bool							validUsername(std::string const&) const;
	bool							validPassword(std::string const&) const;

	void							disconnectUser(ITCPRemoteClient*, std::string const&);
	void							signInUser(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator&, UserData*);

	void							notifyFriends(UserData&, eFriendStatus);

	void							processFriendRequest(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator&, int, std::istringstream&);
	void							processFriendValidation(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator&, int, std::istringstream&);

	void							kickIfRequired(ITCPRemoteClient*);
	void							kickUser(ITCPRemoteClient*, std::string const&);
	void							kickUser(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator&, std::string const&);
	void							kickStranger(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator&, std::string const&);
	void							kickStrangers();

	void							processAddToCall(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator&, int, std::istringstream&);
	void							processAnswerCall(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator&, int, std::istringstream&);
	void							processHostReady(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator&, int, std::istringstream&);

	void							processStrangerMessage(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator&, TCPPacketHeader const&, std::istringstream&);
	void							processUserMessage(std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator&, TCPPacketHeader const&, std::istringstream&);

	void							processSignIn(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator&, int, std::istringstream&);
	void							processSignUp(std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator&, int, std::istringstream&);

private:
	Database						_database;
	myTCPServer						_server;
	mySelect						_select;

	short							_port;
	bool							_running;
	unsigned long long int			_lastTimeout;

	std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >													_strangers;
	std::list<std::pair<ITCPRemoteClient*, UserData&> >																_users;

	bool																											_userFound;
	std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator													_soughtUser;
	bool																											_strangerFound;
	std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator										_soughtStranger;

	std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, unsigned long long int> >::iterator, std::string> >	_strangersToKick;
	std::list<std::pair<std::list<std::pair<ITCPRemoteClient*, UserData&> >::iterator, std::string> >					_usersToKick;

};


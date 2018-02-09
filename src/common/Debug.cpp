#include <iostream>
#include "Debug.h"
#include "eCommandId.h"
#include "eErrorCode.h"
#include "constant.h"

bool Debug::_debugEnabled = DEBUG_ENABLED;

void		Debug::Log(std::string const& message)
{
	if (Debug::_debugEnabled)
	{
		std::cout << message << std::endl;
	}
}

void		Debug::LogError(std::string const& message)
{
	if (Debug::_debugEnabled)
	{
		std::cerr << message << std::endl;
	}
}

void		Debug::LogCommandId(std::string const& message, int commandId, std::string const& after)
{
	if (Debug::_debugEnabled)
	{
		std::cout << message;
		switch (commandId)
		{
			case RequestAuth:
				std::cout << "RequestAuth";
				break;
			case SignUp:
				std::cout << "SignUp";
				break;
			case SignIn:
				std::cout << "SignIn";
				break;
			case SendFriendsList:
				std::cout << "SendFriendsList";
				break;
			case FriendStatusUpdate:
				std::cout << "FriendStatusUpdate";
				break;
			case FriendRequest:
				std::cout << "FriendRequest";
				break;
			case FriendValidation:
				std::cout << "FriendValidation";
				break;
			case AddToCall:
				std::cout << "AddToCall";
				break;
			case AnswerCall:
				std::cout << "AnswerCall";
				break;
			case CallDropped:
				std::cout << "CallDropped";
				break;
			case Host:
				std::cout << "Host";
				break;
			case HostReady:
				std::cout << "HostReady";
				break;
			case ConnectToPeer:
				std::cout << "ConnectToPeer";
				break;
			case OK:
				std::cout << "OK";
				break;
			case KO:
				std::cout << "KO";
				break;
			case Welcome:
				std::cout << "Welcome";
				break;
			case ParticipantStatusUpdate:
				std::cout << "ParticipantStatusUpdate";
				break;
			case UDPReady:
				std::cout << "UDPReady";
				break;
			case SendText:
				std::cout << "SendText";
				break;
			default:
				std::cout << "Unknown command (" << commandId << ")";
				break;
		}
		std::cout << after << std::endl;
	}
}

void		Debug::LogErrorCode(std::string const& message, int errorCode, std::string const& after)
{
	if (Debug::_debugEnabled)
	{
		std::cout << message;
		switch (errorCode)
		{
			case Success:
				std::cout << "Success";
				break;
			case InvalidUsername:
				std::cout << "InvalidUsername";
				break;
			case InvalidPassword:
				std::cout << "InvalidPassword";
				break;
			case UnavailableUsername:
				std::cout << "UnavailableUsername";
				break;
			case UnknownUser:
				std::cout << "UnknownUser";
				break;
			case UserAlreadyConnected:
				std::cout << "UserAlreadyConnected";
				break;
			case AlreadyFriend:
				std::cout << "AlreadyFriend";
				break;
			case FriendsMaxedOut:
				std::cout << "FriendsMaxedOut";
				break;
			case UserOffline:
				std::cout << "UserOffline";
				break;
			case RequestPending:
				std::cout << "RequestPending";
				break;
			case AuthentificationTimeOut:
				std::cout << "AuthentificationTimeOut";
				break;
			case UnknownCommand:
				std::cout << "UnknownCommand";
				break;
			case InvalidCredentials:
				std::cout << "InvalidCredentials";
				break;
			default:
				std::cout << "Unknown error code (" << errorCode << ")";
				break;
		}
		std::cout << after << std::endl;
	}
}

void		Debug::enableDebug(bool enabled)
{
	Debug::_debugEnabled = enabled;

}

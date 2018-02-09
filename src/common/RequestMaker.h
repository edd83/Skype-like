#pragma once

#include <list>
#include <string>
#include <utility>
#include "eErrorCode.h"
#include "eCommandId.h"

class RequestMaker
{
public:
	~RequestMaker() {}

	static std::string KORequest(eErrorCode);
	static std::string OKRequest(eCommandId);
	static std::string SendFriendList(std::list<std::pair<std::string, char> > const&);
	static std::string FriendStatusUpdateRequest(char, std::string const&);
	static std::string FriendsRequest(char, std::string const&, std::string const&);
	static std::string AddToCallRequest(std::string const&, std::list<std::string> const&);
	static std::string CallDroppedRequest(std::string const&);
	static std::string HostRequest(std::string const&, std::string const&);
	static std::string ConnectToPeerRequest(int, std::string const&, std::string const&);


private:
	RequestMaker() {}
};

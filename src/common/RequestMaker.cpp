#include "PacketHelper.h"
#include "RequestMaker.h"
#include "eCommandId.h"
#include "Serializer.hpp"

std::string			RequestMaker::KORequest(eErrorCode errorCode)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, KO);
	r += Serializer::serialize<int>(errorCode);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

std::string			RequestMaker::OKRequest(eCommandId commandId)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, OK);
	r += Serializer::serialize<int>(commandId);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

std::string			RequestMaker::SendFriendList(std::list<std::pair<std::string, char> > const& friendList)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, SendFriendsList);
	r += Serializer::serialize<std::list<std::pair<std::string, char> > >(friendList);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

std::string			RequestMaker::FriendStatusUpdateRequest(char status, std::string const& username)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, FriendStatusUpdate);
	r += Serializer::serialize<char>(status);
	r += Serializer::serialize<std::string>(username);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

std::string			RequestMaker::FriendsRequest(char operation, std::string const& asker, std::string const& asked)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, FriendRequest);
	r += Serializer::serialize<char>(operation);
	r += Serializer::serialize<std::string>(asker);
	r += Serializer::serialize<std::string>(asked);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

std::string			RequestMaker::AddToCallRequest(std::string const& caller, std::list<std::string> const& callers)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, AddToCall);
	r += Serializer::serialize<std::string>(caller);
	r += Serializer::serialize<std::list<std::string> >(callers);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

std::string			RequestMaker::CallDroppedRequest(std::string const& refuser)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, CallDropped);
	r += Serializer::serialize<std::string>(refuser);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

std::string			RequestMaker::HostRequest(std::string const& ip, std::string const& callee)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, Host);
	r += Serializer::serialize<std::string>(ip);
	r += Serializer::serialize<std::string>(callee);
	PacketHelper::writeTcpHeaderSize(r);
	return r;

}

std::string			RequestMaker::ConnectToPeerRequest(int port, std::string const& ip, std::string const& caller)
{
	std::string r;
	PacketHelper::writeTcpHeader(r, ConnectToPeer);
	r += Serializer::serialize<int>(port);
	r += Serializer::serialize<std::string>(ip);
	r += Serializer::serialize<std::string>(caller);
	PacketHelper::writeTcpHeaderSize(r);
	return r;
}

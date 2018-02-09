#include "myTCPRemoteClient.h"


myTCPRemoteClient::myTCPRemoteClient(struct sockaddr_in &addr, int fd) :
#ifdef _WIN32
	WindowsTCPRemoteClient(addr, fd)
#else
	LinuxTCPRemoteClient(addr, fd)
#endif
{
}

myTCPRemoteClient::~myTCPRemoteClient()
{
};

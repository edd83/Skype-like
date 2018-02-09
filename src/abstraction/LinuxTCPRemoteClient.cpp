#ifndef _WIN32

#include <exception>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ReceiveException.h"
#include "LinuxTCPSocket.h"
#include "LinuxTCPRemoteClient.h"

LinuxTCPRemoteClient::LinuxTCPRemoteClient(struct sockaddr_in &addr,
	int fd)
{
	this->_closing = false;
	this->_sock = new LinuxTCPSocket(addr, fd);
	if (this->_sock == 0)
		throw std::runtime_error("Could not create a new LinuxTCPSocket");
	this->_ip = inet_ntoa(addr.sin_addr);
	this->_toSendLen = 0;
}

LinuxTCPRemoteClient::~LinuxTCPRemoteClient()
{
	this->_sock->closeSock();
	delete this->_sock;
}

int 		LinuxTCPRemoteClient::getWriteFd() const
{
	return (this->_sock->getFd());
}

int			LinuxTCPRemoteClient::getReadFd() const
{
	return (this->_sock->getFd());
}

std::string const 	&LinuxTCPRemoteClient::getIp() const
{
	return (this->_ip);
}

void				LinuxTCPRemoteClient::prepareClose()
{
	this->_closing = true;
}

bool				LinuxTCPRemoteClient::mustBeClosed() const
{
	return (this->_closing);
}

bool 		LinuxTCPRemoteClient::somethingToWrite() const
{
	return (this->_toSendLen != 0);
}

int 		LinuxTCPRemoteClient::receiveMsg(std::string &data)
{
	int		ret;

	ret = this->_sock->receive(data);
	if (ret == -1)
		throw ReceiveException("LinuxTCPRemoteClient: could not receive");
	return (ret);
}

void 		LinuxTCPRemoteClient::prepareMsg(std::string const& msg, int len)
{
	this->_toSend += msg;
	this->_toSendLen += len;
}

int 		LinuxTCPRemoteClient::send()
{
	int 	ret;

	ret = this->_sock->sendData(this->_toSend, this->_toSendLen);
	if (ret == -1)
		throw std::runtime_error("LinuxTCPRemoteClient.send: could not send");
	if (ret != this->_toSendLen)
	{
		this->_toSend = this->_toSend.substr(ret);
		this->_toSendLen -= ret;
	}
	else
	{
		this->_toSend.clear();
		this->_toSendLen = 0;
	}
	return (ret);
}
#endif
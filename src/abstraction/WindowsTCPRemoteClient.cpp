#ifdef _WIN32

#include <exception>
#include <iostream>
#include "ReceiveException.h"
#include "WindowsTCPSocket.h"
#include "WindowsTCPRemoteClient.h"

WindowsTCPRemoteClient::WindowsTCPRemoteClient(struct sockaddr_in &addr, int fd)
{
	this->_closing = false;
	this->_sock = new WindowsTCPSocket(addr, fd);
	if (this->_sock == 0)
		throw std::runtime_error("Could not create a new WindowsTCPSocket");
	this->_ip = inet_ntoa(addr.sin_addr);
	this->_toSendLen = 0;
}

WindowsTCPRemoteClient::~WindowsTCPRemoteClient()
{
	this->_sock->closeSock();
	delete this->_sock;
}

int 		WindowsTCPRemoteClient::getWriteFd() const
{
	return (this->_sock->getFd());
}

int			WindowsTCPRemoteClient::getReadFd() const
{
	return (this->_sock->getFd());
}

std::string const 	&WindowsTCPRemoteClient::getIp() const
{
	return (this->_ip);
}

void				WindowsTCPRemoteClient::prepareClose()
{
	this->_closing = true;
}

bool				WindowsTCPRemoteClient::mustBeClosed() const
{
	return (this->_closing);
}

bool 		WindowsTCPRemoteClient::somethingToWrite() const
{
	return (this->_toSendLen != 0);
}

int 		WindowsTCPRemoteClient::receiveMsg(std::string &data)
{
	int		ret;

	ret = this->_sock->receive(data);
	if (ret == -1)
		throw ReceiveException("WindowsTCPRemoteClient: could not receive");
	return (ret);
}

void 		WindowsTCPRemoteClient::prepareMsg(std::string const &msg, int len)
{
	this->_toSend += msg;
	this->_toSendLen += len;
}

int 		WindowsTCPRemoteClient::send()
{
	int 	ret;

	ret = this->_sock->sendData(this->_toSend, this->_toSendLen);
	if (ret == -1)
		throw std::runtime_error("WindowsTCPRemoteClient.send: could not send");
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
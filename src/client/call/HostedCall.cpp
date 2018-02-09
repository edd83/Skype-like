#include <iostream>
#include <stdexcept>
#include "myMutex.h"
#include "myTimer.h"
#include "HostedCall.h"
#include "Serializer.hpp"
#include "PacketHelper.h"
#include "TCPPacketHeader.h"
#include "ClientWorker.h"
#include "PortAudioSoundManager.h"

HostedCall::HostedCall(ClientWorker &worker, QObject *parent) :
    QObject(parent),
    _worker(worker)
{
    this->_stopping = false;
    this->_stopMutex = new myMutex();
    connect(&this->_tcpServer, SIGNAL(newConnection()), this, SLOT(receiveNewTcpConnection()));
    connect(&this->_tcpServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onAcceptError(QAbstractSocket::SocketError)));

    connect(&this->_udpServer, SIGNAL(readyRead()), this, SLOT(receiveUdp()));
    this->_sManager = new PortAudioSoundManager(this->_container, this);
}

HostedCall::~HostedCall()
{
	disconnect(this);
    delete this->_stopMutex;
    delete this->_sManager;
}

bool        HostedCall::isStopping() const
{
    bool    res;

    this->_stopMutex->lock();
    res = this->_stopping;
    this->_stopMutex->unLock();
    return (res);
}

void        HostedCall::stop()
{
    myTimer timer;
    this->_stopMutex->lock();
    this->_stopping = true;
    this->_stopMutex->unLock();


    while (this->_sManager->isActive())
        timer.run(100);
    std::cout << "Stream stoped" << std::endl;

    for (QMap<int, Callee>::iterator it = this->_connectedUsers.begin(); it != this->_connectedUsers.end(); ++it)
    {
       it->getSock()->close();
	   delete it->getSock();
    }
    this->_tcpServer.close();
}

bool            HostedCall::isHost() const
{
    return (true);
}

QString const   &HostedCall::getUsernameById(int id) const
{
    QMap<int, Callee>::const_iterator it = this->_connectedUsers.find(id);
    return (it->getUsername());
}

void            HostedCall::sendInput()
{
    int             size;
    std::string     packet;
    unsigned char   buff[BUFFER_SIZE];

    size = this->_container.getInput().cpyEncriptedSound(buff, BUFFER_SIZE);
    PacketHelper::writeUdpHeader(packet, 0, size);
    packet = packet.append((char*)buff, size);
    for (QMap<int, Callee>::iterator it = this->_connectedUsers.begin(); it != this->_connectedUsers.end(); ++it)
    {
        if (it.key() != 0)
        {
            size = this->_udpServer.writeDatagram(packet.c_str(), packet.length(), QHostAddress(it->getIp()), DEFAULT_CLIENT_UDP_PORT);
        }
    }
}

void            HostedCall::sendMessage(const QString &msg)
{
    std::string packet;

    std::cout << "Sending msg : " << msg.toStdString() << std::endl;
    PacketHelper::writeTcpHeader(packet, SendText);
    packet = packet.append(Serializer::serialize<int>(0));
    packet = packet.append(Serializer::serialize<std::string>(msg.toStdString()));
    PacketHelper::writeTcpHeaderSize(packet);
    this->broadcastTcpMsg(0, packet);
}

void            HostedCall::start()
{
    if (!this->_tcpServer.listen())
        throw std::runtime_error("Cannot bind TCP server");
    if (!this->_udpServer.bind())
        throw std::runtime_error("Cannot bind UDP server");
    std::cout << "Udp server ready port :" << this->_udpServer.localPort() << std::endl;
    this->_sManager->start();
}

unsigned short  HostedCall::getTcpPort() const
{
    return (this->_tcpServer.serverPort());
}

unsigned short  HostedCall::getUdpPort() const
{
    return (this->_udpServer.localPort());
}

QMap<int, Callee> const &HostedCall::getCallees() const
{
    return (this->_connectedUsers);
}

void            HostedCall::addCallee(const QString &username, const QString &ip)
{
    this->_allowedUser.push_back(Callee(ip, username));
}

void            HostedCall::onReceiveSendTextMsg(int id, const QString &msg)
{
    std::string             packet;

    PacketHelper::writeTcpHeader(packet, SendText);
    packet = packet.append(Serializer::serialize<int>(id));
    packet = packet.append(Serializer::serialize<std::string>(msg.toStdString()));
    PacketHelper::writeTcpHeaderSize(packet);
    this->broadcastTcpMsg(id, packet.c_str());
}

void            HostedCall::receiveNewTcpConnection()
{
    int             id;
    bool            ok = false;
    QTcpSocket      *sock = this->_tcpServer.nextPendingConnection();
    if (sock != 0)
    {
        std::cout << "Receive new tcp connection" << std::endl;
        QString ip = sock->peerAddress().toString();
        QList<Callee>::iterator it = this->_allowedUser.begin();
        for (; it != this->_allowedUser.end(); ++it)
        {
            if (it->getIp() == ip)
            {
                ok = true;
                it->setSock(sock);
                connect(sock, SIGNAL(readyRead()), &this->_worker, SLOT(onReadSomething()));
                connect(sock, SIGNAL(disconnected()), &this->_worker, SLOT(onClientDisconnectedFromCall()));
                connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
                id = this->_connectedUsers.count() + 1;
                this->_container.addProducer(id);
                this->sendWelcome(id, sock);
                this->sendParticipantStatusUpdate(true, id, it->getUsername());
                this->sendUdpReady(sock);
                this->_connectedUsers[id] = Callee(it->getIp(), it->getUsername());
                this->_connectedUsers[id].setSock(sock);
                this->_allowedUser.erase(it);
                break;
            }
        }
        if (!ok)
            sock->close();
    }
}

void            HostedCall::onAcceptError(QAbstractSocket::SocketError)
{
    std::cerr << "HostedCall : Accept client error" << std::endl;
}

bool            HostedCall::removeCallee(QTcpSocket *sock)
{
    for (QMap<int, Callee>::iterator it = this->_connectedUsers.begin(); it != this->_connectedUsers.end(); ++it)
    {
        if (it->getSock() == sock)
        {
            this->sendParticipantStatusUpdate(false, it.key(), it->getUsername());
            this->_connectedUsers.remove(it.key());
            break;
        }
    }
    if (this->_connectedUsers.count() == 0)
        return (true);
    return (false);
}

void            HostedCall::onSocketError(QAbstractSocket::SocketError)
{

}

void            HostedCall::broadcastTcpMsg(int sender, const std::string &msg)
{

    for (QMap<int, Callee>::iterator it = this->_connectedUsers.begin(); it != this->_connectedUsers.end(); ++it)
    {
		if (it.key() != sender)
			it->getSock()->write(msg.c_str(), msg.length());
    }
}

void            HostedCall::receiveUdp()
{
    long int                size;
    QHostAddress            from;
    unsigned short          port;
    long int                current_size;
    char                    buff[BUFFER_SIZE];
    struct UDPPacketHeader  header;

    current_size = 0;
    size = this->_udpServer.readDatagram(buff, BUFFER_SIZE, &from, &port);
    std::istringstream st(std::string(buff, size));
    while ((size - current_size) > sizeof(struct UDPPacketHeader))
    {
        if (PacketHelper::readUdpHeader(st, header) && ((unsigned)size >= current_size +  (sizeof(struct UDPPacketHeader) + header.payloadSize)))
        {
            for (QMap<int, Callee>::iterator it = this->_connectedUsers.begin(); it != this->_connectedUsers.end(); ++it)
            {
                if (it.key() != 0 && it.key() != header.senderID)
                    this->_udpServer.writeDatagram(buff + current_size, header.payloadSize, QHostAddress(it->getIp()), DEFAULT_CLIENT_UDP_PORT);
            }
            this->_container.pushEncriptedOutputSound(header.senderID, (unsigned char*)buff + sizeof(struct UDPPacketHeader), header.payloadSize);
        }
        current_size += (sizeof(struct UDPPacketHeader) + header.payloadSize);
    }
}

void			HostedCall::sendWelcome(int idUser, QTcpSocket *sock)
{
    std::string				packet;
    std::list<std::pair<std::string, char> > listConnectedUsers;

    for (QMap<int, Callee>::iterator it = this->_connectedUsers.begin(); it != this->_connectedUsers.end(); it++)
        listConnectedUsers.push_back(std::pair<std::string, char>(it->getUsername().toStdString(), it.key()));
    PacketHelper::writeTcpHeader(packet, Welcome);
    packet = packet.append(Serializer::serialize<std::list<std::pair<std::string, char> > >(listConnectedUsers));
    packet = packet.append(Serializer::serialize<int>(idUser));
    PacketHelper::writeTcpHeaderSize(packet);
    sock->write(packet.c_str(), packet.length());
}

void			HostedCall::sendParticipantStatusUpdate(bool status, int id, const QString &username)
{
    std::string			packet;

	PacketHelper::writeTcpHeader(packet, ParticipantStatusUpdate);
	if (status == true)
		packet = packet.append(Serializer::serialize<char>(1));
	else
		packet = packet.append(Serializer::serialize<char>(0));
    packet = packet.append(Serializer::serialize<char>(id));
	packet = packet.append(Serializer::serialize<std::string>(username.toStdString()));
	PacketHelper::writeTcpHeaderSize(packet);
    this->broadcastTcpMsg(id, packet);
}

void            HostedCall::sendUdpReady(QTcpSocket *sock)
{
    std::string packet;

    PacketHelper::writeTcpHeader(packet, UDPReady);
    packet = packet.append(Serializer::serialize<int>(this->_udpServer.localPort()));
    PacketHelper::writeTcpHeaderSize(packet);
    sock->write(packet.c_str(), packet.length());
    std::cout << "UDPReady sended" << std::endl;
}

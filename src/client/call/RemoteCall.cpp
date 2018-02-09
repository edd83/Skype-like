#include <sstream>
#include <iostream>
#include "myTimer.h"
#include "myMutex.h"
#include "Serializer.hpp"
#include "PacketHelper.h"
#include "RemoteCall.h"
#include "ClientWorker.h"
#include "UDPPacketHeader.h"
#include "PortAudioSoundManager.h"

RemoteCall::RemoteCall(ClientWorker &worker, QObject *parent) :
    QObject(parent),
    _worker(worker),
	_tcpClient(this),
	_udpClient(this)
{
    this->_stopping = false;
    this->_tcpConnected = false;
    this->_udpConnected = false;
    this->_stopMutex = new myMutex();
    connect(&this->_tcpClient, SIGNAL(connected()), this, SLOT(connectedToHost()));
    connect(&this->_tcpClient, SIGNAL(readyRead()), &this->_worker, SLOT(onReadSomething()));
    connect(&this->_tcpClient, SIGNAL(disconnected()), &this->_worker, SLOT(onClientKickedFromCall()));

    connect(&this->_udpClient, SIGNAL(readyRead()), this, SLOT(receiveUdp()));
    this->_sManager = new PortAudioSoundManager(this->_container, this);
}

RemoteCall::~RemoteCall()
{
	disconnect(this);
    delete this->_stopMutex;
    delete this->_sManager;
}

bool        RemoteCall::isStopping() const
{
    bool    res;

    this->_stopMutex->lock();
    res = this->_stopping;
    this->_stopMutex->unLock();
    return (res);
}

void        RemoteCall::stop()
{
    myTimer timer;

    this->_stopMutex->lock();
    this->_stopping = true;
    this->_stopMutex->unLock();


    while (this->_sManager->isActive())
        timer.run(100);
    std::cout << "Stream stoped" << std::endl;

	disconnect(&this->_tcpClient, SIGNAL(connected()));
	disconnect(&this->_tcpClient, SIGNAL(readyRead()));
	disconnect(&this->_tcpClient, SIGNAL(disconnected()));

	this->_udpClient.disconnect(SIGNAL(readyRead()));

	this->_tcpClient.close();
	this->_udpClient.close();
}

bool        RemoteCall::isHost() const
{
    return (false);
}

QString const   &RemoteCall::getUsernameById(int id) const
{
    QMap<int, QString>::const_iterator it = this->_connectedUsers.find(id);
    return (*it);
}

void            RemoteCall::sendInput()
{
    int             size;
    std::string     packet;
    unsigned char   buff[BUFFER_SIZE];

    size = this->_container.getInput().cpyEncriptedSound(buff, BUFFER_SIZE);
    PacketHelper::writeUdpHeader(packet, this->_myId, size);
    packet = packet.append((char*)buff, size);
    size = this->_udpClient.writeDatagram(packet.c_str(), packet.length(), QHostAddress(this->_ip), this->_udpPort);
}

void            RemoteCall::sendMessage(const QString &msg)
{
    std::string packet;

    PacketHelper::writeTcpHeader(packet, SendText);
    packet = packet.append(Serializer::serialize<int>(this->_myId));
    packet = packet.append(Serializer::serialize<std::string>(msg.toStdString()));
    PacketHelper::writeTcpHeaderSize(packet);
    this->_tcpClient.write(packet.c_str(), packet.length());
}

void            RemoteCall::start(const QString &ip, unsigned short port)
{
    this->_ip = ip;
    this->_tcpClient.connectToHost(ip, port);
}

void            RemoteCall::setMyId(unsigned int id)
{
    this->_myId = id;
}

void            RemoteCall::addCallee(const QString &name, unsigned int id)
{
    this->_connectedUsers[id] = name;
    this->_container.addProducer(id);
}

void            RemoteCall::removeCallee(unsigned int id)
{
    this->_connectedUsers.remove(id);
    this->_container.removeProducer(id);
}

void            RemoteCall::onReceiveUDPReady(unsigned short port)
{
    this->_udpPort = port;
    if (this->_udpClient.bind(DEFAULT_CLIENT_UDP_PORT))
        std::cout << "UDP Client binded" << std::endl;
    this->_sManager->start();
}

void            RemoteCall::connectedToHost()
{
    this->_tcpConnected = true;
    std::cout << "Connected to peer !!" << std::endl;
}

void            RemoteCall::receiveUdp()
{
    long int                size;
    QHostAddress            from;
    unsigned short          port;
    long int                current_size;
    char                    buff[BUFFER_SIZE];
    struct UDPPacketHeader  header;

    current_size = 0;
    size = this->_udpClient.readDatagram(buff, BUFFER_SIZE, &from, &port);
    std::string tmp(buff, size);
    std::istringstream st(tmp);
    while ((size - current_size) > sizeof(struct UDPPacketHeader))
    {
        if (PacketHelper::readUdpHeader(st, header) && ((unsigned)size >= current_size +  (sizeof(struct UDPPacketHeader) + header.payloadSize)))
            this->_container.pushEncriptedOutputSound(header.senderID, (unsigned char*)buff + sizeof(struct UDPPacketHeader), header.payloadSize);
        current_size += (sizeof(struct UDPPacketHeader) + header.payloadSize);
    }
}




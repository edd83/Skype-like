#pragma once

#include <QTcpServer>
#include <QUdpSocket>
#include <QObject>
#include "IMutex.h"
#include "ICall.h"
#include "Callee.h"
#include "eCalleeStatus.h"
#include "ISoundManager.h"
#include "SoundMixer.h"
#include "SoundContainer.h"

class ClientWorker;

class HostedCall : public QObject, public ICall
{
    Q_OBJECT
public:
    explicit    HostedCall(ClientWorker &, QObject *parent = 0);
    virtual     ~HostedCall();

    virtual bool    isStopping() const;
    virtual void    stop();
    virtual bool    isHost() const;
    virtual QString const   &getUsernameById(int) const;
    virtual void    sendInput();
    virtual void    sendMessage(QString const &);

    void            start();
    unsigned short  getTcpPort() const;
    unsigned short  getUdpPort() const;

    QMap<int, Callee> const &getCallees() const;
    void                    addCallee(QString const &username, QString const &ip);
    bool                    removeCallee(QTcpSocket *);
    void                    onReceiveSendTextMsg(int, QString const &);
    void					sendWelcome(int, QTcpSocket *);
    void					sendParticipantStatusUpdate(bool, int, const QString &);
    void                    sendUdpReady(QTcpSocket *);

signals:

public slots:

private slots:
    void        receiveNewTcpConnection();       
    void        onAcceptError(QAbstractSocket::SocketError);
    void        onSocketError(QAbstractSocket::SocketError);


    void        receiveUdp();

private:
    void        broadcastTcpMsg(int, std::string const &);

    IMutex              *_stopMutex;
    bool                _stopping;

    QTcpServer          _tcpServer;
    QUdpSocket          _udpServer;
    QList<Callee>       _allowedUser;
    QMap<int, Callee>   _connectedUsers;
    ClientWorker        &_worker;

    ISoundManager       *_sManager;
    SoundContainer      _container;
};

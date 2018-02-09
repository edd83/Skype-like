#pragma once
#include <QString>

class       ICall
{
public:
    virtual ~ICall() {}

    virtual bool isStopping() const = 0;
    virtual void stop() = 0;
    virtual bool isHost() const = 0;

    virtual QString const   &getUsernameById(int) const = 0;
    virtual void            sendInput() = 0;
    virtual void            sendMessage(QString const &) = 0;
};

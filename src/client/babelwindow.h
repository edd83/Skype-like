#ifndef BABELWINDOW_H
#define BABELWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QtGui>
#include <QVBoxLayout>
#include <iostream>
#include <QThread>
#include "ChatDialog.h"
#include "ClientData.h"
#include "ClientWorker.h"

namespace Ui {
class BabelWindow;
}

class BabelWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BabelWindow(QWidget *parent = 0);
    ~BabelWindow();
    void    displayList();
    void    sendChatBox(QString const &);
    void    switchImage();
    bool	registerServer(std::string, std::string);

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

private slots:

    void onConnectionSuccess();
    void onConnectionFailed();
    void onCommandFailed(eErrorCode);

    void onUpdateListFriend();
    void onFriendRequest(QString);
    void onCallDropped(QString);
    void onCallRequest(QString const &, std::list<std::string> const &);
    void onJoinCall(QString const &);
    void onLeaveCall(QString const &);
    void onSendText(QString const &, QString const &);

    void onEnterInCall();
    void onLeaveCall();

    void on_pushButton_seconnecter_clicked();

	void on_pushButton_registration_clicked();

	void on_pushButton_register_clicked();

    void on_btn_swap_signin_clicked();

    void on_pushButton_HangUp_clicked();

    void on_pushButton_call_clicked();

    void on_pushButton_manageFriend_clicked();

    void on_pushButton_Disconnection_clicked();

    void on_pushButton_chatbox_clicked();

signals:
    void onSignInRequest();
    void onSignUpRequest();
    void onAddFriend(QString);
    void onRemoveFriend(QString);
    void answerFriendRequest(QString, bool);
    void answerRequestCall(const QString &, bool);
    void addToCallRequest(QString);
    void sendMsg(QString const &);
    void onHangUp();
    void onLogoutRequest();
private:
    Ui::BabelWindow *ui;
    QString         tmp;
    QString         _tmpCall;
    bool            _chat;

    QThread         _workerThread;
    ClientData      _data;
    ChatDialog      _myBox;
    ClientWorker    *_worker;
};

#endif // BABELWINDOW_H

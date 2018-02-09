#include <QtPrintSupport/QPrinter>
#include <list>
#include <iostream>
#include <QMessageBox>
#include <QBrush>
#include <QInputDialog>
#include "babelwindow.h"
#include "ui_babelwindow.h"
#include "eFriendStatus.h"

BabelWindow::BabelWindow(QWidget *parent) :
    QMainWindow(parent),
    _myBox(*this),
    ui(new Ui::BabelWindow)
{
    ui->setupUi(this);
    this->_chat = false;
    this->ui->stackedWidget->setCurrentIndex(0);
    this->_myBox.hide();
    this->ui->pushButton_chatbox->setEnabled(false);
    this->setFixedSize(220, 370);
	this->ui->lineEdit_password->setEchoMode(QLineEdit::Password);
	this->ui->lineEdit_passwordregister->setEchoMode(QLineEdit::Password);
	this->ui->lineEdit_passwordconfirmregister->setEchoMode(QLineEdit::Password);
    this->setWindowIcon(QIcon(":/images/images/dark_souls_icon.png"));
}

BabelWindow::~BabelWindow()
{
    delete ui;
}

void    BabelWindow::closeEvent(QCloseEvent *)
{
    this->_workerThread.exit(0);
    this->_workerThread.wait();
}

void    BabelWindow::showEvent(QShowEvent *)
{
    this->_worker = new ClientWorker(this->_data, &this->_workerThread);
    this->_worker->moveToThread(&this->_workerThread);
    connect(this, SIGNAL(onSignInRequest()), this->_worker, SLOT(onSignInRequest()));
    connect(this, SIGNAL(onSignUpRequest()), this->_worker, SLOT(onSignUpRequest()));
    connect(this, SIGNAL(onAddFriend(QString)), this->_worker, SLOT(addFriendRequest(QString)));
    connect(this, SIGNAL(onRemoveFriend(QString)), this->_worker, SLOT(deleteFriendRequest(QString)));
    connect(this, SIGNAL(answerFriendRequest(QString,bool)), this->_worker, SLOT(friendValidationRequest(QString,bool)));
    connect(this, SIGNAL(answerRequestCall(QString,bool)), this->_worker, SLOT(answerCallRequest(QString,bool)));
    connect(this, SIGNAL(addToCallRequest(QString)), this->_worker, SLOT(addToCallRequest(QString)));
    connect(this, SIGNAL(onHangUp()), this->_worker, SLOT(onHangUp()));
    connect(this, SIGNAL(sendMsg(QString)), this->_worker, SLOT(onSendText(QString)));
    connect(this, SIGNAL(onLogoutRequest()), this->_worker, SLOT(logoutRequest()));

    connect(this->_worker, SIGNAL(connectedToServer()), this, SLOT(onConnectionSuccess()));
    connect(this->_worker, SIGNAL(friendStatusUpdate()), this, SLOT(onUpdateListFriend()));
    connect(this->_worker, SIGNAL(connectionFailed()), this, SLOT(onConnectionFailed()));
    connect(this->_worker, SIGNAL(commandFailed(eErrorCode)), this, SLOT(onCommandFailed(eErrorCode)));
    connect(this->_worker, SIGNAL(friendRequest(QString)), this, SLOT(onFriendRequest(QString)));
    connect(this->_worker, SIGNAL(addInCall(QString)), this, SLOT(onJoinCall(QString)));
    connect(this->_worker, SIGNAL(leftCall(QString)), this, SLOT(onLeaveCall(QString)));
    connect(this->_worker, SIGNAL(callDropped(QString)), this, SLOT(onCallDropped(QString)));
    connect(this->_worker, SIGNAL(callRequest(QString, std::list<std::string>)), this, SLOT(onCallRequest(QString, std::list<std::string>)));
    connect(this->_worker, SIGNAL(sendText(QString,QString)), this, SLOT(onSendText(QString,QString)));
    connect(this->_worker, SIGNAL(leaveCall()), this, SLOT(onLeaveCall()));
    connect(this->_worker, SIGNAL(enterInCall()), this, SLOT(onEnterInCall()));

    this->_workerThread.start();
}

void    BabelWindow::sendChatBox(const QString &message)
{
    emit this->sendMsg(message);
}

void    BabelWindow::switchImage()
{
    this->ui->pushButton_chatbox->setChecked(false);
}

//-------------------------Notifications--------------------------------//
void    BabelWindow::onConnectionSuccess()
{
    this->onUpdateListFriend();
    this->ui->stackedWidget->setCurrentIndex(2);
    this->ui->statusBar->showMessage("Connected", 2000);
    this->setWindowTitle(this->_data.getUser().getName());
}

void    BabelWindow::onUpdateListFriend()
{
    this->_data.lockUser();
    this->ui->listConnected->clear();
    std::list<Friend> const &myList = this->_data.getUser().getFriendList();
    for (std::list<Friend>::const_iterator it = myList.begin(); it != myList.end(); ++it)
    {
        if (it->getStatus() == Offline)
        {
            this->ui->listConnected->addItem(it->getName());
            this->ui->listConnected->item(this->ui->listConnected->count() - 1)->setForeground(Qt::red);
        }
        else if (it->getStatus() == FriendRequestPending)
            this->onFriendRequest(it->getName());
        else
        {
            this->ui->listConnected->addItem(it->getName());
            this->ui->listConnected->item(this->ui->listConnected->count() - 1)->setForeground(QBrush(QColor(0, 128, 0)));
        }
    }
    this->ui->listConnected->sortItems(Qt::AscendingOrder);
    this->_data.unlockUser();
}

void    BabelWindow::onConnectionFailed()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText("Unable to connect to the server ...");
    msgBox.exec();
    this->ui->statusBar->clearMessage();
    this->ui->pushButton_seconnecter->setEnabled(true);
    this->ui->pushButton_registration->setEnabled(true);
    this->ui->pushButton_register->setEnabled(true);
    this->ui->btn_swap_signin->setEnabled(true);
}

void    BabelWindow::onFriendRequest(QString name)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Friend request");
    msgBox.setText(name + " want to be your friend. Do you agree ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes)
        emit this->answerFriendRequest(name, true);
    else
        emit this->answerFriendRequest(name, false);
}

void    BabelWindow::onJoinCall(const QString &username)
{
    this->_myBox.writeMsg(username + " has join the call.");
}

void    BabelWindow::onLeaveCall(const QString &username)
{
    this->_myBox.writeMsg(username +" has left the call.");
}

void    BabelWindow::onSendText(const QString &usr, const QString &msg)
{
    this->_myBox.writeMsg(usr + " : " + msg);
    if (this->ui->pushButton_chatbox->isChecked() == false)
        this->ui->pushButton_chatbox->click();
}

void    BabelWindow::onCommandFailed(eErrorCode err)
{
    QMap<eErrorCode, QString> strErr;
    strErr[InvalidUsername] = "SignIn failure : Invalid username";
    strErr[InvalidPassword] = "SignIn failure : Invalid password";
    strErr[UnavailableUsername] = "SignUp failure : Username unavailable";
    strErr[UnknownUser] = "Unknown user";
    strErr[UserAlreadyConnected] = "SignIn failure : User already connected";
    strErr[AlreadyFriend] = "Friend requested failure : Already friend";
    strErr[FriendsMaxedOut] = "Friend requested failure : Too much friends";
    strErr[UserOffline] = "User is offline";
    strErr[RequestPending] = "Friend requested failure : Friend request pending";
    strErr[AuthentificationTimeOut] = "SignIn failure : Authentification timed out";
    strErr[InvalidCredentials] = "SignIn failure : Invalid credentials";

    QMessageBox msgBox;
    msgBox.setText(strErr[err]);
    msgBox.exec();

    if (err == InvalidUsername || err == InvalidPassword || err == UserAlreadyConnected
            || err == UnavailableUsername || err == AuthentificationTimeOut || err == InvalidCredentials)
    {
        this->ui->statusBar->clearMessage();
        this->ui->pushButton_seconnecter->setEnabled(true);
        this->ui->pushButton_registration->setEnabled(true);
        this->ui->pushButton_register->setEnabled(true);
        this->ui->btn_swap_signin->setEnabled(true);
    }
}

void    BabelWindow::onCallRequest(const QString &name, std::list<std::string> const &)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Call request !");
    msgBox.setText(name + " want to call you.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes)
        emit this->answerRequestCall(name, true);
    else
        emit this->answerRequestCall(name, false);
}

void    BabelWindow::onCallDropped(QString name)
{
    onUpdateListFriend();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText(name + " don't want to speak with you");
    msgBox.exec();
}

void    BabelWindow::onLeaveCall()
{
    this->_myBox.hide();
    this->ui->pushButton_call->setEnabled(true);
    this->ui->pushButton_HangUp->setEnabled(false);
    this->ui->pushButton_chatbox->setEnabled(false);
}

void    BabelWindow::onEnterInCall()
{
    this->ui->pushButton_call->setEnabled(false);
    this->ui->pushButton_HangUp->setEnabled(true);
    this->ui->pushButton_chatbox->setEnabled(true);
}

//------------------------------------------------------------------------------------//


//-------------------------- Graphic events ------------------------------------------//

void    BabelWindow::on_pushButton_registration_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}

void    BabelWindow::on_pushButton_register_clicked()
{
    if (!this->ui->txt_signUpIp->text().isEmpty() &&
        this->ui->lineEdit_pseudoregister->text().toStdString() != "" &&
		this->ui->lineEdit_passwordregister->text().toStdString() != "" &&
		this->ui->lineEdit_passwordconfirmregister->text().toStdString() != "" &&
        this->ui->lineEdit_passwordregister->text().toStdString() == this->ui->lineEdit_passwordconfirmregister->text().toStdString())
	{
        this->_data.lockUser();
        User &user = this->_data.getUser();
        user.setIdent(this->ui->lineEdit_pseudoregister->text(), this->ui->lineEdit_passwordregister->text());
        this->_data.unlockUser();
        this->_data.lockServer();
        this->_data.setServerIp(this->ui->txt_signUpIp->text());
        this->_data.unlockServer();
        emit this->onSignUpRequest();
        this->ui->statusBar->showMessage("Connecting ...", 0);
        this->ui->pushButton_register->setEnabled(false);
        this->ui->btn_swap_signin->setEnabled(false);
        this->ui->btn_swap_signin->setEnabled(false);
        this->ui->pushButton_register->setEnabled(false);
    }
}

void    BabelWindow::on_pushButton_seconnecter_clicked()
{
    if (this->ui->lineEdit_pseudo->text().toStdString() != "" &&
            this->ui->lineEdit_password->text().toStdString() != "" &&
            this->ui->lineEdit_ip->text().toStdString() != "")
    {
        this->_data.lockUser();
        User &user = this->_data.getUser();
        user.setIdent(this->ui->lineEdit_pseudo->text(), this->ui->lineEdit_password->text());
        this->_data.unlockUser();
        this->_data.lockServer();
        this->_data.setServerIp(this->ui->lineEdit_ip->text());
        this->_data.unlockServer();
        emit this->onSignInRequest();
        this->ui->pushButton_seconnecter->setEnabled(false);
        this->ui->pushButton_registration->setEnabled(false);
        this->ui->btn_swap_signin->setEnabled(false);
        this->ui->pushButton_register->setEnabled(false);
        this->ui->statusBar->showMessage("Connecting ...", 0);
    }
    else
		this->ui->statusBar->showMessage("Error identifier, try again", 5000);
}

void    BabelWindow::on_btn_swap_signin_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void    BabelWindow::on_pushButton_HangUp_clicked()
{
    emit this->onHangUp();
}

void    BabelWindow::on_pushButton_call_clicked()
{
    if (this->ui->listConnected->selectedItems().count() != 0)
        emit this->addToCallRequest(this->ui->listConnected->currentItem()->text());
    else
        this->ui->statusBar->showMessage("Select a friend please.", 3000);
}

void    BabelWindow::on_pushButton_manageFriend_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Manage friends"),
                                        tr("User name:"), QLineEdit::Normal,
                                        QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        emit this->onAddFriend(text);
}

void    BabelWindow::on_pushButton_Disconnection_clicked()
{
    emit this->onLogoutRequest();
    this->ui->stackedWidget->show();
    this->ui->stackedWidget->setCurrentIndex(0);
    this->ui->pushButton_seconnecter->setEnabled(true);
    this->ui->pushButton_registration->setEnabled(true);
    this->ui->btn_swap_signin->setEnabled(true);
    this->ui->pushButton_register->setEnabled(true);
    this->setWindowTitle("Babel");
    this->setFixedSize(220, 350);
}

void BabelWindow::on_pushButton_chatbox_clicked()
{
    if (this->ui->pushButton_chatbox->isChecked())
        this->_myBox.show();
    else
        this->_myBox.hide();
}

#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include "babelwindow.h"

ChatDialog::ChatDialog(BabelWindow &main, QWidget *parent) :
    QDialog(parent),
    _main(main),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void    ChatDialog::closeEvent(QCloseEvent *)
{
    this->_main.switchImage();
}

void ChatDialog::on_btn_send_clicked()
{
    if (this->ui->txt_send->text() != "")
    {
        this->ui->txt_chat->append("Me : " + this->ui->txt_send->text());
        this->_main.sendChatBox(this->ui->txt_send->text());
        this->ui->txt_send->clear();
    }
    QTextCursor c = this->ui->txt_chat->textCursor();
    c.movePosition(QTextCursor::End);
    this->ui->txt_chat->setTextCursor(c);
}

void        ChatDialog::writeMsg(const QString &msg)
{
    this->ui->txt_chat->append(msg);
}

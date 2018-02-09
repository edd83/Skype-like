/********************************************************************************
** Form generated from reading UI file 'ChatDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *txt_send;
    QPushButton *btn_send;
    QTextEdit *txt_chat;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName(QStringLiteral("ChatDialog"));
        ChatDialog->resize(305, 201);
        gridLayout = new QGridLayout(ChatDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        txt_send = new QLineEdit(ChatDialog);
        txt_send->setObjectName(QStringLiteral("txt_send"));

        gridLayout->addWidget(txt_send, 1, 0, 1, 1);

        btn_send = new QPushButton(ChatDialog);
        btn_send->setObjectName(QStringLiteral("btn_send"));

        gridLayout->addWidget(btn_send, 1, 1, 1, 1);

        txt_chat = new QTextEdit(ChatDialog);
        txt_chat->setObjectName(QStringLiteral("txt_chat"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        txt_chat->setFont(font);

        gridLayout->addWidget(txt_chat, 0, 0, 1, 2);


        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QApplication::translate("ChatDialog", "Chatbox", 0));
        btn_send->setText(QApplication::translate("ChatDialog", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H

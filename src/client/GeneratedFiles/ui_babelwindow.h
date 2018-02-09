/********************************************************************************
** Form generated from reading UI file 'babelwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BABELWINDOW_H
#define UI_BABELWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BabelWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QLabel *label_password;
    QPushButton *pushButton_seconnecter;
    QLabel *label_4;
    QLabel *label_pseudo;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_registration;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_pseudo;
    QLabel *label_ip_2;
    QWidget *page_3;
    QGridLayout *gridLayout_2;
    QPushButton *btn_swap_signin;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *pushButton_register;
    QLineEdit *lineEdit_passwordconfirmregister;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_pseudoregister;
    QLineEdit *lineEdit_passwordregister;
    QLabel *label_6;
    QLineEdit *txt_signUpIp;
    QWidget *page_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_call;
    QPushButton *pushButton_manageFriend;
    QPushButton *pushButton_HangUp;
    QListWidget *listConnected;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Disconnection;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_chatbox;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BabelWindow)
    {
        if (BabelWindow->objectName().isEmpty())
            BabelWindow->setObjectName(QStringLiteral("BabelWindow"));
        BabelWindow->resize(430, 406);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(39, 170, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(147, 218, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(93, 194, 247, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(19, 85, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(26, 113, 160, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(147, 212, 247, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        BabelWindow->setPalette(palette);
        BabelWindow->setAnimated(true);
        centralWidget = new QWidget(BabelWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setMaximumSize(QSize(200, 320));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_password = new QLabel(page);
        label_password->setObjectName(QStringLiteral("label_password"));

        gridLayout->addWidget(label_password, 4, 0, 1, 1);

        pushButton_seconnecter = new QPushButton(page);
        pushButton_seconnecter->setObjectName(QStringLiteral("pushButton_seconnecter"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_seconnecter->setFont(font);

        gridLayout->addWidget(pushButton_seconnecter, 6, 1, 1, 1);

        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(16777215, 50));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 2);

        label_pseudo = new QLabel(page);
        label_pseudo->setObjectName(QStringLiteral("label_pseudo"));

        gridLayout->addWidget(label_pseudo, 3, 0, 1, 1);

        lineEdit_password = new QLineEdit(page);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));

        gridLayout->addWidget(lineEdit_password, 4, 1, 1, 1);

        pushButton_registration = new QPushButton(page);
        pushButton_registration->setObjectName(QStringLiteral("pushButton_registration"));

        gridLayout->addWidget(pushButton_registration, 6, 0, 1, 1);

        lineEdit_ip = new QLineEdit(page);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 2, 1, 1, 1);

        lineEdit_pseudo = new QLineEdit(page);
        lineEdit_pseudo->setObjectName(QStringLiteral("lineEdit_pseudo"));

        gridLayout->addWidget(lineEdit_pseudo, 3, 1, 1, 1);

        label_ip_2 = new QLabel(page);
        label_ip_2->setObjectName(QStringLiteral("label_ip_2"));

        gridLayout->addWidget(label_ip_2, 2, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        gridLayout_2 = new QGridLayout(page_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        btn_swap_signin = new QPushButton(page_3);
        btn_swap_signin->setObjectName(QStringLiteral("btn_swap_signin"));

        gridLayout_2->addWidget(btn_swap_signin, 9, 0, 1, 1);

        label_5 = new QLabel(page_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(16777215, 50));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 1, 0, 1, 3);

        label_3 = new QLabel(page_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 5, 0, 1, 1);

        pushButton_register = new QPushButton(page_3);
        pushButton_register->setObjectName(QStringLiteral("pushButton_register"));
        pushButton_register->setFont(font);

        gridLayout_2->addWidget(pushButton_register, 9, 1, 1, 2);

        lineEdit_passwordconfirmregister = new QLineEdit(page_3);
        lineEdit_passwordconfirmregister->setObjectName(QStringLiteral("lineEdit_passwordconfirmregister"));

        gridLayout_2->addWidget(lineEdit_passwordconfirmregister, 5, 2, 1, 1);

        label = new QLabel(page_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 3, 0, 1, 2);

        label_2 = new QLabel(page_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 4, 0, 1, 1);

        lineEdit_pseudoregister = new QLineEdit(page_3);
        lineEdit_pseudoregister->setObjectName(QStringLiteral("lineEdit_pseudoregister"));

        gridLayout_2->addWidget(lineEdit_pseudoregister, 3, 2, 1, 1);

        lineEdit_passwordregister = new QLineEdit(page_3);
        lineEdit_passwordregister->setObjectName(QStringLiteral("lineEdit_passwordregister"));

        gridLayout_2->addWidget(lineEdit_passwordregister, 4, 2, 1, 1);

        label_6 = new QLabel(page_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        txt_signUpIp = new QLineEdit(page_3);
        txt_signUpIp->setObjectName(QStringLiteral("txt_signUpIp"));

        gridLayout_2->addWidget(txt_signUpIp, 2, 2, 1, 1);

        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        layoutWidget = new QWidget(page_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 20, 201, 302));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_call = new QPushButton(layoutWidget);
        pushButton_call->setObjectName(QStringLiteral("pushButton_call"));
        pushButton_call->setEnabled(true);
        pushButton_call->setMinimumSize(QSize(73, 56));
        pushButton_call->setMaximumSize(QSize(100, 100));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/call.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_call->setIcon(icon);
        pushButton_call->setIconSize(QSize(40, 40));
        pushButton_call->setFlat(true);

        horizontalLayout->addWidget(pushButton_call);

        pushButton_manageFriend = new QPushButton(layoutWidget);
        pushButton_manageFriend->setObjectName(QStringLiteral("pushButton_manageFriend"));
        pushButton_manageFriend->setEnabled(true);
        pushButton_manageFriend->setMinimumSize(QSize(40, 40));
        pushButton_manageFriend->setMaximumSize(QSize(40, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/add_friend.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_manageFriend->setIcon(icon1);
        pushButton_manageFriend->setIconSize(QSize(40, 40));
        pushButton_manageFriend->setFlat(true);

        horizontalLayout->addWidget(pushButton_manageFriend);

        pushButton_HangUp = new QPushButton(layoutWidget);
        pushButton_HangUp->setObjectName(QStringLiteral("pushButton_HangUp"));
        pushButton_HangUp->setEnabled(false);
        pushButton_HangUp->setMinimumSize(QSize(72, 56));
        pushButton_HangUp->setMaximumSize(QSize(72, 56));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/images/uncall.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_HangUp->setIcon(icon2);
        pushButton_HangUp->setIconSize(QSize(40, 40));
        pushButton_HangUp->setFlat(true);

        horizontalLayout->addWidget(pushButton_HangUp);


        verticalLayout_2->addLayout(horizontalLayout);

        listConnected = new QListWidget(layoutWidget);
        listConnected->setObjectName(QStringLiteral("listConnected"));
        listConnected->setMinimumSize(QSize(190, 150));
        listConnected->setMaximumSize(QSize(190, 150));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        listConnected->setPalette(palette1);
        listConnected->setFont(font);

        verticalLayout_2->addWidget(listConnected, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButton_Disconnection = new QPushButton(layoutWidget);
        pushButton_Disconnection->setObjectName(QStringLiteral("pushButton_Disconnection"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_Disconnection->sizePolicy().hasHeightForWidth());
        pushButton_Disconnection->setSizePolicy(sizePolicy);
        pushButton_Disconnection->setMinimumSize(QSize(50, 50));
        pushButton_Disconnection->setMaximumSize(QSize(50, 50));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/images/LogoutButton.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Disconnection->setIcon(icon3);
        pushButton_Disconnection->setIconSize(QSize(200, 50));
        pushButton_Disconnection->setAutoDefault(false);
        pushButton_Disconnection->setDefault(false);
        pushButton_Disconnection->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_Disconnection);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_chatbox = new QPushButton(layoutWidget);
        pushButton_chatbox->setObjectName(QStringLiteral("pushButton_chatbox"));
        pushButton_chatbox->setEnabled(false);
        pushButton_chatbox->setMinimumSize(QSize(50, 20));
        pushButton_chatbox->setMaximumSize(QSize(32, 32));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/images/chatbox.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_chatbox->setIcon(icon4);
        pushButton_chatbox->setIconSize(QSize(32, 32));
        pushButton_chatbox->setCheckable(true);
        pushButton_chatbox->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_chatbox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(page_2);

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);

        BabelWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BabelWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 430, 21));
        BabelWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(BabelWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BabelWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(lineEdit_ip, lineEdit_pseudo);
        QWidget::setTabOrder(lineEdit_pseudo, lineEdit_password);
        QWidget::setTabOrder(lineEdit_password, pushButton_registration);
        QWidget::setTabOrder(pushButton_registration, pushButton_seconnecter);
        QWidget::setTabOrder(pushButton_seconnecter, txt_signUpIp);
        QWidget::setTabOrder(txt_signUpIp, lineEdit_pseudoregister);
        QWidget::setTabOrder(lineEdit_pseudoregister, lineEdit_passwordregister);
        QWidget::setTabOrder(lineEdit_passwordregister, lineEdit_passwordconfirmregister);
        QWidget::setTabOrder(lineEdit_passwordconfirmregister, btn_swap_signin);
        QWidget::setTabOrder(btn_swap_signin, pushButton_register);
        QWidget::setTabOrder(pushButton_register, pushButton_call);
        QWidget::setTabOrder(pushButton_call, pushButton_manageFriend);
        QWidget::setTabOrder(pushButton_manageFriend, pushButton_HangUp);
        QWidget::setTabOrder(pushButton_HangUp, listConnected);
        QWidget::setTabOrder(listConnected, pushButton_Disconnection);

        retranslateUi(BabelWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(BabelWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BabelWindow)
    {
        BabelWindow->setWindowTitle(QApplication::translate("BabelWindow", "Babel", 0));
        label_password->setText(QApplication::translate("BabelWindow", "Password :", 0));
        pushButton_seconnecter->setText(QApplication::translate("BabelWindow", "SignIn", 0));
        label_4->setText(QApplication::translate("BabelWindow", "SignIn", 0));
        label_pseudo->setText(QApplication::translate("BabelWindow", "Pseudo :", 0));
        lineEdit_password->setText(QApplication::translate("BabelWindow", "eddy", 0));
        pushButton_registration->setText(QApplication::translate("BabelWindow", "SignUp", 0));
        lineEdit_ip->setText(QApplication::translate("BabelWindow", "10.20.86.128", 0));
        lineEdit_pseudo->setText(QApplication::translate("BabelWindow", "eddy", 0));
        label_ip_2->setText(QApplication::translate("BabelWindow", "IP :", 0));
        btn_swap_signin->setText(QApplication::translate("BabelWindow", "SignIn", 0));
        label_5->setText(QApplication::translate("BabelWindow", "SignUp", 0));
        label_3->setText(QApplication::translate("BabelWindow", "Confirm password :", 0));
        pushButton_register->setText(QApplication::translate("BabelWindow", "SignUp", 0));
        label->setText(QApplication::translate("BabelWindow", "Pseudo : ", 0));
        label_2->setText(QApplication::translate("BabelWindow", "Password :", 0));
        label_6->setText(QApplication::translate("BabelWindow", "Server ip :", 0));
        pushButton_call->setText(QString());
        pushButton_manageFriend->setText(QString());
        pushButton_HangUp->setText(QString());
        pushButton_Disconnection->setText(QString());
        pushButton_chatbox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BabelWindow: public Ui_BabelWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BABELWINDOW_H

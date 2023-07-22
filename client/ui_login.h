/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *label;
    QTextEdit *TPORT;
    QLabel *label_2;
    QTextEdit *TIP;
    QLabel *label_3;
    QTextEdit *TNAME;
    QPushButton *pushButton;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(400, 300);
        label = new QLabel(login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 100, 67, 17));
        TPORT = new QTextEdit(login);
        TPORT->setObjectName(QString::fromUtf8("TPORT"));
        TPORT->setGeometry(QRect(130, 90, 161, 41));
        label_2 = new QLabel(login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 20, 67, 17));
        TIP = new QTextEdit(login);
        TIP->setObjectName(QString::fromUtf8("TIP"));
        TIP->setGeometry(QRect(130, 10, 161, 41));
        label_3 = new QLabel(login);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 180, 67, 17));
        TNAME = new QTextEdit(login);
        TNAME->setObjectName(QString::fromUtf8("TNAME"));
        TNAME->setGeometry(QRect(130, 170, 161, 41));
        pushButton = new QPushButton(login);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 230, 89, 25));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("login", "\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("login", "\345\234\260\345\235\200", nullptr));
        label_3->setText(QCoreApplication::translate("login", "\345\220\215\347\247\260", nullptr));
        pushButton->setText(QCoreApplication::translate("login", "\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

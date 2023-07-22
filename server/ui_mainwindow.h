/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;
    QLabel *info;
    QTextEdit *tport;
    QLabel *label;
    QListWidget *tankName;
    QLabel *label_2;
    QPushButton *pbBattle;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pbBattle_2;
    QListWidget *sinfo;
    QLabel *label_3;
    QPushButton *pushButton_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(310, 60, 89, 25));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(100, 300, 89, 25));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(60, 220, 201, 70));
        info = new QLabel(centralWidget);
        info->setObjectName(QString::fromUtf8("info"));
        info->setGeometry(QRect(40, 20, 311, 17));
        tport = new QTextEdit(centralWidget);
        tport->setObjectName(QString::fromUtf8("tport"));
        tport->setGeometry(QRect(160, 60, 101, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 70, 67, 17));
        tankName = new QListWidget(centralWidget);
        tankName->setObjectName(QString::fromUtf8("tankName"));
        tankName->setGeometry(QRect(490, 30, 256, 192));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(490, 10, 67, 17));
        pbBattle = new QPushButton(centralWidget);
        pbBattle->setObjectName(QString::fromUtf8("pbBattle"));
        pbBattle->setGeometry(QRect(60, 140, 89, 25));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(500, 240, 89, 25));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(630, 240, 89, 25));
        pbBattle_2 = new QPushButton(centralWidget);
        pbBattle_2->setObjectName(QString::fromUtf8("pbBattle_2"));
        pbBattle_2->setGeometry(QRect(180, 140, 89, 25));
        sinfo = new QListWidget(centralWidget);
        sinfo->setObjectName(QString::fromUtf8("sinfo"));
        sinfo->setGeometry(QRect(470, 270, 261, 131));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(390, 290, 67, 17));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(370, 320, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\347\276\244\345\217\221\346\266\210\346\201\257", nullptr));
        info->setText(QCoreApplication::translate("MainWindow", "\346\227\240\346\266\210\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\235\246\345\205\213\345\210\227\350\241\250", nullptr));
        pbBattle->setText(QCoreApplication::translate("MainWindow", "\345\274\200\346\210\230\345\221\275\344\273\244", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\224\237", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\255\273\344\272\241", nullptr));
        pbBattle_2->setText(QCoreApplication::translate("MainWindow", "\346\210\230\346\226\227\346\232\202\345\201\234", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\266\210\346\201\257\350\256\260\345\275\225", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

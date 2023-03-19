/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
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
    QLabel *label;
    QLabel *info;
    QLabel *labelHp;
    QLabel *labelScore;
    QLabel *labelReload;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label_2;
    QListWidget *sinfo;
    QTextEdit *chatEdit;
    QLabel *label_3;
    QPushButton *sendChat;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1440, 1000);
        MainWindow->setMouseTracking(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 20, 89, 25));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 10, 1024, 768));
        QFont font;
        font.setPointSize(42);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        info = new QLabel(centralWidget);
        info->setObjectName(QString::fromUtf8("info"));
        info->setGeometry(QRect(430, 860, 311, 17));
        labelHp = new QLabel(centralWidget);
        labelHp->setObjectName(QString::fromUtf8("labelHp"));
        labelHp->setGeometry(QRect(50, 850, 67, 17));
        labelScore = new QLabel(centralWidget);
        labelScore->setObjectName(QString::fromUtf8("labelScore"));
        labelScore->setGeometry(QRect(50, 870, 91, 17));
        labelReload = new QLabel(centralWidget);
        labelReload->setObjectName(QString::fromUtf8("labelReload"));
        labelReload->setGeometry(QRect(50, 900, 171, 17));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 60, 89, 25));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 110, 89, 25));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(30, 170, 89, 25));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(30, 210, 89, 25));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1230, 130, 101, 17));
        sinfo = new QListWidget(centralWidget);
        sinfo->setObjectName(QString::fromUtf8("sinfo"));
        sinfo->setGeometry(QRect(1225, 180, 211, 471));
        chatEdit = new QTextEdit(centralWidget);
        chatEdit->setObjectName(QString::fromUtf8("chatEdit"));
        chatEdit->setGeometry(QRect(1250, 690, 171, 181));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1250, 660, 67, 17));
        sendChat = new QPushButton(centralWidget);
        sendChat->setObjectName(QString::fromUtf8("sendChat"));
        sendChat->setGeometry(QRect(1220, 880, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1440, 28));
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
        pushButton->setText(QCoreApplication::translate("MainWindow", "\346\226\260AI\346\225\214\344\272\272", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        info->setText(QCoreApplication::translate("MainWindow", "\346\227\240\346\266\210\346\201\257", nullptr));
        labelHp->setText(QCoreApplication::translate("MainWindow", "HP=100", nullptr));
        labelScore->setText(QCoreApplication::translate("MainWindow", "\345\276\227\345\210\206=0", nullptr));
        labelReload->setText(QCoreApplication::translate("MainWindow", "\345\211\251\344\275\231\350\243\205\345\241\253\346\227\266\351\227\264=4", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\224\237", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\350\277\234\347\250\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\344\277\241\346\201\257", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251\345\214\272", nullptr));
        sendChat->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

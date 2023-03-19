#include "mainwindow.h"
#include "ui_login.h"
#include <QMessageBox>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{    int fontId=QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");
     QString mysh=QFontDatabase::applicationFontFamilies(fontId).at(0);
     QFont font(mysh);
     this->setFont(font);
    ui->setupUi(this);
    ui->TIP->setText("127.0.0.1");
    ui->TNAME->setText("jeb");
    ui->TPORT->setText("8217");
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString ip,port,name;
    ip=ui->TIP->toPlainText();
    port=ui->TPORT->toPlainText();
    name=ui->TNAME->toPlainText();
    if(name.indexOf("#")>=0||name.indexOf("@")>=0)
    {
        QMessageBox::information(this,tr("错误"),tr("不支持的用户名"));
        return;
    }
    if(name.indexOf("服务器管理员")>=0)
    {
        QMessageBox::information(this,tr("错误"),tr("不支持的用户名"));
        return;
    }
    md->connectToServer(ip,port,name);
    this->close();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QFontDatabase>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ int fontId=QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");
    QString mysh=QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(mysh);
    this->setFont(font);
    ui->setupUi(this);
    ui->tport->setText("8217");
    ui->pbBattle->setEnabled(false);
     ui->pbBattle_2->setEnabled(false);
    shouldAccept=1;
    isPaused=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
     webserver = new QWebSocketServer(QStringLiteral("tankServer"),QWebSocketServer::NonSecureMode);

     webserver->listen(QHostAddress::Any,ui->tport->toPlainText().toInt());
       connect(webserver,SIGNAL(newConnection()),this,SLOT(server_newConnection()));
       ui->info->setText("服务器已经打开");
       ui->pbBattle->setEnabled(true);
}
void MainWindow::server_newConnection()
{ if(!shouldAccept)
    {
        return;
    }
    QWebSocket* pSocket = webserver->nextPendingConnection();
    sockList.append(pSocket);
    pSocket->sendTextMessage(QStringLiteral("服务器:欢迎来到本战场"));
        connect(pSocket,SIGNAL(textMessageReceived(QString)),this,SLOT(sock_receiveText(QString)));
    ui->textEdit->setText("new connection");
}

void MainWindow::on_pushButton_2_clicked()
{
    QString text=ui->textEdit->toPlainText();
    for(int i=0;i<sockList.count();i++)
    {
       QWebSocket* pSocket=sockList.at(i);
        pSocket->sendTextMessage("服务器管理员说:"+text);
    }
      ui->sinfo->addItem("我说:"+text);
}
void MainWindow::sock_receiveText(QString msg)
{     int a=decodingText(msg);

      if(a!=-1)
     {for(int i=0;i<sockList.count();i++)
         {

              QWebSocket* pSocket=sockList.at(i);
               pSocket->sendTextMessage(msg);

         }
  //    PortLineEdit->setText(msg);
     }
      if(msg.indexOf("#")<0||msg.indexOf("DIE")>=0)
      {
        ui->sinfo->addItem(msg);
      }
      else
     { ui->info->setText("接收"+msg);}
}
int MainWindow::decodingText(QString a)
{
    int endPos=a.indexOf("@");
       if(a.indexOf("#UNAME=")==0)
       {
           QString namet=a.mid(strlen("#UNAME="),endPos);
         //  namet=namet.left(endPos-strlen("#UNAME="));

            if(!isFind(a))
            {
                   ui->tankName->addItem(namet);
              nameList.append(namet);
             }
              return -1;
       }
       return 0;
}
int MainWindow::isFind(QString a)
{
    for ( int i=0; i!=this->nameList.size(); ++i )
       {

        if(nameList.at(i)==a)
        {
            return  1;
        }
    }
    return 0;
}
void MainWindow::sendStart()
{ QString sendStr="#LIST=";
    for ( int i=0; i!=this->nameList.size(); ++i )
    {
      sendStr+=nameList.at(i);
          sendStr+=",";
     }
    for(int i=0;i<sockList.count();i++)
    {
       QWebSocket* pSocket=sockList.at(i);
        pSocket->sendTextMessage(sendStr);
    }

}

void MainWindow::on_pbBattle_clicked()
{
    sendStart();
    ui->pbBattle->setEnabled(false);
     ui->pbBattle_2->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString name=ui->tankName->currentItem()->text();
    sendRespawn(name);
}
void MainWindow::sendRespawn(QString name)
{QString sendStr="#RESPAWN=";
    sendStr+=name+",";
    for(int i=0;i<sockList.count();i++)
    {
       QWebSocket* pSocket=sockList.at(i);
        pSocket->sendTextMessage(sendStr);
    }
       ui->sinfo->addItem("重生了"+name);
}

void MainWindow::sendDie(QString name)
{
    QString sendStr="#KILL=";
        sendStr+=name+",";
        for(int i=0;i<sockList.count();i++)
        {
           QWebSocket* pSocket=sockList.at(i);
            pSocket->sendTextMessage(sendStr);
        }
          ui->sinfo->addItem("杀死了"+name);
}
void MainWindow::sendPause()
{
    QString sendStr="#PAUSE=";

        for(int i=0;i<sockList.count();i++)
        {
           QWebSocket* pSocket=sockList.at(i);
            pSocket->sendTextMessage(sendStr);
        }
}

void MainWindow::sendResume()
{
    QString sendStr="#RESUME=";

        for(int i=0;i<sockList.count();i++)
        {
           QWebSocket* pSocket=sockList.at(i);
            pSocket->sendTextMessage(sendStr);
        }
}
void MainWindow::on_pushButton_4_clicked()
{
    QString name=ui->tankName->currentItem()->text();
    sendDie(name);
 }

void MainWindow::on_pbBattle_2_clicked()
{
    if(!isPaused)
    {
        sendPause();
        ui->pbBattle_2->setText("战斗继续");
        isPaused=1;
    }
    else {
        sendResume();
        ui->pbBattle_2->setText("战斗暂停");
        isPaused=0;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->sinfo->clear();
}

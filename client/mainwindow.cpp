#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <time.h>
#include <QMessageBox>
#include <QHostInfo>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    int fontId=QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");
     QString mysh=QFontDatabase::applicationFontFamilies(fontId).at(0);
     QFont font(mysh);
     this->setFont(font);
    ui->setupUi(this);
    ypos=0;
    QPalette pal(this->palette());
    ui->label->setScaledContents(true);
   ui->label->setStyleSheet(QString("background: transparent;border-image:url(:/pics/bg.jpg);color:rgb(0,255,0);"));
   ui->label->setText("等待进入");
   ui->label->setMouseTracking(true);
   Guitank *newTank= new Guitank(ui->label,this,48,48,128,ypos,"me",1);
   //newTank->show();
   myTank=newTank;
 tankList.append(myTank);
 //net work
   serverIP =new QHostAddress();
   isOnline=0;
  srand(time(0));
  ui->sendChat->setEnabled(false);
   ui->pushButton_4->setText("帮助");
    //pal.setColor(QPalette::Background, Qt::green); //设置背景黑色
   // this->setAutoFillBackground(true);
    //this->setPalette(pal);
}

MainWindow::~MainWindow()
{  delete  myTank;
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
            if(ui->label->geometry().contains(this->mapFromGlobal(QCursor::pos())))
            {
               QPoint ap=event->globalPos();
               ap=ui->label->mapFromGlobal(ap);
               myTank->setDest(ap.x(),ap.y());
               if(isOnline)
               {
                   sendMove(ap.x(),ap.y());
               }
            }

    }
    else if (event->button()==Qt::RightButton) {
       int damage=10+(rand()%5-2);
      //  int damage=10;
        if(  myTank->fireShell(damage))
         {
          ui->info->setText("提示:开火完成!");
          if(isOnline)
          {
              sendFire(damage);
          }
         }
         else {
              ui->info->setText("提示:正在装填!");
         }
    }
}
void MainWindow::wheelEvent(QWheelEvent *event)
{   if(ui->label->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
         int ta;
         if(event->delta()>0)
            {ta=myTank->angle+1;}
             else {
             ta=myTank->angle-1;
                }
             if(ta>3)
            {
             ta=0;
            }
            else if(ta<0)
             {
                 ta=3;
             }
         myTank->setRotate(ta);
         if(isOnline)
         {
             sendRotate(ta);
         }
        }
}
void MainWindow::on_pushButton_clicked()
{
    int x=rand()%ui->label->height();
    int y=rand()%ui->label->width();
    Guitank *newTank= new Guitank(ui->label,this,48,48,x,y,"enmy",0);
    newTank->aiTarget=myTank;
    //newTank->remoteMask=1;
    //newTank->show();
tankList.append(newTank);
    ypos+=40;
  //  tl->setPixmap(QPixmap(":/pics/tank.jpg"));
}
void MainWindow::renewStatus(int hp, int score,int reload)
{
  ui->labelHp->setText("HP="+QString::number(hp));
  ui->labelScore->setText("得分="+QString::number(score));
  ui->labelReload->setText("剩余装弹时间="+QString::number(reload));
  if(reload==0)
 { ui->label->setText("Ready");}
  else {
      ui->label->setText(QString::number(reload));
  }
}
void MainWindow::renewMessage(QString a)
{
    ui->info->setText("信息:"+a);
}
void MainWindow::setMapTittle(QString a)
{
       ui->label->setText(a);
}
void MainWindow::on_pushButton_2_clicked()
{

    if(ypos==0)
    {
        /*for ( int i=0; i!=this->tankList.size(); ++i )
        {
          Guitank *tank=this->tankList.at(i);
          tank->pauseAction();
        }*/
         pauseAll();
         ypos=1;
         ui->pushButton_2->setText("继续");
    }
    else {
       /* for ( int i=0; i!=this->tankList.size(); ++i )
        {
          Guitank *tank=this->tankList.at(i);
          tank->resumeAction();
        }*/
        resumeAll();
         ui->pushButton_2->setText("暂停");
         ypos=0;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    myTank->hp=100;
    myTank->reloadTime=4;
    myTank->reloadV=0;
    myTank->v=2;
    tankList.append(myTank);
}

void MainWindow::on_pushButton_4_clicked()
{
   /* ui->label->setWindowFlags(Qt::Dialog);
    ui->label->setFocus();
        ui->label->setScaledContents(true);
        ui->label->showFullScreen();*/
    QString h="1.鼠标左键-移动到指定位置,滚轮-旋转,右键-开火(只在装填完成时可用)\r\n";
    h+="2.请时刻关注您的hp,因为炮弹伤害值会在8~13变化\r\n";
    h+="3.联机模式下,暂停继续与重生功能都被服务器管理员控制,请与他/她沟通\r\n";
    h+="4.祝旗开得胜!!";
            QMessageBox::information(this,tr("帮助"),h);
}

void MainWindow::on_pushButton_5_clicked()
{
 lwindow.show();
 lwindow.md=this;

}
void MainWindow::connectToServer(QString ip, QString port, QString name)
{    int sport=port.toInt();
     ui->info->setText("尝试连接到"+ip+"的端口"+port+",名称是"+name);
     if(!serverIP->setAddress(ip))
     {
         QMessageBox::information(this,tr("错误"),tr("不能解析的ip地址"));
         return;
     }
     userName=name;
     sock=new QWebSocket();

      QString con="ws://"+ip+":"+port;

     connect(sock,SIGNAL(connected()),this,SLOT(slotConnected()));
     //检测如果断开
     connect(sock,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
     //检测如果有新可以读信号
    // connect(sock,SIGNAL(readyRead()),this,SLOT(dataReceived()));
      connect(sock,SIGNAL(textMessageReceived(QString)),this,SLOT(dataReceived(QString)));
   //  tcpSocket->connectToHost(*serverIP,sport);
         sock->open(QUrl(con));
}
void MainWindow::slotSend()
{

}
void MainWindow::slotConnected()
{
    QString msg="#UNAME="+userName;
    int length;
  ui->sendChat->setEnabled(true);
  sock->sendTextMessage(msg);

    myTank->hp=0;
    myTank->nameTag=userName;
    myTank->setText(userName);
    ui->info->setText("连接成功,等待服务器开战信号");
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->label->setText("Wait");
    isOnline=1;
    for ( int i=0; i!=this->tankList.size(); ++i )
       {
         Guitank *tank=this->tankList.at(i);
         tank->hp=0;
         tank->close();
         tank->soundPlayer.stop();
         tank->hitPlayer.stop();
         tank->reloadPlayer.stop();

         //this->tankList.removeAt(i);
      //   tank->onDeath();
        // tank->~Guitank();
       }
      tankList.clear();
}
void MainWindow::slotDisconnected()
{
isOnline=0;
   QMessageBox::information(this,tr("错误"),tr("与服务器连接断开或者服务器不存在"));
   ui->pushButton->setEnabled(true);
   ui->pushButton_2->setEnabled(true);
   ui->pushButton_3->setEnabled(true);
   tankList.clear();
   tankList.append(myTank);
   myTank->reset(myTank->x(),myTank->y());
   ui->sendChat->setEnabled(false);
}
void MainWindow::decodingText(QString a)
{  QString out="玩家:";

    if(a.indexOf("#LIST=")==0)
    {  int cnt=0;
        int xd=ui->label->width()/10;
        int xpos=xd;
        int ypos=0;
       QString token=a.mid(strlen("#LIST="));
       int getLen=token.indexOf(",");
       while(getLen>0)
        {QString namet=token.left(getLen);
            token=token.mid(getLen+1);
           getLen=token.indexOf(",");
           printf("%d,%s\r\n",getLen,token.toUtf8().data());
           out+=namet+",";
           xpos+=xd;
           if(xpos>=ui->label->width())
           {
               xpos=xd;
               ypos+=ui->label->height()/10;
           }
           if(namet==userName)
           {
            tankList.append(myTank);
            myTank->reset(xpos,ypos);
          //  myTank->nameLabel->show();
           }
           else {
                Guitank *newTank= new Guitank(ui->label,this,48,48,xpos,ypos,namet,0);
                tankList.append(newTank);
                newTank->reset(xpos,ypos);

           }
        }
       ui->info->setText("开始战斗"+out);
       ui->label->setText("开始战斗!");

    }
    else if(a.indexOf("#MOVE=")==0)
    {   //Guitank *oTank;
          QString token=a.mid(strlen("#MOVE="));
           int getLen=token.indexOf(",");
           QString namet=token.left(getLen);
           token=token.mid(getLen+1);
           Guitank *tk=findTank(namet);//name
          if(tk==nullptr||tk==myTank)
          {
              return;
          }
          getLen=token.indexOf(",");
          QString xt=token.left(getLen);
          token=token.mid(getLen+1); //x
          getLen=token.indexOf(",");
          QString yt=token.left(getLen);
          token=token.mid(getLen+1); //y
          tk->setDest(xt.toInt(),yt.toInt());
    }
    else if(a.indexOf("#ROTATE=")==0)
    {
        QString token=a.mid(strlen("#ROTATE="));
         int getLen=token.indexOf(",");
         QString namet=token.left(getLen);
         token=token.mid(getLen+1);
         Guitank *tk=findTank(namet);//name
        if(tk==nullptr||tk==myTank)
        {
            return;
        }
        getLen=token.indexOf(",");
        QString at=token.left(getLen);
        token=token.mid(getLen+1); //a
        getLen=token.indexOf(",");
        tk->setRotate(at.toInt());
    }
    else if(a.indexOf("#FIRE=")==0)
    {
        QString token=a.mid(strlen("#FIRE="));
         int getLen=token.indexOf(",");
         QString namet=token.left(getLen);
         token=token.mid(getLen+1);
         Guitank *tk=findTank(namet);//name
        if(tk==nullptr||tk==myTank)
        {
            return;
        }
        getLen=token.indexOf(",");
        QString da=token.left(getLen);
        getLen=token.indexOf(",");
        QString at=token.left(getLen);
        tk->fireShell(da.toInt());
        ui->info->setText(namet+"开火");
    }
    else if(a.indexOf("#RESPAWN=")==0)
    {
        QString token=a.mid(strlen("#RESPAWN="));
         int getLen=token.indexOf(",");
         QString namet=token.left(getLen);
         token=token.mid(getLen+1);
         Guitank *tk=findTank(namet);//name
        if(tk==nullptr)
        {
            return;
        }
        getLen=token.indexOf(",");
        QString da=token.left(getLen);
        getLen=token.indexOf(",");
        QString at=token.left(getLen);
        if(tk==myTank)
        {
            ui->label->setText("重生");
        }
        tk->reset(tk->x(),tk->y());
        ui->info->setText(namet+"被"+"服务器管理员设置重生");
        ui->sinfo->addItem(namet+"被"+"服务器管理员设置重生");
    }
    else if(a.indexOf("#KILL=")==0)
    {
        QString token=a.mid(strlen("#KILL="));
         int getLen=token.indexOf(",");
         QString namet=token.left(getLen);
         token=token.mid(getLen+1);
         Guitank *tk=findTank(namet);//name
        if(tk==nullptr)
        {
            return;
        }
        getLen=token.indexOf(",");
        QString da=token.left(getLen);
        getLen=token.indexOf(",");
        QString at=token.left(getLen);
        tk->hp=-1;
        if(tk==myTank)
        {
           tk->onDeath("服务器管理员");
        }
       /* tk->reset(tk->x(),tk->y());
        ui->info->setText(namet+"被"+"服务器管理员设置死亡");
        ui->sinfo->addItem(namet+"被"+"服务器管理员设置死亡");*/
    }
    else if(a.indexOf("#DIE=")==0)
    {
        QString token=a.mid(strlen("#DIE="));
         int getLen=token.indexOf(",");
         QString namet=token.left(getLen);
         token=token.mid(getLen+1);

        getLen=token.indexOf(",");
        QString src=token.left(getLen);
        getLen=token.indexOf(",");
        QString at=token.left(getLen);

        ui->info->setText(namet+"被"+src+"杀死了");
        ui->sinfo->addItem(namet+"被"+src+"杀死了");
    }
    else if(a.indexOf("#PAUSE=")==0)
    {
        pauseAll();
        ui->sinfo->addItem("服务器管理员设置了暂停");
    }
    else if(a.indexOf("#RESUME=")==0)
    {
        resumeAll();
        ui->sinfo->addItem("服务器管理员设置了继续");
    }

    else {
         ui->sinfo->addItem(a);
    }


}
void MainWindow::dataReceived(QString msg)
{
    decodingText(msg);
}
void MainWindow::sendMove(int x, int y)
{
    QString outStr="#MOVE=";
    outStr+=userName+",";
    outStr+=QString::number(x)+","+QString::number(y)+",";
    sock->sendTextMessage(outStr);
}
void MainWindow::sendRotate(int a)
{
    QString outStr="#ROTATE=";
    outStr+=userName+",";
    outStr+=QString::number(a)+",";
     sock->sendTextMessage(outStr);
}
void MainWindow::sendFire(int damage)
{
    QString outStr="#FIRE=";
    outStr+=userName+",";
     outStr+=QString::number(damage)+",";
    sock->sendTextMessage(outStr);
}
Guitank *MainWindow::findTank(QString a)
{
    for ( int i=0; i!=tankList.count(); i++ )
    {
      Guitank *tank=tankList.at(i);
     if(tank->nameTag==a)
     {
         return tank;
     }
    }
    return  nullptr;
}
void MainWindow::selfDie(QString srcName)
{

  renewMessage("你失败了!!");
    setMapTittle("你失败了");
    if(isOnline)
    {
        QString outStr="#DIE=";
        outStr+=userName+",";
         outStr+=srcName+",";
    sock->sendTextMessage(outStr);
    }
}

void MainWindow::on_sendChat_clicked()
{
    if(isOnline)
    {

        QString textC=ui->chatEdit->toPlainText();
        if(textC.indexOf("#")>=0)
        {
             QMessageBox::information(this,tr("错误"),tr("不能发送非法字符"));
             return;
        }
        QString send=userName+" 说:"+textC;
          sock->sendTextMessage(send);
    }
}
void MainWindow::resumeAll()
{
    for ( int i=0; i!=this->tankList.size(); ++i )
    {
      Guitank *tank=this->tankList.at(i);
      tank->resumeAction();
    }
         ui->label->setText("继续");
}
void MainWindow::pauseAll()
{
    for ( int i=0; i!=this->tankList.size(); ++i )
    {
      Guitank *tank=this->tankList.at(i);
      tank->pauseAction();
    }
      ui->label->setText("已暂停");
}

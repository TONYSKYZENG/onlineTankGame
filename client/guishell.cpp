#include "mainwindow.h"


#include <QTimer>
Guishell::Guishell(QWidget *parent,MainWindow *mw,int w,int h,int x,int y,int sdamage)
{
    this->setGeometry(x,y,w,h);

    this->setScaledContents(true);
   this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/shell.png);color:rgb(255,0,0);"));
    this->setParent(parent);
    destX=x;
    destY=y;
    damage=sdamage;
    v=20;
    moveTimer = new QTimer(this);
   moveTimer->setInterval(33);   //set timer match with FPS
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(onMoveTimer()));
    moveTimer->start();

  this->angle=0;
    soundPlayer.setVolume(30);
   myParent=parent;
   myWindow=mw;
   //  this->show();
}
Guishell::~Guishell()
{
 moveTimer->stop();
 moveTimer->~QTimer();

}
void Guishell::onMoveTimer()
{  int shouldMove=0;
    if(this->colideWith())
    {
        moveTimer->stop();
        this->setVisible(false);
        this->~Guishell();
    }
    if(destX>this->x()+v)
    {
        this->move(this->x()+v,this->y());
        shouldMove=1;
      //  soundPlayer.play();
    }
    else if(destX<this->x()-v)
    {
        this->move(this->x()-v,this->y());
       // soundPlayer.play();
        shouldMove=1;

    }
    if(destY>this->y()+v)
    {
        this->move(this->x(),this->y()+v);
        shouldMove=1;
       // soundPlayer.play();
    }
    else if(destY<this->y()-v)
    {
        this->move(this->x(),this->y()-v);
        shouldMove=1;
       // soundPlayer.play();
    }
    if(!shouldMove)
    {
        soundPlayer.stop();
        this->~Guishell();
    }
}
void Guishell::setDest(int dx, int dy)
{
    destX=dx;
    destY=dy;
    if(soundPlayer.isPlaying())
    {
        return;
    }
    soundPlayer.setSource(QUrl::fromLocalFile(":/sound/fire.wav"));
   soundPlayer.setLoopCount(1);
  soundPlayer.play();
}
int Guishell::colideWith(void)
{
    for ( int i=0; i!=myWindow->tankList.count(); i++ )
    {
      Guitank *tank=myWindow->tankList.at(i);
      if(tank->geometry().contains(this->pos())&&tank!=this->mytank)
      {
          tank->onHitted(damage,70,mytank);
         // mytank->onHitOther();
          return 1;
      }
    }
    return 0;
}

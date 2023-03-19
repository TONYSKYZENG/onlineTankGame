#include "mainwindow.h"
#include <QTimer>

Guitank::Guitank(QWidget *parent,MainWindow *mw,int w,int h,int x,int y,QString a,int ifself)
{   int fontId=QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");
    QString mysh=QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(mysh);
    this->setFont(font);
    screen=parent;
     myWindow=mw;
      aiTarget=NULL;
       remoteMask=0;
    this->setGeometry(x,y,w,h);
    this->setScaledContents(true);
  shellSize=20;
   reloadTime=4;
   reloadV=1;
    destX=x;
    destY=y;
    v=2;
    moveTimer = new QTimer(this);
   moveTimer->setInterval(33);   //set timer match with FPS
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(onMoveTimer()));
    moveTimer->start();
    reloadTimer = new QTimer(this);
   reloadTimer->setInterval(1000);   //set timer match with FPS
    connect(reloadTimer, SIGNAL(timeout()), this, SLOT(onReloadTimer()));
    reloadTimer->start();
  this->angle=0;
    this->range=400;
    hp=100;
    score=0;
      self=ifself;
      if(self)
    {soundPlayer.setVolume(50);
    reloadPlayer.setVolume(30);
    reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));
    reloadPlayer.setLoopCount(QSoundEffect::Infinite);
    reloadPlayer.play();
     this->myWindow->renewStatus(hp,score,reloadTime-reloadV);
    this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank.png);color:rgb(255,255,255);"));
  }
      else {soundPlayer.setVolume(0);
             reloadPlayer.setVolume(0);
              this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank.png);color:rgb(0,0,0);"));

      }

       this->setParent(parent);
       this->setText(a);
     this->show();
       policy=rand()%3;
        nameTag=a;
}
Guitank::~Guitank()
{
 moveTimer->stop();
 moveTimer->~QTimer();
reloadTimer->stop();
reloadTimer->~QTimer();

}
void Guitank::onMoveTimer()
{  int shouldMove=0;

    if(hp<=0)
    {
        return;
    }
    if(!self&&!remoteMask&&aiTarget)
    {
        attackTargetAi();
    }
  //  this->colideWith();
    if(destX>this->x()+v)
    {
        this->move(this->x()+v,this->y());

     //  soundPlayer.play();
    }
    else if(destX<this->x()-v)
    {
        this->move(this->x()-v,this->y());


        //soundPlayer.play();
        shouldMove=1;

    }
    if(destY>this->y()+v)
    {
        this->move(this->x(),this->y()+v);
        shouldMove=1;

     //  soundPlayer.play();
    }
    else if(destY<this->y()-v)
    {
        this->move(this->x(),this->y()-v);
        shouldMove=1;

     //  soundPlayer.play();
    }
    if(!shouldMove)
    {
       soundPlayer.stop();
    }
    else {
        if(soundPlayer.isPlaying())
                 {
                     return;
                 }
                 soundPlayer.setSource(QUrl::fromLocalFile(":/sound/leave.wav"));
               soundPlayer.setLoopCount(QSoundEffect::Infinite);
                soundPlayer.play();

     }

}
void Guitank::setDest(int dx, int dy)
{     if(hp<=0)
    {
        return;
    }
    destX=dx;
    destY=dy;
    if(dx>screen->width()-this->width())
    {
       destX=screen->width()-this->width();
    }
    else if(dx<0)
    {
        destX=0;
    }
    else {
         destX=dx;
    }
    if(dy>screen->height()-this->height())
    {
           destY= screen->height()-this->height();
    }
    else if(dy<0)
    {
        destY=0;
    }
    else {
        destY=dy;
    }
      if(self)
    {   /*if(soundPlayer.isPlaying())
          {
              return;
          }
          soundPlayer.setSource(QUrl::fromLocalFile(":/sound/leave.wav"));
        soundPlayer.setLoopCount(QSoundEffect::Infinite);
         soundPlayer.play();*/
      }

}
void Guitank::setRotate(int an)
{  QString colorSet;
    if(hp<=0)
      {
          return;
      }
    if(self)
    {
        colorSet="color:rgb(255,255,255);";
     }
    else {
         colorSet="color:rgb(0,0,0);";
    }
    if(an==angle)
    {
        return;
    }
    angle=an;
    switch (an) {
    case 0: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank.png);")+colorSet);break;
    case 1: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank1.png);")+colorSet);break;
    case 2: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank2.png);")+colorSet);break;
    case 3: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank3.png);")+colorSet);break;
    }
}
void Guitank::forcedFireShell()
{int dx,dy;
    int px,py;
    switch (angle) {
    case 0: px+=this->width();dx=this->x()+range;dy=this->y();py+=this->height()/2-shellSize/2;break;
    case 1:py+=this->height();dx=this->x();dy=this->y()+range;px+=this->width()/2-shellSize/2;break;
    case 2:px-=this->width();dx=this->x()-range;dy=this->y();py+=this->height()/2-shellSize/2;break;
    case 3:py-=this->height();dx=this->x();dy=this->y()-range;px+=this->width()/2-shellSize/2;break;
    }
    myShell=new Guishell(screen,myWindow,shellSize,shellSize,px,py,10+(rand()%5-2));
    myShell->show();
    myShell->setDest(dx,dy);
    myShell->mytank=this;
   // reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));
   // reloadPlayer.setLoopCount(QSoundEffect::Infinite);
    //reloadPlayer.play();
    reloadV=1;
    return ;

}
int Guitank::fireShell()
{   if(hp<=0)
    {
        return -1;
    }
    if(reloadV==reloadTime)
    {int dx,dy;
    int px,py;
    px=this->x();
    py=this->y();

    switch (angle) {
    case 0: px+=this->width();dx=this->x()+range;dy=this->y();py+=this->height()/2-shellSize/2;break;
    case 1:py+=this->height();dx=this->x();dy=this->y()+range;px+=this->width()/2-shellSize/2;break;
    case 2:px-=this->width();dx=this->x()-range;dy=this->y();py+=this->height()/2-shellSize/2;break;
    case 3:py-=this->height();dx=this->x();dy=this->y()-range;px+=this->width()/2-shellSize/2;break;
    }
    myShell=new Guishell(screen,myWindow,shellSize,shellSize,px,py,10+(rand()%5-2));
    myShell->show();
    myShell->setDest(dx,dy);
    myShell->mytank=this;
    reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));
    reloadPlayer.setLoopCount(QSoundEffect::Infinite);
    reloadPlayer.play();
    reloadV=1;
    return 1;
    }
    else {
        return 0;
    }
}
int Guitank::fireShell(int damage)
{
    if(hp<=0)
        {
            return -1;
        }
        if(reloadV==reloadTime)
        {int dx,dy;
        int px,py;
        px=this->x();
        py=this->y();

        switch (angle) {
        case 0: px+=this->width();dx=this->x()+range;dy=this->y();py+=this->height()/2-shellSize/2;break;
        case 1:py+=this->height();dx=this->x();dy=this->y()+range;px+=this->width()/2-shellSize/2;break;
        case 2:px-=this->width();dx=this->x()-range;dy=this->y();py+=this->height()/2-shellSize/2;break;
        case 3:py-=this->height();dx=this->x();dy=this->y()-range;px+=this->width()/2-shellSize/2;break;
        }
        myShell=new Guishell(screen,myWindow,shellSize,shellSize,px,py,damage);
        myShell->show();
        myShell->setDest(dx,dy);
        myShell->mytank=this;
        reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));
        reloadPlayer.setLoopCount(QSoundEffect::Infinite);
        reloadPlayer.play();
        reloadV=1;
        return 1;
        }
        else {
            return 0;
        }
}
void Guitank::onReloadTimer()
{  if(hp<=0)
    {
        return;
    }
    if(reloadV==reloadTime)
    {

        reloadPlayer.stop();
         //return;
    }
    else {
        reloadV=reloadV+1;
    }
    if(self)
    {
          this->myWindow->renewStatus(hp,score,reloadTime-reloadV);

    }
}
void Guitank::onHitted(int damage, int vol,Guitank *src)
{  if(hp<=0)
    {
        return;
    }
   /* if(this->self==src->self)
    {
        return;
    }*/
    hp=hp-damage;
    if(hitPlayer.isPlaying())
    {
        return;
    }
    hitPlayer.setVolume(vol);
    hitPlayer.setSource(QUrl::fromLocalFile(":/sound/hit.wav"));
    hitPlayer.setLoopCount(1);
    hitPlayer.play();
    if(self)
    {
          this->myWindow->renewStatus(hp,score,reloadTime-reloadV);
         this->myWindow->renewMessage("遭到攻击!!");
    }
    if(hp<=0)
    {

        this->onDeath(src->nameTag);

       // this->~Guitank();
        src->onKillOther(this);
        //delete  this;
    }
    else {
        src->onHitOther(this);
        if(hp<50)
        {
            reloadTime=8;
            if(hp<20)
            {
                v=1;
            }
        }
    }
}
void Guitank::onHitOther(Guitank *dest)
{
    this->score+=1;
      policy=rand()%3;
    if(self)
    {
        this->myWindow->renewStatus(hp,score,reloadTime-reloadV);
            this->myWindow->renewMessage("击中目标:)!!!");
    }
}
void Guitank::onDeath(QString srcName)
{
    if(self)
    {  soundPlayer.stop();
        reloadPlayer.stop();
        reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/death.wav"));
    reloadPlayer.setLoopCount(1);
    reloadPlayer.setVolume(50);
    reloadPlayer.play();
   this->myWindow->renewStatus(hp,score,reloadTime-reloadV);
    this->myWindow->selfDie(srcName);
    }


}
void Guitank::onKillOther(Guitank *dest)
{
    score+=10;
    if(self)
    {
          this->myWindow->renewStatus(hp,score,reloadTime-reloadV);
         this->myWindow->renewMessage("击杀目标!!");
        reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/kill.wav"));
            reloadPlayer.setLoopCount(1);
            reloadPlayer.setVolume(50);
            reloadPlayer.play();
             this->myWindow->setMapTittle("击杀!");
    }
   /* if(dest==this->aiTarget)
    {
        this->aiTarget=NULL;
    }*/
   //dest->~Guitank();
}
void Guitank::pauseAction()
{
    moveTimer->stop();
    reloadTimer->stop();
    reloadPlayer.setMuted(true);
    soundPlayer.setMuted(true);
}
void Guitank::resumeAction()
{
    moveTimer->start();
    reloadTimer->start();
    reloadPlayer.setMuted(false);
    soundPlayer.setMuted(false);
}
void Guitank::reset(int x,int y)
{     moveTimer->stop();
      reloadTimer->stop();
    hp=100;
    reloadV=0;
    reloadTime=4;
    v=2;
     this->setGeometry(x,y,this->width(),this->height());

     setDest(x,y);
      moveTimer->start();
      reloadTimer->start();
      reloadPlayer.setMuted(false);
     soundPlayer.setMuted(false);
       this->show();
   //    this->nameLabel->show();
}

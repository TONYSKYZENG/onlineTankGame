#include "mainwindow.h"
#include <QTimer>

Guitank::Guitank(QWidget* parent, MainWindow* mw, int w, int h, int x, int y, QString a, int ifself)
//参数依次为父组件,主窗口,宽度,高度,位置(x,y),坦克名(会跟随在坦克上),itself?
{
	int fontId = QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");
	QString mysh = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont font(mysh);
	this->setFont(font);//设置字体
	screen = parent;//父组件QLabel为屏幕
	myWindow = mw;//mv即为Mainwindow
	aiTarget = NULL;//无ai对手
	remoteMask = 0;
	this->setGeometry(x, y, w, h);
	this->setScaledContents(true);//(即QLabel)图片自适应窗口大小
	shellSize = 20;//子弹大小
	reloadTime = 3;//装载子弹时间
	reloadV = 1;
	destX = x;
	destY = y;
	v = 2;
	moveTimer = new QTimer(this);
	moveTimer->setInterval(33);   //set timer match with FPS
	connect(moveTimer, SIGNAL(timeout()), this, SLOT(onMoveTimer()));//定时刷新位置
	moveTimer->start();
	reloadTimer = new QTimer(this);
	reloadTimer->setInterval(1000);   //set timer match with FPS
	connect(reloadTimer, SIGNAL(timeout()), this, SLOT(onReloadTimer()));
	reloadTimer->start();
	this->angle = 0;
	this->range = 400;
	hp = 100;
	score = 0;
	self = ifself;//自己初始为1，AI初始为0
	if (self)
	{
		soundPlayer.setVolume(50);
		reloadPlayer.setVolume(30);//设置音量
		reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));//开场声音
		reloadPlayer.setLoopCount(QSoundEffect::Infinite);
		reloadPlayer.play();
		this->myWindow->renewStatus(hp, score, reloadTime - reloadV);
		this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank.png);color:rgb(255,255,255);"));
	}
	else {
		soundPlayer.setVolume(0);
		reloadPlayer.setVolume(0);//AI坦克无声登场
		this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank.png);color:rgb(0,0,0);"));//设置坦克图标

	}
	this->setParent(screen);//设置父组件
	this->setText(a);//Guitank为Label，设置文本
	this->show();//坦克出现
	policy = rand() % 3;
	nameTag = a;//储存名字
}
Guitank::~Guitank()
{
	moveTimer->stop();
	moveTimer->~QTimer();
	reloadTimer->stop();
	reloadTimer->~QTimer();

}
void Guitank::onMoveTimer()//在更新时间点同时微调x,y坐标，同时播放音乐
{
	int shouldMove = 0;

	if (hp <= 0)
	{
		return;//死亡，退出
	}
	if (!self && aiTarget)//不是自己，ai实现自动打击
	{
		attackTargetAi();//ai敌人攻击
	}
	//  this->colideWith();
	if (destX > this->x() + v)
	{
		this->move(this->x() + v, this->y());

		//  soundPlayer.play();
	}
	else if (destX < this->x() - v)
	{
		this->move(this->x() - v, this->y());


		//soundPlayer.play();
		shouldMove = 1;

	}
	if (destY > this->y() + v)
	{
		this->move(this->x(), this->y() + v);
		shouldMove = 1;

		//  soundPlayer.play();
	}
	else if (destY < this->y() - v)
	{
		this->move(this->x(), this->y() - v);
		shouldMove = 1;

		//  soundPlayer.play();
	}
	if (!shouldMove)
	{
		soundPlayer.stop();
	}
	else {
		if (soundPlayer.isPlaying())//正在运作，不打扰退出(如发炮时)
		{
			return;
		}
		soundPlayer.setSource(QUrl::fromLocalFile(":/sound/leave.wav"));
		soundPlayer.setLoopCount(QSoundEffect::Infinite);//无限循环
		soundPlayer.play();
	}

}
void Guitank::setDest(int dx, int dy)//更新坐标
{
	if (hp <= 0)
	{
		return;
	}
	destX = dx;
	destY = dy;
	if (dx > screen->width() - this->width())
	{
		destX = screen->width() - this->width();
	}
	else if (dx < 0)
	{
		destX = 0;
	}
	else {
		destX = dx;
	}
	if (dy > screen->height() - this->height())
	{
		destY = screen->height() - this->height();
	}
	else if (dy < 0)
	{
		destY = 0;
	}
	else {
		destY = dy;
	}
	if (self)
	{
		if (soundPlayer.isPlaying())
		{
			return;
		}
		soundPlayer.setSource(QUrl::fromLocalFile(":/sound/leave.wav"));
		soundPlayer.setLoopCount(QSoundEffect::Infinite);
		soundPlayer.play();
	}

}
void Guitank::setRotate(int an)//转向
{
	QString colorSet;
	if (hp <= 0)
	{
		return;
	}
	if (self)
	{
		colorSet = "color:rgb(255,255,255);";
	}
	else {
		colorSet = "color:rgb(0,0,0);";
	}
	if (an == angle)
	{
		return;
	}
	angle = an;
	switch (an) {
	case 0: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank.png);") + colorSet); break;
	case 1: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank1.png);") + colorSet); break;
	case 2: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank2.png);") + colorSet); break;
	case 3: this->setStyleSheet(QString("background: transparent;border-image:url(:/pics/tank3.png);") + colorSet); break;
	}
}
void Guitank::forcedFireShell()
{
	int dx, dy;
	int px, py;
	switch (angle) {//子弹发射
	case 0: px += this->width(); dx = this->x() + range; dy = this->y(); py += this->height() / 2 - shellSize / 2; break;
	case 1:py += this->height(); dx = this->x(); dy = this->y() + range; px += this->width() / 2 - shellSize / 2; break;
	case 2:px -= this->width(); dx = this->x() - range; dy = this->y(); py += this->height() / 2 - shellSize / 2; break;
	case 3:py -= this->height(); dx = this->x(); dy = this->y() - range; px += this->width() / 2 - shellSize / 2; break;
	}
	myShell = new Guishell(screen, myWindow, shellSize, shellSize, px, py, 10 + rand() % 5);
	myShell->show();
	myShell->setDest(dx, dy);
	myShell->mytank = this;
	// reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));
	// reloadPlayer.setLoopCount(QSoundEffect::Infinite);
	 //reloadPlayer.play();
	reloadV = 0;
	return;

}
int Guitank::fireShell()
{
	if (hp <= 0)
	{
		return -1;
	}
	if (reloadV == reloadTime)
	{
		int dx, dy;
		int px, py;
		px = this->x();
		py = this->y();

		switch (angle) {
		case 0: px += this->width(); dx = this->x() + range; dy = this->y(); py += this->height() / 2 - shellSize / 2; break;
		case 1:py += this->height(); dx = this->x(); dy = this->y() + range; px += this->width() / 2 - shellSize / 2; break;
		case 2:px -= this->width(); dx = this->x() - range; dy = this->y(); py += this->height() / 2 - shellSize / 2; break;
		case 3:py -= this->height(); dx = this->x(); dy = this->y() - range; px += this->width() / 2 - shellSize / 2; break;
		}
		myShell = new Guishell(screen, myWindow, shellSize, shellSize, px, py, 10 + rand() % 5);
		myShell->show();
		myShell->setDest(dx, dy);
		myShell->mytank = this;
		reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));
		reloadPlayer.setLoopCount(QSoundEffect::Infinite);
		reloadPlayer.play();
		reloadV = 0;
		return 1;
	}
	else {
		return 0;
	}
}
int Guitank::fireShell(int damage)//有damage参数，在右键时触发
{
	if (hp <= 0)
	{
		return -1;
	}
	if (reloadV == reloadTime)
	{
		int dx, dy;//目标位置
		int px, py;//当前位置
		px = this->x();
		py = this->y();

		switch (angle) {//range=400
		case 0: px += this->width(); dx = this->x() + range; dy = this->y(); py += this->height() / 2 - shellSize / 2; break;
		case 1:py += this->height(); dx = this->x(); dy = this->y() + range; px += this->width() / 2 - shellSize / 2; break;
		case 2:px -= this->width(); dx = this->x() - range; dy = this->y(); py += this->height() / 2 - shellSize / 2; break;
		case 3:py -= this->height(); dx = this->x(); dy = this->y() - range; px += this->width() / 2 - shellSize / 2; break;
		}
		myShell = new Guishell(screen, myWindow, shellSize, shellSize, px, py, damage);
		myShell->show();
		myShell->setDest(dx, dy);
		myShell->mytank = this;//将子弹类的主人设为mytank，即this
		reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/reload.wav"));
		reloadPlayer.setLoopCount(QSoundEffect::Infinite);
		reloadPlayer.play();//播放音效
		reloadV = 0;//装载时间为3s,0/3
		return 1;
	}
	else {
		return 0;
	}
}
void Guitank::onReloadTimer()
{
	if (hp <= 0)
	{
		return;
	}
	if (reloadV == reloadTime)
	{

		reloadPlayer.stop();
		//return;
	}
	else {
		reloadV += 1;
	}
	if (self)//如果是自己的坦克
	{
		this->myWindow->renewStatus(hp, score, reloadTime - reloadV);
	}
}
void Guitank::onHitted(int damage, int vol, Guitank* Shelltank)//Shelltank为发出子弹的坦克
{
	if (hp <= 0)
	{
		return;
	}
	/* if(this->self==src->self)//
	 {
		 return;
	 }*/
	hp -= damage;//hp减少
	if (hitPlayer.isPlaying())
	{
		return;
	}
	hitPlayer.setVolume(vol);
	hitPlayer.setSource(QUrl::fromLocalFile(":/sound/hit.wav"));
	hitPlayer.setLoopCount(1);
	hitPlayer.play();//播放音效
	if (self)
	{
		this->myWindow->renewStatus(hp, score, reloadTime - reloadV);
		this->myWindow->renewMessage(QString::fromLocal8Bit("遭到攻击!"));

	}
	else
	{
		if (hp <= 0)
		{
			this->onDeath(Shelltank->nameTag);
			// this->~Guitank();
			Shelltank->onKillOther(this);
			//delete this;//删除该坦克
		}
		else {
			Shelltank->onHitOther(this);
			if (hp < 50)
			{
				reloadTime = 8;
				if (hp < 20)
				{
					v = 1;
				}
			}
		}
	}
}
void Guitank::onHitOther(Guitank* dest)
{
	this->score += 1;
	policy = rand() % 3;
	if (self)
	{
		this->myWindow->renewStatus(hp, score, reloadTime - reloadV);
		this->myWindow->renewMessage(QString::fromLocal8Bit("击中目标!!!"));
	}
}
void Guitank::onDeath(QString srcName)//死亡
{
	if (self)
	{
		soundPlayer.stop();
		reloadPlayer.stop();
		reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/death.wav"));
		reloadPlayer.setLoopCount(1);
		reloadPlayer.setVolume(50);
		reloadPlayer.play();//播放音效
		this->myWindow->renewStatus(hp, score, reloadTime - reloadV);
		this->myWindow->selfDie(srcName);
	}
}
void Guitank::onKillOther(Guitank* dest)
{
	score += 10;
	if (self)
	{
		this->myWindow->renewStatus(hp, score, reloadTime - reloadV);
		this->myWindow->setMapTittle(QString::fromLocal8Bit("击杀!"));
		this->myWindow->renewMessage(QString::fromLocal8Bit("击杀目标!!"));
		reloadPlayer.setSource(QUrl::fromLocalFile(":/sound/kill.wav"));
		reloadPlayer.setLoopCount(1);
		reloadPlayer.setVolume(50);
		reloadPlayer.play();//播放音效

	}
	if (dest == this->aiTarget)
	{
		this->aiTarget = NULL;
	}
	dest->~Guitank();
}
void Guitank::pauseAction()
{
	moveTimer->stop();
	reloadTimer->stop();
	reloadPlayer.setMuted(true);
	soundPlayer.setMuted(true);
}

void Guitank::resumeAction()//重生
{
	moveTimer->start();
	reloadTimer->start();
	reloadPlayer.setMuted(false);
	soundPlayer.setMuted(false);
}
void Guitank::reset(int x, int y)//重置
{
	moveTimer->stop();
	reloadTimer->stop();
	hp = 100;
	reloadV = 0;
	reloadTime = 4;
	v = 2;
	this->setGeometry(x, y, this->width(), this->height());

	setDest(x, y);
	moveTimer->start();
	reloadTimer->start();
	reloadPlayer.setMuted(false);
	soundPlayer.setMuted(false);
	this->show();
	//this->nameLabel->show();
}

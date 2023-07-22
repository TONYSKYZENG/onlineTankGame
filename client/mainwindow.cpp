#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <ctime>
#include <QMessageBox>
#include <QHostInfo>
MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	int fontId = QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");
	QString mysh = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont font(mysh);
	this->setFont(font);//设置字体
	ui->setupUi(this);//启动ui界面
	ypos = 0;
	QPalette pal(this->palette());
	ui->label->setScaledContents(true);
	ui->label->setStyleSheet(QString("background: transparent;border-image:url(:/pics/bg.jpg);color:rgb(0,255,0);"));//设置背景
	ui->label->setText("等待进入");
	ui->label->setMouseTracking(true);
	Guitank* newTank = new Guitank(ui->label, this, 48, 48, 128, ypos, "me", 1);
	//newTank->show();
	myTank = newTank;
	tankList.append(myTank);
	//net work
	serverIP = new QHostAddress();
	isOnline = 0;
	srand(time(0));
	ui->sendChat->setEnabled(false);
	ui->pushButton_4->setText(QString::fromLocal8Bit("帮助"));//解决
	//pal.setColor(QPalette::Background, Qt::green); //设置背景黑色
	// this->setAutoFillBackground(true);
	//this->setPalette(pal);
}

MainWindow::~MainWindow()
{
	delete  myTank;
	delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent* event)//点击鼠标进行移动
{
	if (event->button() == Qt::LeftButton)//移动
	{
		if (ui->label->geometry().contains(this->mapFromGlobal(QCursor::pos())))
		{
			QPoint ap = event->globalPos();
			ap = ui->label->mapFromGlobal(ap);//获取点击处坐标
			myTank->setDest(ap.x(), ap.y());
			if (isOnline)//联网
			{
				sendMove(ap.x(), ap.y());//发送实施坐标
			}
		}

	}
	else if (event->button() == Qt::RightButton) {//开火
		int damage = 10 + rand() % 5;//10(基础)+x的爆伤
		//  int damage=10;
		if (myTank->fireShell(damage))
		{
			ui->info->setText(QString::fromLocal8Bit("提示:开火完成!"));
			if (isOnline)
			{
				sendFire(damage);
			}
		}
		else {
			ui->info->setText(QString::fromLocal8Bit("提示:正在装填!"));
		}
	}
}
void MainWindow::wheelEvent(QWheelEvent* event)//转向
{
	if (ui->label->geometry().contains(this->mapFromGlobal(QCursor::pos())))
	{
		int ta;
		if (event->delta() > 0)
		{
			ta = myTank->angle + 1;
		}
		else {
			ta = myTank->angle - 1;
		}
		if (ta > 3)
		{
			ta = 0;
		}
		else if (ta < 0)
		{
			ta = 3;
		}
		myTank->setRotate(ta);
		if (isOnline)
		{
			sendRotate(ta);//发送旋转请求
		}
	}
}
void MainWindow::on_pushButton_clicked()//新AI敌人按钮
{
	int x = rand() % ui->label->height();//生成随机位置
	int y = rand() % ui->label->width();//
	Guitank* newTank = new Guitank(ui->label, this, 48, 48, x, y, "enemy", 0);
	newTank->aiTarget = myTank;//ai敌人的目标是我
	newTank->remoteMask = 1;
	//newTank->show();
	tankList.append(newTank);
	ypos += 40;
	//  tl->setPixmap(QPixmap(":/pics/tank.jpg"));
}
void MainWindow::renewStatus(int hp, int score, int reload)//更新坦克信息
{
	ui->labelHp->setText("HP=" + QString::number(hp));
	ui->labelScore->setText(("SCORE=" + QString::number(score)));
	ui->labelReload->setText(("RELOADING TIME=" + QString::number(reload)));
	if (reload == 0)
	{
		ui->label->setText("Ready");
	}
	else {
		ui->label->setText(QString::number(reload));
	}
}
void MainWindow::renewMessage(QString a)//更新info信息
{
	ui->info->setText(QString::fromLocal8Bit("Information:") + (a));
}
void MainWindow::setMapTittle(QString a)//设置地图标题
{
	ui->label->setText(a);
}
void MainWindow::on_pushButton_2_clicked()//暂停
{

	if (ypos == 0)
	{
		/*for ( int i=0; i!=this->tankList.size(); ++i )
		{
		  Guitank *tank=this->tankList.at(i);
		  tank->pauseAction();
		}*/
		pauseAll();
		ypos = 1;
		ui->pushButton_2->setText(QString::fromLocal8Bit("继续"));
	}
	else {
		/* for ( int i=0; i!=this->tankList.size(); ++i )
		 {
		   Guitank *tank=this->tankList.at(i);
		   tank->resumeAction();
		 }*/
		resumeAll();
		ui->pushButton_2->setText(QString::fromLocal8Bit("暂停"));
		ypos = 0;
	}
}

void MainWindow::on_pushButton_3_clicked()//重生按钮
{
	myTank->hp = 100;
	myTank->reloadTime = 4;
	myTank->reloadV = 0;
	myTank->v = 2;
	tankList.append(myTank);
}

void MainWindow::on_pushButton_4_clicked()//帮助
{
	/* ui->label->setWindowFlags(Qt::Dialog);
	 ui->label->setFocus();
		 ui->label->setScaledContents(true);
		 ui->label->showFullScreen();*/
	QString h = QString::fromLocal8Bit("1.鼠标左键-移动到指定位置,滚轮-旋转,右键-开火(只在装填完成时可用)\r\n");
	h += QString::fromLocal8Bit("2.请时刻关注您的hp,因为炮弹伤害值会在10~15变化\r\n");
	h += QString::fromLocal8Bit("3.联机模式下,暂停继续与重生功能都被服务器管理员控制,请与他/她沟通\r\n");
	h += QString::fromLocal8Bit("4.祝旗开得胜!");
	QMessageBox::information(this, QString::fromLocal8Bit("帮助"), h);
}

void MainWindow::on_pushButton_5_clicked()//远程,on_pushButton_5_clicked()可以不用connect()根据控件打开
{
	lwindow.show();
	lwindow.md = this;
}
void MainWindow::connectToServer(QString ip, QString port, QString name)
{
	int sport = port.toInt();
	ui->info->setText(QString::fromLocal8Bit("尝试连接到") + ip + QString::fromLocal8Bit("端口") + port + QString::fromLocal8Bit("名称") + name);
	if (!serverIP->setAddress(ip))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不能解析的ip address"));
		return;
	}
	userName = name;

	QString con = "ws://" + ip + ":" + port;
	sock = new QWebSocket();
	sock->open(QUrl(con));
	//sock是QWebSocket对象指针，connected()是QWebSocket对象的信号函数名，slotConnected()是接收信号的槽函数名。
	connect(sock, &QWebSocket::connected, this, &MainWindow::slotConnected);
	//检测如果断开
	connect(sock, &QWebSocket::disconnected, this, &MainWindow::slotDisconnected);//connect(sock, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
	//检测如果有新可以读信号
	connect(sock, &QWebSocket::textMessageReceived, this, &MainWindow::dataReceived);
	//connect(sock, &QTcpSocket::textMessageReceived, this, &MainWindow::dataReceived);
	/*
	QTcpSocket* tcpSocket = new QTcpSocket(this);
	tcpSocket->connectToHost(*serverIP, sport);
	if (tcpSocket->waitForConnected()) {
		//连接成功
		QMessageBox::information(this, QString::fromLocal8Bit("连接成功"), QString::fromLocal8Bit("tcpSocket连接到服务器"));
		sock->open(QUrl(con));
	}
	else {
		//连接失败，输出错误信息
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("tcpSocket无法连接到服务器"));
		delete tcpSocket;
		return;
	}
	*/
}
void MainWindow::slotSend()
{

}
void MainWindow::slotConnected()
{
	QString msg = "#UNAME=" + userName;
	int length;
	ui->sendChat->setEnabled(true);
	sock->sendTextMessage(msg);
	myTank->hp = 0;
	myTank->nameTag = userName;
	myTank->setText(userName);//设置玩家名称
	ui->info->setText(QString::fromLocal8Bit("连接成功,等待服务器开战信号"));
	ui->pushButton->setEnabled(false);
	ui->pushButton_2->setEnabled(false);
	ui->pushButton_3->setEnabled(false);
	ui->label->setText("Wait");
	isOnline = 1;
	/*for (int i = 0; i != this->tankList.size(); ++i)
	{
		Guitank* tank = this->tankList.at(i);
		tank->hp = 0;
		tank->close();
		tank->soundPlayer.stop();
		tank->hitPlayer.stop();
		tank->reloadPlayer.stop();

		//this->tankList.removeAt(i);
	 //   tank->onDeath();
	   // tank->~Guitank();
	}*/
	//tankList.clear();
}
void MainWindow::slotDisconnected()
{
	isOnline = 0;
	QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("与服务器连接断开或者服务器不存在"));
	ui->pushButton->setEnabled(true);
	ui->pushButton_2->setEnabled(true);
	ui->pushButton_3->setEnabled(true);
	tankList.clear();
	tankList.append(myTank);
	myTank->reset(myTank->x(), myTank->y());
	ui->sendChat->setEnabled(false);
}
void MainWindow::decodingText(QString a)
{
	QString out = QString::fromLocal8Bit("玩家:");

	if (a.indexOf("#LIST=") == 0)
	{
		int cnt = 0;
		int xd = ui->label->width() / 10;
		int xpos = xd;
		int ypos = 0;
		QString token = a.mid(strlen("#LIST="));
		int getLen = token.indexOf(",");
		while (getLen > 0)
		{
			QString namet = token.left(getLen);
			token = token.mid(getLen + 1);
			getLen = token.indexOf(",");
			printf("%d,%s\r\n", getLen, token.toUtf8().data());
			out += namet + ",";
			xpos += xd;
			if (xpos >= ui->label->width())
			{
				xpos = xd;
				ypos += ui->label->height() / 10;
			}
			if (namet == userName)
			{
				tankList.append(myTank);
				myTank->reset(xpos, ypos);
				//  myTank->nameLabel->show();
			}
			else {
				Guitank* newTank = new Guitank(ui->label, this, 48, 48, xpos, ypos, namet, 0);
				tankList.append(newTank);
				newTank->reset(xpos, ypos);

			}
		}
		ui->info->setText(QString::fromLocal8Bit("开始战斗") + out);
		ui->label->setText(QString::fromLocal8Bit("开始战斗!"));

	}
	else if (a.indexOf("#MOVE=") == 0)
	{   //Guitank *oTank;
		QString token = a.mid(strlen("#MOVE="));
		int getLen = token.indexOf(QString::fromLocal8Bit(","));
		QString namet = token.left(getLen);
		token = token.mid(getLen + 1);
		Guitank* tk = findTank(namet);//name
		if (tk == nullptr || tk == myTank)
		{
			return;
		}
		getLen = token.indexOf(QString::fromLocal8Bit(","));
		QString xt = token.left(getLen);
		token = token.mid(getLen + 1); //x
		getLen = token.indexOf(QString::fromLocal8Bit(","));
		QString yt = token.left(getLen);
		token = token.mid(getLen + 1); //y
		tk->setDest(xt.toInt(), yt.toInt());
	}
	else if (a.indexOf("#ROTATE=") == 0)
	{
		QString token = a.mid(strlen("#ROTATE="));
		int getLen = token.indexOf(",");
		QString namet = token.left(getLen);
		token = token.mid(getLen + 1);
		Guitank* tk = findTank(namet);//name
		if (tk == nullptr || tk == myTank)
		{
			return;
		}
		getLen = token.indexOf(",");
		QString at = token.left(getLen);
		token = token.mid(getLen + 1); //a
		getLen = token.indexOf(",");
		tk->setRotate(at.toInt());
	}
	else if (a.indexOf("#FIRE=") == 0)
	{
		QString token = a.mid(strlen("#FIRE="));
		int getLen = token.indexOf(",");
		QString namet = token.left(getLen);
		token = token.mid(getLen + 1);
		Guitank* tk = findTank(namet);//name
		if (tk == nullptr || tk == myTank)
		{
			return;
		}
		getLen = token.indexOf(",");
		QString da = token.left(getLen);
		getLen = token.indexOf(",");
		QString at = token.left(getLen);
		tk->fireShell(da.toInt());
		ui->info->setText(namet + QString::fromLocal8Bit("开火"));
	}
	else if (a.indexOf("#RESPAWN=") == 0)
	{
		QString token = a.mid(strlen("#RESPAWN="));
		int getLen = token.indexOf(",");
		QString namet = token.left(getLen);
		token = token.mid(getLen + 1);
		Guitank* tk = findTank(namet);//name
		if (tk == nullptr)
		{
			return;
		}
		getLen = token.indexOf(",");
		QString da = token.left(getLen);
		getLen = token.indexOf(",");
		QString at = token.left(getLen);
		if (tk == myTank)
		{
			ui->label->setText(QString::fromLocal8Bit("重生"));
		}
		tk->reset(tk->x(), tk->y());
		ui->info->setText(namet + QString::fromLocal8Bit("被") + QString::fromLocal8Bit("服务器管理员设置重生"));
		ui->sinfo->addItem(namet + QString::fromLocal8Bit("被") + QString::fromLocal8Bit("服务器管理员设置重生"));
	}
	else if (a.indexOf("#KILL=") == 0)
	{
		QString token = a.mid(strlen("#KILL="));
		int getLen = token.indexOf(",");
		QString namet = token.left(getLen);
		token = token.mid(getLen + 1);
		Guitank* tk = findTank(namet);//name
		if (tk == nullptr)
		{
			return;
		}
		getLen = token.indexOf(",");
		QString da = token.left(getLen);
		getLen = token.indexOf(",");
		QString at = token.left(getLen);

		/*if (tk == myTank)
		{
			tk->onDeath(QString::fromLocal8Bit("服务器管理员");
		}*/
		tk->reset(tk->x(), tk->y());
		tk->hp = -1;
		ui->labelHp->setText("HP=" + QString::number(tk->hp));
		ui->info->setText(namet + QString::fromLocal8Bit("被") + QString::fromLocal8Bit("服务器管理员设置死亡"));
		ui->sinfo->addItem(namet + QString::fromLocal8Bit("被") + QString::fromLocal8Bit("服务器管理员设置死亡"));

	}
	else if (a.indexOf("#DIE=") == 0)
	{
		QString token = a.mid(strlen("#DIE="));
		int getLen = token.indexOf(",");
		QString namet = token.left(getLen);
		token = token.mid(getLen + 1);

		getLen = token.indexOf(",");
		QString src = token.left(getLen);
		getLen = token.indexOf(",");
		QString at = token.left(getLen);

		ui->info->setText(namet + QString::fromLocal8Bit("被") + src + QString::fromLocal8Bit("杀死了"));
		ui->sinfo->addItem(namet + QString::fromLocal8Bit("被") + src + QString::fromLocal8Bit("杀死了"));
	}
	else if (a.indexOf("#PAUSE=") == 0)
	{
		pauseAll();
		ui->sinfo->addItem(QString::fromLocal8Bit("服务器管理员设置了暂停"));
	}
	else if (a.indexOf("#RESUME=") == 0)
	{
		resumeAll();
		ui->sinfo->addItem(QString::fromLocal8Bit("服务器管理员设置了继续"));
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
	QString outStr = QString::fromLocal8Bit("#MOVE=");
	outStr += userName + ",";
	outStr += QString::number(x) + QString::fromLocal8Bit(",") + QString::number(y) + QString::fromLocal8Bit(",");
	sock->sendTextMessage(outStr);
}
void MainWindow::sendRotate(int a)
{
	QString outStr = QString::fromLocal8Bit("#ROTATE=");
	outStr += userName + QString::fromLocal8Bit(",");
	outStr += QString::number(a) + QString::fromLocal8Bit(",");
	sock->sendTextMessage(outStr);
}
void MainWindow::sendFire(int damage)
{
	QString outStr = QString::fromLocal8Bit("#FIRE=");
	outStr += userName + ",";
	outStr += QString::number(damage) + QString::fromLocal8Bit(",");
	sock->sendTextMessage(outStr);
}
Guitank* MainWindow::findTank(QString a)
{
	for (int i = 0; i != tankList.count(); i++)
	{
		Guitank* tank = tankList.at(i);
		if (tank->nameTag == a)
		{
			return tank;
		}
	}
	return  nullptr;
}
void MainWindow::selfDie(QString srcName)
{

	renewMessage(QString::fromLocal8Bit("你失败了!!"));
	setMapTittle(QString::fromLocal8Bit("你失败了"));
	if (isOnline)//线上
	{
		QString outStr = "#DIE=";
		outStr += userName + ",";
		outStr += srcName + ",";
		sock->sendTextMessage(outStr);
	}
}

void MainWindow::on_sendChat_clicked()
{
	if (isOnline)
	{

		QString textC = ui->chatEdit->toPlainText();
		if (textC.indexOf("#") >= 0)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不能发送非法字符"));
			return;
		}
		QString send = userName + QString::fromLocal8Bit(" 说:") + textC;
		sock->sendTextMessage(send);
		ui->chatEdit->clear();
	}
}
void MainWindow::resumeAll()
{
	for (int i = 0; i != this->tankList.size(); ++i)
	{
		Guitank* tank = this->tankList.at(i);
		tank->resumeAction();
	}
	ui->label->setText(QString::fromLocal8Bit("继续"));
}
void MainWindow::pauseAll()
{
	for (int i = 0; i != this->tankList.size(); ++i)
	{
		Guitank* tank = this->tankList.at(i);
		tank->pauseAction();
	}
	ui->label->setText(QString::fromLocal8Bit("已暂停"));
}

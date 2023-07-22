#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QFontDatabase>
#include <qmessagebox>
//MainWindow的构造函数
MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	int fontId = QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");//生成字体ID可用于通过removeApplicationFont()再次移除字体或获取字体中包含的族名列表
	QString mysh = QFontDatabase::applicationFontFamilies(fontId).at(0);//返回ID对应的字符族列表
	QFont font(mysh);//根据fontID->生成字体
	this->setFont(font);//设置窗口字体
	ui->setupUi(this);//设置ui
	ui->tport->setText("8888");
	ui->pbBattle->setEnabled(false);
	ui->pbBattle_2->setEnabled(false);
	ui->tankName->show();
	shouldAccept = 1;//是否接受
	isPaused = 0;//是否暂停
}

MainWindow::~MainWindow()
{
	delete ui;//ui是MainWindow*
}

void MainWindow::on_pushButton_clicked()//开启服务器按钮
{
	webserver = new QWebSocketServer(QStringLiteral("tankServer"), QWebSocketServer::NonSecureMode);
	//创建了一个非安全的QWebSocketServer对象(Web服务器)命名为"tankServer"，用于监听WebSocket server(这里相对来说是其他client)的连接(WebSocket)请求
	webserver->listen(QHostAddress::Any, ui->tport->toPlainText().toInt());//监听任何IP,tport->text(指定端口号)的请求
	//nextPendingConnection()函数需要在listen()函数之后调用，因为它只有在有客户端尝试连接到Web服务器时才会返回一个QWebSocket对象，而listen()函数是用于启动Web服务器并开始监听来自客户端的连接请求。
	//因此，只有在Web服务器处于监听状态时，才能使用nextPendingConnection()函数来获取客户端连接。
	connect(webserver, &QWebSocketServer::newConnection, this, &MainWindow::server_newConnection);
	//connect(webserver, SIGNAL(QWebSocketServer::newConnection()), this, SLOT(server_newConnection()));
	//连接
	ui->info->setText("服务器已经打开");
	ui->pbBattle->setEnabled(true);
}
void MainWindow::server_newConnection()
{
	ui->sinfo->addItem("有新连接");
	if (!shouldAccept)//如果Accept为0，即此时server不接受连接请求
	{
		return;
	}
	QWebSocket* pSocket = webserver->nextPendingConnection();
	//当有客户端尝试连接到Web服务器时，它将返回一个QWebSocket对象pSocket，该对象表示该连接。
	//通过使用该对象，Web服务器可以与客户端进行通信并交换数据。
	sockList.append(pSocket);//加入连接列表
	pSocket->sendTextMessage("欢迎来到战场");//发送消息
	connect(pSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(sock_receiveText(QString)));//显示接收的信息
}

void MainWindow::on_pushButton_2_clicked()//群发消息按钮
{
	QString text = ui->textEdit->toPlainText();//获取编辑框中的纯文本你内容
	for (int i = 0; i < sockList.count(); i++)
	{
		QWebSocket* pSocket = sockList.at(i);
		pSocket->sendTextMessage(("服务器管理员:") + text);//群发内容
	}
	ui->sinfo->addItem(("我说:") + text);//管理员视角发送
	ui->textEdit->clear();
}
void MainWindow::sock_receiveText(QString msg)//接受并转发信息
{
	int a = decodingText(msg);//解码信息

	if (a != -1)//之前出现过
	{
		for (int i = 0; i < sockList.count(); i++)
		{
			QWebSocket* pSocket = sockList.at(i);
			pSocket->sendTextMessage(msg);//群发消息给每一个人
		}
		//    PortLineEdit->setText(msg);
	}
	if (msg.indexOf("#") < 0 || msg.indexOf("DIE") >= 0)//不包含#或包含DIE
	{
		ui->sinfo->addItem(msg);
		//sinfo是一个QListWidget控件，用于显示服务器端接收到的所有消息，包括新用户连接、普通消息和断开连接等。
		//它是一个可滚动的列表框，每条消息都以单独的项的形式显示在列表中
	}
	else
	{
		ui->info->setText(("接收") + msg);
		//info是一个QLabel控件，用于显示当前客户端接收到的最新消息。它只显示最后一条消息
	}
}
int MainWindow::decodingText(QString a)
{
	int endPos = a.indexOf("@");//endPos代表a中"@"第一次出现的位置，这个位置将被用来截取消息中的一部分内容。
	if (a.indexOf("#UNAME=") == 0)
		//使用indexOf()函数查找字符串a中是否包含子字符串#UNAME=，并检查它是否在字符串的开头
		//如果是，则表示接收到了一个新用户的连接请求，并且包含了该用户的用户名。
	{
		QString namet = a.mid(strlen("#UNAME="), endPos);//截取新用户的用户名(#UNAME=XX@),其中XX是用户名
		//  namet=namet.left(endPos-strlen("#UNAME="));同理

		if (!isFind(a))//isFind检查名字列表中是否有a
		{
			ui->tankName->addItem(namet);
			nameList.append(namet);
			ui->tankName->show();
		}
		return -1;//有a了就退出
	}
	return 0;//没有找到#UNAME就退出
}
int MainWindow::isFind(QString a)//查找列表中是否有a
{
	for (int i = 0; i != this->nameList.size(); ++i)
	{
		if (nameList.at(i) == a)//nameList[i]是否等于a?
		{
			return  1;
		}
	}
	return 0;
}
void MainWindow::sendStart()//群发信息，发送一个带所有client的用户列表信息
{
	QString sendStr = "#LIST=";
	for (int i = 0; i != this->nameList.size(); ++i)
	{
		sendStr += nameList.at(i);
		sendStr += ",";
	}
	for (int i = 0; i < sockList.count(); i++)
	{
		QWebSocket* pSocket = sockList.at(i);
		pSocket->sendTextMessage(sendStr);
	}
}

void MainWindow::on_pbBattle_clicked()//开战按钮
{
	sendStart();//发送队列信息
	ui->pbBattle->setEnabled(false);//已经开战
	ui->pbBattle_2->setEnabled(true);//已经开战，只能暂停
	//也可以用radio_button
}

void MainWindow::on_pushButton_3_clicked()//重生按钮
{
	QString name = ui->tankName->currentItem()->text();
	//使用currentItem()函数获取名为tankName的QListWidget控件中当前选中的项
	//并使用text()函数获取该项的文本内容，即要复活的坦克名
	sendRespawn(name);
}
void MainWindow::sendRespawn(QString name)//重生
{
	QString sendStr = "#RESPAWN=";
	sendStr += name + ",";
	for (int i = 0; i < sockList.count(); i++)
	{
		QWebSocket* pSocket = sockList.at(i);
		pSocket->sendTextMessage(sendStr);
	}
	ui->sinfo->addItem(("复活") + name);
}

void MainWindow::sendDie(QString name)//死亡
{
	QString sendStr = "#KILL=";
	sendStr += name + ",";
	for (int i = 0; i < sockList.count(); i++)
	{
		QWebSocket* pSocket = sockList.at(i);
		pSocket->sendTextMessage(sendStr);
	}
	ui->sinfo->addItem("杀死了" + name);
}
void MainWindow::sendPause()//暂停
{
	QString sendStr = "#PAUSE=";

	for (int i = 0; i < sockList.count(); i++)
	{
		QWebSocket* pSocket = sockList.at(i);
		pSocket->sendTextMessage(sendStr);
	}
}

void MainWindow::sendResume()//恢复暂停
{
	QString sendStr = "#RESUME=";

	for (int i = 0; i < sockList.count(); i++)
	{
		QWebSocket* pSocket = sockList.at(i);
		pSocket->sendTextMessage(sendStr);
	}
}
void MainWindow::on_pushButton_4_clicked()//死亡按钮
{
	QString name = ui->tankName->currentItem()->text();
	sendDie(name);
}

void MainWindow::on_pbBattle_2_clicked()//停战|继续按钮
{
	if (!isPaused)
	{
		sendPause();
		ui->pbBattle_2->setText("战斗继续");
		isPaused = 1;
	}
	else {
		sendResume();
		ui->pbBattle_2->setText("战斗暂停");
		isPaused = 0;
	}
}

void MainWindow::on_pushButton_5_clicked()//消息记录清空按钮
{
	ui->sinfo->clear();
}

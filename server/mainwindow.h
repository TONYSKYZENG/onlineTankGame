#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QWebSocketServer>
namespace Ui {
	class MainWindow;//声明Ui命名空间，启动Ui即为启动MainWindow的一系列操作
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	QWebSocketServer* webserver;//定义webserver端
	QList <QWebSocket*> sockList;//webSocket指针队列
	QList <QString>nameList;//名字队列
	explicit MainWindow(QWidget* parent = nullptr);//explicit限定了MainWindow只能被显式的构造
	~MainWindow();//默认析构函数
	int decodingText(QString a);//解码文本
	int isFind(QString a);
	void sendStart(void);
	void sendRespawn(QString name);
	void sendDie(QString name);
	void sendPause(void);
	void sendResume(void);
	int shouldAccept, isPaused;
	//槽函数
private slots:
	void server_newConnection();//服务端连接请求
	void sock_receiveText(QString msg);//接受信息
	void on_pushButton_clicked(); //开启服务器按钮
	void on_pushButton_2_clicked();//群发消息按钮
	void on_pushButton_3_clicked();//重生按钮
	void on_pushButton_4_clicked();//死亡按钮
	void on_pushButton_5_clicked();//消息记录清空按钮

	void on_pbBattle_clicked();//开战按钮
	void on_pbBattle_2_clicked();//停战按钮


private:
	Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H

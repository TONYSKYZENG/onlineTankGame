#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QTimer>
#include <QtMultimedia>
#include <QSoundEffect>
#include <QMainWindow>
#include <QHostAddress>
#include <QWebSocket>
#include <QFont>
#include <QFontDatabase>
#include <QTcpSocket>
//提前声明,GuiShell中涉及
class Guitank;
class MainWindow;
//坦克子弹类
class Guishell : public QLabel
{
	Q_OBJECT
public:
	Guishell(QWidget* parent, MainWindow* mw, int w, int h, int x, int y, int sdamage);
	~Guishell();
	int destX, destY;
	int v, damage;
	int angle;
	Guitank* mytank;
	QWidget* myParent;
	MainWindow* myWindow;
	void setDest(int dx, int dy);
private:
	QTimer* moveTimer;
	QSoundEffect soundPlayer;
	int colideWith(void);
private slots:
	void onMoveTimer();
};
#include <QDialog>

namespace Ui {
	class login;
	class MainWindow;
}
//登录类(处理Socket,tcp等连接)
class login : public QDialog
{
	Q_OBJECT

public:
	explicit login(QWidget* parent = nullptr);
	~login();
	MainWindow* md;
private slots:
	void on_pushButton_clicked();

private:
	Ui::login* ui;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	int ypos;
	Guitank* myTank;
	QList <Guitank*> tankList;
	void renewStatus(int hp, int score, int reload);
	void renewMessage(QString a);
	void setMapTittle(QString a);
	login lwindow;
	//net work:
	QHostAddress* serverIP;
	QString userName;
	QWebSocket* sock;
	//  QTcpSocket *tcpSocket;
	void connectToServer(QString ip, QString port, QString name);
	char isOnline;
	void decodingText(QString a);
	void sendMove(int x, int y);
	void sendRotate(int a);
	void sendFire(int damage);
	void selfDie(QString srcName);
	Guitank* findTank(QString a);
	void resumeAll(void);
	void pauseAll(void);
private slots:
	void on_pushButton_clicked();//新AI敌人
	void on_pushButton_2_clicked();//暂停
	void on_pushButton_3_clicked();//重生
	void on_pushButton_4_clicked();//帮助
	void on_pushButton_5_clicked();//远程
	//net
	void slotConnected();
	void slotDisconnected();
	void dataReceived(QString msg);
	void slotSend();
	void on_sendChat_clicked();//发送消息
protected:
	void mousePressEvent(QMouseEvent* event);//点击鼠标实现坐标移动
	//void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent* event);

private:
	Ui::MainWindow* ui;

};
//坦克类
class Guitank : public QLabel
{
	Q_OBJECT
public:
	Guitank(QWidget* parent, MainWindow* myw, int w, int h, int x, int y, QString a, int ifself);
	~Guitank();
	QString nameTag;//坦克名
	int hp;//生命值
	int destX, destY;
	int v, range, reloadTime, reloadV;
	int angle;//角度,涉及旋转
	int score;//得分
	int self;//
	int remoteMask;
	int shellSize, policy;

	Guishell* myShell;
	Guitank* aiTarget;//ai敌人
	QWidget* screen;//
	MainWindow* myWindow;
	void setDest(int dx, int dy);
	void setRotate(int an);//旋转
	int fireShell(void);
	int fireShell(int damage);
	void forcedFireShell(void);
	void onHitted(int damage, int vol, Guitank* src);
	void onHitOther(Guitank* dest);
	void onKillOther(Guitank* dest);
	void onDeath(QString srcName);
	void attackTargetAi(void);
	void attackP1(void);
	void attackP2(void);
	void attackP3(void);
	void pauseAction(void);
	void resumeAction(void);
	void reset(int x, int y);

	QSoundEffect soundPlayer;
	QSoundEffect reloadPlayer, hitPlayer;
private:
	QTimer* moveTimer;
	QTimer* reloadTimer;

	// int colideWith(void);
private slots:
	void onMoveTimer();
	void onReloadTimer();
};


#endif // MAINWINDOW_H

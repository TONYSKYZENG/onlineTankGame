#include "mainwindow.h"
#include "ui_login.h"
#include <QMessageBox>
login::login(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::login)
{
	int fontId = QFontDatabase::addApplicationFont(":/ttf/catoon.ttf");
	QString mysh = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont font(mysh);
	this->setFont(font);
	ui->setupUi(this);
	ui->TIP->setText("192.168.111.1");
	ui->TPORT->setText("8888");
	ui->TNAME->setText("tank1");
}

login::~login()
{
	delete ui;
}

void login::on_pushButton_clicked()
{
	QString ip, port, name;
	ip = ui->TIP->toPlainText();
	port = ui->TPORT->toPlainText();
	name = ui->TNAME->toPlainText();
	if (name.indexOf("#") >= 0 || name.indexOf("@") >= 0)
		//如果name中有#且有@
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不支持的用户名"));
		return;
	}
	if (name.indexOf("服务器管理员") >= 0)//如果name中有服务器管理员
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不支持的用户名"));
		return;
	}
	md->connectToServer(ip, port, name);//连接server端
	this->close();
}

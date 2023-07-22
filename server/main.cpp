#include "mainwindow.h"
#include <QApplication>
//此为服务器server(管理员)的文件
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

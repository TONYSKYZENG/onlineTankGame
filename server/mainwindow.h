#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QWebSocketServer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWebSocketServer* webserver;
    QList <QWebSocket*> sockList;
    QList <QString>nameList;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int decodingText(QString a);
    int isFind(QString a);
    void sendStart(void);
    void sendRespawn(QString name);
    void sendDie(QString name);
    void sendPause(void);
    void sendResume(void);
    int shouldAccept,isPaused;
private slots:
    void on_pushButton_clicked();
    void server_newConnection();
    void sock_receiveText(QString msg);
    void on_pushButton_2_clicked();

    void on_pbBattle_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pbBattle_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

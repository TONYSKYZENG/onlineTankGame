#ifndef GUISHELL_H
#define GUISHELL_H
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QtMultimedia>
#include <QSoundEffect>
class Guitank;
class MainWindow;
namespace Ui {
class MainWindow;
}
class Guishell: public QLabel
{
    Q_OBJECT
public:
   Guishell(QWidget *parent,MainWindow *mw,int w,int h,int x,int y);
    ~Guishell();
   int destX,destY;
   int v;
   int angle;
   Guitank *mytank;
   QWidget *myParent;
   MainWindow *myWindow;
   void setDest(int dx,int dy);
private:
      QTimer *moveTimer;
      QSoundEffect soundPlayer;
     void colideWith(void);
private slots:
    void onMoveTimer();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int ypos;
    Guitank *myTank;
    QList <Guitank *> tankList;
private slots:
    void on_pushButton_clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;

};
class Guitank: public QLabel
{
    Q_OBJECT
public:
   Guitank(QWidget *parent,MainWindow *myw,int w,int h,int x,int y,QString a,int ifself);
    ~Guitank();
   int hp;
   int destX,destY;
   int v,range,reloadTime,reloadV;
   int angle;
   int score;
   int self;
   Guishell *myShell;
    QWidget *screen;
    MainWindow *myWindow;
   void setDest(int dx,int dy);
   void setRotate(int an);
   int fireShell(void);
   void onHitted(int damage,int vol);
private:
      QTimer *moveTimer;
      QTimer *reloadTimer;
      QSoundEffect soundPlayer;
      QSoundEffect reloadPlayer,hitPlayer;
private slots:
    void onMoveTimer();
    void onReloadTimer();
};

#endif // GUISHELL_H

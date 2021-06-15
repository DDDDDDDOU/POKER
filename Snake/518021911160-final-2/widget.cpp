#include "widget.h"
#include <QDebug>
#include "widget2.h"
#include <QFont>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(1280,800);                         //decide the size of the welcome window
    this->setWindowTitle("518021911160_贪吃蛇");    //decide the title of the welcome window

   // event = new QMouseEvent(this);

    this->setMouseTracking(true);
    QPalette Palette;
    Palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/Widget/img/background1.JPG")));
                                                   //choose the background picture of the welcome window

    this->setPalette((Palette));


    Start = new QPushButton(this);
    Quit  = new QPushButton(this);
    DualStart = new QPushButton(this);

    StartL = new QLabel(this);
    QuitL = new QLabel(this);
    DualStartL = new QLabel(this);

    StartLabel.setFamily("NSimSun");
    StartLabel.setPointSize(25); //字号


    DualStartLabel.setFamily("NSimSun");
    DualStartLabel.setPointSize(25);

    QuitLable.setFamily("NSimSun");
    QuitLable.setPointSize(25);

    StartL -> setText("单人游戏");
    QuitL -> setText("退出游戏");
    DualStartL -> setText("双人对抗");

    StartL->setStyleSheet("color:green;");
    QuitL ->setStyleSheet("color:red;");
    DualStartL ->setStyleSheet("color:blue;");

    StartL->setGeometry(540,330,100,60);
    QuitL->setGeometry(540,410,100,60);
    DualStartL->setGeometry(540,490,100,60);

    StartL->setFont(StartLabel);
    QuitL->setFont(QuitLable);
    DualStartL->setFont(DualStartLabel);

    Start->setIconSize(QSize(100,60));       //decide the size of icons
    Quit->setIconSize(QSize(100,60));
    DualStart->setIconSize(QSize(100,60));

    Start->setGeometry(640,330,100,60);      //decide the point of icons
    Quit->setGeometry(640,410,100,60);
    DualStart->setGeometry(640,490,100,60);
    Start->setIcon(QIcon(":/new/Widget/img/tubiao.png"));
    DualStart->setIcon(QIcon(":/new/Widget/img/tubiao3.png"));
    Quit->setIcon(QIcon(":/new/Widget/img/tubiao2.png"));


    Start->setFlat(1);                      //icon is invisiable
    Quit->setFlat(1);
    DualStart->setFlat(1);

    QuitBox = new QMessageBox;              //a message box

    connect(Start,SIGNAL(clicked(bool)),SLOT(ClickToStart()));
    connect(Quit,SIGNAL(clicked(bool)),SLOT(ClickToQuit()));       //connect the icons with particular functions
    connect(DualStart,SIGNAL(clicked(bool)),SLOT(ClickToDualStart()));

}

Widget::~Widget(){

}


void Widget::ClickToStart(){
   widget2=new Widget2(false,this);
   widget2->show();                      //to activate the seconde window-----the game window
}

void Widget::ClickToDualStart(){
    widget2 = new Widget2(true,this);
    widget2->show();
}

void Widget::ClickToQuit(){
    if(QMessageBox::Yes==QMessageBox::question(this,"Tips:","Leave the game?",QMessageBox::Yes|QMessageBox::No)){
        delete this;
        exit(0);
    }
}

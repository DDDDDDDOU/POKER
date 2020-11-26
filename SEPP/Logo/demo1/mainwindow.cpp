#include "mainwindow.h"
#include <constants.h>
#include <QtGlobal>
#include <qdebug.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
//        QRect screenRect = QApplication::desktop()->screenGeometry();
    this->setWindowTitle("My PCLogo");
    this->setFixedSize(window.winWidth,window.winHeight);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->showFullScreen(); //全屏

    solo  =   new QPushButton(this);
    pk     =   new QPushButton(this);

//    this->solo->setGeometry(3*window.winWidth/10,window.winHeight/5,2*window.winWidth/5,window.winHeight/10);
    pk    ->  setGeometry(3*window.winWidth/10,4*window.winHeight/10,4*window.winWidth/10,window.winHeight/10);
    solo ->  setGeometry(0,0,100,100);

    pk    ->   setText("PK");
    solo ->   setText("SOLO");
    qDebug() <<"12";





}

MainWindow::~MainWindow()
{
}


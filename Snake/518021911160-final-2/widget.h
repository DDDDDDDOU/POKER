#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "widget2.h"
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    QPushButton *Start;
    QPushButton *DualStart;
    QPushButton *Quit;

    QMouseEvent *event;

    QFont StartLabel;
    QFont DualStartLabel;
    QFont QuitLable;

    QLabel *StartL;
    QLabel *DualStartL;
    QLabel *QuitL;


    QMessageBox *QuitBox;
    Widget2  *widget2;
    ~Widget();

private slots:


    void ClickToStart();
    void ClickToDualStart();
    void ClickToQuit();

};

#endif // WIDGET_H

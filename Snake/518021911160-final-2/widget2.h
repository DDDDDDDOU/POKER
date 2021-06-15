
#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QStyle>


#define LineNum 300  //decide the number of lines and rows
#define RowNum  400

class Widget2 : public QWidget {
     Q_OBJECT
public:
    int Timeleft;
    int Timeleft2;
    int Bunustime;

    explicit Widget2 (bool Dualplay,QWidget *parent = 0);
    void paintEvent (QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);

    QPushButton *Start;
    QPushButton *Quit;
    QPushButton *AI;

    QLabel *ScoreLabel;
    QLabel *ScoreLabel2;//
    QLabel *LevelLabel;
    QLabel *LevelLabel2;//
    QLabel *TimeLabel;
    QLabel *TimeLabel2;//
    QLabel *TimeLeft;
    QLabel *TimeLeft2;//
    QLabel *ScoreNum;
    QLabel *ScoreNum2;//
    QLabel *LevelNum;
    QLabel *LevelNum2;
    QLabel *Player1;
    QLabel *Player2;
    QLabel *BunusType;
    QTimer *Timer;
    QTimer *Timer2;
    QTimer *Timer3;
    QTimer *extraTimer;
    QTimer *bunusTimer;
    QFont   ft;
    QLabel *StartL;
    QLabel *QuitL;


    int Snake[100][2];      //To save the point of every piece of the snake
    int PreSnake[100][2];   //This is a copy of the Snake
    int Snake2[100][2];     //Snake for player2
    int PreSnake2[100][2];


    int Wall[150][2];
    int front1,rear1,front2,rear2;

    int Direction;          //To save the direction of the snake. 1 for up ,2 for down, 3 for left, 4 for right
    int Direction2;

    QButtonGroup *ButtonGroup; //Define a buttongroup for up,down,left and right

    int Corex;
    int Corey;              //To save the point of the core

    int Cores[100][2];

    int extraCorex;
    int extraCorey;          // Another core;

    int Bunuscorex=-1;
    int Bunuscorey=-1;        // For bunus core

    int BodyCount;          //To save the number of body
    int BodyCount2;

    int Score;
    int Score2;

    int Difficulty;          //Difficulty is the speed pf snake
    int Difficulty2;

    int  GameOver=0;
    bool notBite;           //If the snake bites itself or go out of the window ,return 0;


    bool DualPlay;          //Dualplay  return 1;
    bool PlayState;
    bool AImode=0;

    int Bunus;

private:
    QPalette *Palette;
signals:


public slots:
    void Timeout();
    void Timeout2();
    void SetDirection(int n);
    void CheckGameOver();
    void StartPush();
    void PausePush();
    void QuitPush();
    void setFood();
    void settime();
    void setWall();   //生成墙壁
    void AISnake();
    void AITimeout();
    void clearCore();





};













































#endif // WIDGET2_H


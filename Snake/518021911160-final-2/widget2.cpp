#include <QWidget>
#include <widget.h>
#include <widget2.h>
#include <QPainter>
#include <QTime>
#include <QtGlobal>
#include <QDebug>
#include <ctime>
#include <iostream>
#include <QObject>
#include <QDebug>
#include <QTimer>
using namespace std;

Widget2::Widget2(bool Dualplay,QWidget *parent):QWidget (parent){

    DualPlay=Dualplay;
    PlayState=false;
    Score=0;
    rear1=front1=front2=rear2=0;
    Difficulty=1;
    Timeleft=100;
    front1=rear1=0;
    AImode=0;
    Bunustime=10;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    this->setAutoFillBackground(true);
    this->resize(1280,800);
    this->setWindowTitle("518021911160_贪吃蛇");

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/Widget/img/background1.JPG").scaled(this->size())));    //Choose the background of the window2
    this->setPalette(palette);


    Start       = new QPushButton  (this);
    Quit        = new QPushButton  (this);

    Start -> setFlat(1);
    Quit  -> setFlat(1);

    ButtonGroup = new QButtonGroup (this);
    connect(ButtonGroup,SIGNAL(buttonClicked(int)),this,SLOT(SetDirection(int)));

    Start->setIconSize(QSize(100,60));
    Quit ->setIconSize(QSize(100,60));
    Start->setGeometry(1100,400,100,60);
    Quit ->setGeometry(1100,480,100,60);


    if(!Dualplay){
        Start->setIcon(QIcon(":/new/Widget/img/tubiao.png"));
    }
    else Start->setIcon(QIcon(":/new/Widget/img/tubiao3.png"));

    Quit->setIcon(QIcon(":/new/Widget/img/tubiao2.png"));        //choose picture for "Start" and "Quit"

    ft.setPointSize(25);


    if(!Dualplay){
    AI  = new QPushButton(this);
    AI->setIconSize(QSize(100,60));
    AI->setGeometry(1050,320,100,60);
    AI->setFlat(0);
    AI->setText("AI");
    AI->setFont(ft);

    }

    ScoreLabel = new QLabel(this);
    LevelLabel = new QLabel(this);
    ScoreNum   = new QLabel(this);
    LevelNum   = new QLabel(this);
    TimeLabel  = new QLabel(this);
    TimeLeft   = new QLabel(this);
    StartL     = new QLabel(this);
    QuitL      = new QLabel(this);
    Player1    = new QLabel(this);
    BunusType  = new QLabel(this);




    StartL -> setText("开始游戏");
    StartL -> setFont(ft);
    StartL -> setGeometry(1000,400,100,60);
    StartL -> setStyleSheet("color:green;");

    QuitL  -> setText("退出游戏");
    QuitL  -> setFont(ft);
    QuitL  -> setGeometry(1000,480,100,60);
    QuitL  -> setStyleSheet("color:red;");

    BunusType -> setText("");
    BunusType -> setFont(ft);
    BunusType -> setGeometry(1040,700,100,60);
    BunusType -> setStyleSheet("color:pink;");





    ScoreLabel -> setGeometry(1025,40,200,90);
    LevelLabel -> setGeometry(1025,80,200,90);
    ScoreNum   -> setGeometry(1115,40,120,90);
    LevelNum   -> setGeometry(1115,80,120,90);            //Give place to the Labels
    TimeLabel  -> setGeometry(1025,120,200,90);
    TimeLeft   -> setGeometry(1115,120,120,90);
    Player1    -> setGeometry(980, 10,100,60);



    ScoreLabel -> setFont(ft);
    LevelLabel -> setFont(ft);
    TimeLabel  -> setFont(ft);
    ScoreNum   -> setFont(ft);
    LevelNum   -> setFont(ft);
    TimeLeft   -> setFont(ft);
    Player1    -> setFont(ft);

    ScoreLabel -> setText("Score:             分");
    LevelLabel -> setText("Level:             级");
    TimeLabel  -> setText("Time :             秒");
    Player1    -> setText("Player 1 :");
    ScoreNum  ->setText(QString::number(Score));
    LevelNum  ->setText(QString::number(Difficulty)); //Set the text of labels
    TimeLeft  ->setText(QString::number(Timeleft));

    Timer      = new QTimer(this);                              //define a Timer
    Timer2     = new QTimer(this);
    bunusTimer = new QTimer(this);


    connect(Timer2 ,SIGNAL(timeout()),this,SLOT(settime()));
    connect(Timer  ,SIGNAL(timeout()),this,SLOT(Timeout()));
    connect(Start  ,SIGNAL(clicked(bool)),this,SLOT(StartPush()));
    connect(Quit   ,SIGNAL(clicked(bool)),this,SLOT(QuitPush()));
    connect(AI     ,SIGNAL(clicked(bool)),this,SLOT(AISnake()));
    connect(bunusTimer,SIGNAL(timeout()),this,SLOT(clearCore()));

    this->grabKeyboard();                                  //grab the event from keyboard
    Snake[0][0]=((qrand()%65)*10+150);
    Snake[0][1]=((qrand()%50)*10+150);                //set the place of snake

    Direction=qrand()%4+1;                                    //set the direction
    setFood();
    notBite=true;
    BodyCount=1;                                           //include head and a body
    switch (Direction) {
    case 1:Snake[1][0]=Snake[0][0];
           Snake[1][1]=Snake[0][1]+10; break;
    case 2:Snake[1][0]=Snake[0][0];
           Snake[1][1]=Snake[0][1]-10; break;
    case 3:Snake[1][0]=Snake[0][0]+10;
           Snake[1][1]=Snake[0][1]; break;
    case 4:Snake[1][0]=Snake[0][0]-10;
           Snake[1][1]=Snake[0][1]; break;

    }




    if(Dualplay==true){

        Score2 = 0;
        Difficulty2 = 0;
        Timeleft2 = 100;


        //初始化墙壁数组

        StartL  ->   setStyleSheet("color:blue;");

        ScoreLabel2 = new QLabel(this);
        ScoreNum2   = new QLabel(this);
        LevelLabel2 = new QLabel(this);
        LevelNum2   = new QLabel(this);
        TimeLabel2  = new QLabel(this);
        TimeLeft2   = new QLabel(this);
        Player2     = new QLabel(this);

        ScoreLabel2 -> setGeometry(1025,200,200,90);
        ScoreNum2   -> setGeometry(1115,200,120,90);
        LevelLabel2 -> setGeometry(1025,240,200,90);
        LevelNum2   -> setGeometry(1115,240,120,90);
        TimeLabel2  -> setGeometry(1025,280,200,90);
        TimeLeft2   -> setGeometry(1115,280,120,90);
        Player2     -> setGeometry(980 ,170,100,60);

        ScoreLabel2 -> setFont(ft);
        ScoreNum2   -> setFont(ft);
        LevelLabel2 -> setFont(ft);
        LevelNum2   -> setFont(ft);
        TimeLabel2  -> setFont(ft);
        TimeLeft2   -> setFont(ft);
        Player2     -> setFont(ft);

        ScoreLabel2  -> setText("Score:             分");
        LevelLabel2  -> setText("Level:             级");
        TimeLabel2   -> setText("Time :             秒" );
        Player2      -> setText("Palyer 2 :");
        ScoreNum2    -> setText(QString::number(Score2));
        LevelNum2    -> setText(QString::number(Difficulty2));
        TimeLeft2    -> setText(QString::number(Timeleft2));

        Timer3 = new QTimer(this);

        connect(Timer3,SIGNAL(timeout()),this,SLOT(Timeout2()));

        do{
            Snake2[0][0]=((qrand()%65)*10+150);
            Snake2[0][1]=((qrand()%50)*10+150);
        }while(Snake2[0][0]-Snake[0][0]<=50||Snake2[0][1]-Snake[0][1]<=50);

        Direction2 = qrand()%4+1;

        switch (Direction2) {
        case 1:Snake2[1][0]=Snake2[0][0];
               Snake2[1][1]=Snake2[0][1]+10; break;
        case 2:Snake2[1][0]=Snake2[0][0];
               Snake2[1][1]=Snake2[0][1]-10; break;
        case 3:Snake2[1][0]=Snake2[0][0]+10;
               Snake2[1][1]=Snake2[0][1]; break;
        case 4:Snake2[1][0]=Snake2[0][0]-10;
               Snake2[1][1]=Snake2[0][1]; break;
        }

        BodyCount2=1;


    }

    this->repaint();

}

void Widget2::settime(){
    Timeleft-=1;
   // if(Bunustime==0){
     //   Bunustime=10;
      //  Bunus=qrand()%3+1;

    Bunustime--;

    TimeLeft->setText(QString::number(Timeleft));
    if(DualPlay){
    Timeleft2-=1;
    TimeLeft2->setText(QString::number(Timeleft2));
    }
    Timer2->start(1000);
}


void Widget2::setFood(){
    if(Bunus!=3){
    Corex=(qrand()%92)*10;
    Corey=(qrand()%78)*10;
    Cores[0][0]=-1;
    }


}


void Widget2::setWall(){

    int direction = qrand()%2+1;
    int n         = qrand()%10+5;
    front1        = (front1+1)%150;

    if(direction==1){
        do{
            Wall[front1][0]=(qrand()%92)*10;
        }while(Wall[front1][0]-Snake[0][0]>=0&&Wall[front1][0]-Snake[0][0]<=50);

     Wall[front1][1]=(qrand()%68)*10;

     for( int i = 0 ; i < n-1 ; ++i ){
             front1 = (front1+1)%150;
             Wall[front1][0]=Wall[(front1+149)%150][0];
             Wall[front1][1]=Wall[(front1+149)%150][1]+10;
     }

    }
    if(direction==2){
        do{
            Wall[front1][1]=(qrand()%78)*10;
        }while(Wall[front1][1]-Snake[0][1]>=0&&Wall[front1][1]-Snake[0][1]<=50);
     Wall[front1][0]=(qrand()%82)*10;
     for( int i = 0 ; i < n-1 ; ++i ){
             front1 = (front1+1)%50;
             Wall[front1][1]=Wall[(front1+149)%150][1];
             Wall[front1][0]=Wall[(front1+149)%150][0]+10;
     }
    }

    if((front1-rear1+150)%150>=140) {
        rear1=(rear1+n)%150;
    }
}



void Widget2::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Up:if(Direction != 2) Direction=1; break;
    case Qt::Key_Down:if(Direction != 1) Direction=2; break;
    case Qt::Key_Left:if(Direction != 4) Direction=3; break;
    case Qt::Key_Right:if(Direction != 3) Direction=4; break;
    case Qt::Key_W:if(Direction2!=2) Direction2=1;break;
    case Qt::Key_S:if(Direction2!=1) Direction2=2;break;
    case Qt::Key_A:if(Direction2!=4) Direction2=3;break;
    case Qt::Key_D:if(Direction2!=3) Direction2=4;break;
    case Qt::Key_Space: if(PlayState) PausePush();
        else StartPush();break;
    default: break;
    }
}

void Widget2::paintEvent(QPaintEvent *){
    QPainter Painter(this);

    if(qrand()%200==0&&Bunuscorex==-1&&Bunuscorey==-1){
        Bunuscorex=(qrand()%92)*10;
        Bunuscorey=(qrand()%78)*10;

    }

    if(qrand()%150==0&&!AImode&&Bunus!=2) setWall();

    if(Snake[0][0]<0||Snake[0][0]>910||Snake[0][1]<0||Snake[0][1]>770) return;

    Painter.setPen(QPen(Qt::blue,1,Qt::SolidLine));
    Painter.setBrush(QBrush(Qt::gray,Qt::SolidPattern));
    for(int i=BodyCount;i>=0;--i) Painter.drawEllipse(Snake[i][0],Snake[i][1],10,10);
    Painter.setBrush(QBrush(Qt::darkYellow,Qt::SolidPattern));
    if(DualPlay) {for(int i=BodyCount2;i>=0;--i) Painter.drawEllipse(Snake2[i][0],Snake2[i][1],10,10);}

    Painter.setPen(QPen(Qt::red,3,Qt::SolidLine));
    Painter.setBrush(Qt::NoBrush);
    Painter.drawEllipse(Corex,Corey,10,10);
    if(Cores[0][0]!=-1){
        for(int i =0;i<100;++i) {if(Cores[i][0]!=-1 )Painter.drawEllipse(Cores[i][0],Cores[i][1],10,10);}
    }

    if(Bunuscorex!=-1&&Bunuscorey!=-1) {
        Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        Painter.drawEllipse(Bunuscorex,Bunuscorey,10,10);
    }
    if(!AImode){
    Painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    Painter.setPen(QPen(Qt::blue,1,Qt::SolidLine));
    if(front2!=front1)
        front2=(front2+1)%150;
    if(rear2!=rear1)
        rear2=(rear2+1)%150;
    if(rear2!=front2){

        for(int i = (rear2+1)%150 ;(front2+150-i)%150>0 ; i = (i+1)%150)
        Painter.drawRect(Wall[i][0],Wall[i][1],10,10);
        Painter.drawRect(Wall[front2][0],Wall[front2][1],10,10);
    }
        }
    Painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    Painter.setBrush(Qt::NoBrush);

    Painter.drawLine(0,0,0,920);
    Painter.drawLine(0,780,920,780);
    Painter.drawLine(920,0,920,780);

}

void Widget2::Timeout(){


    switch (Bunus) {
case 1 :BunusType -> setText("加速！");break;
case 2 :BunusType -> setText("清除墙壁");break;
case 3 :BunusType -> setText("大量果实");break;
    default: BunusType ->setText(""); break;

    }


    if(Bunus==3){
        for(int i=0;i<100;++i){
            if(Snake[0][0]==Cores[i][0]&&Snake[0][1]==Cores[i][1]){
                Cores[i][0]=-1;
                Cores[i][1]=-1;
                BodyCount++;
                Score+=Difficulty;
                Difficulty=BodyCount/5+1;
                ScoreNum->setText(QString::number(Score));
                LevelNum->setText(QString::number(Difficulty));
                Timer->start(210-20*Difficulty>30? 150-10*Difficulty : 90/(Difficulty)+30);
                break;
            }
        }
    }
    if(Snake[0][0]==Corex&&Snake[0][1]==Corey){
        Timeleft+=5;
        setFood();
        BodyCount++;
        Score+=Difficulty;
        Difficulty=BodyCount/5+1;
        ScoreNum->setText(QString::number(Score));
        LevelNum->setText(QString::number(Difficulty));
       if(Bunus!=1) Timer->start(210-20*Difficulty>30? 150-10*Difficulty : 90/(Difficulty)+30);
       if(Bunus==1)  Timer->start(40);
    }


    if(Bunus==3&&Cores[0][0]!=0){

            for(int i=0;i<100;++i){
                Cores[i][0]=(qrand()%92)*10;
                Cores[i][1]=(qrand()%78)*10;

    }

            Cores[0][0]=0;
    }
            if(Bunus==1||Bunus==2){Cores[0][0]=-1;}
    if(Snake[0][0]==Bunuscorex&&Snake[0][1]==Bunuscorey){
        Timeleft+=5;
        Bunuscorex=-1;
        Bunuscorey=-1;
        BodyCount++;
        Score+=15;

        int tem = Bunus;
        while(Bunus==tem){
            Bunus=qrand()%4;
        }
        if(Bunus==2){
            for(int i=0;i<150;i++){
                        Wall[i][0]=-1;
                        Wall[i][1]=-1;
                 }
         }
        if(Bunus==3){
            bunusTimer->start(10000);
        }
        Difficulty=BodyCount/5+1;
        ScoreNum->setText(QString::number(Score));
        LevelNum->setText(QString::number(Difficulty));
       if(Bunus!=1) Timer->start(210-20*Difficulty>30? 150-10*Difficulty : 90/(Difficulty)+40);
       if(Bunus==1) Timer->start(40);
    }
    if(AImode==1){
        if(Bunuscorex!=-1&&Bunuscorey!=-1){
            if(Bunuscorex==Snake[0][0]||Bunuscorey==Snake[0][1]){
                if(Bunuscorex>Snake[0][0]) {
                    if(Direction!=3) Direction=4;
                    else if(Snake[0][1]>=20) Direction=1;
                        else  Direction=2;
                }
                if(Bunuscorex<Snake[0][0]) {
                    if(Direction!=4) Direction=3;
                    else  if(Snake[0][1]>=20) Direction=1;
                    else  Direction=2;
                }
                if(Bunuscorey>Snake[0][1]) {
                    if(Direction!=1) Direction=2;
                    else if(Snake[0][0]>=20) Direction=3;
                        else Direction=4;
                }
                if(Bunuscorey<Snake[0][1]) {
                    if(Direction!=2) Direction=1;
                    else if(Snake[0][0]>=20) Direction=3;
                    else Direction=4;
                }
            }
            if(Bunuscorex>Snake[0][0]) {
                if(Bunuscorey>Snake[0][1]){
                    if(Direction==1) Direction=4;
                    if(Direction==3) Direction=2;
                }
                if(Bunuscorey<Snake[0][1]){
                    if(Direction==2) Direction=4;
                    if(Direction==3) Direction=1;
                }

            }
            if(Bunuscorex<Snake[0][0]) {
                if(Bunuscorey>Snake[0][1]){
                    if(Direction==1) Direction=3;
                    if(Direction==4) Direction=2;
                }
                if(Bunuscorey<Snake[0][1]){
                    if(Direction==2) Direction=3;
                    if(Direction==4) Direction=1;

            }
            }
        }







    if(Bunuscorex==-1&&Bunuscorey==-1){
        if(Corex==Snake[0][0]||Corey==Snake[0][1]){
        if(Corex>Snake[0][0]) {
            if(Direction!=3) Direction=4;
            else if(Snake[0][1]>=20) Direction=1;
                else  Direction=2;
        }
        if(Corex<Snake[0][0]) {
            if(Direction!=4) Direction=3;
            else  if(Snake[0][1]>=20) Direction=1;
            else  Direction=2;
        }
        if(Corey>Snake[0][1]) {
            if(Direction!=1) Direction=2;
            else if(Snake[0][0]>=20) Direction=3;
                else Direction=4;
        }
        if(Corey<Snake[0][1]) {
            if(Direction!=2) Direction=1;
            else if(Snake[0][0]>=20) Direction=3;
            else Direction=4;
        }
    }  //优先右下

    if(Corex>Snake[0][0]) {
        if(Corey>Snake[0][1]){
            if(Direction==1) Direction=4;
            if(Direction==3) Direction=2;
        }
        if(Corey<Snake[0][1]){
            if(Direction==2) Direction=4;
            if(Direction==3) Direction=1;
        }

    }
    if(Corex<Snake[0][0]) {
        if(Corey>Snake[0][1]){
            if(Direction==1) Direction=3;
            if(Direction==4) Direction=2;
        }
        if(Corey<Snake[0][1]){
            if(Direction==2) Direction=3;
            if(Direction==4) Direction=1;

    }
    }
}}
    memcpy(PreSnake,Snake,sizeof(Snake));



    for(int i = BodyCount;i > 0;--i){
        Snake[i][0]=Snake[i-1][0];
        Snake[i][1]=Snake[i-1][1];
    }

    for(int i = BodyCount;i>2;--i){
        if(Snake[0][0]==Snake[i][0]&&Snake[0][1]==Snake[i][1]) notBite=false;
        GameOver=1;
    }

    if(Timeleft<=0) notBite=false;

    if(DualPlay){
        for(int i=0;i<=BodyCount2;++i) {
            if(Snake2[i][0]==Snake[0][0]&&Snake2[i][1]==Snake[0][1]) notBite=false;
            GameOver=1;
        }
    }
    if(!AImode){
    for(int i=(rear2+1)%150;(front2-i+150)%50>0;i=(i+1)%150){
        if(Snake[0][0]==Wall[i][0]&&Snake[0][1]==Wall[i][1]) notBite=false;
        GameOver=1;
    }
        }

    switch (Direction) {
    case 1:
        Snake[0][0]=Snake[1][0];
        Snake[0][1]=Snake[1][1]-10;break;
    case 2:
        Snake[0][0]=Snake[1][0];
        Snake[0][1]=Snake[1][1]+10;break;
    case 3:
        Snake[0][0]=Snake[1][0]-10;
        Snake[0][1]=Snake[1][1];break;
    case 4:
        Snake[0][0]=Snake[1][0]+10;
        Snake[0][1]=Snake[1][1];break;
    default: break;
    }

    if(Snake[0][0]<0||Snake[0][0]>1197||Snake[0][1]<0||Snake[0][1]>897){
        notBite=false;
        memcpy(Snake,PreSnake,sizeof(Snake));
    }
    if(!AImode){
    for(int i=(rear2+1)%150;(front2-i+150)%150>0;i=(i+1)%150){
        if(Snake[0][0]==Wall[i][0]&&Snake[0][1]==Wall[i][1]) notBite=false;
    }
}


    this->update();
    connect(Timer,SIGNAL(timeout()),SLOT(CheckGameOver()));
}

void Widget2::Timeout2() {

    if(Bunus==3){
        for(int i=0;i<100;++i){
            if(Snake2[0][0]==Cores[i][0]&&Snake2[0][1]==Cores[i][1]){
                Cores[i][0]=-1;
                Cores[i][1]=-1;
                BodyCount2++;
                Score2+=Difficulty2;
                Difficulty2=BodyCount2/5+1;
                ScoreNum2->setText(QString::number(Score2));
                LevelNum2->setText(QString::number(Difficulty2));
                Timer->start(210-20*Difficulty2>30? 150-10*Difficulty2 : 90/(Difficulty2)+30);
                break;
            }
        }
    }
    if(Snake2[0][0]==Corex&&Snake2[0][1]==Corey){
        Timeleft2+=5;
        setFood();
        BodyCount2++;
        Score2+=Difficulty2;
        Difficulty2=BodyCount2/5+1;
        ScoreNum2->setText(QString::number(Score2));
        LevelNum2->setText(QString::number(Difficulty2));
        if(Bunus!=1)Timer3->start(210-20*Difficulty2>30? 150-10*Difficulty2 : 90/(Difficulty2)+30);
        if(Bunus==1) Timer3->start(40);
    }

    if(Snake2[0][0]==Bunuscorex&&Snake2[0][1]==Bunuscorey){


        int tem = Bunus;
        while(Bunus==tem){
            Bunus=qrand()%4;
        }
        if(Bunus==2){
            for(int i=0;i<150;i++){
                        Wall[i][0]=-1;
                        Wall[i][1]=-1;
                 }
         }
        if(Bunus==3){
            for(int i=0;i<100;++i){
                Cores[i][0]=(qrand()%92)*10;
                Cores[i][1]=(qrand()%78)*10;
            }
            bunusTimer->start(10000);
        }

        Timeleft2+=10;
        Bunuscorex=-1;
        Bunuscorey=-1;
        BodyCount2++;
        Score2+=15;
        Difficulty2=BodyCount2/5+1;
        ScoreNum2->setText(QString::number(Score));
        LevelNum2->setText(QString::number(Difficulty));
        if(Bunus!=1)Timer3->start(210-20*Difficulty>30? 150-10*Difficulty : 90/(Difficulty)+30);
        if(Bunus==1)Timer3->start(40);
    }

    memcpy(PreSnake2,Snake2,sizeof(Snake2));

    for(int i = BodyCount2 ; i > 0 ; --i ){
        Snake2[i][0]=Snake2[i-1][0];
        Snake2[i][1]=Snake2[i-1][1];
    }

    if(Timeleft2<=0) {
        GameOver=2;
        notBite=false;
    }

    for(int i = 3 ; i < BodyCount2 ; ++i ){
        if(Snake2[i][0]==Snake2[0][0]&&Snake2[i][1]==Snake2[0][1]) notBite=false;
        GameOver=2;
    }

    if(!AImode&&rear2!=front2){
    for(int i=(rear2+1)%150;(front2-i+150)%150>0;i=(i+1)%150){
        if(Snake2[0][0]==Wall[i][0]&&Snake2[0][1]==Wall[i][1]) notBite=false;
        GameOver=2;
    }
    }
    for(int i = 0 ; i < BodyCount ; ++i ){
        if(Snake[i][0]==Snake2[0][0]&&Snake[i][1]==Snake2[0][1]) notBite=false;
        GameOver=2;
    }

    switch (Direction2) {
    case 1:
        Snake2[0][0]=Snake2[1][0];
        Snake2[0][1]=Snake2[1][1]-10;break;
    case 2:
        Snake2[0][0]=Snake2[1][0];
        Snake2[0][1]=Snake2[1][1]+10;break;
    case 3:
        Snake2[0][0]=Snake2[1][0]-10;
        Snake2[0][1]=Snake2[1][1];break;
    case 4:
        Snake2[0][0]=Snake2[1][0]+10;
        Snake2[0][1]=Snake2[1][1];break;


    }

    if(Snake2[0][0]<0||Snake2[0][0]>910||Snake2[0][1]<0||Snake2[0][1]>770){
        notBite=false;
        memcpy(Snake2,PreSnake2,sizeof(PreSnake2));
    }

    this->update();
    connect(Timer3,SIGNAL(timeout()),this,SLOT(CheckGameOver()));


}


void Widget2::StartPush(){
    StartL -> setText("暂停游戏");
    AImode = 0;
    PlayState=true;
    Timer->start(210-20*Difficulty>30? 150-10*Difficulty : 90/(Difficulty)+30);
    Timer2->start(1000);
    if(DualPlay) Timer3->start(210-20*Difficulty2>30 ? 150-10*Difficulty2 : 90/Difficulty2+30);
    disconnect(Start,SIGNAL(clicked(bool)),this,SLOT(StartPush()));
    connect(Start,SIGNAL(clicked(bool)),this,SLOT(PausePush()));
}

void Widget2::PausePush(){
    StartL -> setText("开始游戏");
    AImode =0 ;
    PlayState=false;
    Timer->stop();
    Timer2->stop();
    if(DualPlay) Timer3->stop();
    disconnect(Start,SIGNAL(clicked(bool)),this,SLOT(PausePush()));
    connect(Start,SIGNAL(clicked(bool)),this,SLOT(StartPush()));
}

void Widget2::AISnake(){
    AImode=1;
    front1=rear1=front2=rear2=0;
    disconnect(Timer,SIGNAL(timeout()),this,SLOT(Timeout()));
    connect(Timer,SIGNAL(timeout()),this,SLOT(AITimeout()));
    Timer->start(100);






}

void Widget2::AITimeout(){
    if(Bunuscorex!=-1&&Bunuscorey!=-1){
        if(Bunuscorex==Snake[0][0]||Bunuscorey==Snake[0][1]){
            if(Bunuscorex>Snake[0][0]) {
                if(Direction!=3) Direction=4;
                else if(Snake[0][1]>=20) Direction=1;
                    else  Direction=2;
            }
            if(Bunuscorex<Snake[0][0]) {
                if(Direction!=4) Direction=3;
                else  if(Snake[0][1]>=20) Direction=1;
                else  Direction=2;
            }
            if(Bunuscorey>Snake[0][1]) {
                if(Direction!=1) Direction=2;
                else if(Snake[0][0]>=20) Direction=3;
                    else Direction=4;
            }
            if(Bunuscorey<Snake[0][1]) {
                if(Direction!=2) Direction=1;
                else if(Snake[0][0]>=20) Direction=3;
                else Direction=4;
            }
        }
        if(Bunuscorex>Snake[0][0]) {
            if(Bunuscorey>Snake[0][1]){
                if(Direction==1) Direction=4;
                if(Direction==3) Direction=2;
            }
            if(Bunuscorey<Snake[0][1]){
                if(Direction==2) Direction=4;
                if(Direction==3) Direction=1;
            }

        }
        if(Bunuscorex<Snake[0][0]) {
            if(Bunuscorey>Snake[0][1]){
                if(Direction==1) Direction=3;
                if(Direction==4) Direction=2;
            }
            if(Bunuscorey<Snake[0][1]){
                if(Direction==2) Direction=3;
                if(Direction==4) Direction=1;

        }
        }
    }
if(Bunuscorex==-1&&Bunuscorey==-1){
    if(Corex==Snake[0][0]||Corey==Snake[0][1]){
        if(Corex>Snake[0][0]) {
            if(Direction!=3) Direction=4;
            else if(Snake[0][1]>=20) Direction=1;
                else  Direction=2;
        }
        if(Corex<Snake[0][0]) {
            if(Direction!=4) Direction=3;
            else  if(Snake[0][1]>=20) Direction=1;
            else  Direction=2;
        }
        if(Corey>Snake[0][1]) {
            if(Direction!=1) Direction=2;
            else if(Snake[0][0]>=20) Direction=3;
                else Direction=4;
        }
        if(Corey<Snake[0][1]) {
            if(Direction!=2) Direction=1;
            else if(Snake[0][0]>=20) Direction=3;
            else Direction=4;
        }
    }  //优先右下

    if(Corex>Snake[0][0]) {
        if(Corey>Snake[0][1]){
            if(Direction==1) Direction=4;
            if(Direction==3) Direction=2;
        }
        if(Corey<Snake[0][1]){
            if(Direction==2) Direction=4;
            if(Direction==3) Direction=1;
        }

    }
    if(Corex<Snake[0][0]) {
        if(Corey>Snake[0][1]){
            if(Direction==1) Direction=3;
            if(Direction==4) Direction=2;
        }
        if(Corey<Snake[0][1]){
            if(Direction==2) Direction=3;
            if(Direction==4) Direction=1;

    }
    }
}
    Timeout();

}

void Widget2::SetDirection(int index)//接收按钮组的整数，确定方向
{
    switch (index)
    {
    case 1:if(Direction!=2)Direction=1;  break;
    case 2:if(Direction!=1)Direction=2;  break;
    case 3:if(Direction!=4)Direction=3;  break;
    case 4:if(Direction!=3)Direction=4;  break;
    default:                   break;
    }
}

void Widget2::QuitPush(){
    this->close();
    delete this;
}

void Widget2::CheckGameOver()
{
    if(!DualPlay){
        if(0>Snake[0][0]||Snake[0][0]>910||0>Snake[0][1]||Snake[0][1]>770||(!notBite)){
                notBite=true;
                this->update();
                Timer->stop();

                if(QMessageBox::Yes==QMessageBox::information(this,"Tips：","Game Over!",QMessageBox::Yes))
                {
                    this ->hide();
                    delete this;
                    return;
                }
    }
    }

   if(DualPlay){
    if(0>Snake[0][0]||Snake[0][0]>910||0>Snake[0][1]||Snake[0][1]>770||(!notBite)||Snake2[0][0]<0||Snake2[0][1]<0||Snake2[0][0]>910||Snake2[0][1]>770)
    {
        notBite=true;
        this->update();
        Timer->stop();
        Timer3->stop();
        Timer2->stop();
        switch (GameOver) {


        case 0:if(QMessageBox::Yes==QMessageBox::information(this,"Tips：","Game Over!",QMessageBox::Yes))
            {
            this ->hide();
            delete this;
            return;
            }
            break;
        case 1:if(QMessageBox::Yes==QMessageBox::information(this,"Tips：","Player1 Game Over!",QMessageBox::Yes))
            {
            this ->hide();
            delete this;
            return;
            }break;
        case 2:if(QMessageBox::Yes==QMessageBox::information(this,"Tips：","Player2 Game Over!",QMessageBox::Yes))
            {
            this ->hide();
            delete this;
            return;
            }
            break;
        default: break;
     }
    }
   }

}

void Widget2::clearCore(){
   Cores[0][0]=-1;
   Bunus=0;
}



/*bool Widget2::checknum(int t){
    for(int i = 0 ;i<=BodyCount;++i){
        if(Snake[i][0]/10+98*(Snake[i][1]/10)==t) return false;

    }

    return true;
}
bool Widget2::FindWay(){
    Way[0]=0;
    queue.clear();
    int numcore = Corex/10+98*(Corey/10);
    int numhead = Snake[0][0]/10+98*(Snake[0][1]/10);
    queue.enqueue(numhead);
    Map[numhead] = 0;
    Map[numcore] = 0;
    while(queue.isEmpty()==false){
        int num = queue.dequeue();
        if(num>0&&num<91){
            if(checknum(num-1)) {queue.enqueue(num-1);Map[num-1]=Map[num]+1;}
            if(checknum(num+1)){queue.enqueue(num+1);Map[num+1]=Map[num]+1;}
            if(checknum(num+92)){queue.enqueue(num+92);Map[num+92]=Map[num]+1;}
        }
        else if(num%92==91){
            if(num==91){
                if(checknum(num-1)){ queue.enqueue(num-1);Map[num-1]=Map[num]+1; }
                if(checknum(num+92)){ queue.enqueue((num+92));Map[num+92]=Map[num]+1 ; }
            }
           else if(num==7175){
                if(checknum(num-92)){ queue.enqueue((num-92));Map[num-92]=Map[num]+1 ; }
                if(checknum(num-1)){ queue.enqueue(num-1);Map[num-1] = Map[num]+1 ;}
            }

            else {
                 if(checknum(num-1)){ queue.enqueue(num-1);Map[num-1] = Map[num]+1 ;}
                 if(checknum(num+92)){ queue.enqueue((num+92));Map[num+92]=Map[num]+1 ; }
                 if(checknum(num-92)){ queue.enqueue((num-92));Map[num-92]=Map[num]+1 ; }
            }
        }
        else if(num%92==0){
            if(num==0){
               if(checknum(num+1)){ queue.enqueue(num-1);Map[num-1]=Map[num]+1; }
               if(checknum(num+92)){ queue.enqueue((num+92));Map[num+92]=Map[num]+1 ; }
            }
            else if(num==7184){
                if(checknum(num+1)){ queue.enqueue(num-1);Map[num-1]=Map[num]+1; }
                if(checknum(num-92)){ queue.enqueue((num+92));Map[num+92]=Map[num]+1 ; }
            }
            else{
                if(checknum(num+1)){ queue.enqueue(num-1);Map[num-1]=Map[num]+1; }
                if(checknum(num-92)){ queue.enqueue((num+92));Map[num+92]=Map[num]+1 ; }
                if(checknum(num+92)){ queue.enqueue((num+92));Map[num+92]=Map[num]+1 ; }
            }
        }
        else if(num-7084>=0&&num-7084<=91){
            if(checknum(num-1)) {queue.enqueue(num-1);Map[num-1]=Map[num]+1;} ;
            if(checknum(num+1)){queue.enqueue(num+1);Map[num+1]=Map[num]+1;} ;
            if(checknum(num-92)){queue.enqueue(num+92);Map[num+92]=Map[num]+1;}
        }
        else{
            if(checknum(num-1)) {queue.enqueue(num-1);Map[num-1]=Map[num]+1;}
            if(checknum(num+1)){queue.enqueue(num+1);Map[num+1]=Map[num]+1;}
            if(checknum(num-92)){queue.enqueue(num+92);Map[num+92]=Map[num]+1;}
            if(checknum(num+92)){ queue.enqueue((num+92));Map[num+92]=Map[num]+1 ; }
        }


    }
    if(Map[numcore]==0) return 0;
    if(Map[numcore]!=0){
        while(Map[numcore]!=0){

            queue2.enqueue(numcore);
                 if(Map[numcore-1]==Map[numcore]-1) numcore--;
            else if(Map[numcore+1]==Map[numcore]-1) numcore++;
            else if(Map[numcore+92]==Map[numcore]-1) numcore+=92;
            else if(Map[numcore-92]==Map[numcore]-1)  numcore-=92;
        }
        int i = 0 ;
        while (!queue2.isEmpty()) {

            Way[i]=queue2.dequeue();

        }
    }

    return 1;

}


*/







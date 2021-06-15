#include "BoggleWindow.h"
#include "lexicon.h"
#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <string.h>
#include <iostream>
#include <cstring>
#include <string>
#include <QObject>
using namespace std;
BoggleWindow::BoggleWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    this->setMouseTracking(true);

    me              = new WordListWidget(this, "Me");
    computer    = new WordListWidget(this, "Computer");
    board          = new Board(this);
    console       = new Console(this);

    me->setGeometry(20, 20, 230, 300);
    board->setGeometry(230, 0, 300, 300);
    computer->setGeometry(800 - 50 - 200, 20, 230, 300);
    console->setGeometry(30, 320, 740, 260);

    for(int i = 0 ; i < board->getSize()*board->getSize() ; ++i){
        connect(board->cubes[i],SIGNAL(cubesClicked(int)),this,SLOT(MousePlay(int)));
    }

    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly)) {
        throw new std::runtime_error("Resource file not found!");
    }

    lex = new Lexicon(qFile);
    console->write("Welcome to the game Boggle!\nyour must input words with at least four letters or you will not get score\npress @ to let the computer help you!\n");
    connect(console,SIGNAL(newLineWritten(QString)),this,SLOT(check()));

}

void BoggleWindow::check(){
    string str = console->line.toLower().toStdString();                                //输入的槽函数，执行后检查输入是否合法

    int numq=0,numqu=0;
    for(int i = 0 ; i < console->line.length(); ++i){
        if(console->line[i]=='q') numq++;
        if(i!=console->line.length()-1&&console->line[i]=='q'&&console->line[i+1]=='u') numqu++;
    }
    if(numq!=numqu) {console->write("没有这个单词呢，再想想吧\n！");return;}
    console->line=console->line.toLower();
    while(console->line.indexOf("qu",0)!=-1){
     console->line.remove(console->line.indexOf("qu")+1,1);}

    if(str=="@"){
        computer->reset();
        for(int i = 0 ; i < board->getSize()*board->getSize() ; ++i){
        computerfind(Computer,i);
        }
    }                                                                           //如果输入@则进入电脑模式
    else{if(lex->contains(str)){
    int score = str.length();
    str = console->line.toLower().toStdString();
        way[0]=way[str.size()-1]=-1;

          find(str,0,str);

        if(way[str.size()-1]!=-1){                                      //如果形成路径，进入判分
            switch (score) {
            case 1:case 2 : case 3:  console->write("找到啦，但是不得分！\n");break;
            default: {
                if(!me->isincluded(QString::fromStdString(str))) {
                    console->write("你太棒了！得"+QString::number(score-3)+"分！\n");
                    board->HightLight(way,int(str.size()));
                me->addScore(score-3);
                me->repaint();
                me->addWord(QString::fromStdString(str));}
                else {
                    console->write("已经找过了哦！\n");
                }}
            }

        }
        else{
                  console->write("没有这个单词呢，再想想吧！\n");
            }
    }else{
        console->write("没有这个单词呢，再想想吧！\n");
    }
    }

}

BoggleWindow::~BoggleWindow()
{
}

bool BoggleWindow::Highlight(){


}

void BoggleWindow::find(string & st, int i,const string s){                                                     //human递归，深度优先搜索寻找路径
    string s1(1,st[0]);
    string s3(1,board->let[way[i-1]-1]);
    string s4(1,board->let[way[i-1]+1]);
    string s5(1,board->let[way[i-1]-board->getSize()]);
    string s6(1,board->let[way[i-1]+board->getSize()]);
    string s7(1,board->let[way[i-1]-board->getSize()-1]);
    string s8(1,board->let[way[i-1]-board->getSize()+1]);
    string s9(1,board->let[way[i-1]+board->getSize()-1]);
    string s10(1,board->let[way[i-1]+board->getSize()+1]);


    if( i  == 0 ){                                                                                              //依次寻找st的首个字母，进行递归

        for( int j = 0 ; j < board->getSize()*board->getSize() ;++j){
            string s2(1,board->let[j]);

            if(s1== s2) {
                way[0] = j;
                string tmp = st;
                tmp.erase(0,1);
                find (tmp,i+1,s);
                string sss(i,way[1]);
                if ( way[s.size()-1]!=-1 ) break;

            }
        }
    }

    if(way[s.size()-1]!= -1 ) return;
    if( s1==s5 &&way[s.size()-1]== -1){
        way[i] = way[i-1]-board->getSize();
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);
                find (tmp,i+1,s);
            }
        }
    }
    if(s6==s1&&way[s.size()-1]== -1 ){
        way[i] = way[i-1]+board->getSize();
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);

                find (tmp,i+1,s);
            }
        }
    }
    if (way[i-1]%5 != 0 && s1==s3&&way[s.size()-1]== -1){
        way[i] = way[i-1]-1;
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);

                find (tmp,i+1,s);
            }
        }
    }
    if(way[i-1]%5 != 4 && s1 ==s4&&way[s.size()-1]== -1){
        way[i] = way[i-1]+1;
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);

                find (tmp,i+1,s);
            }
        }
    }
    if(way[i-1]%5 != 0 && s1 ==s7&&way[s.size()-1]== -1){
        way[i] = way[i-1]-board->getSize()-1;
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);

                find (tmp,i+1,s);
            }
        }
    }
    if(way[i-1]%5 != 4 && s1 ==s8&&way[s.size()-1]== -1){
        way[i] = way[i-1]-board->getSize()+1;
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);

                find (tmp,i+1,s);
            }
        }
    }
    if(way[i-1]%5 != 0 && s1 ==s9&&way[s.size()-1]== -1){
        way[i] = way[i-1]+board->getSize()-1;
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);

                find (tmp,i+1,s);
            }
        }
    }
    if(way[i-1]%5 != 4 && s1 ==s10&&way[s.size()-1]== -1){
        way[i] = way[i-1]+board->getSize()+1;
        for(int m =0; m<i ; ++m){
            if (way[m]==way[i]) { way[i]=-1; break;}
            if(m==i-1){
                string tmp = st;
                tmp.erase(0,1);

                find (tmp,i+1,s);
            }
        }
    }

}


void BoggleWindow::computerfind(QString com,int pos){
    string s(1,board->let[pos]);
    if(s=="q") s+="u";
    com+=QString::fromStdString(s)  ;
    if(!lex->containsPrefix(com.toStdString())&&!lex->contains(com.toStdString())) return;
    if(com.length()>=4&&lex->contains(com.toStdString())&&!computer->isincluded(com)&&!me->isincluded(com)) {
        string ss=com.toStdString();
        way[com.length()-1]=way[0]=-1;
        find(ss,0,com.toStdString());
        if(way[com.length()-1]!=-1){
            computer->addWord(com);
            computer->addScore(com.length()-3);

        }
    }
    if(pos%5!=0&&pos>(board->getSize()-1))      computerfind(com,pos-board->getSize()-1);
    if(pos>=board->getSize()-1)                             computerfind(com,pos-board->getSize());
    if(pos%5!=4&&pos>(board->getSize()-1))      computerfind(com,pos-board->getSize()+1);
    if(pos%5!=0)                                                      computerfind(com,pos-1);
    if(pos%5!=4)                                                      computerfind(com,pos+1);
    if(pos%5!=0&&pos<(board->getSize()*board->getSize()-board->getSize()-1)) computerfind(com,pos+board->getSize()-1);
    if(pos%5!=4&&pos<(board->getSize()*board->getSize()-board->getSize()-1)) computerfind(com,pos+board->getSize()+1);
    if(pos<(board->getSize()*board->getSize()-board->getSize()-1)) computerfind(com,pos+board->getSize());
    if(com.length()==1) return;
}





void BoggleWindow::MousePlay(int Index){                //鼠标点击的槽函数
         if(board->cubes[Index]->clicked==0) {                  //当该cube未被点击的情况
             board->cubes[Index]->clicked =1;
             board->cubes[Index]->setStyleSheet("background-color: yellow; border-radius: 15px; border: 2px solid");
             string s(1,board->let[Index]);
             if(s=="q")Mouse+="qu";
             else Mouse+=QString::fromStdString(s);
             QString ss=Mouse;
              int score = ss.length();
             while(ss.contains("qu")) ss.remove(ss.indexOf("qu")+1,1);
             way[ss.size()-1]  = Index;
             if(ss.size()>=2&&!checkMouse(way,ss.size()-1)){
                 console->write("没有这个单词哦，再想想吧！\n");
                 clearBoard();
                 Mouse = nullptr;
                 return;
             }
             if(!lex->containsPrefix(Mouse.toStdString())){
                 console->write("没有这个单词哦，再想想吧！\n");
                 clearBoard();
                 Mouse = nullptr;
                 return;
             }


             if(Mouse.size()>=4&&lex->contains(Mouse.toStdString())){
                 string sss=ss.toStdString();
                 if(me->isincluded(ss)) {
                     console->write("已经找到过了哦！\n");
                     Mouse=nullptr;
                     clearBoard();
                     return;
                 }

                 else{
                     console->write("找到啦！得"+QString::number(score-3)+ "分!\n");
                     me->addWord(ss);
                     me->addScore(score-3);
                     board->HightLight(way,(int)sss.size());
                     clearBoard();
                     Mouse=nullptr;
                     return;
                 }


         }

         }
         else {                                                             //取消点击的情况
             if((board->let[Index]=='q'&&Mouse[Mouse.size()-2]==board->let[Index])||(board->let[Index]!='q'&&Mouse[Mouse.length()-1]==board->let[Index])){
            board->cubes[Index]->clicked =0;
             if(board->let[Index]=='q'){ Mouse.remove(Mouse.size()-2,2); }
             else {Mouse.remove(Mouse.size()-1,1) ;}
             board->cubes[Index]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
         }
         }
}

void BoggleWindow::clearBoard(){
    for(int i = 0 ; i < board->getSize()*board->getSize() ; ++i){
        board->cubes[i]->clicked = 0 ;
        board->cubes[i]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
    }
}

bool BoggleWindow::checkMouse(int a[], int n){                          //判断鼠标点击合法性
    if(a[n-1]%5==0&&(a[n]==a[n-1]-6||a[n]==a[n-1]+4||a[n]==a[n-1]-1)) return false;
    if(a[n-1]%5==4&&(a[n]==a[n-1]-4||a[n]==a[n-1]+1||a[n]==a[n-1]+6)) return false;
    if(a[n]==a[n-1]-6||a[n]==a[n-1]-5||a[n]==a[n-1]-4||a[n]==a[n-1]-1||a[n]==a[n-1]+1||a[n]==a[n-1]+4||a[n]==a[n-1]+5||a[n]==a[n-1]+6) return true;
    return false;
}

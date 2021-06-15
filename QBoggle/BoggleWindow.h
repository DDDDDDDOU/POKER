#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include "Board.h"
#include "Console.h"
#include "WordListWidget.h"
#include <QString>
#include <QMainWindow>
#include <lexicon.h>
#include <QMouseEvent>
using namespace std;

class BoggleWindow : public QMainWindow
{
    Q_OBJECT

public:

    BoggleWindow(QWidget *parent = 0);
    bool Highlight();
    int way[25];
    void find(string & st,int i,const string s);
    void computerfind(QString com,int pos);
    QString Computer;
    QString Mouse;
  //  QString MouseClick;
    void clearBoard();
    bool checkMouse(int a[],int n);

 public slots:
    void check();
    void MousePlay(int Index);
public:
    ~BoggleWindow();
private:
    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    Lexicon *lex;



    static const int BOGGLE_WINDOW_WIDTH = 800;
    static const int BOGGLE_WINDOW_HEIGHT = 600;
};

#endif // BOGGLEWINDOW_H

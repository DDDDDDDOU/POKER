#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"
#include <string.h>
#include <string>
#include <QTime>

#include <QWidget>
using namespace std;
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr, int size = 5, const QString *cubeLetters = BIG_BOGGLE_CUBES);
    virtual ~Board();
    void shake();
    int getSize();
    int getcubes(int m);
   char *let;
   QTime *T;
   void HightLight(int a[],int  s);


   //void HLhelper(int b );
    Cube **cubes;
signals:

public slots:

private:
    int size;

    QString *letters;
    inline int index(int i, int j) { return i * size + j; }
    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];
};

#endif // BOARD_H

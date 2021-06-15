#include "Board.h"
#include "Cube.h"
#include <QTime>
#include <QGridLayout>
#include <QtGlobal>
#include <ctime>
#include <QString>
#include <string>
#include <string.h>
#include <QCoreApplication>
using namespace std;

const QString Board::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString Board::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};
Board::Board(QWidget *parent, int size, const QString *cubeLetters) : QWidget(parent)
{

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    this->size = size;
    this->cubes = new Cube*[size * size];
    this->letters = new QString[size * size];

    for(int i = 0 ; i < size*size ; ++i){
        letters[i]=cubeLetters[i];
    }

    this->setMouseTracking(true);
    QGridLayout *layout = new QGridLayout();
    T     = new QTime ;
    layout->setMargin(20);
    layout->setSpacing(10);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(this);
            cubes[index(i,j)]->setIndex(index(i,j));
            layout->addWidget(this->cubes[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
        }
    }
    setLayout(layout);

   shake();
}

Board::~Board()
{
    if (cubes) delete[] cubes;
    if (letters) delete[] letters;
}

void Board::shake()
{


    //shake cubes

    for ( int i = 0 ; i < this->size*this->size-1 ; ++i){
        int j = qrand()%(this->size*this->size-i-1)+i+1;
        QString tmp;
        tmp = this->letters[i];
        this -> letters[i] = letters[j];
        this -> letters[j] = tmp;
    }


    //shake the letters in each cube

    let = new char [size*size];
    for (int i=0 ; i < this->size ; ++i) {
        for(int j = 0 ; j < this->size ; ++j){
            QString tmp;

                    tmp=this -> letters[index(i,j)].at(qrand()%6);
            let[i*size+j]=tmp.toStdString()[0];
            this -> cubes[index(i,j)] -> setLetter(tmp=="Q" ? "QU" : tmp);
        }
        for(int i = 0 ; i < this->size*this->size;++i){
            if(let[i]>='A'&&let[i]<='Z')
            let[i]=let[i]-('A'-'a');
        }

    }
}

int Board::getSize(){
    return this->size;
}


void Board::HightLight(int a[],int s){
    for(int i  = 0 ; i < s ; ++i){
         cubes[a[i]]->setStyleSheet("background-color: yellow; border-radius: 15px; border: 2px solid");
        T->start();
        while(T->elapsed()<100) {QCoreApplication::processEvents();}
        cubes[a[i]]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
    }
    for(int i = 0; i < s ; ++i ){
        cubes[a[i]]->setStyleSheet("background-color: yellow; border-radius: 15px; border: 2px solid");
    }
    T->start();
    while(T->elapsed()<1000){QCoreApplication::processEvents();}
    for(int i = 0; i < s ; ++i ){
        cubes[a[i]]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
    }

}


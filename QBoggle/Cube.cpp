#include "Cube.h"

#include <QHBoxLayout>

Cube::Cube(QWidget *parent) : QWidget(parent)
{
    label = new QLabel();
    label->setText("");
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPointSize(20);
    label->setFont(font);
    this->setFixedSize(75, 75);
    this->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
    this->setMouseTracking(true);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
    clicked=0;
}

void Cube::setLetter(QString l)
{
    label->setText(l);
}


void Cube::mousePressEvent(QMouseEvent *event){
    emit cubesClicked(Index);
}

void Cube::setIndex(int m){
    this->Index=m;
}

#ifndef CUBE_H
#define CUBE_H

#include <QLabel>
#include <QWidget>

class Cube : public QWidget
{
    Q_OBJECT
public:
    explicit Cube(QWidget *parent = nullptr);
    void setLetter(QString l);
    void mousePressEvent(QMouseEvent *event);
    void setIndex(int m);
    bool clicked;
    int Index;
signals:
    void cubesClicked(int index);

public slots:

private:
    QLabel *label;

};

#endif // CUBE_H

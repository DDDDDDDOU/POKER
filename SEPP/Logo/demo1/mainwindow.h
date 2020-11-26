#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <login.h>
#include <window.h>
#include <qpushbutton.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Login *login;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


private:
    Window window;
    QPushButton *solo;
    QPushButton *pk;
};
#endif // MAINWINDOW_H

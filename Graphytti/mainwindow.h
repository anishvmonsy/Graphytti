#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include "exponeplotter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
     QStackedWidget* stackedWidget;
       ExpOnePlotter *myGraphPlotter;
private slots:
    void graphChoice();
    void mainScreen();
    void prevCycle();
    void nextCycle();


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

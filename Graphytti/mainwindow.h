#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
     QStackedWidget* stackedWidget;

private slots:
    void graphChoice();
    void mainScreen();



public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

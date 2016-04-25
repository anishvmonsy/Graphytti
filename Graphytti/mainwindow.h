#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include "exponeplotter.h"
#include "anisoplotter.h"
class QMenu;
class QAction;

/**
 * @brief
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    /**
      * @brief reference to the qstackedwidget present in main window
      */
     QStackedWidget* stackedWidget;
     /**
        * @brief responsible for plotting  graphs and displaying other details of particular file format
        */
       ExpOnePlotter *myGraphPlotter;
       /**
        * @brief creates action for menuBar()
        */
       GraphPlotter *GraphPlotterFactory(int n,QStackedWidget *CentralWindowWdiget);
       void createAction();
             /**
               * @brief creates menubar
               */
              void createMenu();
              /**
               * @brief creates helpmenu in menubar
               */
              QMenu *helpMenu;
              /**
               * @brief creates "about" action in help menu
               */
              QAction *aboutAct;
              /**
               * @brief creates "aboutQt" action in help menu
               */
              QAction *aboutQtAct;
private slots:
   /**
     * @brief slot activated when user chooses excitation intensity analyis
     */
    void excitationIntensityChoice();
    /**
     * @brief changes display back  to the main screen
     */
    void mainScreen();
    /**
     * @brief slot activated when myGraphPlotter needs to display previous Cycle
     */
    void prevCycle();
    /**
     * @brief slot activated when myGraphPlotter needs to display next Cycle
     */
    void nextCycle();
    /**
     * @brief slot to simulate "about" action
     */
    void about();
    /**
     * @brief slot to simulate "about Qt" action
     */
    void aboutQt();


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

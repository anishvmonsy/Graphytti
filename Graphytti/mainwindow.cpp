#include "mainwindow.h"
#include "interactiveplot.h"
#include "exponeplotter.h"
#include<QPushButton>
#include <QVBoxLayout>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    stackedWidget = new QStackedWidget;
    QWidget *widget1=new QWidget;
    QHBoxLayout *hbox = new QHBoxLayout(this);
    QLabel *label  = new QLabel(this);
    QPixmap p(":/icons/lolpid.PNG");
    label->setPixmap(p);
    hbox->addWidget(label);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QPushButton *anisotropy=new QPushButton("Anisotropy",this);
    QPushButton *excitationAnalysis=new QPushButton("Excitation Analysis",this);
    vbox->addWidget(anisotropy);
    vbox->addWidget(excitationAnalysis);
    hbox->addLayout(vbox);
    widget1->setLayout(hbox);
    stackedWidget->addWidget(widget1);
    stackedWidget->setCurrentIndex(0);
    //stackedWidget->widget(0)->show();
    this->setCentralWidget(stackedWidget);

    //signals and slots connection
    connect(excitationAnalysis, &QPushButton::clicked, this, &MainWindow::excitationIntensityChoice);

    createAction();
    createMenu();

}
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Menu"),
               tr("<b>GRAPHYTTI</b><br> "
                  "This project is aimed at implementing an GUI interface for easily visualising"
                  " the results of analysis after the fluorescence intensity decay experiment.<br>"
                  "<br>"
                  "<b>Supported Platforms</b><br>"
                  "* Windows 7 or later<br>"
                  "* Ubuntu Linux 14.04 (32-bit and 64-bit) or later <br>"
                  "* Mac OS X 10.7 or later<br>"
                  "<br>"
                  "<a href = 'https://gitlab.com/anishvmonsy/team17cs243/blob/master/DEPENDENCIES.md'> Depencencies  </a><br>"
                  "<br>"
                  "<b>Copyright (C) 2015  Anish V Monsy,Vivek Datir,Mohd Imran,Likhith Pallagani</b><br>"
                  "This program is free software: you can redistribute it and/or modify"
                   " it under the terms of the GNU General Public License as published by"
                   " the Free Software Foundation, either version 3 of the License, or"
                   " (at your option) any later version."
                   "<br>"
                   "This program is distributed in the hope that it will be useful,"
                  " but WITHOUT ANY WARRANTY; without even the implied warranty of"
                  " MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
                  " GNU General Public License for more details.<br>"
                  "<br>"
                  "Please see <a href ='http://www.gnu.org/licenses/gpl-3.0.en.html'>License</a>for an overview of licensing<br>"
                  "Please see<a href = 'https://github.com/likhith208/Graphytti'>Code </a>for an overview of Source Code<br>"
                  ));

}
void MainWindow::aboutQt()
{


}
void MainWindow::createAction()
{
        aboutAct = new QAction(tr("&About"), this);
        aboutAct->setStatusTip(tr("Shows about"));
        connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
        aboutQtAct = new QAction(tr("About &Qt"), this);
        aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
        connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
        connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

}
void MainWindow::createMenu(){
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

MainWindow::~MainWindow()
{

}

GraphPlotter *MainWindow::GraphPlotterFactory(int n,QStackedWidget *CentralWindowWdiget)
{
    if(n==0)
        return new ExpOnePlotter(CentralWindowWdiget);
    else if(n==1)
        return new AnisoPlotter(CentralWindowWdiget);
}

void MainWindow::excitationIntensityChoice(){

    myGraphPlotter= new ExpOnePlotter(stackedWidget);
    QString file_path= QFileDialog::getOpenFileName(this,
                                                       tr("Open a file"),
                                                       QDir().rootPath(),
                                                       "All files (*)");
    if(file_path.isEmpty()){
        QMessageBox::information(this,tr("No file selected"),"Please choose a file to continue");
        mainScreen();
    }
    else{




        int fileCheckingCode= myGraphPlotter->checkFile(file_path);
           if(fileCheckingCode){
               QMessageBox::information(this,tr("Wrong file selected"),"Please choose a correct file to continue");
               mainScreen();
           }
           else{

           myGraphPlotter->parseFile(file_path);
           myGraphPlotter->plotGraph();
           connect(myGraphPlotter->getNextButton(),&QPushButton::clicked,this, &MainWindow::nextCycle);
           connect(myGraphPlotter->getPrevButton(),&QPushButton::clicked,this, &MainWindow::prevCycle);

           connect(myGraphPlotter->getGoBackButton(),&QPushButton::clicked,this, &MainWindow::mainScreen);
         }
       }

}
void MainWindow::mainScreen(){
    stackedWidget->setCurrentIndex(0);
    QWidget *topWidget=stackedWidget->widget(1);
    stackedWidget->removeWidget(topWidget);
    delete topWidget;
}
void MainWindow::nextCycle(){

        myGraphPlotter->nextCycle();


}
void MainWindow::prevCycle(){
    myGraphPlotter->prevCycle();
}

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
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QPushButton *anisotropy=new QPushButton("Anisotropy",this);
    QPushButton *excitationAnalysis=new QPushButton("Excitation Analysis",this);
    vbox->addWidget(anisotropy);
    vbox->addWidget(excitationAnalysis);
    widget1->setLayout(vbox);
    stackedWidget->addWidget(widget1);
    stackedWidget->setCurrentIndex(0);
    //stackedWidget->widget(0)->show();
    this->setCentralWidget(stackedWidget);

    //signals and slots connection
    connect(excitationAnalysis, &QPushButton::clicked, this, &MainWindow::graphChoice);

}

MainWindow::~MainWindow()
{

}
void MainWindow::graphChoice(){

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
        myGraphPlotter->parseFile(file_path);
    }


    myGraphPlotter->plotGraph();
    connect(myGraphPlotter->getNextButton(),&QPushButton::clicked,this, &MainWindow::nextCycle);
    connect(myGraphPlotter->getPrevButton(),&QPushButton::clicked,this, &MainWindow::prevCycle);

    connect(myGraphPlotter->getGoBackButton(),&QPushButton::clicked,this, &MainWindow::mainScreen);
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

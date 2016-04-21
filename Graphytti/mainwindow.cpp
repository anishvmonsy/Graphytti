#include "interactiveplot.h"
#include "mainwindow.h"
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

    QWidget *dummynew=new QWidget;
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QPushButton *goBack=new QPushButton("go Back",this);
    vbox->addWidget(goBack);
    dummynew->setLayout(vbox);
    stackedWidget->addWidget(dummynew);
    stackedWidget->setCurrentIndex(1);


    connect(goBack,&QPushButton::clicked,this, &MainWindow::mainScreen);


}
void MainWindow::mainScreen(){
    stackedWidget->setCurrentIndex(0);
    QWidget *topWidget=stackedWidget->widget(1);
    stackedWidget->removeWidget(topWidget);
    delete topWidget;
}


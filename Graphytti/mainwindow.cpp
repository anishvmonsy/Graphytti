#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_file_button_clicked()
{

    QString fileName= QFileDialog::getOpenFileName(this,
                                                       tr("Open a file"),
                                                       QDir().rootPath(),
                                                       "All files (*)");
    if(fileName.isEmpty()){
        QMessageBox::information(this,tr("No file selected"),"Please choose a file to continue");
    }
    else{
        QMessageBox::information(this,tr("Filename"),fileName);
    }

}

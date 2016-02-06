#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "exptcycle.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void file_parser(QString filepath);
    void plot_fluor_graph();
    void plot_res_graph();
    ~MainWindow();

private slots:
    void on_file_button_clicked();

private:
    QString file_selected;
    QString expt_title;
    exptcycle current_cycle;

    int current_cycle_no;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

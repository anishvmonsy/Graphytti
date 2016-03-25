#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<vector>
#include <QMainWindow>
#include "qcustomplot.h"
#include "exptcycle.h"
namespace Ui {
class MainWindow;
}


/*
 * MainWindow class is responsible for handling user interactions,
 * getting data from files and plotting the data on the screen.
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int file_parser(QString filepath);


    void plot_fluor_graph();
    void plot_res_graph();
    void plot_acorr_graph();
    void display_cycle_text();
    ~MainWindow();

private slots:

    void on_file_button_clicked();

    void on_prev_cycle_button_clicked();

    void on_next_cycle_button_clicked();




private:
    bool file_already_open;
    QString file_selected;
    QString expt_title;

    std::vector<exptcycle> all_cycles;
    int current_cycle_index;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

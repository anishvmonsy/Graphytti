#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<vector>
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
    void plot_acorr_graph();
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

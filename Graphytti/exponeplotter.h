#ifndef EXPONEPLOTTER_H
#define EXPONEPLOTTER_H
#include "graphplotter.h"
#include "exptcycle.h"
#include<QLabel>
#include "interactiveplot.h"
class ExpOnePlotter : public GraphPlotter{


private:
    bool file_already_open;
    QString file_selected;
    QString expt_title;

    std::vector<exptcycle> all_cycles;
    int current_cycle_index;
    //ui variables
    QLabel *expt_title_label;
    InteractivePlot *fluor_graph;
    InteractivePlot *res_graph;
    InteractivePlot *acorr_graph;
    QPushButton *prev_button;
    QPushButton *next_button;
    QLabel *expt_cycle_label;
    QPushButton *go_back_button;

    void plot_fluor_graph();
    void plot_res_graph();
    void plot_acorr_graph();

public:
    ExpOnePlotter(QStackedWidget *);
    void plotGraph();
    void parseFile(QString);
    int checkFile(QString);
    void nextCycle();
    void prevCycle();
    QPushButton *getGoBackButton();
    QPushButton *getNextButton();
    QPushButton *getPrevButton();






};

#endif // EXPONEPLOTTER_H

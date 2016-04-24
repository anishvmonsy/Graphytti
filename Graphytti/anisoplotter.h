#ifndef ANISOPLOTTER_H
#define ANISOPLOTTER_H
#include "graphplotter.h"
#include "exptcycle2.h"
#include<QLabel>
#include "interactiveplot.h"
class AnisoPlotter : public GraphPlotter{


private:
    bool file_already_open;
    QString file_selected;
    QString expt_title;

    std::vector<exptcycle2> all_cycles;
    int current_cycle_index;
    //ui variables
    QLabel *expt_title_label;
    InteractivePlot *aniso_graph;
    InteractivePlot *res1_graph;
    InteractivePlot *res2_graph;
    QPushButton *prev_button;
    QPushButton *next_button;
    QLabel *expt_cycle_label;
    QPushButton *go_back_button;
     QTableWidget *tableWidget;

    void plot_aniso_graph();
    void plot_res1_graph();
    void plot_res2_graph();
    QVector<QString> getCycleParameters(QString);
    QVector<QString> getCycleParameterValues(QString);

public:
    AnisoPlotter(QStackedWidget *);
    void plotGraph();
    void parseFile(QString);
    int checkFile(QString);
    void nextCycle();
    void prevCycle();
    QPushButton *getGoBackButton();
    QPushButton *getNextButton();
    QPushButton *getPrevButton();






};

#endif // ANISOPLOTTER_H

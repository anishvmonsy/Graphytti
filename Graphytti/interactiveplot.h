#ifndef INTERACTIVEPLOT_H
#define INTERACTIVEPLOT_H
#include "qcustomplot.h"


class InteractivePlot : public QCustomPlot{

    Q_OBJECT
    public:
    explicit InteractivePlot(QWidget *parent = 0);
        private slots:
        void showPointToolTip(QMouseEvent *event);









};

#endif // INTERACTIVEPLOT_H

#ifndef INTERACTIVEPLOT_H
#define INTERACTIVEPLOT_H
#include "qcustomplot.h"

/**
 * @brief Graph displaying approx coordinates of selected graph
 */
class InteractivePlot : public QCustomPlot{

    Q_OBJECT
    public:
    /**
     * @brief makes connections between mouse signals and graph widget
     */
    explicit InteractivePlot(QWidget *parent = 0);
        private slots:
    /**
         * @brief finds approx coordinates from position of cursor and selected graph
         * @param provides information about position of cursor
         */
        void showPointToolTip(QMouseEvent *event);









};

#endif // INTERACTIVEPLOT_H

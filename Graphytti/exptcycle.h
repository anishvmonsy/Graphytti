#ifndef EXPTCYCLE_H
#define EXPTCYCLE_H
#include<QVector>

/*
 * The class exptcycle contains all the data associated with one cycle of the experiment
 * The data is loaded during the fileparser method call and this data is used in graph plot methods.
 */


class exptcycle{
    QVector<double> ex;
    QVector<double> em;
    QVector<double> cal_em;
    QVector<double> res;
    QVector<double> acorr;
    QVector<double> chan;
    QString cycle_text;
    long point_count;
    bool cycle_is_loaded;   //to make sure cycle is loaded only once
    public:

    exptcycle();

    void load_cycle_data(long new_point_count,QVector<double> & new_chan,QVector<double> & new_ex,QVector<double> & new_em,QVector<double> & new_cal_em,
                         QVector<double> & new_res,QVector<double> & new_acorr);

    void append_cycle_text(QString more_cycle_text);
    QVector<double> get_ex();
    QVector<double> get_em();
    QVector<double> get_cal_em();
    QVector<double> get_res();
    QVector<double> get_acorr();
    QVector<double> get_chan();
    QString get_cycle_text();
    long get_point_count();

    //have to define public methods to return data(that is to be made private)

};

#endif // EXPTCYCLE_H

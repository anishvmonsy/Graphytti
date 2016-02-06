#ifndef EXPTCYCLE_H
#define EXPTCYCLE_H
#include<QVector>
class exptcycle{


    public:

    exptcycle();
    void enter_point_count(int new_point_count);
    void enter_ex(QVector<double> & new_ex);
    void enter_em(QVector<double> & new_em);
    void enter_cal_em(QVector<double> & new_cal_em);
    void enter_res(QVector<double> & new_res);
    void enter_acorr(QVector<double> & new_acorr);
    void enter_chan(QVector<double> & new_chan);
    void enter_cycle_text(QString new_cycle_text);
    void append_cycle_text(QString more_cycle_text);
    QVector<double> ex;
    QVector<double> em;
    QVector<double> cal_em;
    QVector<double> res;
    QVector<double> acorr;
    QVector<double> chan;
    QString cycle_text;
    int point_count;
    //have to define public methods to return data(that is to be made private)

};

#endif // EXPTCYCLE_H

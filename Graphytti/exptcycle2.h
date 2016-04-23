#ifndef EXPTCYCLE2_H
#define EXPTCYCLE2_H
#include<QVector>

class exptcycle2{
    QVector<double> time;
    QVector<double> ex;
    QVector<double> em_par;
    QVector<double> em_per;
    QVector<double> res1;
    QVector<double> acorr1;
    QVector<double> cal_par;
    QVector<double> cal_per;
    QVector<double> res2;
    QVector<double> acorr2;
    QVector<double> r_exp;
    QVector<double> r_cal;
    QVector<double> chan;
//    QString parameter1;
 //   QString parameter2;
 //   double p_value1;
 //   double p_value2;
    QString cycle_text;
    long point_count;
    bool cycle_is_loaded;
    //to make sure cycle is loaded only once
    public:

    exptcycle2();
    void load_cycle_data(long new_point_count,QVector<double> & new_chan,QVector<double> & new_time,QVector<double> & new_ex,QVector<double> & new_em_par,\
                         QVector<double> & new_em_per,QVector<double> & new_res1,QVector<double> & new_accor1,QVector<double> & new_cal_par,QVector<double> & new_cal_per\
                         ,QVector<double> & new_res2,QVector<double> & new_acorr2,QVector<double> & new_r_exp,QVector<double> & new_r_cal);

    void append_cycle_text(QString more_cycle_text);
    QVector<double> get_time();
    QVector<double> get_ex();
    QVector<double> get_em_par();
    QVector<double> get_em_per();
    QVector<double> get_res1();
    QVector<double> get_acorr1();
    QVector<double> get_cal_par();
    QVector<double> get_cal_per();
    QVector<double> get_res2();
    QVector<double> get_acorr2();
    QVector<double> get_r_exp();
    QVector<double> get_r_cal();
    QVector<double> get_chan();
  //  QString get_parameter1();
   // QString get_parameter2();
   // double get_p_value1();
   // double get_p_value2();
    QString get_cycle_text();
    long get_point_count();

    //have to define public methods to return data(that is to be made private)

};

#endif // EXPTCYCLE2_H

#include "exptcycle.h"

exptcycle::exptcycle(){
    cycle_text="";
    point_count=0;
}

void exptcycle::enter_point_count(int new_point_count){
    point_count=new_point_count;
}

void exptcycle::enter_acorr(QVector<double> &new_acorr){
    acorr=new_acorr;
}
void exptcycle::enter_cal_em(QVector<double> &new_cal_em){
    cal_em=new_cal_em;
}
void exptcycle::enter_chan(QVector<double> &new_chan){
    chan=new_chan;
}
void exptcycle::enter_em(QVector<double> &new_em){
    em=new_em;
}
void exptcycle::enter_ex(QVector<double> &new_ex){
    ex=new_ex;
}
void exptcycle::enter_res(QVector<double> &new_res){
    res=new_res;
}
void exptcycle::enter_cycle_text(QString new_cycle_text){
    cycle_text=new_cycle_text;
}
void exptcycle::append_cycle_text(QString more_cycle_text){
    cycle_text.append(more_cycle_text);
}

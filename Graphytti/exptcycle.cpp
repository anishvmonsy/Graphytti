#include "exptcycle.h"

exptcycle::exptcycle(){
    cycle_text="";
    point_count=0;
    cycle_is_loaded=false;
}

void exptcycle::load_cycle_data(long new_point_count,QVector<double> &new_chan,\
                                QVector<double> &new_ex, \
                                QVector<double> &new_em, QVector<double> &new_cal_em,\
                                QVector<double> &new_res, QVector<double> &new_acorr\
                                ) {
    if(cycle_is_loaded)
        return;
    else{
        point_count=new_point_count;
        acorr=new_acorr;
        cal_em=new_cal_em;
        chan=new_chan;
        em=new_em;
        ex=new_ex;
        res=new_res;
        cycle_is_loaded=true;
    }

}
void exptcycle::append_cycle_text(QString more_cycle_text){
    cycle_text.append(more_cycle_text);
}

QString exptcycle::get_cycle_text(){
    return cycle_text;
}

QVector<double> exptcycle::get_ex(){
    return ex;
}

QVector<double> exptcycle::get_em(){
    return em;
}

QVector<double> exptcycle::get_cal_em(){
    return cal_em;
}

QVector<double> exptcycle::get_res(){
    return res;
}

QVector<double> exptcycle::get_acorr(){
    return acorr;
}

QVector<double> exptcycle::get_chan(){
    return chan;
}

long exptcycle::get_point_count(){
    return point_count;
}

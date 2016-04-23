#include "exptcycle2.h"

exptcycle2::exptcycle2(){
    cycle_text="";
    point_count=0;
    cycle_is_loaded=false;
}



void exptcycle2::load_cycle_data(long new_point_count,QVector<double> & new_chan,QVector<double> & new_time,QVector<double> & new_ex,QVector<double> & new_em_par,\
                                      QVector<double> & new_em_per,QVector<double> & new_res1,QVector<double> & new_acorr1,QVector<double> & new_cal_par,QVector<double> & new_cal_per\
                                      ,QVector<double> & new_res2,QVector<double> & new_acorr2,QVector<double> & new_r_exp,QVector<double> & new_r_cal) {
    if(cycle_is_loaded)
        return;
    else{
        point_count=new_point_count;
        time=new_time;
        ex=new_ex;
        em_par=new_em_par;
        em_per=new_em_per;
        res1=new_res1;
        acorr1=new_acorr1;
        cal_par=new_cal_par;
        cal_per=new_cal_per;
        res2=new_res2;
        acorr2=new_acorr2;
        r_exp=new_r_exp;
        r_cal=new_r_cal;
        chan=new_chan;
//        parameter1=new_parameter1;
//        parameter2=new_parameter2;
//        p_value1=new_p_value1;
//        p_value2=new_p_value2;
        cycle_is_loaded=true;
    }

}
void exptcycle2::append_cycle_text(QString more_cycle_text){
    cycle_text.append(more_cycle_text);
}

QString exptcycle2::get_cycle_text(){
    return cycle_text;
}

QVector<double> exptcycle2::get_time(){
    return time;
}

QVector<double> exptcycle2::get_em_par(){
    return em_par;
}

QVector<double> exptcycle2::get_em_per(){
    return em_per;
}

QVector<double> exptcycle2::get_res1(){
    return res1;
}

QVector<double> exptcycle2::get_acorr1(){
    return acorr1;
}

QVector<double> exptcycle2::get_cal_par(){
    return cal_par;
}

QVector<double> exptcycle2::get_cal_per(){
    return cal_per;
}

QVector<double> exptcycle2::get_res2(){
    return res2;
}

QVector<double> exptcycle2::get_acorr2(){
    return acorr2;
}

QVector<double> exptcycle2::get_r_exp(){
    return r_exp;
}

QVector<double> exptcycle2::get_r_cal(){
    return r_cal;
}

QVector<double> exptcycle2::get_chan(){
    return chan;
}

QVector<double> exptcycle2::get_ex(){
    return ex;
}

//QString exptcycle2::get_parameter1(){
//    return parameter1;
//}
//QString exptcycle2::get_parameter2(){
//    return parameter2;
//}
//double exptcycle2::get_p_value1(){
//    return p_value1;
//}
//double exptcycle2::get_p_value2(){
//    return p_value2;
//}

long exptcycle2::get_point_count(){
    return point_count;
}

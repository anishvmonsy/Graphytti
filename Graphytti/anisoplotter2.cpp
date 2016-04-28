#include "anisoplotter2.h"
#include <QVBoxLayout>
#include<QPushButton>
#include<QHBoxLayout>
#include<QFont>
#include<QTableWidget>
#include<QStringList>
#include "exptcycle2.h"
#include "interactiveplot.h"
#define MAX_POINTS 5000
#define ACORR1_TICK_STEP 2
#define ACORR2_TICK_STEP 2
#define CHANNELS_VIEWED 40

 AnisoPlotter2::AnisoPlotter2(QStackedWidget *centralWindowWidget)
{
    this->centralWindowWidget=centralWindowWidget;
    expt_title="";
    QWidget *dummynew=new QWidget;
    QVBoxLayout *vbox = new QVBoxLayout(dummynew);
    QVBoxLayout *graphLayout=new QVBoxLayout(dummynew);
    QVBoxLayout *sideLayout=new QVBoxLayout(dummynew);
    go_back_button=new QPushButton("Go back",dummynew);
    QHBoxLayout *hbox1=new QHBoxLayout(dummynew);
    rgraph=new InteractivePlot(dummynew);
    acorr1_graph=new InteractivePlot(dummynew);
    acorr2_graph=new InteractivePlot(dummynew);
    expt_title_label= new QLabel(dummynew);
    tableWidget = new QTableWidget(2,2,dummynew);
    prev_button=new QPushButton("Previous Cycle",dummynew);
    next_button=new QPushButton("Next Cycle",dummynew);
    expt_cycle_label=new QLabel(dummynew);
    expt_cycle_label->setWordWrap(true);
    expt_cycle_label->setAlignment(Qt::AlignHCenter);

    sideLayout->addWidget(prev_button,2);
    sideLayout->addWidget(next_button,2);
    sideLayout->addWidget(expt_cycle_label);
    sideLayout->addWidget(tableWidget,2);

    sideLayout->addStretch(1);
    sideLayout->addWidget(go_back_button,2);

    graphLayout->addWidget(rgraph,9);
    graphLayout->addWidget(acorr1_graph,3);
    graphLayout->addWidget(acorr2_graph,3);
    graphLayout->addStretch(2);

    QFont f( "Arial", 20, QFont::Bold);
    expt_title_label->setFont( f);
    vbox->addWidget(expt_title_label,1);
    expt_title_label->setAlignment(Qt::AlignHCenter);


    hbox1->addLayout(graphLayout,5);
    hbox1->addLayout(sideLayout,1);
    vbox->addLayout(hbox1,20);

    dummynew->setLayout(vbox);



    centralWindowWidget->addWidget(dummynew);
    centralWindowWidget->setCurrentIndex(1);

    current_cycle_index=0;
    file_already_open=false;


}


 QPushButton * AnisoPlotter2::getNextButton(){
     return next_button;
 }

 QPushButton * AnisoPlotter2::getPrevButton(){
    return prev_button;
 }
 QPushButton * AnisoPlotter2::getGoBackButton(){
     return go_back_button;
 }



 QVector<QString> AnisoPlotter2::getCycleParameters(QString expt_cycle_text){
      QVector<QString> cycle_parameters;
      QStringList initial_list=expt_cycle_text.split(QRegExp("[=,\n]"));
      for (QStringList::iterator it = initial_list.begin();
               it != initial_list.end(); ++it) {
              QString current = *it;
              QRegularExpression re("^[a-zA-Z \.]*$");  // at least one alphabet(detecting a parameter)
              QString trimmed_current=current.trimmed();
              QRegularExpressionMatch match=re.match(trimmed_current);

              if (match.hasMatch())
                 cycle_parameters.append(trimmed_current);

          }




 //     expt_cycle_label->setText(cycle_parameters[0]);
      return cycle_parameters;


  }
 QVector<QString> AnisoPlotter2::getCycleParameterValues(QString expt_cycle_text){
     QVector<QString> cycle_parameter_values;
     QStringList initial_list=expt_cycle_text.split(QRegExp("[=,\n]"));
     for (QStringList::iterator it = initial_list.begin();
              it != initial_list.end(); ++it) {
             QString current = *it;
             QRegularExpression re("[0-9]");  // at least one alphabet(detecting a parameter)
             QString trimmed_current=current.trimmed();
             QRegularExpressionMatch match=re.match(trimmed_current);

               QString cycle_match = QString("Cycle");
             if (match.hasMatch()&&!trimmed_current.contains(cycle_match))
                cycle_parameter_values.append(trimmed_current);

         }





     return cycle_parameter_values;

 }

 void AnisoPlotter2::plotGraph(){
        plot_rgraph();
        plot_acorr1_graph();
        plot_acorr2_graph();
        QVector<QString> cycle_parameters=getCycleParameters(all_cycles[current_cycle_index].get_cycle_text());
 //        QVgetCycleParameters(all_cycles[current_cycle_index].get_cycle_text());
        QVector<QString> cycle_parameter_values=getCycleParameterValues(all_cycles[current_cycle_index].get_cycle_text());

        QStringList TableHeader;
        TableHeader<<"Parameter"<<"Value";
        tableWidget->setHorizontalHeaderLabels(TableHeader);

        int i;
         for(i=0;i<2;i++){
             tableWidget->setItem(i, 0, new QTableWidgetItem(cycle_parameters[i]));
             tableWidget->setItem(i, 1, new QTableWidgetItem(cycle_parameter_values[i]));
         }

         QFont f( "Arial", 15, QFont::Normal);
         expt_title_label->setFont( f);
         QString cycle_title=all_cycles[current_cycle_index].get_cycle_text().split("\n").at(0).trimmed();
         expt_cycle_label->setText(cycle_title);


 }


 void AnisoPlotter2::plot_rgraph(){

     QVector<double> r_cal=all_cycles[current_cycle_index].get_r_cal();
     QVector<double> time=all_cycles[current_cycle_index].get_time();
     QVector<double> r_exp=all_cycles[current_cycle_index].get_r_exp();


     long point_count=all_cycles[current_cycle_index].get_point_count();



     double max_point=0;
     double min_point=0;
     for(int i=0;i<point_count;i++){
           if(max_point<r_cal[i]){
               max_point=r_cal[i];
           }
           if(max_point<r_exp[i]){
               max_point=r_exp[i];
           }


           if(min_point>r_cal[i]){
               min_point=r_cal[i];
           }
           if(min_point>r_exp[i]){
               min_point=r_exp[i];
           }


       }

     rgraph->setInteraction(QCP::iRangeZoom,true);
     rgraph->setInteraction(QCP::iRangeDrag, true);
     rgraph->setInteraction(QCP::iSelectPlottables,true);
     rgraph->xAxis->setLabel("Time");
     rgraph->yAxis->setLabel("R_EXP And R_CALC");
     rgraph->xAxis->setRange(0,CHANNELS_VIEWED);
     rgraph->yAxis->setRange(min_point,max_point);

     rgraph->addGraph();
     rgraph->graph(0)->setData(time,r_cal);
     rgraph->graph(0)->setPen(QPen(Qt::red));



     rgraph->addGraph();
     rgraph->graph(1)->setData(time,r_exp);
     rgraph->graph(1)->setPen(QPen(Qt::green));



     rgraph->replot();
 }


 void AnisoPlotter2::plot_acorr1_graph(){

     QVector<double> acorr1=all_cycles[current_cycle_index].get_acorr1();
     QVector<double> time=all_cycles[current_cycle_index].get_time();

     long point_count=all_cycles[current_cycle_index].get_point_count();

     double max_point=0;
     double min_point=0;
     for(int i=0;i<point_count;i++){
         if(max_point<acorr1[i]){
             max_point=acorr1[i];
         }
         if(min_point>acorr1[i])
             min_point=acorr1[i];

     }

     acorr1_graph->setInteraction(QCP::iRangeZoom,true);
     acorr1_graph->setInteraction(QCP::iSelectPlottables,true);
     acorr1_graph->setInteraction(QCP::iRangeDrag, true);
     acorr1_graph->xAxis->setLabel("Time");
     acorr1_graph->yAxis->setLabel("Autocorrelation 1");
     acorr1_graph->xAxis->setRange(0,CHANNELS_VIEWED);
     acorr1_graph->yAxis->setRange(floor(min_point),ceil(max_point));
     acorr1_graph->yAxis->setAutoTickStep(false);
     acorr1_graph->yAxis->setTickStep(ACORR1_TICK_STEP);
     acorr1_graph->addGraph();
     acorr1_graph->graph(0)->setData(time,acorr1);
     acorr1_graph->graph(0)->setPen(QPen(Qt::red));


     acorr1_graph->replot();

     ;
 }


 void AnisoPlotter2::plot_acorr2_graph(){
     QVector<double> acorr2=all_cycles[current_cycle_index].get_acorr2();
     QVector<double> time=all_cycles[current_cycle_index].get_time();

     long point_count=all_cycles[current_cycle_index].get_point_count();

     double max_point=0;
     double min_point=0;
     for(int i=0;i<point_count;i++){


         if(max_point<acorr2[i]){
             max_point=acorr2[i];
         }
         if(min_point>acorr2[i])
             min_point=acorr2[i];

     }
     acorr2_graph->setInteraction(QCP::iRangeZoom,true);
     acorr2_graph->setInteraction(QCP::iSelectPlottables,true);
     acorr2_graph->setInteraction(QCP::iRangeDrag, true);
     acorr2_graph->xAxis->setLabel("Time");
     acorr2_graph->yAxis->setLabel("Autocorrelation 2");
     acorr2_graph->yAxis->setAutoTickStep(false);
     acorr2_graph->yAxis->setTickStep(ACORR2_TICK_STEP);
     acorr2_graph->xAxis->setRange(0,CHANNELS_VIEWED);
     acorr2_graph->yAxis->setRange(floor(min_point),ceil(max_point));





     acorr2_graph->addGraph();
     acorr2_graph->graph(0)->setData(time,acorr2);


     acorr2_graph->replot();

 }

 void AnisoPlotter2::parseFile(QString file_path){

     QFile inputFile(file_path);
   //  bool counter=false;


     if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);


           if(all_cycles.empty()){
           all_cycles.push_back(*(new exptcycle2()));
            }

           QString cycle_first_line=in.readLine();
           cycle_first_line.append("\n");
           cycle_first_line.append(in.readLine());
           qDebug()<<cycle_first_line;
           all_cycles[current_cycle_index].append_cycle_text(cycle_first_line);


           QVector<double> chan(MAX_POINTS),ex(MAX_POINTS),em_par(MAX_POINTS),em_per(MAX_POINTS),res1(MAX_POINTS),res2(MAX_POINTS),acorr1(MAX_POINTS),acorr2(MAX_POINTS),time(MAX_POINTS),\
        cal_par(MAX_POINTS),cal_per(MAX_POINTS),r_exp(MAX_POINTS),r_cal(MAX_POINTS);


           bool next_cycle_start=false;
           long point_index=0;
           while (!in.atEnd()&&!next_cycle_start)
           {
              QString file_line = in.readLine();
              QString simplified_line = file_line.trimmed();
              if(simplified_line[0].isNumber())
              {
                  QRegExp rx("(\\ |\\t)");



                  QStringList data_strings =simplified_line.split(rx);


                  int word_index=1;


                  chan[point_index]=data_strings[0].toDouble();

                  while(data_strings[word_index].isEmpty()) word_index++;

                  time[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;


                  ex[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  em_par[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  em_per[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  res1[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;


                  acorr1[point_index]=data_strings[word_index].toDouble();
                  word_index++;



                  while(data_strings[word_index].isEmpty()) word_index++;

                  cal_par[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  cal_per[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  res2[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  acorr2[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  r_exp[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  r_cal[point_index]=data_strings[word_index].toDouble();
                  point_index++;


              }

              else if(simplified_line[0].isLetter())
              {
                  QString left_five=simplified_line.left(5);
                  if(QString::compare(left_five, "Cycle") == 0 ){
                     next_cycle_start=true;
                     cycle_first_line=simplified_line;

                  }

              }
              else{

                 ;
              }

           }


           all_cycles[current_cycle_index].load_cycle_data(point_index,chan,time,ex,em_par,em_per,res1,acorr1,cal_par,cal_per,res2,acorr2,r_exp,r_cal);







           while (!in.atEnd()){
             all_cycles.push_back(*(new exptcycle2));

             current_cycle_index++;
             cycle_first_line.append("\n");
             cycle_first_line.append(in.readLine().trimmed());
             all_cycles[current_cycle_index].append_cycle_text(cycle_first_line);



             bool chan_reached=false;


             while(!in.atEnd()&&!chan_reached){

                 QString file_line = in.readLine();
                 QString simplified_line = file_line.trimmed();

                 if(simplified_line[0].isLetter()){
                     QString left_three=simplified_line.left(3);

                     if(QString::compare(left_three, "ch#") == 0 ){
                         chan_reached=true;

                     }
                     else{


                         ;

                     }
                 }
             }
             next_cycle_start=false;
             point_index=0;
             while(!in.atEnd()&&!next_cycle_start){

                 QString file_line = in.readLine();
                 QString simplified_line = file_line.trimmed();
                 if(simplified_line[0].isNumber()){
                     QRegExp rx("(\\ |\\t)");



                     QStringList data_strings =simplified_line.split(rx);


                     int word_index=1;


                  chan[point_index]=data_strings[0].toDouble();

                  while(data_strings[word_index].isEmpty()) word_index++;

                  time[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;


                  ex[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  em_par[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  em_per[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  res1[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;


                  acorr1[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;


                  cal_par[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  cal_per[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  res2[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  acorr2[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  r_exp[point_index]=data_strings[word_index].toDouble();
                  word_index++;

                  while(data_strings[word_index].isEmpty()) word_index++;

                  r_cal[point_index]=data_strings[word_index].toDouble();
                  point_index++;
                 }

                 else if(simplified_line[0].isLetter()){
                     QString left_five=simplified_line.left(5);
                     if(QString::compare(left_five, "Cycle") == 0 ){
                        next_cycle_start=true;
                        cycle_first_line=simplified_line;

                     }
                 }
                 else{

                    ;
                 }
             }

             all_cycles[current_cycle_index].load_cycle_data(point_index,chan,time,ex,em_par,em_per,res1,acorr1,cal_par,cal_per,res2,acorr2,r_exp,r_cal);
//             all_cycles[current_cycle_index].append_cycle_text(cycle_first_line);




           }




           inputFile.close();
     }
     current_cycle_index=0;




 }


 int  AnisoPlotter2::checkFile(QString){return 0;}
 void AnisoPlotter2::prevCycle(){

     current_cycle_index=(current_cycle_index-1)%all_cycles.size();
     plotGraph();

 }
 void AnisoPlotter2::nextCycle(){
     current_cycle_index=(current_cycle_index+1)%all_cycles.size();
     plotGraph();

 }

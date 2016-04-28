#include "anisoplotter.h"
#include <QVBoxLayout>
#include<QPushButton>
#include<QHBoxLayout>
#include<QFont>
#include<QTableWidget>
#include<QStringList>
#include "exptcycle.h"
#include "interactiveplot.h"
#define MAX_POINTS 5000
#define RES1_TICK_STEP 2
#define RES2_TICK_STEP 2
#define CHANNELS_VIEWED 40

 AnisoPlotter::AnisoPlotter(QStackedWidget *centralWindowWidget)
{
    this->centralWindowWidget=centralWindowWidget;
    expt_title="";
    QWidget *dummynew=new QWidget;
    QVBoxLayout *vbox = new QVBoxLayout(dummynew);
    QVBoxLayout *graphLayout=new QVBoxLayout(dummynew);
    QVBoxLayout *sideLayout=new QVBoxLayout(dummynew);
    go_back_button=new QPushButton("Go back",dummynew);
    QHBoxLayout *hbox1=new QHBoxLayout(dummynew);
    aniso_graph=new InteractivePlot(dummynew);
    res1_graph=new InteractivePlot(dummynew);
    res2_graph=new InteractivePlot(dummynew);

    expt_title_label= new QLabel(dummynew);
    prev_button=new QPushButton("Previous Cycle",dummynew);
    next_button=new QPushButton("Next Cycle",dummynew);
    expt_cycle_label=new QLabel(dummynew);
    tableWidget = new QTableWidget(2,2,dummynew);
    expt_cycle_label->setWordWrap(true);
    expt_cycle_label->setAlignment(Qt::AlignHCenter);


    sideLayout->addWidget(prev_button,2);
    sideLayout->addWidget(next_button,2);
    sideLayout->addWidget(expt_cycle_label);
    sideLayout->addWidget(tableWidget,2);
    sideLayout->addStretch(1);



    sideLayout->addWidget(go_back_button,2);
    graphLayout->addWidget(aniso_graph,9);
    graphLayout->addWidget(res1_graph,2);
    graphLayout->addWidget(res2_graph,2);

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
 QPushButton * AnisoPlotter::getNextButton(){
     return next_button;
 }

 QPushButton * AnisoPlotter::getPrevButton(){
    return prev_button;
 }
 QPushButton * AnisoPlotter::getGoBackButton(){
     return go_back_button;
 }

 QVector<QString> AnisoPlotter::getCycleParameters(QString expt_cycle_text){
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
 QVector<QString> AnisoPlotter::getCycleParameterValues(QString expt_cycle_text){
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


 void AnisoPlotter::plotGraph(){
        plot_aniso_graph();
        plot_res1_graph();
        plot_res2_graph();
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
 void AnisoPlotter::plot_aniso_graph(){

     QVector<double> ex=all_cycles[current_cycle_index].get_ex();
     QVector<double> time=all_cycles[current_cycle_index].get_time();
     QVector<double> em_per=all_cycles[current_cycle_index].get_em_per();
     QVector<double> em_par=all_cycles[current_cycle_index].get_em_par();
     QVector<double> cal_par=all_cycles[current_cycle_index].get_cal_par();
     QVector<double> cal_per=all_cycles[current_cycle_index].get_cal_per();

     long point_count=all_cycles[current_cycle_index].get_point_count();
     for(int i=0;i<point_count;i++){
         if(ex[i]!=0){
             ex[i]=log10(ex[i]);
         }
         if(em_per[i]!=0){
             em_per[i]=log10(em_per[i]);
         }
         if(em_par[i]!=0){
             em_par[i]=log10(em_par[i]);
         }
         if(cal_per[i]!=0){
             cal_per[i]=log10(cal_per[i]);
         }
         if(cal_par[i]!=0){
             cal_par[i]=log10(cal_par[i]);
         }
     }
     double max_point=0;
     double min_point=0;
     for(int i=0;i<point_count;i++){
           if(max_point<ex[i]){
               max_point=ex[i];
           }
           if(max_point<em_par[i]){
               max_point=em_par[i];
           }
           if(max_point<em_per[i]){
               max_point=em_per[i];
           }
           if(max_point<cal_par[i]){
               max_point=cal_per[i];
           }
           if(max_point<cal_per[i]){
               max_point=cal_per[i];
           }

           if(min_point>ex[i]){
               min_point=ex[i];
           }
           if(min_point>em_par[i]){
               min_point=em_par[i];
           }
           if(min_point>em_per[i]){
               min_point=em_per[i];
           }
           if(min_point>cal_par[i]){
               min_point=cal_per[i];
           }
           if(min_point>cal_per[i]){
               min_point=cal_per[i];
           }

       }

     aniso_graph->setInteraction(QCP::iRangeZoom,true);
     aniso_graph->setInteraction(QCP::iRangeDrag, true);
     aniso_graph->setInteraction(QCP::iSelectPlottables,true);
     aniso_graph->xAxis->setLabel("Time");
     aniso_graph->yAxis->setLabel("Intensity(log10 scale)");
     aniso_graph->xAxis->setRange(0,CHANNELS_VIEWED);
     aniso_graph->yAxis->setRange(min_point,max_point);

     aniso_graph->addGraph();
     aniso_graph->graph(0)->setData(time,ex);
     aniso_graph->graph(0)->setPen(QPen(Qt::red));



     aniso_graph->addGraph();
     aniso_graph->graph(1)->setData(time,em_par);
     aniso_graph->graph(1)->setPen(QPen(Qt::black));


     aniso_graph->addGraph();
     aniso_graph->graph(2)->setData(time,em_per);
     aniso_graph->graph(2)->setPen(QPen(Qt::magenta));

     aniso_graph->addGraph();
     aniso_graph->graph(3)->setData(time,cal_par);
     aniso_graph->graph(3)->setPen(QPen(Qt::blue));

     aniso_graph->addGraph();
     aniso_graph->graph(4)->setData(time,cal_per);
     aniso_graph->graph(4)->setPen(QPen(Qt::green));

     aniso_graph->replot();
 }



 void AnisoPlotter::plot_res1_graph(){

     QVector<double> res1=all_cycles[current_cycle_index].get_res1();
     QVector<double> time=all_cycles[current_cycle_index].get_time();

     long point_count=all_cycles[current_cycle_index].get_point_count();

     double max_point=0;
     double min_point=0;
     for(int i=0;i<point_count;i++){
         if(max_point<res1[i]){
             max_point=res1[i];
         }
         if(min_point>res1[i])
             min_point=res1[i];




     }

     res1_graph->setInteraction(QCP::iRangeZoom,true);
     res1_graph->setInteraction(QCP::iSelectPlottables,true);
     res1_graph->setInteraction(QCP::iRangeDrag, true);
     res1_graph->xAxis->setLabel("Time");
     res1_graph->yAxis->setLabel("Residuals 1");
     res1_graph->xAxis->setRange(0,CHANNELS_VIEWED);
     res1_graph->yAxis->setRange(floor(min_point),ceil(max_point));
     res1_graph->yAxis->setAutoTickStep(false);
     res1_graph->yAxis->setTickStep(RES1_TICK_STEP);
     res1_graph->addGraph();
     res1_graph->graph(0)->setData(time,res1);
     res1_graph->graph(0)->setPen(QPen(Qt::red));


     res1_graph->replot();

     ;
 }




 void AnisoPlotter::plot_res2_graph(){
     QVector<double> res2=all_cycles[current_cycle_index].get_res2();
     QVector<double> time=all_cycles[current_cycle_index].get_time();

     long point_count=all_cycles[current_cycle_index].get_point_count();

     double max_point=0;
     double min_point=0;
     for(int i=0;i<point_count;i++){


         if(max_point<res2[i]){
             max_point=res2[i];
         }
         if(min_point>res2[i])
             min_point=res2[i];

     }
     res2_graph->setInteraction(QCP::iRangeZoom,true);
     res2_graph->setInteraction(QCP::iSelectPlottables,true);
     res2_graph->setInteraction(QCP::iRangeDrag, true);
     res2_graph->xAxis->setLabel("Time");
     res2_graph->yAxis->setLabel("Residual 2");
     res2_graph->yAxis->setAutoTickStep(false);
     res2_graph->yAxis->setTickStep(RES2_TICK_STEP);
     res2_graph->xAxis->setRange(0,CHANNELS_VIEWED);
     res2_graph->yAxis->setRange(floor(min_point),ceil(max_point));





     res2_graph->addGraph();
     res2_graph->graph(0)->setData(time,res2);


     res2_graph->replot();

 }
 void AnisoPlotter::parseFile(QString file_path){

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
 int  AnisoPlotter::checkFile(QString){return 0;}
 void AnisoPlotter::prevCycle(){

     current_cycle_index=(current_cycle_index+all_cycles.size()-1)%all_cycles.size();
     plotGraph();

 }
 void AnisoPlotter::nextCycle(){
     current_cycle_index=(current_cycle_index+1)%all_cycles.size();
     plotGraph();


 }

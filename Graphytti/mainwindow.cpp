#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MAX_POINTS 5000
#define RES_TICK_STEP 2
#define ACORR_TICK_STEP 0.6
#define CHANNELS_VIEWED 150

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    expt_title="";
    current_cycle_index=0;
    file_already_open=false;
}

MainWindow::~MainWindow()
{
    all_cycles.clear();
    delete ui;
}


void MainWindow::on_file_button_clicked()
{

    QString file_path= QFileDialog::getOpenFileName(this,
                                                       tr("Open a file"),
                                                       QDir().rootPath(),
                                                       "All files (*)");
    if(file_path.isEmpty()){
        QMessageBox::information(this,tr("No file selected"),"Please choose a file to continue");
    }
    else{
        QMessageBox::information(this,tr("File Path"),file_path);
        if(file_already_open){
            all_cycles.clear();
            current_cycle_index=0;
            expt_title="";
        }
        else{
            file_already_open=true;

        }
        file_parser(file_path);
        plot_fluor_graph();
        plot_res_graph();
        plot_acorr_graph();



    }

}
void MainWindow::file_parser(QString file_path){
    QFile inputFile(file_path);
    bool counter=false;  // to make sure that parsing gets over after reading the cycle_text
    bool star_counter=false;//to make sure the graph_title is taken care of(graph_title occurs one line after )

    if (inputFile.open(QIODevice::ReadOnly))
       {
          QTextStream in(&inputFile);


          while (!in.atEnd()&&!counter)
          {
             QString file_line = in.readLine();            //read every line
             QString simplified_line = file_line.trimmed(); /*remove white spaces at the beginning and end
                                                              of every line*/

             //if there is a title of the result file
             if(simplified_line[0]=='*'){
                 star_counter=true;
             }
             else if(star_counter==true){
                 expt_title.append(simplified_line);
                 //expt_title.append("</b>");
                 star_counter=false;                                      //set up the title of the experiment
                 ui->expt_label->setText(expt_title);
             }
             else if(simplified_line[0].isLetter()){
                 QString left_four=simplified_line.left(4);        //get first 4 characters of the line after
                                                                    //first non-whitespace character
                 if(QString::compare(left_four, "chan") == 0 ){     //check whether cycle data has been reached yet
                     counter=true;

                 }
                 else{
                     if(all_cycles.empty()){
                     all_cycles.push_back(*(new exptcycle()));

                     }
                     simplified_line.append("\n");
                     all_cycles[0].append_cycle_text(simplified_line);           //otherwise append to the cycle_text
                 }

             }


          }

          ui->cycle_label->setText(all_cycles[current_cycle_index].cycle_text);

          QString cycle_first_line;//used for  storing the first line of the next cycle

          QVector<double> chan(MAX_POINTS),ex(MAX_POINTS),em(MAX_POINTS),cal_em(MAX_POINTS),res(MAX_POINTS),acorr(MAX_POINTS);
          //now extracting the fields for making the graph
          bool next_cycle_start=false;    //this takes care that data is extracted only for this particular cycle
          long point_index=0;     // this variable indicates which point is being extracted at the moment
          while (!in.atEnd()&&!next_cycle_start)
          {
             QString file_line = in.readLine();
             QString simplified_line = file_line.trimmed();
             if(simplified_line[0].isNumber()){
                 QRegExp rx("(\\ |\\t)"); //regular expression for ' ' or  '\t'


                 /* The below method breaks the string into multiple strings based on the separators
                  * in the regular expression while keeping the separators in the String list as well
                 */
                 QStringList data_strings =simplified_line.split(rx);


                 int word_index=1;
                 //word_index allows to understand where the appropriate number strings are in the list

                 chan[point_index]=data_strings[0].toDouble();

                 //after taking first number string we skip the remaining empty strings in the list
                 while(data_strings[word_index].isEmpty()) word_index++;

                 ex[point_index]=data_strings[word_index].toDouble();
                 word_index++;

                 while(data_strings[word_index].isEmpty()) word_index++;

                 em[point_index]=data_strings[word_index].toDouble();
                 word_index++;

                 while(data_strings[word_index].isEmpty()) word_index++;

                 cal_em[point_index]=data_strings[word_index].toDouble();
                 word_index++;

                 while(data_strings[word_index].isEmpty()) word_index++;

                 res[point_index]=data_strings[word_index].toDouble();
                 word_index++;

                 while(data_strings[word_index].isEmpty()) word_index++;

                 acorr[point_index]=data_strings[word_index].toDouble();
                 point_index++;

             }

             //this checks whether the next cycle has started or not
             else if(simplified_line[0].isLetter()){
                 QString left_five=simplified_line.left(5);
                 if(QString::compare(left_five, "Cycle") == 0 ){
                    next_cycle_start=true;
                    cycle_first_line=simplified_line;
                    cycle_first_line.append("\n");
                 }


             }

          }

          //Loading the parsed data into the current_cycle
          all_cycles[current_cycle_index].enter_point_count(point_index);
          all_cycles[current_cycle_index].enter_ex(ex);
          all_cycles[current_cycle_index].enter_chan(chan);
          all_cycles[current_cycle_index].enter_em(em);
          all_cycles[current_cycle_index].enter_cal_em(cal_em);
          all_cycles[current_cycle_index].enter_res(res);
          all_cycles[current_cycle_index].enter_acorr(acorr);



          //loading cycles after first one




          while (!in.atEnd()){
            all_cycles.push_back(*(new exptcycle));
            current_cycle_index++;
            all_cycles[current_cycle_index].append_cycle_text(cycle_first_line);


            bool chan_reached=false;        //if chan line is reached then true

            //this while loop for collecting cycle text data until chan line is reached
            while(!in.atEnd()&&!chan_reached){

                QString file_line = in.readLine();
                QString simplified_line = file_line.trimmed();

                if(simplified_line[0].isLetter()){
                    QString left_four=simplified_line.left(4);        //get first 4 characters of the line after
                                                                       //first non-whitespace character
                    if(QString::compare(left_four, "chan") == 0 ){     //check whether cycle data has been reached yet
                        chan_reached=true;

                    }
                    else{


                        simplified_line.append("\n");
                        all_cycles[current_cycle_index].append_cycle_text(simplified_line);           //otherwise append to the cycle_text
                    }
                }
            }
            next_cycle_start=false;
            point_index=0;
            while(!in.atEnd()&&!next_cycle_start){

                QString file_line = in.readLine();
                QString simplified_line = file_line.trimmed();
                if(simplified_line[0].isNumber()){
                    QRegExp rx("(\\ |\\t)"); //regular expression for ' ' or  '\t'


                    /* The below method breaks the string into multiple strings based on the separators
                     * in the regular expression while keeping the separators in the String list as well
                    */
                    QStringList data_strings =simplified_line.split(rx);


                    int word_index=1;
                    //word_index allows to understand where the appropriate number strings are in the list

                    chan[point_index]=data_strings[0].toDouble();

                    //after taking first number string we skip the remaining empty strings in the list
                    while(data_strings[word_index].isEmpty()) word_index++;

                    ex[point_index]=data_strings[word_index].toDouble();
                    word_index++;

                    while(data_strings[word_index].isEmpty()) word_index++;

                    em[point_index]=data_strings[word_index].toDouble();
                    word_index++;

                    while(data_strings[word_index].isEmpty()) word_index++;

                    cal_em[point_index]=data_strings[word_index].toDouble();
                    word_index++;

                    while(data_strings[word_index].isEmpty()) word_index++;

                    res[point_index]=data_strings[word_index].toDouble();
                    word_index++;

                    while(data_strings[word_index].isEmpty()) word_index++;

                    acorr[point_index]=data_strings[word_index].toDouble();
                    point_index++;

                }

                else if(simplified_line[0].isLetter()){
                    QString left_five=simplified_line.left(5);
                    if(QString::compare(left_five, "Cycle") == 0 ){
                       next_cycle_start=true;
                       cycle_first_line=simplified_line;
                       cycle_first_line.append("\n");
                    }


                }
                else{

                   ;
                }
            }
            //Loading the parsed data into the current_cycle
            all_cycles[current_cycle_index].enter_point_count(point_index);
            all_cycles[current_cycle_index].enter_ex(ex);
            all_cycles[current_cycle_index].enter_chan(chan);
            all_cycles[current_cycle_index].enter_em(em);
            all_cycles[current_cycle_index].enter_cal_em(cal_em);
            all_cycles[current_cycle_index].enter_res(res);
            all_cycles[current_cycle_index].enter_acorr(acorr);



          }




          inputFile.close();
    }




}


void MainWindow::plot_fluor_graph(){

    QVector<double> ex=all_cycles[current_cycle_index].ex;
    QVector<double> chan=all_cycles[current_cycle_index].chan;
    QVector<double> em=all_cycles[current_cycle_index].em;
    QVector<double> cal_em=all_cycles[current_cycle_index].cal_em;
    int point_count=all_cycles[current_cycle_index].point_count;
    for(int i=0;i<point_count;i++){
        ex[i]=log10(ex[i]);
        em[i]=log10(em[i]);
        cal_em[i]=log10(cal_em[i]);
    }
    double max_point=0;
    double min_point=0;
    for(int i=0;i<point_count;i++){
          if(max_point<ex[i]){
              max_point=ex[i];
          }
          if(max_point<em[i]){
              max_point=em[i];
          }
          if(max_point<cal_em[i]){
              max_point=cal_em[i];
          }
          if(min_point>ex[i]){
              min_point=ex[i];
          }
          if(min_point>em[i]){
              min_point=em[i];
          }
          if(min_point>cal_em[i]){
              min_point=cal_em[i];
          }
      }

    ui->fluor_graph->setInteraction(QCP::iRangeDrag, true);
    ui->fluor_graph->xAxis->setLabel("ChannelNo.");
    ui->fluor_graph->yAxis->setLabel("Intensity(log10 scale)");
    ui->fluor_graph->xAxis->setRange(0,CHANNELS_VIEWED);
    ui->fluor_graph->yAxis->setRange(min_point,max_point);

    ui->fluor_graph->addGraph();
    ui->fluor_graph->graph(0)->setData(chan,ex);
    ui->fluor_graph->graph(0)->setPen(QPen(Qt::red));



    ui->fluor_graph->addGraph();
    ui->fluor_graph->graph(1)->setData(chan,em);
    ui->fluor_graph->graph(1)->setPen(QPen(Qt::black));


    ui->fluor_graph->addGraph();
    ui->fluor_graph->graph(2)->setData(chan,cal_em);
    ui->fluor_graph->graph(2)->setPen(QPen(Qt::yellow));

    ui->fluor_graph->replot();
}

void MainWindow::plot_res_graph(){

    QVector<double> res=all_cycles[current_cycle_index].res;
    QVector<double> chan=all_cycles[current_cycle_index].chan;

    int point_count=all_cycles[current_cycle_index].point_count;

    double max_point=0;
    double min_point=0;
    for(int i=0;i<point_count;i++){
        if(max_point<res[i]){
            max_point=res[i];
        }
        if(min_point>res[i])
            min_point=res[i];
      //  QTextStream(stdout) << ex[i]<< endl;



    }


    ui->res_graph->setInteraction(QCP::iRangeDrag, true);
    ui->res_graph->xAxis->setLabel("ChannelNo.");
    ui->res_graph->yAxis->setLabel("Residuals");
    ui->res_graph->xAxis->setRange(0,CHANNELS_VIEWED);
    ui->res_graph->yAxis->setRange(floor(min_point),ceil(max_point));
    ui->res_graph->yAxis->setAutoTickStep(false);   //to prevent crowding of tick labels on the y axis
    ui->res_graph->yAxis->setTickStep(RES_TICK_STEP);
    ui->res_graph->addGraph();
    ui->res_graph->graph(0)->setData(chan,res);
    ui->res_graph->graph(0)->setPen(QPen(Qt::red));


    ui->res_graph->replot();

    ;
}
void MainWindow::plot_acorr_graph(){
    QVector<double> acorr=all_cycles[current_cycle_index].acorr;
    QVector<double> chan=all_cycles[current_cycle_index].chan;

    int point_count=all_cycles[current_cycle_index].point_count;

    double max_point=0;
    double min_point=0;
    for(int i=0;i<point_count;i++){


        if(max_point<acorr[i]){
            max_point=acorr[i];
        }
        if(min_point>acorr[i])
            min_point=acorr[i];

    }
    ui->acorr_graph->setInteraction(QCP::iRangeDrag, true);
    ui->acorr_graph->xAxis->setLabel("ChannelNo.");
    ui->acorr_graph->yAxis->setLabel("Auto-corr");
    ui->acorr_graph->yAxis->setAutoTickStep(false);
    ui->acorr_graph->yAxis->setTickStep(ACORR_TICK_STEP);
    ui->acorr_graph->xAxis->setRange(0,CHANNELS_VIEWED);
    ui->acorr_graph->yAxis->setRange(floor(min_point),ceil(max_point));





    ui->acorr_graph->addGraph();
    ui->acorr_graph->graph(0)->setData(chan,acorr);


    ui->acorr_graph->replot();

}


void MainWindow::on_prev_cycle_button_clicked()
{
    current_cycle_index=(current_cycle_index-1)%all_cycles.size();
    ui->cycle_label->setText(all_cycles[current_cycle_index].cycle_text);
    plot_acorr_graph();
    plot_fluor_graph();
    plot_res_graph();
}

void MainWindow::on_next_cycle_button_clicked()
{
    current_cycle_index=(current_cycle_index+1)%all_cycles.size();
    ui->cycle_label->setText(all_cycles[current_cycle_index].cycle_text);
    plot_acorr_graph();
    plot_fluor_graph();
    plot_res_graph();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MAX_POINTS 5000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    expt_title="";
}

MainWindow::~MainWindow()
{
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
        file_parser(file_path);
        plot_fluor_graph();
        plot_res_graph();



    }

}
void MainWindow::file_parser(QString file_path){
    QFile inputFile(file_path);
    int counter=0;  // to make sure that parsing gets over after reading the cycle_text
    int star_counter=0;//to make sure the graph_title is taken care of
    if (inputFile.open(QIODevice::ReadOnly))
       {
          QTextStream in(&inputFile);
          while (!in.atEnd()&&!counter)
          {
             QString file_line = in.readLine();            //read every line
             QString simplified_line = file_line.trimmed(); /*remove white spaces at the beginning and end
                                                              of every line*/
             if(simplified_line[0]=='*'){
                 star_counter=1;
             }
             else if(star_counter==1){
                 expt_title.append(simplified_line);
                 star_counter=0;                                      //set up the title of the experiment
                 ui->expt_label->setText(expt_title);
             }
             else if(simplified_line[0].isLetter()){
                 QString left_four=simplified_line.left(4);        //get first 4 characters of the line after
                                                                    //first non-whitespace character
                 if(QString::compare(left_four, "chan") == 0 ){     //check whether cycle data has been reached yet
                     counter=1;

                 }
                 else{
                     simplified_line.append("\n");
                     current_cycle.append_cycle_text(simplified_line);           //otherwise append to the cycle_text
                 }

             }


          }

          ui->cycle_label->setText(current_cycle.cycle_text);


          QVector<double> chan(MAX_POINTS),ex(MAX_POINTS),em(MAX_POINTS),cal_em(MAX_POINTS),res(MAX_POINTS),acorr(MAX_POINTS);
          //now extracting the fields for making the graph
          counter=0;    //this takes care that data is extracted only for first cycle
          int point_index=0;     // this variable indicates which point is being extracted at the moment
          while (!in.atEnd()&&!counter)
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
                     counter=1;

                 }


             }

          }

          //Loading the parsed data into the current_cycle
          current_cycle.enter_point_count(point_index);
          current_cycle.enter_ex(ex);
          current_cycle.enter_chan(chan);
          current_cycle.enter_em(em);
          current_cycle.enter_cal_em(cal_em);
          current_cycle.enter_res(res);
          current_cycle.enter_acorr(acorr);
          inputFile.close();
    }




}

void MainWindow::plot_fluor_graph(){
    double max_point=0;
    QVector<double> ex=current_cycle.ex;
    QVector<double> chan=current_cycle.chan;
    QVector<double> em=current_cycle.em;
    QVector<double> cal_em=current_cycle.cal_em;
    int point_count=current_cycle.point_count;
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



      }


    ui->fluor_graph->xAxis->setLabel("ChannelNo.");
    ui->fluor_graph->yAxis->setLabel("Intensity");
    ui->fluor_graph->xAxis->setRange(0,150);
    ui->fluor_graph->yAxis->setRange(0,ceil(max_point));

    ui->fluor_graph->addGraph();
    ui->fluor_graph->graph(0)->setData(chan,ex);
    ui->fluor_graph->graph(0)->setPen(QPen(Qt::red));



    ui->fluor_graph->addGraph();
    ui->fluor_graph->graph(1)->setData(chan,em);
    ui->fluor_graph->graph(1)->setPen(QPen(Qt::green));


    ui->fluor_graph->addGraph();
    ui->fluor_graph->graph(2)->setData(chan,cal_em);

    ui->fluor_graph->replot();
}

void MainWindow::plot_res_graph(){

    QVector<double> res=current_cycle.res;
    QVector<double> chan=current_cycle.chan;
    QVector<double> acorr=current_cycle.acorr;
    int point_count=current_cycle.point_count;

    double max_point=0;
    double min_point=0;
    for(int i=0;i<point_count;i++){
        if(max_point<res[i]){
            max_point=res[i];
        }
        if(min_point>res[i])
            min_point=res[i];
      //  QTextStream(stdout) << ex[i]<< endl;

        if(max_point<acorr[i]){
            max_point=acorr[i];
        }
        if(min_point>acorr[i])
            min_point=acorr[i];

    }


    ui->res_graph->setInteraction(QCP::iRangeDrag, true);
    ui->res_graph->xAxis->setLabel("ChannelNo.");
    ui->res_graph->yAxis->setLabel("Residuals");
    ui->res_graph->xAxis->setRange(0,150);
    ui->res_graph->yAxis->setRange(floor(min_point),ceil(max_point));

    ui->res_graph->addGraph();
    ui->res_graph->graph(0)->addData(chan,res);
    ui->res_graph->graph(0)->setPen(QPen(Qt::red));




    ui->res_graph->addGraph();
    ui->res_graph->graph(1)->addData(chan,acorr);


    ui->res_graph->replot();

    ;
}


#include "interactiveplot.h"

InteractivePlot::InteractivePlot(QWidget * parent)
    : QCustomPlot(parent)

{
    connect(this, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
}
void InteractivePlot::showPointToolTip(QMouseEvent *event)
{

   double x = this->xAxis->pixelToCoord(event->pos().x());
   double approx_y;

   // the below condition check whether a graph is selected
   if(this->selectedGraphs().count() != 0){
       QCPDataMap *graph_data_map=this->selectedGraphs().first()->data();

       //making sure the x is in the appropriate range of the defined coordinates
       if(graph_data_map->find(ceil(x))!=graph_data_map->end()){
           QCPDataMap::iterator it_upper=graph_data_map->upperBound(x);
           double upper_x=it_upper.key();
           double upper_y=it_upper->value;
           QCPDataMap::iterator it_morelower=graph_data_map->find(upper_x-1);


           //if lower coordinate in the range
           if(it_morelower!=graph_data_map->end()){
              double lower_x=it_morelower.key();
              double lower_y=it_morelower->value;
              //based on coordinate geometry
              double slope=(upper_y-lower_y)/(upper_x-lower_x);
              approx_y= slope*(x-lower_x)+lower_y;
           }
           else{
               approx_y=upper_y;
           }




       }
       else{
           approx_y=0;
       }
       setToolTip(QString("%1 , %2").arg(x).arg(approx_y));
   }
}

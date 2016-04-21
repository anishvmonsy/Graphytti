#ifndef GRAPHPLOTTER_H
#define GRAPHPLOTTER_H
#include<QStackedWidget>
#include<QPushButton>
class GraphPlotter{

    protected:
    int current_cycle_index;
    bool file_already_open;
    QStackedWidget *centralWindowWidget;


    public:

    virtual void plotGraph()=0;
    virtual void parseFile(QString)=0;
    virtual int  checkFile(QString)=0;
    virtual void nextCycle()=0;
    virtual void prevCycle()=0;
    virtual  QPushButton *getNextButton()=0;
    virtual  QPushButton *getPrevButton()=0;
    virtual  QPushButton *getGoBackButton()=0;



};

#endif // GRAPHPLOTTER_H

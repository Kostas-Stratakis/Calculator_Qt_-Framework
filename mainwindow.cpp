#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcval=0.0;
bool divtrigger=false;
bool multtrigger=false;
bool addtrigger=false;
bool subtrigger=false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcval));
    QPushButton *numbtn[10];
    for(int i=0; i<10;i++){
        QString btnname="Btn_" +QString::number(i);
        numbtn[i]=MainWindow::findChild<QPushButton *> (btnname);
        connect(numbtn[i],SIGNAL(released()),this, SLOT(NumPressed()));
    }
    connect(ui->Btn_plus,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Btn_minus,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Btn_div,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Btn_multi,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Btn_equal,SIGNAL(released()),this,SLOT(EqualButton()));
    connect(ui->Btn_plusminus,SIGNAL(released()),this,SLOT(ChangeNumberSign()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button= (QPushButton*)sender();
    QString butval=button->text();
    QString disval=ui->Display->text();
    if((disval.toDouble()==0)|| disval.toDouble()==0.0){
       ui->Display->setText(butval) ;
    }
    else{
        QString newval=disval+butval;
        double dblnewval=newval.toDouble();
        ui->Display->setText(QString::number(dblnewval,'g',16));
    }

}

void MainWindow::MathButtonPressed(){
    divtrigger=false;
    multtrigger=false;
    addtrigger=false;
    subtrigger=false;
    QString disval= ui->Display->text();
    calcval=disval.toDouble();
    QPushButton *button= (QPushButton *) sender();
    QString butval=button->text();
    if(QString:: compare(butval,"/",Qt::CaseInsensitive)==0){
        divtrigger=true;

    }
    else if(QString:: compare(butval,"*",Qt::CaseInsensitive)==0){
        multtrigger=true;
    }
    else if(QString:: compare(butval,"+",Qt::CaseInsensitive)==0){
        addtrigger=true;
    }
    else {
        subtrigger=true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButton(){
    double sol=0.0;
    QString disval=ui->Display->text();
    double dbldisval=disval.toDouble();
    if(addtrigger || subtrigger ||multtrigger|| divtrigger){
        if(addtrigger){
          sol=calcval +dbldisval;
    }
        else if(multtrigger){
           sol=calcval *dbldisval;
        }
        else if(subtrigger){
           sol=calcval -dbldisval;
        }
        else {
           sol=calcval / dbldisval;
        }
    }
    ui->Display->setText(QString::number(sol));

}
void MainWindow::ChangeNumberSign(){
    QString disval=ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(disval)){
        double dbldisval= disval.toDouble();
        double dbldisvalsign=-1 *dbldisval;
        ui->Display->setText(QString::number(dbldisvalsign));

    }
}

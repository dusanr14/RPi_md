#include "dialog.h"
#include "ui_dialog.h"

const char PCF8591 = 0x48; // adresa

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
        fd = wiringPiI2CSetup(PCF8591);
        myTimer1 = new QTimer(this);
        connect(myTimer1, SIGNAL(timeout()), this,SLOT(Read()));
        t=0;
        //kreiranje podataka za prikaz
         series = new QLineSeries();


         chart = new QChart();
         chart->legend()->hide();
         chart->addSeries(series);
         chart->createDefaultAxes();
         //postavljanje opsega
         chart->axisX()->setMin(0);
         chart->axisX()->setMax(5);
         //2. način za postavljanje opsega
         chart->axisY()->setRange(0,3.3);
         chart->setTitle("Merenje napona");

         chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);

         //postavljanje grafika u vertikal layout
         ui->verticalLayout->addWidget(chartView);
}
void Dialog::Read()
{
    wiringPiI2CReadReg8(fd, PCF8591 + 3) ; // dummy
    adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3)*3.3/255 ;

    if(obrisi)
    {
        obrisi=0;
        t=0;
        series->clear();
    }
    if(t==6)
    {
        series->clear();
        t=0;
    }
    series->append(t, adcVal);
    t++;
     chartView->update();


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    obrisi=1;
}

void Dialog::on_pushButton_2_clicked()
{
    myTimer1->start(1000);
}

#include "dialog.h"
#include "ui_dialog.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

int click = 0;
int cnt = 0;

FILE *log;
char tekst[100];
const char NESTO = 0x48;
int fd, adcVal;
double vr;

QLineSeries *series = new QLineSeries();

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup();
    fd = wiringPiI2CSetup(NESTO);

    QTimer *myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(rtcTimer()));
    myTimer->start(1000);

    QChart *chart = new QChart();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setMin(0);
    chart->axisX()->setMax(5);
    chart->axisY()->setMin(0);
    chart->axisY()->setMax(3.3);

    chart -> setTitle("Merenje napona");

    QChartView *chartView = new QChartView(chart);

    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()    chart -> setTitle("Merenje napona");
{
    click = 1;
}

void Dialog::rtcTimer()
{


    if (click)
    {
        wiringPiI2CReadReg8(fd, NESTO+3);
        adcVal = wiringPiI2CReadReg8(fd, NESTO+3);
        vr = ((double)adcVal / 255) * 3.3;

        series -> append(cnt, vr);


        cnt++;
        if (cnt > 6)
        {
            cnt = 0;
            series -> clear();
        }
    }

}

void Dialog::on_pushButton_2_clicked()
{
    click = 0;
    cnt = 0;
    series -> clear();
}

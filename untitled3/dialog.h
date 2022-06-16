#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCharts>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
QT_CHARTS_USE_NAMESPACE
#include<QTimer>


QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QTimer *myTimer1;
    int obrisi;
    int t;
    int fd;
    int adcVal;
    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void Read();
private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H

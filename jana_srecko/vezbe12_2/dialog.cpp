#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <QDebug>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    myTimer1 = new QTimer(this);
        connect(myTimer1, SIGNAL(timeout()), this,
        SLOT(ReadTemp()));
         myTimer1->start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::ReadTemp()
{

        FILE *ft;
            char tekst[100];
            ft=fopen("/sys/devices/w1_bus_master1/28-00000d3d4ebb/w1_slave","r");
            if(ft==NULL) exit(1);
            int i=0;
            for(i=0;i<22;i++)
            fscanf(ft,"%s", tekst);
            fclose(ft);

            for(i=0;i<10;i++) tekst[i]=tekst[i+2];
            int temp=atoi(tekst);
            double tem=(double)temp/1000;

        ui->lcdNumber->display(tem);
      //  close(fd);
}


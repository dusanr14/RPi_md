#include "dialog.h"
#include "ui_dialog.h"
#include <stdio.h>
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
/*
    if ((fd = open("/sys/devices/w1_bus_master1/28-00000d3d4ebb/w1_slave", O_RDONLY)) < 0)
      {
            perror("Greška pri otvaranju!");
            exit(1);
        }

        ret = read(fd, buffer, sizeof(buffer));

        if (ret < 0)
        {
            perror("Greška pri čitanju!");
            exit(1);
        }*/

        FILE *ft;
            char tekst[100];
            ft=fopen("/sys/devices/w1_bus_master1/28-00000d3d4ebb/w1_slave","r");
            if(ft==NULL) exit(1);
            int i=0;
            for(i=0;i<22;i++) //samo temperatura
            fscanf(ft,"%s", tekst);
            fclose(ft);
            //obrisati „t=”
            for(i=0;i<10;i++) tekst[i]=tekst[i+2];
            int temp=atoi(tekst); //prebaci u double
            double tem=(double)temp/1000;
          qDebug() << "vreme "<<tem;
       /* tmp1 = strchr(buffer, ch);
        sscanf(tmp1, "t=%s", tmp2);
        value = atoi(tmp2);
        integer = value / 1000;
        decimal = value % 1000;
        printf("Temperatura je %d.%d\n", integer,decimal);*/

        ui->lcdlcd->display(tem);
      //  close(fd);
}


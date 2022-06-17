#include "wiringPi.h"
#include "dialog.h"
#include <softPwm.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    wiringPiSetup();

        if (softPwmCreate(28, 0, 100)!=0)
            printf("Doslo je do greske.");
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}

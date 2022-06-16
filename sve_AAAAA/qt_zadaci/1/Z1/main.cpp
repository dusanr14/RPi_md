#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    wiringPiSetup();
    softPwmCreate(25,0,100);

    return a.exec();
}

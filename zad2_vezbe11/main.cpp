#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(wiringPiSetup() < 0) return 1;
    Dialog w;
    w.show();
    return a.exec();
}

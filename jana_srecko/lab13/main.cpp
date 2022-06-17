#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if (wiringPiSetup () == -1)
                exit (1);
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}

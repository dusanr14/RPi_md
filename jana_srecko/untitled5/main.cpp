#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if (wiringPiSetup() < 0){
            fprintf (stderr, "Greška pri inicijalizaciji: %s\n", strerror (errno)) ;
            return 1;
        }
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}

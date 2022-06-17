#include "dialog.h"

#include <QApplication>
const char Address = 0x51;

int main(int argc, char *argv[])
{
    //if(wiringPiSetup() < 0) return 1;
    QApplication a(argc, argv);
    Dialog w;
    w.fd = wiringPiI2CSetup(Address);
    if (w.fd == -1) {
       // std::cout << "Failed to init I2C communication.\n";
        return -1;
    }
    w.show();
    return a.exec();
}

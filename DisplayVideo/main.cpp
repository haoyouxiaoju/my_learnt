#include "displayvideo.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    DisplayVideo w;
    w.resize(1280, 780);
    w.show();


    return a.exec();
}

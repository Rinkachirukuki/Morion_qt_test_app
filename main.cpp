#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QObject::connect(&w,SIGNAL(reconnect()),&w,SLOT(connectToDataBase()));

    w.show();

    return a.exec();
}

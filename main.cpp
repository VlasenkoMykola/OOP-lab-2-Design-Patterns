#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //linkedlist_selftest_unittests();
    //DataAnalysis analysis = data_analysis();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

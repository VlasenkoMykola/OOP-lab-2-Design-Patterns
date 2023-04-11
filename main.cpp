#include "mainwindow.h"

#include <QApplication>
#include "Source.h"

int main(int argc, char *argv[])
{
    linkedlist_selftest_unittests();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

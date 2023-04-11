#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "DistributionFactorySingleton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void draw_histogram(int i);

public slots:
    void on_generateButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    DistributionFactorySingleton factory = DistributionFactorySingleton::getDistributionFactory();
};

#endif // MAINWINDOW_H

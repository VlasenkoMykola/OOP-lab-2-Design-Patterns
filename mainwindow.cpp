#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Fill the items of the ComboBox
    for(int i = 0; i < factory.get_count(); i++)
    {
	ui->comboBox->addItem(QString::fromStdString(factory.get_name(i)));
    }
    scene = new QGraphicsScene(this);
    draw_histogram(0);
    connect(ui->comboBox,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &MainWindow::on_generateButton_clicked);
    connect(ui->generateButton,
	    &QPushButton::click,
	this, &MainWindow::on_generateButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

static qreal calculate_histogram_height_scale (int histogramHeight) {
	if (histogramHeight < 25) return 16;
	if (histogramHeight < 50) return 8;
	if (histogramHeight < 100) return 4;
	if (histogramHeight < 200) return 2;
	if (histogramHeight < 400) return 1;
	if (histogramHeight < 800) return .5;
	if (histogramHeight < 1600) return .25;
	if (histogramHeight < 2000) return .2;
	return .1;
}

void MainWindow::draw_histogram(int i) {
    DataAnalysis analysis = factory.get_data_analysis(i);

    delete scene;
    scene = new QGraphicsScene(this);
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen linePen(Qt::green);
    linePen.setWidth(1);
    QPen histoPen(Qt::blue);
    histoPen.setWidth(1);
    QPen markPen(Qt::red);
    markPen.setWidth(1);

    qreal histogram_height_scale = calculate_histogram_height_scale(analysis.histogramHeight);
    scene->addLine(10, 10, 10, 415, linePen);
    scene->addLine(5, 410, 410, 410, linePen);
    for (int i = 0; i < 4; i++) {
	    scene->addLine(5, 410-100*i, 10, 410-100*i, linePen);
	    scene->addLine(7, 360-100*i, 10, 360-100*i, linePen);
	    scene->addLine(10+100*i, 410, 10+100*i, 415, linePen);
	    scene->addLine(60+100*i, 410, 60+100*i, 413, linePen);
    }
    // addEllipse(x,y,w,h,pen,brush)
    //ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);

    //auto text =
    scene->addText(QString::fromStdString(analysis.name), QFont("Arial", 20) );
    // movable text
    //text->setFlag(QGraphicsItem::ItemIsMovable);
    for (int i = 0; i < analysis.histogramSteps; i++) {
	    // qreal 4=400/histogramSteps
	    scene->addRect(10+i*4, 409, 3, -analysis.histogram[i]*histogram_height_scale, histoPen, blueBrush);
    }
    qreal mean_x_coord = 10 + (analysis.mean -analysis.histogramMin) * 400 / (analysis.histogramMax-analysis.histogramMin);
    scene->addLine(mean_x_coord, 410, mean_x_coord, 10, markPen);

    ui->graphicsView->setScene(scene);

    ui->infoLabel->setText(QString::fromStdString(analysis.toHTML()));


}

void MainWindow::on_generateButton_clicked()
{
	MainWindow::draw_histogram(ui->comboBox->currentIndex());
}

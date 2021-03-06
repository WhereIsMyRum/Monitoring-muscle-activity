#include "plotter.h"
#include "ui_plotter.h"

Plotter::Plotter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);
    ui->closeWindowButton->setEnabled(false);
    hideContractionLabel();
    QObject::connect(parent,SIGNAL(shiftSecondPlot(double)),this,SLOT(shiftPLot(double)));
}

Plotter::~Plotter()
{
    delete ui;
}


void Plotter::makePlot()
{
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));


    ui->customPlot->xAxis->setLabel("t[s]");
    ui->customPlot->yAxis->setLabel("U[mV]");
    ui->customPlot->xAxis->setRange(0,20);
    ui->customPlot->yAxis->setRange(-6,6);
    ui->customPlot->replot();
}

void Plotter::updatePlot()
{
    ui->customPlot->graph(0)->setData(x,y_sig);
    ui->customPlot->graph(1)->setData(x,y_raw);

    ui->customPlot->replot(QCustomPlot::rpQueued);

   //ui->customPlot->update();

}

void Plotter::updateSignalParams(QVector<double> signalParams)
{
    ui->meanAbsLineEdit->setText(QString::number(signalParams.at(0)));
    ui->absVarianceLineEdit->setText(QString::number(signalParams.at(1)));
    ui->meanEnergyLineEdit->setText(QString::number(signalParams.at(2)));
    ui->effectiveValueLineEdit->setText(QString::number(signalParams.at(3)));
    ui->maximumValueLineEdit->setText(QString::number(signalParams.at(4)));
    ui->medianOfNonZeroLineEdit->setText(QString::number(signalParams.at(5)));
    ui->meanFreqLineEdit->setText(QString::number(signalParams.at(6)));
    ui->medianFreqLineEdit->setText(QString::number(signalParams.at(7)));
}

void Plotter::showContractionLabel()
{
    ui->contractionLabel->setVisible(true);
}

void Plotter::hideContractionLabel()
{
    ui->contractionLabel->setVisible(false);
}

void Plotter::on_stopMeasurementButton_clicked()
{
    ui->closeWindowButton->setEnabled(true);
    emit stopMeasurement();
}

void Plotter::shiftPLot(double valueToBeShifted)
{
    ui->customPlot->xAxis->moveRange(valueToBeShifted);
}

void Plotter::on_closeWindowButton_clicked()
{
    ui->closeWindowButton->setEnabled(false);
    emit closeWindow();
}

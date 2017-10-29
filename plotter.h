#ifndef PLOTTER_H
#define PLOTTER_H


#include <QWidget>

namespace Ui {
class Plotter;
}

class Plotter : public QWidget
{
    Q_OBJECT

public:
    explicit Plotter(QWidget *parent = 0);
    ~Plotter();

    void makePlot();
    void updatePlot();

    QVector<double> x,y_sig,y_raw,x2;

private slots:
    void on_stopMeasurementButton_clicked();
    void shiftPLot(double);

    void on_closeWindowButton_clicked();

private:
    Ui::Plotter *ui;

signals:
    void stopMeasurement();
    void closeWindow();

};

#endif // PLOTTER_H

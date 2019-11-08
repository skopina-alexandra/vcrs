#ifndef EXPERIMENTWINDOW_H
#define EXPERIMENTWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <chartwindow.h>

namespace Ui {
class ExperimentWindow;
}

class ExperimentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExperimentWindow(QWidget *parent = nullptr);
    ~ExperimentWindow();


private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_open_clicked();
    
    QVector<int> convert (QString string);

    qint64 rabin_karp (QString string, QString pattern);

    void maxBorderArray(QString &string);

    qint64 kmp (QString string, QString pattern);

    void on_pushButton_experiment_clicked();

    QtCharts::QChartView* experiment();

private:
    Ui::ExperimentWindow *ui;
    QWidget *parent;
    QVector <QString> strings;
    QString pattern;
    QVector<int> br;
    QVector<int> P;
    ChartWindow* cw;

};

#endif // EXPERIMENTWINDOW_H

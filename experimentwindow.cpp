#include "experimentwindow.h"
#include "ui_experimentwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QElapsedTimer>

using namespace QtCharts;


ExperimentWindow::ExperimentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExperimentWindow)
{
    ui->setupUi(this);
    this->parent = parent;
}

ExperimentWindow::~ExperimentWindow()
{
    delete ui;
}

void ExperimentWindow::on_pushButton_back_clicked()
{
    hide();
    parent->show();
}


void ExperimentWindow::on_pushButton_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Открыть файл"),
                                                    "C:/Users/super hacka/Desktop/myasko/build-program-Desktop_Qt_5_12_5_MinGW_32_bit-Debug/gen",
                                                    tr("Файл .txt (*.txt)"));

    QFile f(fileName);
     f.open(QFile::ReadOnly | QFile::Text);
     QTextStream out(&f);

     while(!out.atEnd()){
        QString str = out.readLine();
         strings.append(str);
        // ui->plainTextEdit->appendPlainText(str);

     }
    fileName.remove(0, fileName.indexOf("gen/") + 4);
     pattern = fileName.left(fileName.indexOf(' '));



}

qint64 ExperimentWindow::rabin_karp (QString string, QString pattern){
    int m = pattern.length();
    int n = string.length();
    int d = 26;
    unsigned int h = 1;
    for (int i = 0; i < m - 1; i++){
        h *= 26;
    }

    QVector<int> T = convert(string);

    int x = n - m;
    unsigned int p = 0;
    QVector<unsigned int> t(x + 1);
    t[0] = 0;
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < m; i++){
        p = (d * p + P[i]);
        t[0] = (d * t[0] + T[i]);
    }

    for (int s = 0; s <= x; s++){
        if (p == t[s]){
            //found
        }
        if (s < x){
            t[s + 1] = d * (t[s] - T[s/* + 1*/] * h) + T[s + m/* + 1*/];
        }
    }

    return timer.nsecsElapsed();

}

QVector<int>ExperimentWindow::convert (QString string){
    QString alph = "abcdefghijklmnopqrstuvwxyz";
    QVector<int> converted;
    int n = string.length();
    for(int j = 0; j < n; j++){
        converted.append(alph.indexOf(string[j]));
    }
    return converted;
}



void ExperimentWindow::on_pushButton_experiment_clicked()
{   cw = new ChartWindow(this, experiment());
    cw->show();
}

void ExperimentWindow::maxBorderArray(QString &string){
    int n = string.length();
        br.fill(0, n);
    for (int i = 0; i < n - 1; i++){
        int t = br[i];
        while ((t > 0) && (string[i + 1] != string[t])){
            t = br[t];
        }
        if (string[i + 1] == string[t]){
            br[i + 1] = t + 1;
        } else {
            br[i + 1] = 0;
        }
    }

}

qint64 ExperimentWindow::kmp (QString string, QString pattern){
    int n = string.length();
    int m = pattern.length();
    int q = 0;
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < n; i++){
        while ((q > 0) && (string[i] != pattern[q])){
            q = br[q - 1];
        }
        if (string[i] == pattern[q]){
            q++;
        }
        if (q == m){
           q = 0;
        }
    }
    return timer.nsecsElapsed();
}

QtCharts::QChartView*ExperimentWindow:: experiment(){
     P = convert(pattern);
        maxBorderArray(pattern);
        int x = strings.size();
        QLineSeries *series_rk = new QLineSeries();
        series_rk->setName("Алгоритм Рабина-Карпа");
        QLineSeries *series_kmp = new QLineSeries();
        series_kmp->setName("Алгоритм Кнута-Морриса-Пратта");
        for (int i = 0; i < x; i++){
            int len = strings[i].length();
            series_rk->append(len, rabin_karp(strings[i], pattern));

            series_kmp->append(len, kmp(strings[i], pattern));
        }


         QChart *chart = new QChart();
         chart->legend()->show();
         QPen pen(QRgb(0x924E24));
         series_rk->setPen(pen);
         chart->addSeries(series_rk);
         chart->addSeries(series_kmp);

         chart->createDefaultAxes();
         chart->setTitle("Зависимость времени работы алгоритмов от длины строки");
         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);

         return chartView;

}

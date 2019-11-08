#ifndef GENERATIONWINDOW_H
#define GENERATIONWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class GenerationWindow;
}

class GenerationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerationWindow(QWidget *parent = nullptr);
    ~GenerationWindow();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_generate_clicked();

private:
    Ui::GenerationWindow *ui;
    QWidget *parent;
    QString pattern;
    int minLength = 0;
    int maxLength = 0;

    void generate();

    int randInt(int low, int high);
};

#endif // GENERATIONWINDOW_H

#include "generationwindow.h"
#include "ui_generationwindow.h"
#include <QTextStream>
#include <QTime>
#include <QFile>
#include <QDir>


GenerationWindow::GenerationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerationWindow)
{
    ui->setupUi(this);
    this->parent = parent;

}

GenerationWindow::~GenerationWindow()
{
    delete ui;
}

void GenerationWindow::on_pushButton_back_clicked()
{
    hide();
    parent->show();
}

void GenerationWindow::on_pushButton_generate_clicked()
{
    ui->label_patternError->setText("");
    ui->label_maxLengthError->setText("");
    ui->label_minLengthError->setText("");

    bool correct = true;
    pattern  = ui->lineEdit_pattern->text();
    //pattern = pattern.toLower();
     int n = pattern.length();

     if (n > 20){
         correct = false;
         ui->label_patternError->setText("<font color = 'red'>Длина образца должна быть в диапазоне [1;20]</font>");
     } else {
         for (int i = 0; i < n && correct; i++){
             if (!(pattern[i] >= 0x61 && pattern[i] <= 0x7a)){
                 correct = false;
                 ui->label_patternError->setText("<font color = 'red'>Допустимы только буквы латинского алфавита</font>");
             }
         }
     }


     minLength = ui->lineEdit_minLength->text().toInt();
     if (minLength <= n || minLength >= 2000000){
         ui->label_minLengthError->setText("<font color = 'red'>Минимальная длина строки должна быть в диапазоне (" + QString::number(n) + "; 2000000)</font>");
         correct = false;
     }
     maxLength = ui->lineEdit_maxLength->text().toInt();
    if (maxLength <= minLength || maxLength > 2000000){
        ui->label_maxLengthError->setText("<font color = 'red'>Максимальная длина строки должна быть в диапазоне (" + QString::number(minLength) + ";2000000]");
    }



    if (correct){
        generate();
    }
}



void GenerationWindow::generate(){
    pattern = pattern.toLower();
    int x = 1;
    QString fileName = pattern + " " + QString::number(minLength) + "..." + QString::number(maxLength) +
                         " (" + QString::number(x) + ").txt";
     QDir::setCurrent("C:/Users/super hacka/Desktop/myasko/build-program-Desktop_Qt_5_12_5_MinGW_32_bit-Debug/gen");
    while (QFile::exists(fileName)){
        x++;
        int bracket = fileName.indexOf('(');
        fileName.remove(bracket + 1, fileName.indexOf(')') - bracket - 1);
        fileName.insert(bracket + 1, QString::number(x));
    }

    QFile f(fileName);
    f.open(QFile::WriteOnly | QFile::Text);
    QTextStream in(&f);

    for (int i = minLength; i <= maxLength; i++){
        QString string;
        int n = i - /*count * */pattern.length();
        for (int j = 0; j < n; j++){
            string.append((QChar)randInt(0x61, 0x7a));
        }
        int pos = randInt(0, string.length() - 1);
        string.insert(pos, pattern);
        in << string << '\n';
    }


    f.flush();
    f.close();
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream out(&f);
    QString generated = out.readAll();
    ui->plainTextEdit->setPlainText(generated);


}


int GenerationWindow::randInt(int low, int high){
    return qrand() % ((high + 1) - low) + low;
}
















#include "kalkulator.h"
#include "ui_kalkulator.h"

Kalkulator::Kalkulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kalkulator)
{
    ui->setupUi(this);
}

Kalkulator::~Kalkulator()
{
    delete ui;
}

void Kalkulator::on_ObliczBMI_clicked()
{
    QString waga = ui->waga->text();
    QString wzrost = ui->wzrost->text();
    double wagaBMI = waga.toDouble();
    double wzrostBMI = wzrost.toDouble();
    double BMI = ((wagaBMI)/(wzrostBMI*wzrostBMI))*10000;
    ui->WynikBMI->setText(QString::number(BMI, 'f', 2));
}

void Kalkulator::on_Wyjdz_clicked()
{
    QApplication::quit();
}

#include "kalkulator.h"
#include "ui_kalkulator.h"
#include "globals.h"
#include <QString>
#include <QMessageBox>

Kalkulator::Kalkulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kalkulator)
{
    ui->setupUi(this);
    ui->WynikBMI->setText("Kliknij oblicz");
    if(login_user_name==""){
        ui->WelcomUser->setText("Witaj Adminie :)");
    }
    else{
        QString hello="Witaj ";
        hello.append(login_user_name);
        ui->WelcomUser->setText(hello);
    }
}

Kalkulator::~Kalkulator()
{
    delete ui;
}

void Kalkulator::on_ObliczBMI_clicked()
{
    QString waga = ui->waga->text();
    QString wzrost = ui->wzrost->text();
    if(waga=="" && wzrost==""){
        QMessageBox::information(this,"Wagai Wzrost!","Nie podano wagi i wzrostu");
        ui->waga->setText("Podaj wage!");
        ui->wzrost->setText("Podaj wzrost!");
    }
    else if(waga==""){
        QMessageBox::information(this,"Waga!","Nie podano wagi");
        ui->waga->setText("Podaj wage!");
    }
    else if(wzrost==""){
        QMessageBox::information(this,"Wzrost!","Nie podano wzrostu");
        ui->wzrost->setText("Podaj wzrost!");
    }
    else{
        double wagaBMI = waga.toDouble();
        double wzrostBMI = wzrost.toDouble();
        double BMI = ((wagaBMI)/(wzrostBMI*wzrostBMI))*10000;
        ui->WynikBMI->setText(QString::number(BMI, 'f', 2));
    }
}

void Kalkulator::on_Wyjdz_clicked()
{
    QApplication::quit();
}



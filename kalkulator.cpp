#include "kalkulator.h"
#include "ui_kalkulator.h"
#include "globals.h"
#include "funkcje.h"
#include <QString>
#include <QMessageBox>

Kalkulator::Kalkulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kalkulator)
{
    ui->setupUi(this);
    ui->WynikBMI->setText("Kliknij oblicz");
    ui->ErrorBMI->setText("");
    ui->ErrorWaga->setText("");
    ui->ErrorWzrost->setText("");
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
        ui->ErrorWaga->setText("Podaj wage!");
        ui->ErrorWzrost->setText("Podaj wzrost!");
    }
    else if(waga==""){
        ui->ErrorWaga->setText("Podaj wage!");
    }
    else if(wzrost==""){
        ui->ErrorWzrost->setText("Podaj wzrost!");
    }
    else{
        bool wagaNumbers = numbers_in_string(waga.toStdString());
        bool wzrostNumbers = numbers_in_string(wzrost.toStdString());
        ui->ErrorBMI->setText("");
        if(wagaNumbers){
            ui->waga->setStyleSheet("background-color: rgb(220, 220, 220);");
            ui->ErrorWaga->setText("");
            if(wzrostNumbers){
                ui->wzrost->setStyleSheet("background-color: rgb(220, 220, 220);");
                ui->ErrorWzrost->setText("");
                double wagaBMI = waga.toDouble();
                double wzrostBMI = wzrost.toDouble();
                double BMI = ((wagaBMI)/(wzrostBMI*wzrostBMI))*10000;
                ui->WynikBMI->setText(QString::number(BMI, 'f', 2));
                if(BMI>16){
                    if(BMI>17){
                        if(BMI>18.5){
                            if(BMI>25){
                                if(BMI>30){
                                    if(BMI>35){
                                        if(BMI>=40){
                                            ui->ErrorBMI->setText("Otyłość stopnia III!!!");
                                            ui->ErrorBMI->setStyleSheet("color: rgb(255,0,0);");
                                        }
                                        else{
                                            ui->ErrorBMI->setText("Otyłość stopnia II!!");
                                            ui->ErrorBMI->setStyleSheet("color: rgb(250,128,114);");
                                        }
                                    }
                                    else{
                                        ui->ErrorBMI->setText("Otyłość stopnia I!");
                                        ui->ErrorBMI->setStyleSheet("color: rgb(255,165,0);");
                                    }
                                }
                                else{
                                    ui->ErrorBMI->setText("Nadwaga!");
                                    ui->ErrorBMI->setStyleSheet("color: rgb(255,255,0);");
                                }
                            }
                            else{
                                ui->ErrorBMI->setText("Prawidłowa Waga");
                                ui->ErrorBMI->setStyleSheet("color: rgb(0,255,0);");
                            }
                        }
                        else{
                            ui->ErrorBMI->setText("Niedowaga!");
                            ui->ErrorBMI->setStyleSheet("color: rgb(0,0,255);");
                        }
                    }
                    else{
                       ui->ErrorBMI->setText("Stopień Wychudzenia!");
                       ui->ErrorBMI->setStyleSheet("color: rgb(0,191,255);");
                    }
                }
                else{
                   ui->ErrorBMI->setText("Stopień Wygłodzenia!!!");
                   ui->ErrorBMI->setStyleSheet("color: rgb(127,255,212);");
                }
            }
            else{
                ui->wzrost->setStyleSheet("background-color: rgb(255, 86, 8);");
                ui->ErrorWzrost->setText("Niepoprawne dane");
                ui->WynikBMI->setText("Błąd");
            }
        }
        else if(!wagaNumbers && !wzrostNumbers){
            ui->ErrorWaga->setText("Niepoprawne dane");
            ui->ErrorWzrost->setText("Niepoprawne dane");
            ui->WynikBMI->setText("Błąd");
            ui->wzrost->setStyleSheet("background-color: rgb(255, 86, 8);");
            ui->waga->setStyleSheet("background-color: rgb(255, 86, 8);");
        }
        else{
            ui->wzrost->setStyleSheet("background-color: rgb(220, 220, 220);");
            ui->waga->setStyleSheet("background-color: rgb(255, 86, 8);");
            ui->ErrorWaga->setText("Niepoprawne dane");
            ui->WynikBMI->setText("Błąd");
        }
    }
}

void Kalkulator::on_Wyjdz_clicked()
{
    QApplication::quit();
}

void Kalkulator::on_LoggOut_clicked()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

void Kalkulator::on_AddCategory_clicked()
{
    addingcategorywin = new newCategoryWin(this);
    addingcategorywin->show();
}

void Kalkulator::on_AddProduct_clicked()
{
    addingproductwin = new newproductwin(this);
    addingproductwin->show();
}

void Kalkulator::on_DeleteCategory_clicked()
{
    deletinCatWin = new deleteCategorywin(this);
    deletinCatWin->show();
}

void Kalkulator::on_DeleteProduct_clicked()
{
    deleteProdWin = new deleteProductWin(this);
    deleteProdWin->show();
}

void Kalkulator::on_dodajPosilek_clicked()
{
    this->hide();
    addingnewmealwin = new addingNewMeal(this);
    addingnewmealwin->show();
}

void Kalkulator::on_MojDziennik_clicked()
{
    this->hide();
    mojDziennikWin = new MojDzienik(this);
    mojDziennikWin->show();
}

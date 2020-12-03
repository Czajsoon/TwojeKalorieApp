#include "mojdzienik.h"
#include "ui_mojdzienik.h"
#include "funkceProduktow.h"
#include "readingCategoriesAndProducts.h"
#include "writingFunctionsCategoriesAndProducts.h"
#include "funkcje.h"
#include "mealFunctions.h"
#include "mealReadWriteFunctions.h"
#include "mealStructure.h"
#include "globals.h"

MojDzienik::MojDzienik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MojDzienik)
{
    ui->setupUi(this);
    ui->DMerror->setText("");
    ui->dziennikInfo->setText("Dziennik użytkownika " + login_user_name);
    QStringList posilkiTabela;
    posilkiTabela <<"Nazwa Posiłku"<<"Data posiłku"<<"Wartość energetyczna posiłku(kcal)"<<"Waga posiłku(g)";
    ui->tabela->setColumnCount(4);
    ui->tabela->setHorizontalHeaderLabels(posilkiTabela);
    ui->tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tabela->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->AddMeal->setVisible(false);
    posilek* listaPosilkow = NULL;
    czytaj(&listaPosilkow);
    ui->LPError->setText("");
    if(listaPosilkow==NULL){
        ui->numerPosilku->setVisible(false);
        ui->usunPosilek->setVisible(false);
        ui->DMerror->setVisible(false);
        ui->numerDaniaInfo->setVisible(false);
        ui->szowProducts->setVisible(false);

        ui->LPError->setVisible(true);
        ui->tabela->setVisible(false);
        ui->AddMeal->setVisible(true);
        ui->numerPosilku->setMinimum(0);
        ui->numerPosilku->setMaximum(0);
        ui->LPError->setText("Lista Posiłkow jest pusta dodaj najpierw posiłek do swojego dzienika");
    }
    else{
        ui->numerPosilku->setVisible(true);
        ui->usunPosilek->setVisible(true);
        ui->DMerror->setVisible(true);
        ui->numerDaniaInfo->setVisible(true);
        ui->szowProducts->setVisible(true);

        ui->LPError->setVisible(false);
        int max = policzPosilkiwDzienniku(&listaPosilkow);
        while(listaPosilkow){
            ui->tabela->insertRow(ui->tabela->rowCount());
            int cos = ui->tabela->rowCount()-1;
            ui->tabela->setItem(cos,NAZWA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->nazwa_posilku)));
            ui->tabela->setItem(cos,DATA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->data)));
            ui->tabela->setItem(cos,WE,new QTableWidgetItem(QString::number(listaPosilkow->wartosc_energetyczna)));
            ui->tabela->setItem(cos,WAGA,new QTableWidgetItem(QString::number(listaPosilkow->waga)));
            listaPosilkow =listaPosilkow->pNext;
        }
        ui->numerPosilku->setMinimum(1);
        ui->numerPosilku->setMaximum(max);
    }
    ui->NazwaDania->setText("");
    ui->DataPosilku->setText("");
}

MojDzienik::~MojDzienik()
{
    delete ui;
}

void MojDzienik::on_szowProducts_clicked()
{
    posilek* listaPosilkow = NULL;
    czytaj(&listaPosilkow);
    if(listaPosilkow!=NULL){
        QStringList produktyPosilkuTabela;
        produktyPosilkuTabela <<"Nazwa Produktu"<<"Waga produktu(g)"<<"Wartość energetyczna produktu(kcal)";
        ui->tabela->setColumnCount(3);
        ui->tabela->setHorizontalHeaderLabels(produktyPosilkuTabela);
        ui->tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tabela->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        posilek* akutualnyPosilek = produktyPosilkuODanymNumerze(listaPosilkow,ui->numerPosilku->value());
        ui->tabela->setRowCount(0);
        while(akutualnyPosilek->produkty){
            ui->tabela->insertRow(ui->tabela->rowCount());
            int cos = ui->tabela->rowCount()-1;
            ui->tabela->setItem(cos,NAZWA_PRODUKTU,new QTableWidgetItem(QString::fromStdString(akutualnyPosilek->produkty->nazwa_produktu)));
            ui->tabela->setItem(cos,WAGA_PRODUKTU,new QTableWidgetItem(QString::number(akutualnyPosilek->produkty->waga)));
            ui->tabela->setItem(cos,WARTOSC_ENERGETYCZNA,new QTableWidgetItem(QString::number(akutualnyPosilek->produkty->wartosc_energetyczna*akutualnyPosilek->produkty->waga)));
            akutualnyPosilek->produkty =akutualnyPosilek->produkty->pNext;
        }
        ui->NazwaDania->setText("Nazwa Wyświetlanego Posiłku: \n" + QString::fromStdString(akutualnyPosilek->nazwa_posilku));
        ui->DataPosilku->setText("Data Posiłku\n" + QString::fromStdString(akutualnyPosilek->data));
    }
}

void MojDzienik::on_WyswietDziennik_clicked()
{
    posilek* listaPosilkow = NULL;
    czytaj(&listaPosilkow);
    if(listaPosilkow==NULL){
        ui->numerPosilku->setVisible(false);
        ui->usunPosilek->setVisible(false);
        ui->DMerror->setVisible(false);
        ui->numerDaniaInfo->setVisible(false);
        ui->szowProducts->setVisible(false);

        ui->LPError->setVisible(true);
        ui->tabela->setVisible(false);
        ui->AddMeal->setVisible(true);
        ui->numerPosilku->setMinimum(0);
        ui->numerPosilku->setMaximum(0);
        ui->LPError->setText("Lista Posiłkow jest pusta dodaj najpierw posiłek do swojego dzienika");
    }
    else{
        ui->numerPosilku->setVisible(true);
        ui->usunPosilek->setVisible(true);
        ui->DMerror->setVisible(true);
        ui->numerDaniaInfo->setVisible(true);
        ui->szowProducts->setVisible(true);

        ui->LPError->setVisible(false);
        ui->AddMeal->setVisible(false);
        ui->tabela->setVisible(true);
        QStringList posilkiTabela;
        posilkiTabela <<"Nazwa Posiłku"<<"Data posiłku"<<"Wartość energetyczna posiłku(kcal)"<<"Waga posiłku(g)";
        ui->tabela->setColumnCount(4);
        ui->tabela->setHorizontalHeaderLabels(posilkiTabela);
        ui->tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tabela->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        int max = policzPosilkiwDzienniku(&listaPosilkow);
        ui->tabela->setRowCount(0);
        while(listaPosilkow){
            ui->tabela->insertRow(ui->tabela->rowCount());
            int cos = ui->tabela->rowCount()-1;
            ui->tabela->setItem(cos,NAZWA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->nazwa_posilku)));
            ui->tabela->setItem(cos,DATA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->data)));
            ui->tabela->setItem(cos,WE,new QTableWidgetItem(QString::number(listaPosilkow->wartosc_energetyczna)));
            ui->tabela->setItem(cos,WAGA,new QTableWidgetItem(QString::number(listaPosilkow->waga)));
            listaPosilkow =listaPosilkow->pNext;
        }
        ui->numerPosilku->setMinimum(1);
        ui->numerPosilku->setMaximum(max);
    }
    ui->NazwaDania->setText("");
    ui->DataPosilku->setText("");
}

void MojDzienik::on_tabela_activated(const QModelIndex &index)
{

}

void MojDzienik::on_usunPosilek_clicked()
{
    posilek* listaPosilkow = NULL;
    czytaj(&listaPosilkow);
    if(listaPosilkow!=NULL){
        ui->numerPosilku->setVisible(true);
        ui->usunPosilek->setVisible(true);
        ui->DMerror->setVisible(true);
        ui->numerDaniaInfo->setVisible(true);
        ui->szowProducts->setVisible(true);

        ui->LPError->setVisible(false);
        ui->AddMeal->setVisible(false);
        ui->tabela->setVisible(true);
        if(ui->numerPosilku->value()!=0){
            deleteMealFromList(&listaPosilkow,ui->numerPosilku->value());
            ui->tabela->setRowCount(0);
            zapisz_liste_posilkow(&listaPosilkow);
            czytaj(&listaPosilkow);
            int max = policzPosilkiwDzienniku(&listaPosilkow);
            if(listaPosilkow!=NULL){
                while(listaPosilkow){
                    ui->tabela->insertRow(ui->tabela->rowCount());
                    int cos = ui->tabela->rowCount()-1;
                    ui->tabela->setItem(cos,NAZWA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->nazwa_posilku)));
                    ui->tabela->setItem(cos,DATA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->data)));
                    ui->tabela->setItem(cos,WE,new QTableWidgetItem(QString::number(listaPosilkow->wartosc_energetyczna)));
                    ui->tabela->setItem(cos,WAGA,new QTableWidgetItem(QString::number(listaPosilkow->waga)));
                    listaPosilkow =listaPosilkow->pNext;
                }
                ui->numerPosilku->setMaximum(max);
            }
            else{
                ui->numerPosilku->setVisible(false);
                ui->usunPosilek->setVisible(false);
                ui->DMerror->setVisible(false);
                ui->numerDaniaInfo->setVisible(false);
                ui->szowProducts->setVisible(false);

                ui->LPError->setVisible(true);
                ui->tabela->setVisible(false);
                ui->AddMeal->setVisible(true);
                ui->numerPosilku->setMinimum(0);
                ui->numerPosilku->setMaximum(0);
                ui->LPError->setText("Lista Posiłkow jest pusta dodaj najpierw posiłek do swojego dzienika");
            }

        }
    }
    else{
        ui->numerPosilku->setVisible(false);
        ui->usunPosilek->setVisible(false);
        ui->DMerror->setVisible(false);
        ui->numerDaniaInfo->setVisible(false);
        ui->szowProducts->setVisible(false);

        ui->LPError->setVisible(true);
        ui->tabela->setVisible(false);
        ui->AddMeal->setVisible(true);
        ui->numerPosilku->setMinimum(0);
        ui->numerPosilku->setMaximum(0);
        ui->LPError->setText("Lista Posiłkow jest pusta dodaj najpierw posiłek do swojego dzienika");
    }

}

void MojDzienik::on_AddMeal_clicked()
{
    this->hide();
    addingnewmealwin = new addingNewMeal(this);
    addingnewmealwin->show();
}

void MojDzienik::on_GoBack_clicked()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

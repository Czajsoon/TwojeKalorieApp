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
    ui->dziennikInfo->setText("Dziennik " + login_user_name);
    QStringList posilkiTabela;
    posilkiTabela <<"Nazwa Posiłku"<<"Data posiłku"<<"Wartość energetyczna posiłku"<<"Waga posiłku";
    ui->tabela->setColumnCount(4);
    ui->tabela->setHorizontalHeaderLabels(posilkiTabela);
    ui->tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tabela->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    posilek* listaPosilkow = NULL;
    czytaj(&listaPosilkow);
    while(listaPosilkow){
        ui->tabela->insertRow(ui->tabela->rowCount());
        int cos = ui->tabela->rowCount()-1;
        ui->tabela->setItem(cos,NAZWA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->nazwa_posilku)));
        ui->tabela->setItem(cos,DATA,new QTableWidgetItem(QString::fromStdString(listaPosilkow->data)));
        ui->tabela->setItem(cos,WE,new QTableWidgetItem(QString::number(listaPosilkow->wartosc_energetyczna)));
        ui->tabela->setItem(cos,WAGA,new QTableWidgetItem(QString::number(listaPosilkow->waga)));
        listaPosilkow =listaPosilkow->pNext;
    }
}

MojDzienik::~MojDzienik()
{
    delete ui;
}

void MojDzienik::on_szowProducts_clicked()
{

}

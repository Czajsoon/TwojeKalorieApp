#include "sharedmeals.h"
#include "ui_sharedmeals.h"

#include <QPrinter>
#include <QPrintDialog>

SharedMeals::SharedMeals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SharedMeals)
{
    ui->setupUi(this);
    ui->printer->setVisible(false);
    posilek* listaPosilkow = NULL;
    czytajShare(&listaPosilkow);
    QStringList posilkiTabela;
    posilkiTabela <<"Nazwa Posiłku"<<"Wartość energetyczna posiłku(kcal)"<<"Waga posiłku(g)";
    posilek* posilkoPointer = listaPosilkow;
    ui->tabela->setColumnCount(3);
    ui->tabela->setHorizontalHeaderLabels(posilkiTabela);
    ui->tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tabela->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PrintProducts->setVisible(false);
    ui->bkaPrzepisow->setVisible(false);
    ui->nazwaPosilku->setVisible(false);
    if(posilkoPointer==NULL){
        ui->ShowProducts->setVisible(false);
        ui->numberMealSpin->setVisible(false);
        ui->numberMealLabel->setVisible(false);
        ui->pushButton->setVisible(false);
        ui->bkaPrzepisow->setVisible(true);
        ui->tabela->setVisible(false);
    }
    else{
        ui->pushButton->setVisible(true);
        ui->ShowProducts->setVisible(true);
        ui->numberMealSpin->setVisible(true);
        ui->numberMealLabel->setVisible(true);
        int max = policzPosilkiwDzienniku(&posilkoPointer);
        while(posilkoPointer){
            ui->tabela->insertRow(ui->tabela->rowCount());
            int cos = ui->tabela->rowCount()-1;
            ui->tabela->setItem(cos,NAZWA,new QTableWidgetItem(QString::fromStdString(posilkoPointer->nazwa_posilku)));
            ui->tabela->setItem(cos,WE,new QTableWidgetItem(QString::number(posilkoPointer->wartosc_energetyczna)));
            ui->tabela->setItem(cos,WAGA,new QTableWidgetItem(QString::number(posilkoPointer->waga)));
            posilkoPointer = posilkoPointer->pNext;
        }
        ui->numberMealSpin->setMaximum(max);
        ui->numberMealSpin->setMinimum(1);
    }

}

SharedMeals::~SharedMeals()
{
    delete ui;
}

void SharedMeals::on_Back_clicked()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

void SharedMeals::on_ShowProducts_clicked()
{

    posilek* listaPosilkow = NULL;
    czytajShare(&listaPosilkow);
    if(listaPosilkow!=NULL){
        ui->ShowProducts->setVisible(false);
        ui->numberMealSpin->setVisible(false);
        ui->numberMealLabel->setVisible(false);
        ui->PrintProducts->setVisible(true);
        QStringList produktyPosilkuTabela;
        produktyPosilkuTabela <<"Nazwa Produktu"<<"Waga produktu(g)"<<"Wartość energetyczna produktu(kcal)";
        ui->tabela->setColumnCount(3);
        ui->tabela->setHorizontalHeaderLabels(produktyPosilkuTabela);
        ui->tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tabela->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        posilek* akutualnyPosilek = produktyPosilkuODanymNumerze(listaPosilkow,ui->numberMealSpin->value());
        ui->tabela->setRowCount(0);
        while(akutualnyPosilek->produkty){
            ui->tabela->insertRow(ui->tabela->rowCount());
            int cos = ui->tabela->rowCount()-1;
            ui->tabela->setItem(cos,NAZWA_PRODUKTU,new QTableWidgetItem(QString::fromStdString(akutualnyPosilek->produkty->nazwa_produktu)));
            ui->tabela->setItem(cos,WAGA_PRODUKTU,new QTableWidgetItem(QString::number(akutualnyPosilek->produkty->waga)));
            ui->tabela->setItem(cos,WARTOSC_ENERGETYCZNA,new QTableWidgetItem(QString::number(akutualnyPosilek->produkty->wartosc_energetyczna*akutualnyPosilek->produkty->waga)));
            akutualnyPosilek->produkty =akutualnyPosilek->produkty->pNext;
        }
        ui->nazwaPosilku->setText("Nazwa Wyświetlanego Posiłku: \n" + QString::fromStdString(akutualnyPosilek->nazwa_posilku));
    }
}

void SharedMeals::on_pushButton_clicked()
{
    posilek* listaPosilkow = NULL;
    czytajShare(&listaPosilkow);
    QStringList posilkiTabela;
    posilkiTabela <<"Nazwa Posiłku"<<"Wartość energetyczna posiłku(kcal)"<<"Waga posiłku(g)";
    posilek* posilkoPointer = listaPosilkow;
    ui->tabela->setColumnCount(3);
    ui->tabela->setHorizontalHeaderLabels(posilkiTabela);
    ui->tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tabela->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PrintProducts->setVisible(false);
    ui->nazwaPosilku->setText("");
    if(posilkoPointer!=NULL){
        ui->ShowProducts->setVisible(true);
        ui->numberMealSpin->setVisible(true);
        ui->numberMealLabel->setVisible(true);
        ui->tabela->setRowCount(0);
        int max = policzPosilkiwDzienniku(&posilkoPointer);
        while(posilkoPointer){
            ui->tabela->insertRow(ui->tabela->rowCount());
            int cos = ui->tabela->rowCount()-1;
            ui->tabela->setItem(cos,NAZWA,new QTableWidgetItem(QString::fromStdString(posilkoPointer->nazwa_posilku)));
            ui->tabela->setItem(cos,WE,new QTableWidgetItem(QString::number(posilkoPointer->wartosc_energetyczna)));
            ui->tabela->setItem(cos,WAGA,new QTableWidgetItem(QString::number(posilkoPointer->waga)));
            posilkoPointer = posilkoPointer->pNext;
        }
        ui->numberMealSpin->setMaximum(max);
        ui->numberMealSpin->setMinimum(1);
    }
}

void SharedMeals::on_PrintProducts_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
    posilek* listaposilkow = NULL;
    czytaj(&listaposilkow);
    posilek* akutualnyPosilek = produktyPosilkuODanymNumerze(listaposilkow,ui->numberMealSpin->value());
    productMeal* listaproduktow = akutualnyPosilek->produkty;
    std::string lista = "Lista Produktów\n";
    int numer = 1;
    while(listaproduktow){
        string number = to_string(numer);
        string waga = to_string(listaproduktow->waga);
        lista.append(number + ". " + listaproduktow->nazwa_produktu + "\tWaga produktu: " + waga + "g\n");
        listaproduktow =listaproduktow->pNext;
        numer++;
    }
    ui->printer->setText(QString::fromStdString(lista));
    ui->printer->print(&printer);
}

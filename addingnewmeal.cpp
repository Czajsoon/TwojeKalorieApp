#include "addingnewmeal.h"
#include "ui_addingnewmeal.h"
#include "funkceProduktow.h"
#include "readingCategoriesAndProducts.h"
#include "writingFunctionsCategoriesAndProducts.h"
#include "funkcje.h"
#include "mealFunctions.h"
#include "mealReadWriteFunctions.h"

#include <QDateTime>

addingNewMeal::addingNewMeal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addingNewMeal)
{
    ui->setupUi(this);
    ui->ProErr->setText("");
    ui->WErr->setText("");
    ui->Succes->setText("");
    ui->NPError->setText("");
    ui->succesDodPo->setText("");
    ui->wynikWE->setText("Wartość energetyczna posiłku\n 0 kcal");
    nowyPosilek->produkty = NULL;
    nowyPosilek->pNext = NULL;
    nowyPosilek->wartosc_energetyczna = 0;
    nowyPosilek->waga = 0;
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        std::string nazwaCat = phead->nazwa_kategorii;
        QString qnazwaCat = QString::fromStdString(nazwaCat);
        ui->Cat->addItem(qnazwaCat);
        phead = phead->pNext;
    }
    QStringList kolumny;
    kolumny <<"Nazwa Produktu"<<"Waga";
    ui->produkty->setColumnCount(2);
    ui->produkty->setHorizontalHeaderLabels(kolumny);
    ui->produkty->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->produkty->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

addingNewMeal::~addingNewMeal()
{
    delete ui;
}

void addingNewMeal::on_dodaj_clicked()
{
    ui->ProErr->setText("");
    ui->WErr->setText("");
    ui->Succes->setText("");
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    bool is_product_in_cat = !is_product_in_categories(listaKategorii,ui->Cat->currentText().toStdString(),ui->Pro->currentText().toStdString());
    if(is_product_in_cat && ui->waga->text()==""){
        ui->ProErr->setText("Nie ma takiego produktu w tej katgorii!");
        ui->WErr->setText("Proszę wpisać dane!");
        ui->Succes->setText("Nie dodano produktu do posiłku!");
        ui->Succes->setStyleSheet("color:red;");
    }
    else if(is_product_in_cat && !numbers_in_string(ui->waga->text().toStdString())){
        ui->ProErr->setText("Nie ma takiego produktu w tej katgorii!");
        ui->WErr->setText("Niepoprawne dane!");
        ui->Succes->setText("Nie dodano produktu do posiłku!");
        ui->Succes->setStyleSheet("color:red;");
    }
    else if(is_product_in_cat && is_space_in_string(ui->waga->text().toStdString())){
        ui->ProErr->setText("Nie ma takiego produktu w tej katgorii!");
        ui->WErr->setText("Niedozwolony znak 'spacja'");
        ui->Succes->setText("Nie dodano produktu do posiłku!");
        ui->Succes->setStyleSheet("color:red;");
    }
    else if(is_product_in_cat){
        ui->ProErr->setText("Nie ma takiego produktu w tej katgorii!");
        ui->Succes->setText("Nie dodano produktu do posiłku!");
        ui->Succes->setStyleSheet("color:red;");
    }
    else if(ui->waga->text()==""){
        ui->WErr->setText("Proszę wpisać dane!");
        ui->Succes->setText("Nie dodano produktu do posiłku!");
        ui->Succes->setStyleSheet("color:red;");
    }
    else if(is_space_in_string(ui->waga->text().toStdString())){
        ui->WErr->setText("Niedozwolony znak 'spacja'");
        ui->Succes->setText("Nie dodano produktu do posiłku!");
        ui->Succes->setStyleSheet("color:red;");
    }
    else if(!numbers_in_string(ui->waga->text().toStdString())){
        ui->WErr->setText("Niepoprawne dane!");
        ui->Succes->setText("Nie dodano produktu do posiłku!");
        ui->Succes->setStyleSheet("color:red;");
    }
    else{
        if(nowyPosilek==NULL){
            nowyPosilek = new posilek;
            nowyPosilek->produkty = NULL;
            nowyPosilek->pNext = NULL;
            nowyPosilek->wartosc_energetyczna = 0;
            nowyPosilek->waga = 0;
            categoriesProduct* listaKategorii = NULL;
            listaKategorii = addingCategoriesAndProduct();

            QString nazwa_kategorii = ui->Cat->currentText();
            QString nazwa_produktu = ui->Pro->currentText();
            QString wagaProduktu = ui->waga->text();


            product* currentProduct = current_product(listaKategorii,nazwa_kategorii.toStdString(),nazwa_produktu.toStdString());

            addProductToMealNewProducts(&nowyPosilek,currentProduct->nazwa_produktu,currentProduct->wartosc_energetyczna,wagaProduktu.toDouble());

            listaProduktow = nowyPosilek->produkty;
        }
        else{
            categoriesProduct* listaKategorii = NULL;
            listaKategorii = addingCategoriesAndProduct();

            QString nazwa_kategorii = ui->Cat->currentText();
            QString nazwa_produktu = ui->Pro->currentText();
            QString wagaProduktu = ui->waga->text();


            product* currentProduct = current_product(listaKategorii,nazwa_kategorii.toStdString(),nazwa_produktu.toStdString());

            addProductToMealNewProducts(&nowyPosilek,currentProduct->nazwa_produktu,currentProduct->wartosc_energetyczna,wagaProduktu.toDouble());

            listaProduktow = nowyPosilek->produkty;
        }


        ui->produkty->setRowCount(0);
        while(listaProduktow){
            nowyPosilek->waga += listaProduktow->waga;
            ui->produkty->insertRow(ui->produkty->rowCount());
            int cos = ui->produkty->rowCount()-1;
            ui->produkty->setItem(cos,PRODUKT,new QTableWidgetItem(QString::fromStdString(listaProduktow->nazwa_produktu)));
            ui->produkty->setItem(cos,WAGA,new QTableWidgetItem(QString::number(listaProduktow->waga)));
            listaProduktow =listaProduktow->pNext;
        }
        QString WEwynikText = "Wartość energetyczna posiłku\n";
        QString WeneWynik = QString::number(nowyPosilek->wartosc_energetyczna);
        WEwynikText.append(WeneWynik);
        WEwynikText.append(" kcal");
        ui->wynikWE->setText(WEwynikText);
    }
}

void addingNewMeal::on_Zatwierdz_clicked()
{
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    ui->Pro->clear();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        if(phead->nazwa_kategorii == ui->Cat->currentText().toStdString()){
            product* pProduct = phead->produkty;
            while(pProduct){
                ui->Pro->addItem(QString::fromStdString(pProduct->nazwa_produktu));
                pProduct = pProduct->pNext;
            }
        }
        phead = phead->pNext;
    }
}

void addingNewMeal::on_pushButton_clicked()
{
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    ui->Pro->clear();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        if(phead->nazwa_kategorii == ui->Cat->currentText().toStdString()){
            product* pProduct = phead->produkty;
            while(pProduct){
                ui->Pro->addItem(QString::fromStdString(pProduct->nazwa_produktu));
                pProduct = pProduct->pNext;
            }
        }
        phead = phead->pNext;
    }
}

void addingNewMeal::on_saveDanie_clicked()
{
    if(nowyPosilek->produkty==NULL){
        ui->ProductsListError->setText("Nie można dodać dania bez produktów!");
    }
    else if (nowyPosilek->produkty==NULL) {
        ui->ProductsListError->setText("Nie można dodać dania bez produktów!");
    }
    else{
        posilek* dzinnik = NULL;
        czytaj(&dzinnik);
        ui->produkty->setRowCount(0);
        if(ui->nazwaPosilku->text()==""){
            QString time_format_1 = "yyyy-MM-dd  HH:mm:ss";
            QDateTime b = QDateTime::currentDateTime();
            QString data_help = b.toString(time_format_1);
            QString time_format = "yyyy-MM-dd";
            QDateTime a = QDateTime::currentDateTime();
            QString data = a.toString(time_format);
            ui->succesDodPo->setText("Dodano posiłek do dziennika!");
            nowyPosilek->nazwa_posilku = data_help.toStdString();
            nowyPosilek->data = data.toStdString();
            addMeal(&dzinnik,nowyPosilek);
            zapisz_liste_posilkow(&dzinnik);
            nowyPosilek->produkty=NULL;//osobna funkcja
            nowyPosilek=NULL;//osobna funkcja
            ui->wynikWE->setText("Wartość energetyczna posiłku\n 0 kcal");
        }
        else{
            QString time_format = "yyyy-MM-dd";
            QDateTime a = QDateTime::currentDateTime();
            QString data = a.toString(time_format);
            ui->succesDodPo->setText("Dodano posiłek do dziennika!");
            posilek* dzinnik = NULL;
            nowyPosilek->nazwa_posilku = ui->nazwaPosilku->text().toStdString();
            nowyPosilek->data = data.toStdString();
            czytaj(&dzinnik);
            addMeal(&dzinnik,nowyPosilek);
            zapisz_liste_posilkow(&dzinnik);
            nowyPosilek->produkty=NULL;//osobna funkcja
            nowyPosilek=NULL;//osobna funkcja
            ui->wynikWE->setText("Wartość energetyczna posiłku\n 0 kcal");
        }
    }
}

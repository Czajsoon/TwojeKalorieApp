#include "addingnewmeal.h"
#include "ui_addingnewmeal.h"
#include "funkceProduktow.h"
#include "readingCategoriesAndProducts.h"
#include "writingFunctionsCategoriesAndProducts.h"
#include "funkcje.h"

addingNewMeal::addingNewMeal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addingNewMeal)
{
    ui->setupUi(this);
    ui->ProErr->setText("");
    ui->WErr->setText("");
    ui->Succes->setText("");
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
    kolumny << "Kategoria" <<"Nazwa Produktu"<<"Waga";
    ui->produkty->setColumnCount(3);
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
        ui->Succes->setStyleSheet("color:green;");
        ui->Succes->setText("Udało sie dodać produkt do posiłku!");
        ui->produkty->insertRow(ui->produkty->rowCount());
        int cos = ui->produkty->rowCount()-1;
        ui->produkty->setItem(cos,KATEGORIA,new QTableWidgetItem(ui->Cat->currentText()));
        ui->produkty->setItem(cos,PRODUKT,new QTableWidgetItem(ui->Pro->currentText()));
        ui->produkty->setItem(cos,WAGA,new QTableWidgetItem(ui->waga->text()));
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

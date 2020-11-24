#include "deleteproductwin.h"
#include "ui_deleteproductwin.h"
#include "funkceProduktow.h"
#include "readingCategoriesAndProducts.h"
#include "writingFunctionsCategoriesAndProducts.h"
#include "funkcje.h"

deleteProductWin::deleteProductWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteProductWin)
{
    ui->setupUi(this);
    ui->errorCat->setText("");
    ui->errorPro->setText("");
    ui->succes->setText("");
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        std::string nazwaCat = phead->nazwa_kategorii;
        QString qnazwaCat = QString::fromStdString(nazwaCat);
        ui->Category->addItem(qnazwaCat);
        phead = phead->pNext;
    }
}

deleteProductWin::~deleteProductWin()
{
    delete ui;
}

void deleteProductWin::on_anuluj_clicked()
{
    this->close();
}

void deleteProductWin::on_usun_clicked()
{
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    deleteProduct(&listaKategorii,ui->Category->currentText().toStdString(),ui->Product->currentText().toStdString());
    saveProducts(&listaKategorii);
    ui->Product->clear();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        if(phead->nazwa_kategorii == ui->Category->currentText().toStdString()){
            product* pProduct = phead->produkty;
            while(pProduct){
                ui->Product->addItem(QString::fromStdString(pProduct->nazwa_produktu));
                pProduct = pProduct->pNext;
            }
        }
        phead = phead->pNext;
    }
}

void deleteProductWin::on_aktualizuj_clicked()
{
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    ui->Product->clear();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        if(phead->nazwa_kategorii == ui->Category->currentText().toStdString()){
            product* pProduct = phead->produkty;
            while(pProduct){
                ui->Product->addItem(QString::fromStdString(pProduct->nazwa_produktu));
                pProduct = pProduct->pNext;
            }
        }
        phead = phead->pNext;
    }
}

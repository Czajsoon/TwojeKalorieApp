#include "deletecategorywin.h"
#include "ui_deletecategorywin.h"
#include "funkceProduktow.h"
#include "readingCategoriesAndProducts.h"
#include "writingFunctionsCategoriesAndProducts.h"
#include "funkcje.h"

#include <QMessageBox>

deleteCategorywin::deleteCategorywin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteCategorywin)
{
    ui->setupUi(this);
    ui->ErrorCat->setText("");
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        std::string nazwaCat = phead->nazwa_kategorii;
        QString qnazwaCat = QString::fromStdString(nazwaCat);
        ui->category->addItem(qnazwaCat);
        phead = phead->pNext;
    }
}

deleteCategorywin::~deleteCategorywin()
{
    delete ui;
}



void deleteCategorywin::on_anuluj_clicked()
{
    this->close();
}


void deleteCategorywin::on_usun_clicked()
{
    ui->ErrorCat->setText("");
    categoriesProduct* listaKategorii = NULL;
    categoriesProduct* nowalistaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    nowalistaKategorii = listaKategorii;
    QString nazwaCat = ui->category->currentText();
    deleteCategory(&nowalistaKategorii,nazwaCat.toStdString());
    save_CategoriesAndProducts(&nowalistaKategorii);
    ui->ErrorCat->setText("Usuwanie kategorii o nazwie " + nazwaCat +" powiodło się!");
    ui->category->clear();
    listaKategorii = addingCategoriesAndProduct();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        std::string nazwaCat = phead->nazwa_kategorii;
        QString qnazwaCat = QString::fromStdString(nazwaCat);
        ui->category->addItem(qnazwaCat);
        phead = phead->pNext;
    }
//    this->close();
}

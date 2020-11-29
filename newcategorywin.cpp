#include "newcategorywin.h"
#include "ui_newcategorywin.h"
#include "funkceProduktow.h"
#include "readingCategoriesAndProducts.h"
#include "writingFunctionsCategoriesAndProducts.h"
#include "funkcje.h"
#include <QString>

newCategoryWin::newCategoryWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newCategoryWin)
{
    ui->setupUi(this);
    ui->categoryname->setText("");
    ui->bladKategorii->setText("");
}

newCategoryWin::~newCategoryWin()
{
    delete ui;
}

void newCategoryWin::on_anuluj_clicked()
{
    this->close();
}



void newCategoryWin::on_dodaj_clicked()
{
    ui->bladKategorii->setText("");
    ui->bladKategorii->setStyleSheet("color:red;");
    if(ui->categoryname->text()==""){
        ui->bladKategorii->setText("Nie podano danych!");
    }
    else{
        if(is_space_in_string(ui->categoryname->text().toStdString())){
            ui->bladKategorii->setText("Wprowadzono niedozwolony znak - spacja");
        }
        else{
            categoriesProduct* listaKategorii = NULL;
            listaKategorii = addingCategoriesAndProduct();
            QString nCat =  ui->categoryname->text();
            nCat[0] = nCat[0].toUpper();
            if(is_category_in_Categories(listaKategorii,nCat.toStdString())){
                ui->bladKategorii->setText("Taka kategoria istnieje!");
            }
            else{
                QString nazwaKategorii = ui->categoryname->text();
                addCategory(&listaKategorii,nazwaKategorii.toStdString());
                ui->bladKategorii->setText("Dodano nowa kategorie o nazwie: " + ui->categoryname->text());
                ui->bladKategorii->setStyleSheet("color:green;");
                ui->categoryname->setText("");
                save_CategoriesAndProducts(&listaKategorii);
            }
            clearMemoryProductsAndCategory(&listaKategorii);
        }
    }
}

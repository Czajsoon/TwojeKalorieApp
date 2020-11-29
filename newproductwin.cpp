#include "newproductwin.h"
#include "ui_newproductwin.h"
#include "funkceProduktow.h"
#include "readingCategoriesAndProducts.h"
#include "writingFunctionsCategoriesAndProducts.h"
#include "funkcje.h"

newproductwin::newproductwin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newproductwin)
{
    ui->setupUi(this);
    ui->errorNP->setText("");
    ui->errorWE->setText("");
    ui->succes->setText("");
    categoriesProduct* listaKategorii = NULL;
    listaKategorii = addingCategoriesAndProduct();
    categoriesProduct* phead = listaKategorii;
    while(phead){
        std::string nazwaCat = phead->nazwa_kategorii;
        QString qnazwaCat = QString::fromStdString(nazwaCat);
        ui->comboBox->addItem(qnazwaCat);
        phead = phead->pNext;
    }
}

newproductwin::~newproductwin()
{
    delete ui;
}

void newproductwin::on_zakoncz_clicked()
{
    this->close();
}

void newproductwin::on_dodaj_clicked()
{
    ui->errorNP->setText("");
    ui->errorWE->setText("");
    ui->succes->setText("");
    if(ui->NP->text()=="" && ui->WE->text()==""){
        ui->errorNP->setText("Nie wprowadzono danych!");
        ui->errorWE->setText("Nie wprowadzono danych!");
    }
    else if(ui->NP->text()==""){
        ui->errorNP->setText("Nie wprowadzono danych!");
    }
    else if(ui->WE->text()==""){
        ui->errorWE->setText("Nie wprowadzono danych!");
    }
    else{
        if(is_space_in_string(ui->NP->text().toStdString()) && is_space_in_string(ui->WE->text().toStdString())){
            ui->errorNP->setText("Wprowadzono niedozwolony znak - spacja");
            ui->errorWE->setText("Wprowadzono niedozwolony znak - spacja");
        }
        else if(is_space_in_string(ui->NP->text().toStdString())){
            ui->errorNP->setText("Wprowadzono niedozwolony znak - spacja");
        }
        else if(is_space_in_string(ui->WE->text().toStdString())){
             ui->errorWE->setText("Wprowadzono niedozwolony znak - spacja");
        }
        else{
            QString ProName = ui->NP->text();
            ProName[0] = ProName[0].toUpper();
            categoriesProduct* listaKategorii = NULL;
            listaKategorii = addingCategoriesAndProduct();
            if(is_product_in_categories(listaKategorii,ui->comboBox->currentText().toStdString(),ProName.toStdString()) && !numbers_in_string(ui->WE->text().toStdString())){
                ui->errorWE->setText("Proszę wprowadzić tylko liczby (np. 20.5)");
                ui->errorNP->setText("Istnieje taki produkt w tej kategorii!");
            }
            else if(is_product_in_categories(listaKategorii,ui->comboBox->currentText().toStdString(),ProName.toStdString())){
                ui->errorNP->setText("Istnieje taki produkt w tej kategorii!");
            }
            else if(!numbers_in_string(ui->WE->text().toStdString())){
                ui->errorWE->setText("Proszę wprowadzić tylko liczby (np. 20.5)");
            }
            else{
                addProductToCategory(&listaKategorii,ui->comboBox->currentText().toStdString(),ui->NP->text().toStdString(),ui->WE->text().toDouble());
                ui->succes->setText("Udało się dodać produkt!\n o nazwie: " + ui->NP->text() + "\n o wartości energetycznej: " + ui->WE->text() +" kcal");
                save_CategoriesAndProducts(&listaKategorii);
                ui->NP->setText("");
                ui->WE->setText("");
            }
        }
    }
}

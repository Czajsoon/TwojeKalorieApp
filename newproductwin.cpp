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
    clearMemoryProductsAndCategory(&listaKategorii);
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
        if(is_space_in_string(ui->WE->text().toStdString())){
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
                product* nowyProdukt = new product;
                nowyProdukt->nazwa_kategorii = ui->comboBox->currentText().toStdString();
                nowyProdukt->nazwa_produktu = ui->NP->text().toStdString();
                nowyProdukt->pNext = NULL;
                nowyProdukt->wartosc_energetyczna = ui->WE->text().toDouble();
                addProductToCategory(&listaKategorii,nowyProdukt);

                ui->succes->setText("Udało się dodać produkt!\n o nazwie: " + ui->NP->text() + "\n o wartości energetycznej: " + ui->WE->text() +" kcal");
                save_CategoriesAndProducts(&listaKategorii);
                delete nowyProdukt;
                nowyProdukt = NULL;
                clearMemoryProductsAndCategory(&listaKategorii);
                ui->NP->setText("");
                ui->WE->setText("");
            }
        }
    }
}

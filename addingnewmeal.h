#ifndef ADDINGNEWMEAL_H
#define ADDINGNEWMEAL_H

#include <QDialog>
#include "mealStructure.h"

namespace Ui {
class addingNewMeal;
}

class addingNewMeal : public QDialog
{
    Q_OBJECT

public:
    explicit addingNewMeal(QWidget *parent = nullptr);
    ~addingNewMeal();

private slots:
    void on_dodaj_clicked();

    void on_pushButton_clicked();

    void on_Zatwierdz_clicked();

    void on_saveDanie_clicked();

    void on_DEleteListProducts_clicked();

    void on_BackListProducts_clicked();

    void on_Share_clicked();

    void on_wyjdz_clicked();

private:
    Ui::addingNewMeal *ui;
    posilek* nowyPosilek = new posilek;
    productMeal* listaProduktow = NULL;
    productMeal* wczesniejszyProdukt = NULL;

    enum koumny{
        PRODUKT ,WAGA
    };
};

#endif // ADDINGNEWMEAL_H

#ifndef SHAREDMEALS_H
#define SHAREDMEALS_H

#include <QDialog>
#include "mealFunctions.h"
#include "mealReadWriteFunctions.h"

namespace Ui {
class SharedMeals;
}

class SharedMeals : public QDialog
{
    Q_OBJECT

public:
    explicit SharedMeals(QWidget *parent = nullptr);
    ~SharedMeals();

private slots:
    void on_Back_clicked();

    void on_ShowProducts_clicked();

    void on_pushButton_clicked();

    void on_PrintProducts_clicked();

private:
    Ui::SharedMeals *ui;
    enum koumnyPosilkow{
        NAZWA,WE,WAGA
    };
    enum kolumnyProduktow{
        NAZWA_PRODUKTU,WAGA_PRODUKTU,WARTOSC_ENERGETYCZNA
    };
};

#endif // SHAREDMEALS_H

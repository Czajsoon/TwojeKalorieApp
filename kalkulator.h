#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <QMainWindow>
#include "newcategorywin.h"
#include "newproductwin.h"
#include "deletecategorywin.h"
#include "deleteproductwin.h"
#include "addingnewmeal.h"
#include "mojdzienik.h"

namespace Ui {
class Kalkulator;
}

class Kalkulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kalkulator(QWidget *parent = nullptr);
    ~Kalkulator();

private slots:

    void on_ObliczBMI_clicked();

    void on_Wyjdz_clicked();

    void on_LoggOut_clicked();

    void on_AddCategory_clicked();

    void on_AddProduct_clicked();

    void on_DeleteCategory_clicked();

    void on_DeleteProduct_clicked();

    void on_dodajPosilek_clicked();

    void on_MojDziennik_clicked();

private:
    Ui::Kalkulator *ui;
    newCategoryWin* addingcategorywin;
    newproductwin* addingproductwin;
    deleteCategorywin* deletinCatWin;
    deleteProductWin* deleteProdWin;
    addingNewMeal* addingnewmealwin;
    MojDzienik* mojDziennikWin;
};

#endif // KALKULATOR_H

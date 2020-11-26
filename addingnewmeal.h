#ifndef ADDINGNEWMEAL_H
#define ADDINGNEWMEAL_H

#include <QDialog>

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

private:
    Ui::addingNewMeal *ui;

    enum koumny{
        KATEGORIA , PRODUKT ,WAGA
    };
};

#endif // ADDINGNEWMEAL_H

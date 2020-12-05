#ifndef MOJDZIENIK_H
#define MOJDZIENIK_H

#include <QDialog>
#include "addingnewmeal.h"

namespace Ui {
class MojDzienik;
}

class MojDzienik : public QDialog
{
    Q_OBJECT

public:
    explicit MojDzienik(QWidget *parent = nullptr);
    ~MojDzienik();

private slots:
    void on_szowProducts_clicked();

    void on_WyswietDziennik_clicked();

    void on_tabela_activated(const QModelIndex &index);

    void on_usunPosilek_clicked();

    void on_AddMeal_clicked();

    void on_GoBack_clicked();

    void on_print_clicked();

private:
    Ui::MojDzienik *ui;
    addingNewMeal* addingnewmealwin;
    enum koumnyPosilkow{
        NAZWA ,DATA,WE,WAGA
    };
    enum kolumnyProduktow{
        NAZWA_PRODUKTU,WAGA_PRODUKTU,WARTOSC_ENERGETYCZNA
    };
};

#endif // MOJDZIENIK_H

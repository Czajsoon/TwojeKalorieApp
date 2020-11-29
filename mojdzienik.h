#ifndef MOJDZIENIK_H
#define MOJDZIENIK_H

#include <QDialog>

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

private:
    Ui::MojDzienik *ui;
    enum koumnyPosilkow{
        NAZWA ,DATA,WE,WAGA
    };
    enum kolumnyProduktow{
        NAZWA_PRODUKTU,WAGA_PRODUKTU,WARTOSC_ENERGETYCZNA
    };
};

#endif // MOJDZIENIK_H

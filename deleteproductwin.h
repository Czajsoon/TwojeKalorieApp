#ifndef DELETEPRODUCTWIN_H
#define DELETEPRODUCTWIN_H

#include <QDialog>

namespace Ui {
class deleteProductWin;
}

class deleteProductWin : public QDialog
{
    Q_OBJECT

public:
    explicit deleteProductWin(QWidget *parent = nullptr);
    ~deleteProductWin();

private slots:
    void on_anuluj_clicked();

    void on_usun_clicked();

    void on_aktualizuj_clicked();

private:
    Ui::deleteProductWin *ui;
};

#endif // DELETEPRODUCTWIN_H

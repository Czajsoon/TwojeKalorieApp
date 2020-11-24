#ifndef NEWCATEGORYWIN_H
#define NEWCATEGORYWIN_H

#include <QDialog>

namespace Ui {
class newCategoryWin;
}

class newCategoryWin : public QDialog
{
    Q_OBJECT

public:
    explicit newCategoryWin(QWidget *parent = nullptr);
    ~newCategoryWin();

private slots:
    void on_anuluj_clicked();

    void on_dodaj_clicked();

private:
    Ui::newCategoryWin *ui;
};

#endif // NEWCATEGORYWIN_H

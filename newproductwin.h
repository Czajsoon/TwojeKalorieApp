#ifndef NEWPRODUCTWIN_H
#define NEWPRODUCTWIN_H

#include <QDialog>

namespace Ui {
class newproductwin;
}

class newproductwin : public QDialog
{
    Q_OBJECT

public:
    explicit newproductwin(QWidget *parent = nullptr);
    ~newproductwin();

private slots:
    void on_zakoncz_clicked();

    void on_dodaj_clicked();

private:
    Ui::newproductwin *ui;
};

#endif // NEWPRODUCTWIN_H

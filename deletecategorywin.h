#ifndef DELETECATEGORYWIN_H
#define DELETECATEGORYWIN_H

#include <QDialog>

namespace Ui {
class deleteCategorywin;
}

class deleteCategorywin : public QDialog
{
    Q_OBJECT

public:
    explicit deleteCategorywin(QWidget *parent = nullptr);
    ~deleteCategorywin();

private slots:
    void on_anuluj_clicked();

    void on_usun_clicked();

private:
    Ui::deleteCategorywin *ui;
};

#endif // DELETECATEGORYWIN_H

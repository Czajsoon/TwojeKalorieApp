#ifndef ADDINGCATEGORYDIALOG_H
#define ADDINGCATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
class AddingCategoryDialog;
}

class AddingCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddingCategoryDialog(QWidget *parent = nullptr);
    ~AddingCategoryDialog();

private slots:
    void on_Add_clicked();

    void on_cancel_clicked();

private:
    Ui::AddingCategoryDialog *ui;
};

#endif // ADDINGCATEGORYDIALOG_H

#include "addingcategorydialog.h"
#include "ui_addingcategorydialog.h"

AddingCategoryDialog::AddingCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddingCategoryDialog)
{
    ui->setupUi(this);

}

AddingCategoryDialog::~AddingCategoryDialog()
{
    delete ui;
}

void AddingCategoryDialog::on_Add_clicked()
{

}

void AddingCategoryDialog::on_cancel_clicked()
{

}

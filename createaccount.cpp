#include "createaccount.h"
#include "ui_createaccount.h"
#include "login.h"
#include "ui_login.h"

CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_pushButton_2_clicked()
{
    QDialog::close();
}

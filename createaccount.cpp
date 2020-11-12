#include "createaccount.h"
#include "ui_createaccount.h"
#include "login.h"
#include "ui_login.h"
#include "reading_users_functions.h"
#include "users_functions.h"
#include "struct_list_users.h"
#include "writing_functions.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

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

void CreateAccount::on_pushButton_clicked()
{
    Users *users = adding_users_to_list();
    if(ui->password->text() != ui->repeatPassword->text()){
        QMessageBox::warning(this,"Nie stworzono konta!","Hasła nie zgadzają się!");
    }
    else if(verify_login(&users,ui->Login->text().toStdString())){
        QMessageBox::warning(this,"Nie stworzono konta!","Istnieje konto o takim loginie wpisz inny login!");
    }
    else{
        add(&users,ui->Login->text().toStdString(),ui->password->text().toStdString());
        write_users(&users);
        QMessageBox::information(this,"Gratulacje!!!","Udało się stworzyć konto, spróbuj teraz się zalogować :)");
    }
    delete_users_list(&users);
}

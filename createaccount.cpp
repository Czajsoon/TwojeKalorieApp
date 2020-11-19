#include "createaccount.h"
#include "ui_createaccount.h"
#include "login.h"
#include "ui_login.h"
#include "reading_users_functions.h"
#include "users_functions.h"
#include "struct_list_users.h"
#include "writing_functions.h"
#include "funkcje.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
    ui->ErrorLogin->setText("");
    ui->ErrorPassword->setText("");
    ui->ErrorRepeatPassword->setText("");
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_pushButton_2_clicked()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

void CreateAccount::on_pushButton_clicked()
{
    Users *users = adding_users_to_list();
    QString login_user = ui->Login->text();
    QString password = ui->password->text();
    QString rpassword = ui->repeatPassword->text();
    ui->ErrorLogin->setText("");
    ui->ErrorPassword->setText("");
    ui->ErrorRepeatPassword->setText("");
    if(login_user=="" && password =="" && rpassword==""){
        ui->ErrorLogin->setText("Nie wprowadzono danych");
        ui->ErrorPassword->setText("Nie wprowadzono danych");
        ui->ErrorRepeatPassword->setText("Nie wprowadzono danych");
    }
    else if(login_user=="" && password ==""){
        ui->ErrorLogin->setText("Nie wprowadzono danych");
        ui->ErrorPassword->setText("Nie wprowadzono danych");
        if(is_space_in_string(rpassword.toStdString())){
            ui->ErrorRepeatPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
    }
    else if(login_user=="" && rpassword ==""){
        ui->ErrorLogin->setText("Nie wprowadzono danych");
        if(is_space_in_string(password.toStdString())){
            ui->ErrorPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        ui->ErrorRepeatPassword->setText("Nie wprowadzono danych");
    }
    else if(password =="" && rpassword==""){
        if(verify_login(&users,ui->Login->text().toStdString())){
            ui->ErrorLogin->setText("Istnieje już taki login, proszę wybrać inny");
        }
        if(is_space_in_string(login_user.toStdString())){
            ui->ErrorLogin->setText("Wprowadzono niedozwolony znak - spacje");
        }
        ui->ErrorPassword->setText("Nie wprowadzono danych");
        ui->ErrorRepeatPassword->setText("Nie wprowadzono danych");
    }
    else if(login_user == ""){
        ui->ErrorLogin->setText("Nie wprowadzono danych");
        if(is_space_in_string(password.toStdString())){
            ui->ErrorPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        if(is_space_in_string(rpassword.toStdString())){
            ui->ErrorRepeatPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
    }
    else if(password == ""){
        ui->ErrorPassword->setText("Nie wprowadzono danych");
        if(is_space_in_string(login_user.toStdString())){
            ui->ErrorLogin->setText("Wprowadzono niedozwolony znak - spacje");
        }
        if(is_space_in_string(rpassword.toStdString())){
            ui->ErrorRepeatPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
    }
    else if(rpassword == ""){
        ui->ErrorRepeatPassword->setText("Nie wprowadzono danych");
        if(is_space_in_string(login_user.toStdString())){
            ui->ErrorLogin->setText("Wprowadzono niedozwolony znak - spacje");
        }
        if(is_space_in_string(password.toStdString())){
            ui->ErrorPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
    }
    else{
        if(is_space_in_string(login_user.toStdString()) && is_space_in_string(password.toStdString()) && is_space_in_string(rpassword.toStdString())){
           ui->ErrorLogin->setText("Wprowadzono niedozwolony znak - spacje");
           ui->ErrorPassword->setText("Wprowadzono niedozwolony znak - spacje");
           ui->ErrorRepeatPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        else if(is_space_in_string(login_user.toStdString()) && is_space_in_string(password.toStdString())){
            ui->ErrorLogin->setText("Wprowadzono niedozwolony znak - spacje");
            ui->ErrorPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        else if(is_space_in_string(login_user.toStdString()) && is_space_in_string(rpassword.toStdString())){
            ui->ErrorLogin->setText("Wprowadzono niedozwolony znak - spacje");
            ui->ErrorRepeatPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        else if(is_space_in_string(password.toStdString()) && is_space_in_string(rpassword.toStdString())){
            ui->ErrorPassword->setText("Wprowadzono niedozwolony znak - spacje");
            ui->ErrorRepeatPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        else if(is_space_in_string(login_user.toStdString())){
            ui->ErrorLogin->setText("Wprowadzono niedozwolony znak - spacje");
        }
        else if(is_space_in_string(password.toStdString())){
            ui->ErrorPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        else if(is_space_in_string(rpassword.toStdString())){
            ui->ErrorRepeatPassword->setText("Wprowadzono niedozwolony znak - spacje");
        }
        else{
            if(ui->password->text() != ui->repeatPassword->text() && verify_login(&users,ui->Login->text().toStdString())){
                ui->ErrorPassword->setText("Hasła się nie zgadzają!");
                ui->ErrorRepeatPassword->setText("Hasła się nie zgadzają!");
                ui->ErrorLogin->setText("Istnieje już taki login, proszę wybrać inny");
            }
            else if(ui->password->text() != ui->repeatPassword->text()){
                ui->ErrorPassword->setText("Hasła się nie zgadzają!");
                ui->ErrorRepeatPassword->setText("Hasła się nie zgadzają!");

            }
            else if(verify_login(&users,ui->Login->text().toStdString())){
                ui->ErrorLogin->setText("Istnieje już taki login, proszę wybrać inny");
            }
            else{
                add(&users,ui->Login->text().toStdString(),ui->password->text().toStdString());
                write_users(&users);
                QMessageBox::information(this,"Gratulacje!!!","Udało się stworzyć konto, spróbuj teraz się zalogować :)");
                this->close();
                QWidget *parent = this->parentWidget();
                parent->show();
            }
        }
    }

    delete_users_list(&users);
}

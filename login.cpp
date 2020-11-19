#include "login.h"
#include "ui_login.h"
#include "reading_users_functions.h"
#include "users_functions.h"
#include "struct_list_users.h"
#include "globals.h"

#include <iostream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QWidget>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->ErrorLogin->setText("");
    ui->ErrorPassword->setText("");
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void login::on_pushButton_clicked()
{
    Users *users = adding_users_to_list();
    QString login = ui->Login->text();
    QString password =  ui->Password->text();
    ui->ErrorLogin->setText("");
    ui->ErrorPassword->setText("");
    if(login==""&&password==""){
        ui->ErrorLogin->setText("Nie wprowadzono danych");
        ui->ErrorPassword->setText("Nie wprowadzono danych");
    }
    else if(login==""){
        ui->ErrorLogin->setText("Nie wprowadzono danych");
    }
    else if(password==""){
        ui->ErrorPassword->setText("Nie wprowadzono danych");
    }
    else{
        if(verify_login(&users,login.toStdString())){
           if(check_password(&users,login.toStdString(),password.toStdString())){
               login_user_name = ui->Login->text();
               this->hide();
               ui->Login->setText("");
               ui->Password->setText("");
               ui->ErrorLogin->setText("");
               ui->ErrorPassword->setText("");
               calc = new Kalkulator(this);
               calc->show();
           }
           else{
               ui->ErrorPassword->setText("Nie poprawne hasło!");
           }
        }
        else{
            ui->ErrorLogin->setText("Niepoprawne dane logowania!");
        }
    }

    delete_users_list(&users);
}

void login::on_pushButton_3_clicked()
{
   ui->ErrorLogin->setText("");
   ui->ErrorPassword->setText("");
   createacc = new CreateAccount(this);
   this->hide();
   createacc->show();
}

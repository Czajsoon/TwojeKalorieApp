#include "login.h"
#include "ui_login.h"
#include "reading_users_functions.h"
#include "users_functions.h"
#include "struct_list_users.h"

#include <iostream>
#include <string>


#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_2_clicked()
{
    QApplication::quit();
    //QFile file(QDir::currentPath() +"/gowno.txt" );

   // if (file.open(QIODevice::WriteOnly)){
   //     QTextStream out(&file);
   //     QString login = ui->Login->text();
   //     QString password = ui->Password->text();
   //     out<<login<<" "<<password<<"\n";
   //     file.flush();
   //    file.close();
   // }

}

void login::on_pushButton_clicked()
{
    Users *users = adding_users_to_list();
    QString login = ui->Login->text();
    QString password =  ui->Password->text();
    if(verify_account(&users,login.toStdString(),password.toStdString())){
            QMessageBox::information(this,"Super!!!","Udalo ci sie zalogować!!! GRATULACJE!!!");
    }
    else{
        QMessageBox::warning(this,"Uwaga!!!","Niepoprawne dane!!!");
    }
    delete_users_list(&users);
}

void login::on_pushButton_3_clicked()
{
   createacc = new CreateAccount(this);
   createacc->show();
}

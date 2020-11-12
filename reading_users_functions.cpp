#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QFile>
#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include "users_functions.h"

using namespace std;

Users* adding_users_to_list() {
    Users* uzytkownicy = NULL;
    QFile inputFile(QDir::currentPath() + "/Konta.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString login;
          QString password;
          in>>login>>password;
          add(&uzytkownicy, login.toStdString(), password.toStdString());
       }
       inputFile.close();
    }
    return uzytkownicy;
}

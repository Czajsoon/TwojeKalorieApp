#include <iostream>
#include <fstream>
#include <sstream>

#include "struct_list_users.h"
#include "users_functions.h"

#include <QDir>

void write_users(Users **users_list){
    QString path = QDir::currentPath();
    path.append("/konta.txt");
    std::ofstream file(path.toStdString());
        if (file.is_open()) {
            std::string login;
            std::string password;
            Users* phead = *users_list;
            while (phead) {
                file << phead->login << " " << phead->password << std::endl;
                phead = phead->pNext;
            }
        }
}

#include <iostream>
#include <string>
#ifndef STRUCT_LIST_USERS_H
#define STRUCT_LIST_USERS_H
struct Users{
    std::string login;
    std::string password;
    Users *pNext;
};
#endif // STRUCT_LIST_USERS_H

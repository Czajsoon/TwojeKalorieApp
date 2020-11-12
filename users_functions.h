#include <string>
#include "struct_list_users.h"
#ifndef USERS_FUNCTIONS_H
#define USERS_FUNCTIONS_H

void add(Users** head, std::string login, std::string password); //funkcja tworzaca i dodajaca uzytkownika do listy :)
void delete_users_list(Users** head); //Funkcja usuwajaca liste uzytkownikow
bool verify_account(Users** head, std::string login, std::string password); //funkcja sprawdzajaca podane dane logowania

#endif // USERS_FUNCTIONS_H

#include <iostream>
#include "struct_list_users.h"


void createList(Users** head, std::string login, std::string password) {
    if (!*head) {
        Users* phead = new Users;
        phead->pNext = nullptr;
        phead->login = login;
        phead->password = password;
        *head = phead;
    }
}

void addToList(Users** head, std::string login, std::string password) {
    Users* phead = *head;
    if (phead->pNext) {
        addToList(&phead->pNext, login, password);
    }
    else {
        Users* element = new Users;
        element->pNext = NULL;
        element->login = login;
        element->password = password;
        phead->pNext = element;
    }
}

void add(Users** head, std::string login, std::string password) {
    if (*head)
        addToList(head, login, password);
    else
        createList(head, login, password);
}

void delete_users_list(Users** head) {
    Users* current = *head;
    Users* next;
    while (current != NULL)
    {
        next = current->pNext;
        free(current);
        current = next;
    }
    *head = NULL;
}

Users* find_node_users(Users **head, std::string login, std::string password) {
    Users* phead = *head;
    while(phead){
        if (phead->login == login && phead->password == password) {
            return phead;
        }
        phead = phead->pNext;
    }
    return NULL;
}

bool verify_account(Users **head,std::string login,std::string password) {
    if (find_node_users(head, login, password) != NULL) return true;
    else return false;
}

Users* find_node_users_login(Users **head, std::string login) {
    Users* phead = *head;
    while(phead){
        if (phead->login == login) {
            return phead;
        }
        phead = phead->pNext;
    }
    return NULL;
}

bool verify_login(Users **head,std::string login) {
    if (find_node_users_login(head, login) != NULL) return true;
    else return false;
}

int count_users(Users **head) {
    int counter = 0;
    Users* phead = *head;
    while (phead!=NULL) {
        counter++;
        phead = phead->pNext;
    }
    return counter;
}


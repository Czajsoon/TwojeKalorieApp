#include <iostream>
#include <fstream>
#include <sstream>

#include "produktyStruktury.h"
#include "funkceProduktow.h"

#include <QDir>

using namespace std;

void saveProducts(categoriesProduct** head) {
    categoriesProduct* phead = *head;
    string path = QDir::currentPath().toStdString();
    string text = ".txt";
    string category_name;
    while (phead) {
        string folder = "/Produkty/Produkty/";
        path.append(folder);
        category_name = phead->nazwa_kategorii;
        product* produkty = phead->produkty;
        path.append(category_name);
        path.append(text);
        ofstream fileProducts(path);
        if (fileProducts.is_open()) {
            while (produkty) {
                fileProducts << produkty->nazwa_kategorii <<" "<< produkty->nazwa_produktu << " " << produkty->wartosc_energetyczna << endl;
                produkty = produkty->pNext;
            }
        }
        phead = phead->pNext;
    }
}

void save_CategoriesAndProducts(categoriesProduct** head) {
    string path = QDir::currentPath().toStdString();
    path.append("/Produkty/CategoriesProducts.txt");
    ofstream fileCategories(path);
    if (fileCategories.is_open()) {
        string nazwa_kategorii;
        categoriesProduct* phead = *head;
        while (phead) {
            fileCategories << phead->nazwa_kategorii << endl;
            phead = phead->pNext;
        }
    }
    saveProducts(head);
}

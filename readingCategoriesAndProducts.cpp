#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "funkceProduktow.h"

#include <QDir>

using namespace std;


void addingProductsToCategories(categoriesProduct** head) {
    categoriesProduct* phead = *head;
    while (phead != NULL) {
        string path = QDir::currentPath().toStdString();
        string nazwa_kategorii;
        string folder = "/Produkty/Produkty/";
        path.append(folder);
        string line;
        string text = ".txt";
        nazwa_kategorii = phead->nazwa_kategorii;
        path.append(nazwa_kategorii);
        path.append(text);
        ifstream file(path);
        while (getline(file, line)) {
            istringstream iss(line);
            string nazwa_kategorii_produktu;
            string nazwa_produktu;
            double wartosc_energetyczna;
            if (!(iss >> nazwa_kategorii_produktu >> nazwa_produktu >> wartosc_energetyczna)) { return; }
            else {
                nazwa_produktu[0] = toupper(nazwa_produktu[0]);
                addProductToCategory(head, nazwa_kategorii, nazwa_produktu, wartosc_energetyczna);
            }
        }
        phead = phead->pNext;
    }
}

categoriesProduct* addingCategoriesAndProduct() {
    categoriesProduct* kategorie = NULL;
    string path = QDir::currentPath().toStdString();
    string buffor;
    path.append("/Produkty/CategoriesProducts.txt");
    ifstream file(path);
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string nazwa_kategorii;
        if (!(iss >> nazwa_kategorii)) { return kategorie; }
        else {
            nazwa_kategorii[0] = toupper(nazwa_kategorii[0]);
            addCategory(&kategorie, nazwa_kategorii);
        }
    }
    addingProductsToCategories(&kategorie);
    return kategorie;
}

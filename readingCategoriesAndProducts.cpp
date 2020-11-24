#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "funkceProduktow.h"

using namespace std;


void addingProductsToCategories(categoriesProduct** head) {
    categoriesProduct* phead = *head;
    while (phead != NULL) {
        string nazwa_kategorii;
        string folder = "Produkty/Produkty/";
        string line;
        string text = ".txt";
        nazwa_kategorii = phead->nazwa_kategorii;
        folder.append(nazwa_kategorii);
        folder.append(text);
        ifstream file(folder);
        while (getline(file, line)) {
            istringstream iss(line);
            string nazwa_kategorii_produktu;
            string nazwa_produktu;
            double wartosc_energetyczna;
            if (!(iss >> nazwa_kategorii_produktu >> nazwa_produktu >> wartosc_energetyczna)) { return; } //error
            else {
                addProductToCategory(head, nazwa_kategorii, nazwa_produktu, wartosc_energetyczna);
            }
        }
        phead = phead->pNext;
    }
}

categoriesProduct* addingCategoriesAndProduct() {
    categoriesProduct* kategorie = NULL;
    string buffor;
    ifstream file("Produkty/CategoriesProducts.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string nazwa_kategorii;
        if (!(iss >> nazwa_kategorii)) { return kategorie; } //error
        else {
            addCategory(&kategorie, nazwa_kategorii);
        }
    }
    addingProductsToCategories(&kategorie);
    return kategorie;
}

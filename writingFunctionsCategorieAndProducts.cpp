#include <iostream>
#include <fstream>
#include <sstream>

#include "produktyStruktury.h"
#include "funkceProduktow.h"

using namespace std;

void saveProducts(categoriesProduct** head) {
    categoriesProduct* phead = *head;
    string text = ".txt";
    string category_name;
    while (phead) {
        string folder = "Produkty/Produkty/";
        category_name = phead->nazwa_kategorii;
        product* produkty = phead->produkty;
        folder.append(category_name);
        folder.append(text);
        ofstream fileProducts(folder);
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
    ofstream fileCategories("Produkty/CategoriesProducts.txt");
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

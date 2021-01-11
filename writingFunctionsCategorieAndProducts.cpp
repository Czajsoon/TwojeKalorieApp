#include <iostream>
#include <fstream>
#include <sstream>

#include "produktyStruktury.h"
#include "funkceProduktow.h"

#include <QDir>

using namespace std;

void saveProducts(categoriesProduct** head) {
    categoriesProduct* phead = *head;
    string text = ".txt";
    string category_name;
    while (phead) {
        string path = QDir::currentPath().toStdString();
        string folder = "/Produkty/Produkty/";
        path.append(folder);
        category_name = phead->nazwa_kategorii;
        product* produkty = phead->produkty;
        path.append(category_name);
        path.append(text);
        ofstream fileProducts;
        fileProducts.open(path);
        while (produkty) {
            fileProducts<<"--Nazwa Kategorii--"<<endl;
            fileProducts<<produkty->nazwa_kategorii<<endl;
            fileProducts<<"--Nazwa Produktu--"<<endl;
            fileProducts<<produkty->nazwa_produktu<<endl;
            fileProducts<<"--Wartosc Energetyczna--"<<endl;
            fileProducts<<produkty->wartosc_energetyczna;
            fileProducts<<endl;
            produkty = produkty->pNext;
        }
        fileProducts.close();
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

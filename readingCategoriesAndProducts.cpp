#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "funkceProduktow.h"

#include <QDir>

using namespace std;

bool pustaLiniaCopy(const std::string& Linia) {
    bool rezultat = true;
    for (char const& c : Linia) {
        if (!isspace(c))
            rezultat = false;
    }
    return rezultat;
}

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
        enum Produkty{
            NAZWA_KATEGORII,
            NAZWA_PRODUKTU,
            WARTOSC_ENERGETYCZNA
        };
        Produkty typ_lini;
        int numer_lini = 0;
        product* nowyProdukt = NULL;
        while (getline(file, line)) {
            if(pustaLiniaCopy(line)){
                continue;
            }

            if(line == "--Nazwa Kategorii--"){
                typ_lini = NAZWA_KATEGORII;
                numer_lini = 0;
                nowyProdukt = new product;
                nowyProdukt->pNext = NULL;
            }

            if(line == "--Nazwa Produktu--"){
                typ_lini = NAZWA_PRODUKTU;
                numer_lini = 0;
            }

            if(line == "--Wartosc Energetyczna--"){
                typ_lini = WARTOSC_ENERGETYCZNA;
                numer_lini = 0;
            }

            if(typ_lini == NAZWA_KATEGORII && nowyProdukt != NULL){
                if(numer_lini==1)
                    nowyProdukt->nazwa_kategorii = line;
            }

            if(typ_lini == NAZWA_PRODUKTU && numer_lini>0 && nowyProdukt != NULL){
                line[0] = toupper(line[0]);
                nowyProdukt->nazwa_produktu = line;
            }

            if(typ_lini == WARTOSC_ENERGETYCZNA && numer_lini>0 && nowyProdukt != NULL){
                nowyProdukt->wartosc_energetyczna = stod(line);
                addProductToCategory(head,nowyProdukt);
                nowyProdukt->pNext = NULL;
                delete nowyProdukt;
                nowyProdukt = NULL;
            }
            numer_lini++;

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

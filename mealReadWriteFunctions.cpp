#include <iostream>
#include <fstream>
#include <string>

#include "globals.h"
#include "mealFunctions.h"
#include <QDir>

bool pustaLinia(const std::string& Linia);
void ustawProdukt( posilek** akktualnyPosilek, const std::string& liniaProduktu);

void czytaj(posilek** PosilekHead) {
    std::string path = QDir::currentPath().toStdString();
    std::string folderName = "/Dzienniki/";
    path.append(folderName);
    path.append(login_user_name.toStdString());
    path.append(".txt");
    posilek* nowyposilek = nullptr;

    std::ifstream file(path);
    std::string linia;
    enum typLini {
        NAZWA_POSILKU,
        DATA,
        PRODYUKTY,
        WARTOSC_ENERGETYCZNA,
        WAGA
    };
    typLini typ_lini;
    int numer_lini = 0;
    while (std::getline(file, linia)) {
        if (pustaLinia(linia)) {
            continue;
        }

        if (linia == "--- Nazwa Posilku ---") {
            typ_lini = NAZWA_POSILKU;
            numer_lini = 0;
            nowyposilek = new posilek;
            nowyposilek->pNext = nullptr;
            nowyposilek->produkty = nullptr;
            //nowyposilek->opis = "";
        }

        if (linia == "--- Data ---") {
            typ_lini = DATA;
            numer_lini = 0;
        }

        if (linia == "--- Produkty ---") {
            typ_lini = PRODYUKTY;
            numer_lini = 0;
        }

        if (linia == "--- Wartosc Energetyczna Posilku ---") {
            typ_lini = WARTOSC_ENERGETYCZNA;
            numer_lini = 0;
        }

        if (linia == "--- Waga posilku ---") {
            typ_lini = WAGA;
            numer_lini = 0;
        }

        if (typ_lini == 0) {
            if (numer_lini == 1) {
                nowyposilek->nazwa_posilku = linia;
                //tutaj zle
            }
        }

        if (typ_lini == 1 && nowyposilek != nullptr && numer_lini > 0) {
            if (numer_lini == 1)
                nowyposilek->data = linia;
        }

        if (typ_lini == 2 && nowyposilek != nullptr && numer_lini > 0) {
            ustawProdukt(&nowyposilek, linia);
        }

        if (typ_lini == 3 && PosilekHead != nullptr && numer_lini > 0) {
            if (numer_lini == 1)
                nowyposilek->wartosc_energetyczna = stof(linia);
        }
        if (typ_lini == 4 && nowyposilek != nullptr && numer_lini > 0) {
            if (numer_lini == 1){
                nowyposilek->waga = stod(linia);
                addMeal(PosilekHead, nowyposilek);
                usun_produkty_z_posilku(&nowyposilek);
            }
        }
        numer_lini++;
    }
    file.close();
}

void czytajShare(posilek** PosilekHead) {
    std::string path = QDir::currentPath().toStdString();
    std::string folderName = "/Posilki/";
    path.append(folderName);
    path.append("Shared");
    path.append(".txt");
    posilek* nowyposilek = nullptr;

    std::ifstream file(path);
    std::string linia;
    enum typLini {
        NAZWA_POSILKU,
        DATA,
        PRODYUKTY,
        WARTOSC_ENERGETYCZNA,
        WAGA
    };
    typLini typ_lini;
    int numer_lini = 0;
    while (std::getline(file, linia)) {
        if (pustaLinia(linia)) {
            continue;
        }

        if (linia == "--- Nazwa Posilku ---") {
            typ_lini = NAZWA_POSILKU;
            numer_lini = 0;
            nowyposilek = new posilek;
            nowyposilek->pNext = nullptr;
            nowyposilek->produkty = nullptr;
            //nowyposilek->opis = "";
        }

        if (linia == "--- Data ---") {
            typ_lini = DATA;
            numer_lini = 0;
        }

        if (linia == "--- Produkty ---") {
            typ_lini = PRODYUKTY;
            numer_lini = 0;
        }

        if (linia == "--- Wartosc Energetyczna Posilku ---") {
            typ_lini = WARTOSC_ENERGETYCZNA;
            numer_lini = 0;
        }

        if (linia == "--- Waga posilku ---") {
            typ_lini = WAGA;
            numer_lini = 0;
        }

        if (typ_lini == 0) {
            if (numer_lini == 1) {
                nowyposilek->nazwa_posilku = linia;
                //tutaj zle
            }
        }

        if (typ_lini == 1 && nowyposilek != nullptr && numer_lini > 0) {
            if (numer_lini == 1)
                nowyposilek->data = linia;
        }

        if (typ_lini == 2 && nowyposilek != nullptr && numer_lini > 0) {
            ustawProdukt(&nowyposilek, linia);
        }

        if (typ_lini == 3 && PosilekHead != nullptr && numer_lini > 0) {
            if (numer_lini == 1)
                nowyposilek->wartosc_energetyczna = stof(linia);
        }
        if (typ_lini == 4 && nowyposilek != nullptr && numer_lini > 0) {
            if (numer_lini == 1){
                nowyposilek->waga = stod(linia);
                addMeal(PosilekHead, nowyposilek);
                usun_produkty_z_posilku(&nowyposilek);
            }
        }
        numer_lini++;
    }
    file.close();
}

bool pustaLinia(const std::string& Linia) {
    bool rezultat = true;
    for (char const& c : Linia) {
        if (!isspace(c))
            rezultat = false;
    }
    return rezultat;
}

void ustawProdukt(posilek** akktualnyPosilek, const std::string& liniaProduktu) {
    std::string nazwaPro, WEstr, wagaStr;

    int licznik_spacji = 0;
    for (const char& c : liniaProduktu) {
        if (c=='`') {
            licznik_spacji++;
        }
        else if (licznik_spacji == 0) {
            if(c!='"')
                nazwaPro += c;
        }
        else if (licznik_spacji % 2 == 1) {
            WEstr += c;
        }
        else {
            wagaStr += c;
        }

    }
    double WE = stod(WEstr);
    double waga = stod(wagaStr);
    addProductToMealNewProducts(akktualnyPosilek, nazwaPro, WE, waga);
}

void zapisz_liste_posilkow(posilek** lista_posilkow) {
    std::string path = QDir::currentPath().toStdString();
    std::string folderName = "/Dzienniki/";
    path.append(folderName);
    path.append(login_user_name.toStdString());
    path.append(".txt");
    posilek* phead = *lista_posilkow;
    ofstream myfile;
    myfile.open(path);
    while (phead) {
        myfile << "--- Nazwa Posilku ---" << endl;
        myfile << phead->nazwa_posilku << endl;
        myfile << "--- Data ---" << endl;
        myfile << phead->data << endl;
        myfile << "--- Produkty ---" << endl;
        productMeal* pheadPro = phead->produkty;
        while (pheadPro) {
            myfile <<'"'<<pheadPro->nazwa_produktu << '"'<<"`" << pheadPro->wartosc_energetyczna << "`" << pheadPro->waga << endl;
            pheadPro = pheadPro->pNext;
        }
        myfile << "--- Wartosc Energetyczna Posilku ---" << endl;
        myfile << phead->wartosc_energetyczna << endl;
        myfile << "--- Waga posilku ---" << endl;
        myfile << phead->waga << endl;
        myfile << endl;
        phead = phead->pNext;
    }
    myfile.close();
    delete_all_meals(lista_posilkow);
}

void zapisz_liste_posilkow_shared(posilek** lista_posilkow) {
    std::string path = QDir::currentPath().toStdString();
    std::string folderName = "/Posilki/";
    path.append(folderName);
    path.append("Shared");
    path.append(".txt");
    posilek* phead = *lista_posilkow;
    ofstream myfile;
    myfile.open(path);
    while (phead) {
        myfile << "--- Nazwa Posilku ---" << endl;
        myfile << phead->nazwa_posilku << endl;
        myfile << "--- Data ---" << endl;
        myfile << phead->data << endl;
        myfile << "--- Produkty ---" << endl;
        productMeal* pheadPro = phead->produkty;
        while (pheadPro) {
            myfile <<'"'<<pheadPro->nazwa_produktu << '"'<<"`" << pheadPro->wartosc_energetyczna << "`" << pheadPro->waga << endl;
            pheadPro = pheadPro->pNext;
        }
        myfile << "--- Wartosc Energetyczna Posilku ---" << endl;
        myfile << phead->wartosc_energetyczna << endl;
        myfile << "--- Waga posilku ---" << endl;
        myfile << phead->waga << endl;
        myfile << endl;
        phead = phead->pNext;
    }
    myfile.close();
    delete_all_meals(lista_posilkow);
}

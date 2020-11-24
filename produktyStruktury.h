#include <iostream>
#include <string>

#ifndef PRODUKTYSTRUKTURY_H_
#define PRODUKTYSTRUKTURY_H_
struct product {
    std::string nazwa_kategorii;
    std::string nazwa_produktu;
    double wartosc_energetyczna;
    product* pNext;
};

struct categoriesProduct {
    std::string nazwa_kategorii;
    product* produkty;
    categoriesProduct* pNext;
};

#endif // !PRODUKTYSTRUKTURY_H_

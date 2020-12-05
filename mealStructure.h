#include <iostream>
#include <string>


#ifndef MEALSTRUCTURE_H
#define MEALSTRUCTURE_H


using namespace std;

struct productMeal {
    std::string nazwa_produktu;
    double wartosc_energetyczna;
    double waga;
    productMeal* pNext;
};

struct posilek{
    string nazwa_posilku;
    string data;
    productMeal* produkty;
    float wartosc_energetyczna;
    double waga;
    posilek* pNext;
};
#endif // MEALSTRUCTURE_H

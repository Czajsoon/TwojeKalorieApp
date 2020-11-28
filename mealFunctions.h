#include "mealStructure.h"
#ifndef MEALFUNCTIONS_H
#define MEALFUNCTIONS_H
void addMeal(posilek** head, posilek* nowyPosilek);
void addProductToMeal(posilek** headCategory, std::string nazwa_posilku, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu);
void delete_all_meals(posilek** headCategory);
void addProductToMealNewProducts(posilek** headCategory, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu);
#endif // MEALFUNCTIONS_H

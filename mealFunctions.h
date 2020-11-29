#include "mealStructure.h"
#ifndef MEALFUNCTIONS_H
#define MEALFUNCTIONS_H
void addMeal(posilek** head, posilek* nowyPosilek);
void addProductToMeal(posilek** headCategory, std::string nazwa_posilku, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu);
void delete_all_meals(posilek** headCategory);
void addProductToMealNewProducts(posilek** headCategory, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu);
void usun_produkty_z_posilku(posilek** headPosilek);
int countProductsInMeal(posilek** headPosilek);
bool isProductInMeal(posilek** headPosilek,std::string nazwa_produktu);
void AddWeightToProduct(posilek** headPosilek, std::string nazwa_produktu,double waga_produktu);
void MinusWeightToProduct(posilek** headPosilek, std::string nazwa_produktu,double waga_produktu);
void createAddProductMealListHistory(productMeal** head,std::string nazwa_produktu,double warosc_energetyczna,double waga);
void cofnijHistorie(productMeal** head);
void usunHistorie(productMeal** head);
void deleteProduct0gram(posilek** head);
#endif // MEALFUNCTIONS_H

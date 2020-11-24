#include "produktyStruktury.h"
#include <iostream>
#include <string>

#ifndef FUNKCJEPRODUKTOW_H_
#define FUNKCJEPRODUKTOW_H_

void addCategory(categoriesProduct** head, std::string nazwa_kategorii);
void delete_categories_product(categoriesProduct** head);
void printCategories(categoriesProduct** head);
void addProductToCategory(categoriesProduct** headCategory, std::string nazwa_kategorii, std::string nazwa_produktu, double wartosc_energetyczna);
void clearMemoryProductsAndCategory(categoriesProduct** head);
void wypiszKategorieAndProdukty(categoriesProduct* head);
bool is_category_in_Categories(categoriesProduct* head,std::string nazwa_kategorii);
bool is_product_in_categories(categoriesProduct* head, std::string nazwa_kategorii, std::string nazwa_produktu);
void deleteProduct(categoriesProduct** head, std::string nazwa_kategorii, std::string nazwa_produktu);
void deleteCategory(categoriesProduct** head, std::string nazwa_kategorii);
int count_products(categoriesProduct* head,std::string nazwa_kategorii);

#endif // !FUNKCJEPRODUKTOW_H_

#include <iostream>

#include "mealStructure.h"

void createListMeals(posilek** head, posilek* nowyPosilek) {
    if (!*head) {
        *head = nowyPosilek;
    }
}

void addToListMeals(posilek** head, posilek* nowyPosilek) {
    posilek* phead = *head;
    if (nowyPosilek->nazwa_posilku <= phead->nazwa_posilku) {
        *head = nowyPosilek;
        nowyPosilek->pNext = phead;
    }
    else {
        while (phead->pNext != NULL) {
            posilek* pheadnext = phead->pNext;
            if (nowyPosilek->nazwa_posilku <= pheadnext->nazwa_posilku) {
                phead->pNext = nowyPosilek;
                nowyPosilek->pNext = pheadnext;
                break;
            }
            phead = phead->pNext;
        }
        if (nowyPosilek->nazwa_posilku >= phead->nazwa_posilku) {
            phead->pNext = nowyPosilek;
        }
    }
}

void addMeal(posilek** head, posilek* nowyPosilek) {
    if (*head)
        addToListMeals(head, nowyPosilek);
    else
        createListMeals(head, nowyPosilek);
}

void createListProducts(productMeal** head, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu) {
    if (!*head) {
        productMeal* phead = new productMeal;
        phead->pNext = nullptr;
        phead->nazwa_produktu = nazwa_produktu;
        phead->waga = waga_produktu;
        phead->wartosc_energetyczna = wartosc_energetyczna;
        *head = phead;
    }
}

void addToListProducts(productMeal** head, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu) {
    productMeal* phead = *head;
    productMeal* newElement = new productMeal;
    newElement->nazwa_produktu = nazwa_produktu;
    newElement->waga = waga_produktu;
    newElement->pNext = nullptr;
    newElement->wartosc_energetyczna = wartosc_energetyczna;
    *head = newElement;
    newElement->pNext = phead;
}

void addProductToMeal(posilek** headCategory, std::string nazwa_posilku, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu) {
    posilek* pheadCat = *headCategory;
    while (pheadCat != NULL) {
        if (pheadCat->nazwa_posilku == nazwa_posilku) {
            if (pheadCat->produkty) {
                addToListProducts(&pheadCat->produkty, nazwa_produktu, wartosc_energetyczna, waga_produktu);
                pheadCat->wartosc_energetyczna += wartosc_energetyczna;
                return;
            }
            else {
                createListProducts(&pheadCat->produkty, nazwa_produktu, wartosc_energetyczna, waga_produktu);
                pheadCat->wartosc_energetyczna += wartosc_energetyczna;
                return;
            }
        }
        pheadCat = pheadCat->pNext;
    }
    std::cout << "nie dodano produktu do kategorii brak kategorii" << std::endl;
}

void addProductToMealNewProducts(posilek** headCategory, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu) {
    posilek* pheadCat = *headCategory;
    while (pheadCat != NULL) {
        if (pheadCat->produkty){
            addToListProducts(&pheadCat->produkty, nazwa_produktu, wartosc_energetyczna, waga_produktu);
            pheadCat->wartosc_energetyczna += (wartosc_energetyczna*waga_produktu);
            *headCategory = pheadCat;
            return;
        }
        else {
            createListProducts(&pheadCat->produkty, nazwa_produktu, wartosc_energetyczna, waga_produktu);
            pheadCat->wartosc_energetyczna += (wartosc_energetyczna*waga_produktu);
            *headCategory = pheadCat;
            return;
        }
    }
    std::cout << "nie dodano produktu do kategorii brak kategorii" << std::endl;
}

void delete_all_meals(posilek** headCategory) {
    posilek* current = *headCategory;
    posilek* next;
    while (current != NULL)
    {
        next = current->pNext;
        productMeal* currentProduct = current->produkty;
        productMeal* nextProduct;
        while (currentProduct != NULL) {
            nextProduct = currentProduct->pNext;
            free(currentProduct);
            currentProduct = nextProduct;
        }
        current->produkty = NULL;
        free(current);
        current = next;
    }
    *headCategory = NULL;
}

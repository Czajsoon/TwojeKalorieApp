#include <iostream>

#include "mealStructure.h"

void createListMeals(posilek** head, std::string nazwa_posilku) {
    if (!*head) {
        posilek* phead = new posilek;
        phead->pNext = nullptr;
        phead->nazwa_posilku = nazwa_posilku;
        phead->wartosc_energetyczna = 0;
        phead->produkty = nullptr;
        *head = phead;
    }
}

void addToListMeals(posilek** head, std::string nazwa_posilku) {
    posilek* phead = *head;
    posilek* newElement = new posilek;
    newElement->nazwa_posilku = nazwa_posilku;
    newElement->wartosc_energetyczna = 0;
    newElement->pNext = nullptr;
    newElement->produkty = nullptr;
    if (newElement->nazwa_posilku <= phead->nazwa_posilku) {
        *head = newElement;
        newElement->pNext = phead;
    }
    else {
        while (phead->pNext != NULL) {
            posilek* pheadnext = phead->pNext;
            if (newElement->nazwa_posilku <= pheadnext->nazwa_posilku) {
                phead->pNext = newElement;
                newElement->pNext = pheadnext;
                break;
            }
            phead = phead->pNext;
        }
        if (newElement->nazwa_posilku >= phead->nazwa_posilku) {
            phead->pNext = newElement;
        }
    }
}

void addMeal(posilek** head, std::string nazwa_posilku) {
    if (*head)
        addToListMeals(head, nazwa_posilku);
    else
        createListMeals(head, nazwa_posilku);
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
    if (newElement->nazwa_produktu <= phead->nazwa_produktu) {
        *head = newElement;
        newElement->pNext = phead;
    }
    else {
        while (phead->pNext != NULL) {
            productMeal* pheadnext = phead->pNext;
            if (newElement->nazwa_produktu <= pheadnext->nazwa_produktu) {
                phead->pNext = newElement;
                newElement->pNext = pheadnext;
                break;
            }
            phead = phead->pNext;
        }
        if (newElement->nazwa_produktu >= phead->nazwa_produktu) {
            phead->pNext = newElement;
        }
    }
}

void addProductToMeal(posilek** headCategory, std::string nazwa_posilku, std::string nazwa_produktu, float wartosc_energetyczna,double waga_produktu) {
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

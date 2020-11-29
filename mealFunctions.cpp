#include <iostream>

#include "mealStructure.h"

void addProductToMealNewProducts(posilek** headCategory, std::string nazwa_produktu, float wartosc_energetyczna, double waga_produktu);

void createListMeals(posilek** head, posilek* nowyPosilek) {
    posilek* nowyPointer = new posilek;
    nowyPointer->nazwa_posilku = nowyPosilek->nazwa_posilku;
    nowyPointer->pNext = nullptr;
    nowyPointer->produkty = nullptr;
    nowyPointer->data = nowyPosilek->data;
    nowyPointer->waga =nowyPosilek->waga;
    nowyPointer->wartosc_energetyczna = nowyPosilek->wartosc_energetyczna;
    productMeal* nowyPointerProdukty = nowyPosilek->produkty;
    while(nowyPointerProdukty){
        addProductToMealNewProducts(&nowyPointer,nowyPointerProdukty->nazwa_produktu,nowyPointerProdukty->wartosc_energetyczna,nowyPointerProdukty->waga);
        nowyPointerProdukty = nowyPointerProdukty->pNext;
    }
    *head = nowyPointer;

}

void addToListMeals(posilek** head, posilek* nowyPosilek) {
    posilek* phead = *head;
    posilek* nowyPointer = new posilek;
    nowyPointer->nazwa_posilku = nowyPosilek->nazwa_posilku;
    nowyPointer->pNext = nullptr;
    nowyPointer->produkty = nullptr;
    nowyPointer->data = nowyPosilek->data;
    nowyPointer->waga =nowyPosilek->waga;
    nowyPointer->wartosc_energetyczna = nowyPosilek->wartosc_energetyczna;
    productMeal* nowyPointerProdukty = nowyPosilek->produkty;
    while(nowyPointerProdukty){
        addProductToMealNewProducts(&nowyPointer,nowyPointerProdukty->nazwa_produktu,nowyPointerProdukty->wartosc_energetyczna,nowyPointerProdukty->waga);
        nowyPointerProdukty = nowyPointerProdukty->pNext;
    }
    nowyPointer->pNext = phead;
    *head = nowyPointer;
//    if (nowyPosilek->nazwa_posilku <= phead->nazwa_posilku) {
//        *head = nowyPosilek;
//        nowyPosilek->pNext = phead;
//    }
//    else {
//        while (phead->pNext != NULL) {
//            posilek* pheadnext = phead->pNext;
//            if (nowyPosilek->nazwa_posilku <= pheadnext->nazwa_posilku) {
//                phead->pNext = nowyPosilek;
//                nowyPosilek->pNext = pheadnext;
//                break;
//            }
//            phead = phead->pNext;
//        }
//        if (nowyPosilek->nazwa_posilku >= phead->nazwa_posilku) {
//            phead->pNext = nowyPosilek;
//        }
//    }
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
            //pheadCat->wartosc_energetyczna += (wartosc_energetyczna*waga_produktu);
            *headCategory = pheadCat;
            return;
        }
        else {
            createListProducts(&pheadCat->produkty, nazwa_produktu, wartosc_energetyczna, waga_produktu);
            //pheadCat->wartosc_energetyczna += (wartosc_energetyczna*waga_produktu);
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

void usun_produkty_z_posilku(posilek** headPosilek) {
    posilek* pProdukty = *headPosilek;
        productMeal* currentProduct = pProdukty->produkty;
        productMeal* nextProduct;
        while (currentProduct != NULL) {
            nextProduct = currentProduct->pNext;
            free(currentProduct);
            currentProduct = nextProduct;
        }
        (*headPosilek)->produkty = currentProduct;
        free(pProdukty);
        pProdukty = NULL;
        (*headPosilek) = pProdukty;
}

int countProductsInMeal(posilek** headPosilek){
    posilek* phead = *headPosilek;
    int counter = 0;
    productMeal* pheadProducts = phead->produkty;
    while(pheadProducts){
        counter++;
        pheadProducts = pheadProducts->pNext;
    }
    return counter;
}

bool isProductInMeal(posilek** headPosilek,std::string nazwa_produktu) {
    productMeal* listaProduktow = (*headPosilek)->produkty;
    while(listaProduktow){
        if (listaProduktow->nazwa_produktu == nazwa_produktu)
            return true;
        listaProduktow = listaProduktow->pNext;
    }
    return false;
}

void AddWeightToProduct(posilek** headPosilek, std::string nazwa_produktu,double waga_produktu) {
    productMeal* listaProduktow = (*headPosilek)->produkty;
    while (listaProduktow) {
        if (listaProduktow->nazwa_produktu == nazwa_produktu) {
            listaProduktow->waga += waga_produktu;
        }
        listaProduktow = listaProduktow->pNext;
    }
}

void MinusWeightToProduct(posilek** headPosilek, std::string nazwa_produktu,double waga_produktu) {
    productMeal* listaProduktow = (*headPosilek)->produkty;
    while (listaProduktow) {
        if (listaProduktow->nazwa_produktu == nazwa_produktu) {
            listaProduktow->waga -= waga_produktu;
        }
        listaProduktow = listaProduktow->pNext;
    }
}

void createProductMealListHistory(productMeal** head, std::string nazwa_produktu, double warosc_energetyczna, double waga) {
    productMeal* phead = new productMeal;
    phead->nazwa_produktu = nazwa_produktu;
    phead->waga = waga;
    phead->wartosc_energetyczna = warosc_energetyczna;
    phead->pNext = NULL;
    *head = phead;
}

void AddProductMealListHistory(productMeal** head, std::string nazwa_produktu, double warosc_energetyczna, double waga) {
    productMeal* phead = *head;
    productMeal* nowy = new productMeal;
    nowy->nazwa_produktu = nazwa_produktu;
    nowy->waga = waga;
    nowy->wartosc_energetyczna = warosc_energetyczna;
    nowy->pNext = phead;
    *head = nowy;
}

void createAddProductMealListHistory(productMeal** head,std::string nazwa_produktu,double warosc_energetyczna,double waga) {
    if (*head) {
        AddProductMealListHistory(head, nazwa_produktu, warosc_energetyczna, waga);
    }
    else {
        createProductMealListHistory(head, nazwa_produktu, warosc_energetyczna, waga);
    }
}

void cofnijHistorie(productMeal** head) {
    if (*head) {
        productMeal* current = *head;
        productMeal* next = current->pNext;
        current->pNext = NULL;
        free(current);
        *head = next;
    }
}

void usunHistorie(productMeal** head_ref){

    productMeal* current = *head_ref;
    productMeal* next;
    while (current != NULL)
    {
        next = current->pNext;
        free(current);
        current = next;
    }
    *head_ref = NULL;

}

void deleteProduct0gram(posilek** head){
    productMeal* pPro = (*head)->produkty;
    productMeal* prev = NULL;
    if(pPro && pPro->waga==0){
        (*head)->produkty = pPro->pNext;
        delete pPro;
        return;
    }
    while(pPro && pPro->waga!=0){
        prev = pPro;
        pPro = pPro->pNext;
    }
    if (pPro == NULL)
            return;
    prev->pNext = pPro->pNext;
    delete pPro;
}

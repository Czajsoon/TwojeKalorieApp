#include <iostream>

#include "produktyStruktury.h"

void createListCategories(categoriesProduct** head, std::string nazwa_kategorii) {
    if (!*head) {
        categoriesProduct* phead = new categoriesProduct;
        phead->pNext = nullptr;
        phead->nazwa_kategorii = nazwa_kategorii;
        phead->produkty = nullptr;
        *head = phead;
    }
}

void addToListCategories(categoriesProduct** head, std::string nazwa_kategorii) {
    categoriesProduct* phead = *head;
    categoriesProduct* newElement = new categoriesProduct;
    newElement->nazwa_kategorii = nazwa_kategorii;
    newElement->pNext = nullptr;
    newElement->produkty = nullptr;
    if (newElement->nazwa_kategorii <= phead->nazwa_kategorii) {
        *head = newElement;
        newElement->pNext = phead;
    }
    else {
        while (phead->pNext != NULL) {
            categoriesProduct* pheadnext = phead->pNext;
            if (newElement->nazwa_kategorii <= pheadnext->nazwa_kategorii) {
                phead->pNext = newElement;
                newElement->pNext = pheadnext;
                break;
            }
            phead = phead->pNext;
        }
        if (newElement->nazwa_kategorii >= phead->nazwa_kategorii) {
            phead->pNext = newElement;
        }
    }
}

void addCategory(categoriesProduct** head, std::string nazwa_kategorii) {
    if (*head)
        addToListCategories(head, nazwa_kategorii);
    else
        createListCategories(head, nazwa_kategorii);
}

void delete_categories_product(categoriesProduct** head) {
    categoriesProduct* current = *head;
    categoriesProduct* next;
    while (current != NULL)
    {
        next = current->pNext;
        free(current);
        current = next;
    }
    *head = NULL;
}

void printCategories(categoriesProduct** head) {
    categoriesProduct* phead = *head;
    while (phead != nullptr) {
        std::cout << "kategoria: " << phead->nazwa_kategorii << std::endl;
        phead = phead->pNext;
    }
}

void createListProducts(product** head, std::string nazwa_kategorii, std::string nazwa_produktu, double wartosc_energetyczna) {
    if (!*head) {
        product* phead = new product;
        phead->pNext = nullptr;
        phead->nazwa_kategorii = nazwa_kategorii;
        phead->nazwa_produktu = nazwa_produktu;
        phead->wartosc_energetyczna = wartosc_energetyczna;
        *head = phead;
    }
}

void addToListProducts(product** head, std::string nazwa_kategorii, std::string nazwa_produktu, double wartosc_energetyczna) {
    product* phead = *head;
    product* newElement = new product;
    newElement->nazwa_kategorii = nazwa_kategorii;
    newElement->nazwa_produktu = nazwa_produktu;
    newElement->pNext = nullptr;
    newElement->wartosc_energetyczna = wartosc_energetyczna;
    if (newElement->nazwa_produktu <= phead->nazwa_produktu) {
        *head = newElement;
        newElement->pNext = phead;
    }
    else {
        while (phead->pNext != NULL) {
            product* pheadnext = phead->pNext;
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

void addProductToCategory(categoriesProduct** headCategory, std::string nazwa_kategorii, std::string nazwa_produktu, double wartosc_energetyczna) {
    categoriesProduct* pheadCat = *headCategory;
    while (pheadCat != NULL) {
        if (pheadCat->nazwa_kategorii == nazwa_kategorii) {
            if (pheadCat->produkty) {
                addToListProducts(&pheadCat->produkty, nazwa_kategorii, nazwa_produktu, wartosc_energetyczna);
                return;
            }
            else {
                createListProducts(&pheadCat->produkty, nazwa_kategorii, nazwa_produktu, wartosc_energetyczna);
                return;
            }
        }
        pheadCat = pheadCat->pNext;
    }
    std::cout << "nie dodano produktu do kategorii brak kategorii" << std::endl;
}

void clearMemoryProductsAndCategory(categoriesProduct** head) {
    categoriesProduct* current = *head;
    categoriesProduct* next;
    while (current != NULL)
    {
        next = current->pNext;
        product* currentProduct = current->produkty;
        product* nextProduct;
        while (currentProduct != NULL) {
            nextProduct = currentProduct->pNext;
            free(currentProduct);
            currentProduct = nextProduct;
        }
        current->produkty = NULL;
        free(current);
        current = next;
    }
    *head = NULL;
}

void wypiszKategorieAndProdukty(categoriesProduct* head) {
    while (head != NULL) {
        std::cout << "Nazwa kategorii: " << head->nazwa_kategorii << std::endl;
        product* produkty = head->produkty;
        while (produkty != NULL) {
            std::cout << "\t nazwa produktu: " << produkty->nazwa_produktu << " wartosc energetyczna w 1g: " << produkty->wartosc_energetyczna <<" kcal"<< std::endl;
            produkty = produkty->pNext;
        }
        head = head->pNext;
    }
}

bool is_category_in_Categories(categoriesProduct* head,std::string nazwa_kategorii){
    while(head){
        if (head->nazwa_kategorii == nazwa_kategorii) {
            return true;
        }
        head = head->pNext;
    }
    return false;
}

bool is_product_in_categories(categoriesProduct* head, std::string nazwa_kategorii, std::string nazwa_produktu) {
    while (head) {
        if (head->nazwa_kategorii == nazwa_kategorii) {
            product* pProduct = head->produkty;
            while (pProduct) {
                if (pProduct->nazwa_produktu == nazwa_produktu)
                    return true;
                pProduct = pProduct->pNext;
            }
        }
        head = head->pNext;
    }
    return false;
}

void deleteProduct(categoriesProduct** head, std::string nazwa_kategorii, std::string nazwa_produktu) {
    categoriesProduct* phead = *head;
    while (phead) {
        if (phead->nazwa_kategorii == nazwa_kategorii) {
            product* pProduct = phead->produkty;
            product* pPrev = NULL;
            if (pProduct != NULL && pProduct->nazwa_produktu == nazwa_produktu)
            {
                phead->produkty = pProduct->pNext;
                delete pProduct;
                return;
            }
            while (pProduct != NULL && pProduct->nazwa_produktu != nazwa_produktu)
            {
                pPrev = pProduct;
                pProduct = pProduct->pNext;
            }
            if (pProduct == NULL)
                return;
            else {
                pPrev->pNext = pProduct->pNext;
                delete pProduct;
                return;
            }
        }
        phead = phead->pNext;
    }
}

void deleteCategory(categoriesProduct** head, std::string nazwa_kategorii) {
    categoriesProduct* phead = *head;
    categoriesProduct* pPrev = NULL;
    if (phead != NULL && phead->nazwa_kategorii == nazwa_kategorii) {
        product* pProduct = phead->produkty;
        product* pProductNext = NULL;
        while (pProduct) {
            pProductNext = pProduct->pNext;
            delete pProduct;
            pProduct = pProductNext;
        }
        pProduct = NULL;
        *head = phead->pNext;
        delete phead;
        return;
    }
    while (phead != NULL && phead->nazwa_kategorii != nazwa_kategorii)
    {
        pPrev = phead;
        phead = phead->pNext;
    }
    if (phead == NULL)
        return;
    else {
        product* pProduct = phead->produkty;
        product* pProductNext = NULL;
        while (pProduct) {
            pProductNext = pProduct->pNext;
            delete pProduct;
            pProduct = pProductNext;
        }
        pProduct = NULL;
        pPrev->pNext = phead->pNext;
        delete phead;
        return;
    }
}

int count_products(categoriesProduct* head,std::string nazwa_kategorii){
    int counter = 0;
    while(head){
        if(head->nazwa_kategorii == nazwa_kategorii){
            product* pProduct = head->produkty;
            while(pProduct){
                counter++;
                pProduct = pProduct->pNext;
            }
            return counter;
        }
        head = head->pNext;
    }
    return counter;
}

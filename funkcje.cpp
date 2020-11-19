#include <iostream>

bool numbers_in_string(const std::string& linia) {
    int size = linia.size();
    for (int i = 0; i < size; i++) {
        char znak = linia[i];
        if (znak != '0' &&
            znak != '1' &&
            znak != '2'&&
            znak != '3'&&
            znak != '4'&&
            znak != '5'&&
            znak != '6'&&
            znak != '7'&&
            znak != '8'&&
            znak != '9'&&
            znak != '.')
           return false;
    }
    return true;
}


bool is_space_in_string(const std::string& linia) {
    int size = linia.size();
    for (int i = 0; i < size; i++) {
        char znak = linia[i];
        if (isspace(znak)) return true;
    }
    return false;
}

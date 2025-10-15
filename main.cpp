#include <iostream>
#include "Catalog.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "ai scris gresit, trebuie sa scrii ./program catalog.in catalog.out \n";
        return 1;
    }

    Catalog catalog;                 
    catalog.citire(argv[1]);            
    catalog.sorteaza();                  
    catalog.scriere(argv[2]);              
    return 0;
}

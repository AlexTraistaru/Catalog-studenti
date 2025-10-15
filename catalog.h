#include <iostream>
#include <string>
#include "Student.h"

class Catalog {
    Student vector_studenti[1500];
    int N;      
    int K;          

public:
    Catalog();
    void citire(const std::string& fis_intrare);
    void sorteaza();                    
    void scriere(const std::string& fis_iesire) const;
};

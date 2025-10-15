#include "Student.h"

Student::Student(){
    nume = "";
    varsta = 0;
    m = 0;
    medie = 0.0;
    for (int i = 0; i < 20; i++) 
        notele[i] = 0.0;
}

void Student::citire_student(const std::string& n, int v, int nr, const double note[]) {
    nume = n;
    varsta = v;
    m = nr;
    for (int i = 0; i < m; i++) 
        notele[i] = note[i];
    calculeaza_medie();
}

void Student::calculeaza_medie() {
    if (m <= 0) 
    { 
        medie = 0.0; 
        return; 
    }
    double suma = 0.0;
    for (int i = 0; i < m; i++) 
        suma += notele[i];
    medie = suma / (double)m;
}

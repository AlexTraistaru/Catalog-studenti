#include "Student.h"
#include <math.h>

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

double rotunjire(double x) {
    double y = x * 1000.0;                     // mutam virgula 3 zecimale la dreapta
    long long t = (long long)floor(y + 1e-9);  // luam partea intreaga
    int third = (int)(t % 10);                 // a treia zecimala
    long long two = t / 10;                    // primele doua zecimale

    if (third > 5) {
        two += 1;
    } else if (third == 5) {
        if (two % 2 != 0) two += 1;
    }
    return two / 100.0;
}

void Student::calculeaza_medie() {
    if (m <= 0) { medie = 0.0; return; }

    double suma = 0.0;
    for (int i = 0; i < m; i++)
        suma += notele[i];

    double avg = suma / (double)m;
    medie = rotunjire(avg);
}
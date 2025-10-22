#include <iostream>
#include <string>
#include <math.h>

struct Student {
    std::string nume;
    int varsta;
    int m;
    double notele[20];
    double medie;

    Student();
    void citire_student(const std::string& n, int v, int nr, const double note[]);
    void calculeaza_medie();
};
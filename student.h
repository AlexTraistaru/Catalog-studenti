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
//const - garanteaza ca nu se va modifica obiectul curent
    //& - se transmite prin referinta (nu se face copie), se duce in memorie exact unde este numele (din fisier)
    //* - pointer la un array de double (notele), puteam sa mai scriu double notele[]
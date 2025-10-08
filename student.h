#include <iostream>
#include <math.h>
#include <string>

using namespace std;    

struct Student{
    string nume;
    int varsta;
    int nr_note;
    double note[20]; 
    double medie;

public:
    Student();
    void citire_student(const string& n, int v, int nr_n, const double* notele);
    void media_studentului();
};

#include "student.h"

Student::Student() {
    nume = "";
    varsta = 0;
    nr_note = 0;
    medie = 0.0;
    for (int i = 0; i < 20; i++) 
        note[i] = 0.0;
}

void Student :: citire_student(const string& n, int v, int nr_n, const double* notele) {
    nume = n;
    varsta = v;
    nr_note = nr_n;
    medie = 0.0;
    for (int i = 0; i < nr_n; i++) 
        note[i] = notele[i];
    media_studentului();
}

void Student::media_studentului() {
    if (nr_note <= 0) {
        medie = 0.0;
        return;
    }
    double s = 0.0;
    for (int i = 0; i < nr_note; i++) 
        s += note[i];
    
        medie = s / (double)nr_note;
}
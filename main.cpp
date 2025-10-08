#include <iostream>
#include <fstream>
#include "student.h"

using namespace std;

int main()
{
    ifstream fin("catalog.in");
    if (!fin.is_open()) {
        cerr << "eroare cu catalog.in" << endl;
        return 1;
    }

    string nume;
    int varsta, nr_note;
    double notele[20];

    fin >> nume >> varsta >> nr_note;
    for (int i = 0; i < nr_note; i++)
        fin >> notele[i];
    fin.close();

    Student s;
    s.citire_student(nume, varsta, nr_note, notele);

    cout << "Nume: " << s.nume << endl;
    cout << "Varsta: " << s.varsta << endl;
    cout << "Numar note: " << s.nr_note << endl;
    cout << "Note: ";
    for (int i = 0; i < s.nr_note; i++)
        cout << s.note[i] << " ";
    cout << endl;
    cout << "Media: " << s.medie << endl;   
    return 0;
}
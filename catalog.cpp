#include "Catalog.h"
#include <fstream>
#include <math.h>
#include <string>

Catalog::Catalog(){
    N = 0;
    K = 0;
    for (int i = 0; i < 1500; i++)
        vector_studenti[i] = Student();
} 

void Catalog::citire(const std::string& fis_intrare) {
    std::ifstream fis(fis_intrare.c_str());
    if (!fis.is_open()) {
        std::cout << "eroare la deschidere";
        return;
    }

    int n, k;
    fis >> n >> k;
    if (n < 1 || n > 1500 || k < 1 || k > n) {
        std::cout << "parametrii nu respecta cerintele";
        fis.close();
        return;
    }
    N = 0;             
    K = k;        

    for (int i = 0; i < n && N < 1500; i++) {
        std::string nume;
        int varsta, m;
        fis >> nume >> varsta >> m;
        double aux[20];
        for (int j = 0; j < m; j++) 
            fis >> aux[j];
        Student s;
        s.citire_student(nume, varsta, m, aux);
        vector_studenti[N++] = s;               
    }
    fis.close();
}

void Catalog::sorteaza() {
    int i, j;
    double eroare = 1e-7; 
    for (i = 0; i < N - 1; i++) 
    {
        for (j = i + 1; j < N; j++) 
        {
            if (fabs(vector_studenti[i].medie - vector_studenti[j].medie) > eroare) 
            {
                if (vector_studenti[i].medie < vector_studenti[j].medie) 
                {
                    Student aux = vector_studenti[i];
                    vector_studenti[i] = vector_studenti[j];
                    vector_studenti[j] = aux;
                }
            }
            else if (vector_studenti[i].nume > vector_studenti[j].nume)
                {
                    Student aux = vector_studenti[i];
                    vector_studenti[i] = vector_studenti[j];
                    vector_studenti[j] = aux;
                }
            else if (vector_studenti[i].nume == vector_studenti[j].nume && vector_studenti[i].varsta > vector_studenti[j].varsta) 
                {
                    Student aux = vector_studenti[i];
                    vector_studenti[i] = vector_studenti[j];
                    vector_studenti[j] = aux;
                }
        }
    }
}

void Catalog::scriere(const std::string& fis_iesire) const {
    std::ofstream out(fis_iesire.c_str());
    if (!out.is_open()) {
        std::cout << "Eroare la deschiderea fisierului de iesire\n";
        return;
    }

    int latime_nume = 20; 
    int latime_varsta = 6;
    int latime_medie = 5;

    out << "+----------------------+--------+-------+\n";

    out << "| Nume";
    for (int i = 4; i < latime_nume; i++)
        out << ' ';
    out << " | Varsta";
    for (int i = 6; i < latime_varsta; i++) 
        out << ' ';
    out << " | Medie";
    for (int i = 5; i < latime_medie; i++) 
        out << ' ';
    out << " |\n";

    out << "+----------------------+--------+-------+\n";

    int lim = (K < N ? K : N);
    for (int i = 0; i < lim; i++) {
        const Student& s = vector_studenti[i];

        // coloana NUME
        out << "| ";
        std::string nume = s.nume;
        if ((int)nume.size() > latime_nume) nume = nume.substr(0, latime_nume);
        out << nume;
        for (int sp = (int)nume.size(); sp < latime_nume; sp++) out << ' ';
        out << " | ";

        // coloana VARSTA
        out << s.varsta;
        int v = s.varsta, cifre = 0;
        if (v == 0) cifre = 1;
        else while (v > 0) { v /= 10; cifre++; }
        for (int sp = cifre; sp < latime_varsta; sp++) out << ' ';
        out << " | ";

        // coloana MEDIE (exact 2 zecimale, padding fix)
        double m = s.medie;
        long long c = (long long)floor(m * 100.0 + 0.5);
        int parte_int = (int)(c / 100);
        int parte_dec = (int)(c % 100);

        char medie_str[8];
        if (parte_int < 10)
            sprintf(medie_str, " %.2f", m); // spatiu initial pt aliniere
        else
            sprintf(medie_str, "%.2f", m);

        // luam doar primele 5 caractere din rezultat (ex: " 9.50" / "10.00")
        for (int j = 0; j < 5 && medie_str[j] != '\0'; j++)
            out << medie_str[j];

        out << " |\n";
    }

    // linia de jos
    out << "+----------------------+--------+-------+\n";

    out.close();
}

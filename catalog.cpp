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
    double eroare = 1e-5; 
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

void Catalog::scriere(const std::string& fis_iesire) const{
    std::ofstream out(fis_iesire.c_str());
    if (!out.is_open()) {
        std::cout << "Eroare la deschiderea fisierului de iesire\n";
        return;
    }

    const int WN = 20; // latime Nume
    const int WV = 6;  // latime Varsta
    const int WM = 5;  // latime Medie

    // functie locala pentru separator
    auto linie = [&](void) {
        out << '+';
        for (int i = 0; i < WN + 2; i++) out << '-';
        out << '+';
        for (int i = 0; i < WV + 2; i++) out << '-';
        out << '+';
        for (int i = 0; i < WM + 2; i++) out << '-';
        out << "+\n";
    };

    // --- antet ---
    linie();
    out << "| Nume";
    for (int i = 4; i < WN; i++) out << ' ';
    out << " | Varsta";
    for (int i = 6; i < WV; i++) out << ' ';
    out << " | Medie";
    for (int i = 5; i < WM; i++) out << ' ';
    out << " |\n";
    linie();

    // --- randurile studentilor ---
    int lim = (K < N ? K : N);
    for (int i = 0; i < lim; i++) {
        const Student& s = vector_studenti[i];

        // | Nume
        out << "| ";
        std::string nume = s.nume;
        if ((int)nume.size() > WN) nume = nume.substr(0, WN);
        out << nume;
        for (int sp = (int)nume.size(); sp < WN; sp++) out << ' ';
        out << " | ";

        // Varsta
        int varsta = s.varsta;
        char varsta_str[10];
        int len = 0, x = varsta;
        if (x == 0) varsta_str[len++] = '0';
        else {
            char rev[10]; int r = 0;
            while (x > 0) { rev[r++] = '0' + (x % 10); x /= 10; }
            for (int j = r - 1; j >= 0; j--) varsta_str[len++] = rev[j];
        }
        varsta_str[len] = '\0';
        out << varsta_str;
        for (int sp = len; sp < WV; sp++) out << ' ';
        out << " | ";

        // Medie (2 zecimale)
        double medie = s.medie;
        long long c = (long long)floor(medie * 100.0 + 0.5);
        int intp = (int)(c / 100);
        int dec = (int)(c % 100);
        char medie_str[10];
        if (dec < 10)
            sprintf(medie_str, "%d.0%d", intp, dec);
        else
            sprintf(medie_str, "%d.%d", intp, dec);

        out << medie_str;
        int lenm = 0; while (medie_str[lenm] != '\0') lenm++;
        for (int sp = lenm; sp < WM; sp++) out << ' ';
        out << " |\n";
    }

    linie();
    out.close();
}

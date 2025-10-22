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
    if (n < 1 || n > 1500 || k < 0 || k > n) {
        std::cout << "Parametrii nu respecta cerintele\n";
        N = 0;
        K = 0;
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
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            // rotunjim la 2 zecimale ca la afișare
            int mi = (int)floor(vector_studenti[i].medie * 100.0 + 0.5);
            int mj = (int)floor(vector_studenti[j].medie * 100.0 + 0.5);

            bool trebuie_swap = false;

            // 1) medie rotunjită descrescător
            if (mi != mj) {
                if (mi < mj) trebuie_swap = true;
            }
            // 2) la egalitate, după nume (A -> Z)
            else if (vector_studenti[i].nume > vector_studenti[j].nume) {
                trebuie_swap = true;
            }
            // 3) la egalitate și de nume, după vârstă (crescător)
            else if (vector_studenti[i].nume == vector_studenti[j].nume &&
                     vector_studenti[i].varsta > vector_studenti[j].varsta) {
                trebuie_swap = true;
            }

            if (trebuie_swap) {
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

    if (K == 0 || N == 0) {
        out << "+----------------------+--------+-------+\n";
        out << "| Nume                 | Varsta | Medie |\n";
        out << "+----------------------+--------+-------+\n";
        out.close();
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

    int limita; //in cazul in care as vrea sa afisez mai multi studenti decat sunt in catalog
    if (K < N)
        limita = K;
    else
        limita = N;
    for (int i = 0; i < limita; i++) {
        const Student& s = vector_studenti[i];

        // coloana NUME
        out << "| ";
        std::string nume = s.nume;
        out << nume;
        for (int spatii = (int)nume.size(); spatii < latime_nume; spatii++) //pun spatii pana la latimea fixa
            out << ' ';
        out << " | ";

        // coloana VARSTA
        out << s.varsta;
        int v = s.varsta, cifre = 0;
        if (v == 0) 
            cifre = 1;
        while (v > 0) { 
            v = v / 10; 
            cifre++; 
        }
        for (int spatii = cifre; spatii < latime_varsta; spatii++) 
            out << ' ';
        out << " | ";

        // coloana MEDIE (exact 2 zecimale, padding fix)
        // coloana MEDIE (exact 2 zecimale, aliniata la stanga)
        double med = s.medie;

        // rotunjim corect la 2 zecimale
        int a = (int)floor(med * 100.0 + 0.5);
        int parte_intreaga = a / 100;
        int parte_fractionara = a % 100;

        // afisam manual cu 2 zecimale (ex: 9.50, 10.00)
        char media[8];
        sprintf(media, "%d.%02d", parte_intreaga, parte_fractionara);

        // afisam caracterele din string
        out << media;

        // numaram cate caractere am scris (4 sau 5)
        int len = 0;
        while (media[len] != '\0') 
            len++;

        // completam cu spatii pana la latimea coloanei (ex: 5)
        for (int spatii = len; spatii < latime_medie; spatii++)
            out << ' ';

        // incheiem coloana
        out << " |\n";

    }
    // linia de jos
    out << "+----------------------+--------+-------+\n";
    out.close();
}

//
// Created by auma4493 on 2018-02-20.
//

#include "../headers/KolegosFaile.h"
#include "../headers/Skaiciavimai.h"

using std::cout;
using std::exception;

void Nuskaitymas(vector<Kolega> &kolegos) {
    double *p = new double[5], egzam;
    vector<double> darbai{};
    string v, pa;
    Kolega k{};
    ifstream fd;

    try {
        fd.open("kursiokai.txt", std::ios::in);
        if (!fd.good()) throw "Error opening file";
    } catch (string e){
        cout << e << endl;
        return;
    }catch (char const* e){
        cout << "Duomenu failas neegzistuoja" << endl;
        return;
    }


    while (fd >> pa >> v >> p[0] >> p[1] >> p[2] >> p[3] >> p[4] >> egzam) {
        k.vardas = v;
        k.pavard = pa;
        for (int i = 0; i < 5; i++) darbai.push_back(p[i]);
        k.nDarbai = darbai;
        darbai.clear();
        k.egzam = egzam;
        kolegos.push_back(k);
    }
}

bool KolegosCompare(Kolega lhs, Kolega rhs) {
    if (lhs.pavard <= rhs.pavard) {
        if (lhs.pavard == rhs.pavard) {
            if (lhs.vardas < rhs.vardas) return true;
            else return false;
        } else return true;
    } else return false;
}

void Rasymas(vector<Kolega> &kolegos) {
    if(kolegos.size() > 0) {
        sort(kolegos.begin(), kolegos.end(), KolegosCompare);
        auto dv = kolegos[0].vardas.length(), dp = kolegos[0].pavard.length();
        for (int i = 0; i < kolegos.size(); i++) {
            if (kolegos[i].vardas.length() > dv) dv = kolegos[i].vardas.length();
            if (kolegos[i].pavard.length() > dp) dp = kolegos[i].pavard.length();
        }
        if (dv < 6) dv = 6;
        if (dp < 7) dp = 7;

        ofstream fr;

        try {
            fr.open("output.txt", std::ios::out);
            if (!fr.good()) throw "Error opening file";
        } catch (string e){
            cout << e << endl;
            return;
        }

        fr << std::left << std::setw(dp + 5) << "Pavardė" << std::setw(dv + 4) << "Vardas"
           << std::setw(18 + 4) << "Galutinis-vidurkis" << std::setw(17 + 4) << "Galutinis-mediana" << endl;
        for (auto k : kolegos) {
            k.galBalasM = PagalMediana(k.egzam, k.nDarbai);
            k.galBalasV = PagalVidurki(k.egzam, k.nDarbai);
            fr << std::left << std::setw(dp + 4) << k.pavard << std::setw(dv + 4) << k.vardas
               << std::setprecision(2) << std::fixed << std::setw(18 + 4)
               << k.galBalasV << std::setw(17 + 3) << k.galBalasM << endl;
        }
    } else{
        ofstream fr("output.txt");
        fr << std::left << std::setw(7 + 5) << "Pavardė" << std::setw(6 + 4) << "Vardas"
           << std::setw(18 + 4) << "Galutinis-vidurkis" << std::setw(17 + 4) << "Galutinis-mediana" << endl;
    }
}


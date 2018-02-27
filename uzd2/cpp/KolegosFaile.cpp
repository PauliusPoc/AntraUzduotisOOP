//
// Created by auma4493 on 2018-02-20.
//

#include "../headers/KolegosFaile.h"
#include "../headers/Skaiciavimai.h"

using std::cout;
using std::exception;

const int kiekVietos = 18;
const int vienasTabas = 4;

void Nuskaitymas(vector<Kolega> &kolegos, string s) {
    double *p = new double[5], egzam;
    vector<double> darbai{};
    string v, pa;
    Kolega k{};
    ifstream fd;

    try {
        fd.open( s, std::ios::in);
        if (!fd.good()) throw "Error opening file";
    } catch (string &e){
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
    return lhs.pavard <= rhs.pavard && (!(lhs.pavard == rhs.pavard) || lhs.vardas < rhs.vardas);
}

void Rasymas(vector<Kolega> &kolegos) {
    if(!kolegos.empty()) {
        sort(kolegos.begin(), kolegos.end(), KolegosCompare);
        auto dv = kolegos[0].vardas.length(), dp = kolegos[0].pavard.length();
        for (auto &kolego : kolegos) {
            if (kolego.vardas.length() > dv) dv = kolego.vardas.length();
            if (kolego.pavard.length() > dp) dp = kolego.pavard.length();
        }
        if (dv < 6) dv = 6;
        if (dp < 7) dp = 7;

        ofstream fr;

        try {
            fr.open("output.txt", std::ios::out);
            if (!fr.good()) throw "Error opening file";
        } catch (string &e){
            cout << e << endl;
            return;
        }

        fr << std::left << std::setw(dp + vienasTabas + 1) << "Pavardė" << std::setw(dv + vienasTabas) << "Vardas"
           << std::setw(kiekVietos + vienasTabas) << "Galutinis-vidurkis" << std::setw(kiekVietos + vienasTabas) << "Galutinis-mediana" << endl;
        for (auto k : kolegos) {
            k.galBalasM = PagalMediana(k.egzam, k.nDarbai);
            k.galBalasV = PagalVidurki(k.egzam, k.nDarbai);
            k.printKolega(dv,dp,fr);
        }
    } else{
        ofstream fr("output.txt");
        fr << std::left << std::setw(7 + vienasTabas) << "Pavardė" << std::setw(6 + vienasTabas) << "Vardas" // 7 tai "Pavardė ilgis" , 6 tai "Vardas" ilgis
           << std::setw(kiekVietos + vienasTabas) << "Galutinis-vidurkis" << std::setw(kiekVietos + vienasTabas) << "Galutinis-mediana" << endl;
    }
}




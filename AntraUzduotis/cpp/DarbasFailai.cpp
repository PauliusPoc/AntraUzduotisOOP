//
// Created by augus on 18/04/15.
//

#include <utility>
#include "../headers/DarbasFailai.h"

bool KolegosCompare(Studentas lhs, Studentas rhs) {
    return  lhs.compare(std::move(rhs));
}

void Nuskaitymas(vector<Studentas> &kolegos, string s) {

    Studentas k;
    std::ifstream fd;

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

    while (fd >> k) {
        kolegos.push_back(k);
    }
}
void Nuskaitymas(std::list<Studentas> &kolegos, string s){
    Studentas k;
    std::ifstream fd;

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

    while (fd >> k) {
        kolegos.push_back(k);
    }
}
void Nuskaitymas(std::deque<Studentas> &kolegos, string s){
    Studentas k;
    std::ifstream fd;

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

    while (fd >> k) {
        kolegos.push_back(k);
    }
}
void Rasymas(vector<Studentas> &kolegos) {

    const int kiekVietos = 18;
    const int vienasTabas = 4;

    if(!kolegos.empty()) {
        std::sort(kolegos.begin(), kolegos.end(), KolegosCompare);
        auto dv = kolegos[0].vardas().length(), dp = kolegos[0].pavarde().length();
        for (Studentas &kolego : kolegos) {
            if (kolego.vardas().length() > dv) dv = kolego.vardas().length();
            if (kolego.pavarde().length() > dp) dp = kolego.pavarde().length();
        }
        if (dv < 6) dv = 6;
        if (dp < 7) dp = 7;

        std::ofstream fr;
        try {
            fr.open("output.txt", std::ios::out);
            if (!fr.good()) throw "Error opening file";
        } catch (string &e){
            cout << e << endl;
            return;
        }

        fr << std::left << std::setw(dp + vienasTabas + 1) << "Pavardė" << std::setw(dv + vienasTabas) << "Vardas"
           << std::setw(kiekVietos + vienasTabas) << "Galutinis-vidurkis" << std::setw(kiekVietos + vienasTabas) << "Galutinis-mediana" << endl;
        for (Studentas k : kolegos) {
            k.print(dv,dp,fr);
        }
    } else{
        std::ofstream fr("output.txt");
        fr << std::left << std::setw(7 + vienasTabas) << "Pavardė" << std::setw(6 + vienasTabas) << "Vardas" // 7 tai "Pavardė ilgis" , 6 tai "Vardas" ilgis
           << std::setw(kiekVietos + vienasTabas) << "Galutinis-vidurkis" << std::setw(kiekVietos + vienasTabas) << "Galutinis-mediana" << endl;
    }
}


//
// Created by augus on 18/04/15.
//

#include "../headers/Performance.h"
#include "../headers/DarbasFailai.h"
#include "../headers/Timer.h"
#include "../StrongVector.h"

bool RibaV (Studentas& val) {
    return val.vidurkis() >= 5.0;
}
bool RibaM (Studentas& val) {
    return val.mediana() >= 5.0;
}

void StartTesting(const unsigned int nTestu) {
    c2:
    int metod{};
    if (cout << "Pasirinkite funkcija. 1 - skaiciuok pagal vidurki, 2 - skaiciuok pagal mediana: " && !(cin >> metod)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto c2;
    }
    if (metod != 1 && metod != 2) {
        cout << "Toks pasirinkimas negalimas" << endl;
        goto  c2;
    }

    cout << "|Duomenu kiekis                    |Duomenu nuskaitymas|Rusiavimas    |" << endl;
    cout << "|----------------------------------|-------------------|--------------|" << endl;
    for (unsigned int i = 1; i <= 5; i++){
        StartProfiling(i, static_cast<unsigned int>(metod));
    }
}

void GeneruokTestui(unsigned int n, std::ofstream &fk) {
    std::mt19937 mt(static_cast<long unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1, 10);

    for (unsigned int i = 1; i <= n; i++){
        fk << "Vardas" + std::to_string(i) << " Pavarde" + std::to_string(i);
        for (int j = 0; j < 6; j++){
            fk << " " <<  std::to_string(dist(mt));
        }
        fk << endl;
    }
}

void StartProfiling(unsigned int n, const unsigned int met) {
    StrongVector<Studentas> kolegos;

    auto dydis = (unsigned int)std::pow(10,n);
    kolegos.reserve(dydis);

    string fi = "perf" + std::to_string(dydis) + "_IN.txt";
    string fo = "perf" + std::to_string(dydis) + "_OUT.txt";

    std::ofstream frr (fi);
    GeneruokTestui(dydis,frr);
    std::ofstream fr (fo);

    cout << "| n = 10 ^ " + std::to_string(n) + " | ";

    Timer t;
    Nuskaitymas(kolegos, fi);
    cout << t.getTime() <<" s. | ";
    t.reset();
    StrongVector<Studentas> geek;
    ArKietas(kolegos,geek,met == 1);
    cout << t.getTime()<<" s. |"<<endl;
}

void ArKietas(StrongVector<Studentas> &koleg, StrongVector<Studentas> &geek, bool arVidurkiu) {
    auto fx = RibaV;
    if (!arVidurkiu) fx = RibaM;
    auto it = std::stable_partition(koleg.begin(),koleg.end(),fx);
    auto posID = std::distance(koleg.begin(), it);
    geek.assign(koleg.begin(), it);
    koleg.erase(koleg.begin(),it);
}

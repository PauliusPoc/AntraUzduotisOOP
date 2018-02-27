//
// Created by augus on 18/02/27.
//

#include "../headers/PerformanceProfiling.h"

using laikas = std::chrono::high_resolution_clock;
using ns = std::chrono::microseconds;
using std::chrono::time_point;

using std::uniform_int_distribution;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

void StartTesting(const unsigned int nTestu) {
    ofstream pr;
    try {
        pr.open("ProfilingResult.txt", std::ios_base::out);
        if (!pr.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        std::terminate();
    }

    c2:
    int metod{};
    if (cout << "Pasirinkite funkcija. 1 - skaiciuok pagal vidurki, 2 - skaiciuok pagal mediana: " && !(cin >> metod)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto c2;
    }

    for (unsigned int i = 1; i <= nTestu; i++)
        StartProfiling(i, pr, static_cast<unsigned int>(metod));
}
void StartProfiling(unsigned int n, ofstream &pr, const unsigned int met) {

    vector<Kolega> kolegos;
    auto dydis = (unsigned int)std::pow(10,n);
    kolegos.reserve(dydis);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";
    string fo = "perf" + std::__cxx11::to_string(dydis) + "_OUT.txt";

    ofstream fk;
    try {
        fk.open(fi, std::ios_base::out);
        if (!fk.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        std::terminate();
    }

    pr << "------------------------------------------------------------------------------------" << endl;
    pr << "Dirbame su " + std::to_string(dydis) + " įrašų" << endl;

    time_point start = laikas::now();
    GeneruokTestui(dydis, fk);
    time_point end = laikas::now();
    std::chrono::duration<double> diff = end - start;
    pr <<"Generavimas užtruko  "<< (diff).count()<<" s."<<endl;

    start = laikas::now();
    Nuskaitymas(kolegos, fi);
    end = laikas::now();
    diff = end - start;
    pr <<"Nuskaitymas užtruko  "<< (diff).count()<<" s."<<endl;

    start = laikas::now();
    ArKietas(kolegos, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko  "<< (diff).count()<<" s."<<endl;

    start = laikas::now();
    IsrasykTesta(kolegos, fo);
    end = laikas::now();
    diff = end - start;
    pr <<"Išrašymas užtruko  "<<  (diff).count()<<" s."<<endl;

    pr << "------------------------------------------------------------------------------------" << endl;

}
void IsrasykTesta(const vector<Kolega> &kolegos, const string &fo) {
    ofstream fr;

    try {
        fr.open(fo, std::ios_base::out);
        if (!fr.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        return;
    }

    fr << "Vargšiukai: " << endl;
    for (auto k : kolegos) {
        if (!k.arKietas) fr << k.vardas << " " << k.pavard << endl;
    }

    fr << "Galvočiai: " << endl;
    for (auto k : kolegos) {
        if (k.arKietas) fr << k.vardas << " " << k.pavard <<  endl;
    }
}
void GeneruokTestui(unsigned int n, ofstream &fk) {
    mt19937 mt(static_cast<long unsigned int>(std::chrono::_V2::system_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1, 10);

    for (unsigned int i = 1; i <= n; i++){
        fk << "Vardas" + std::__cxx11::to_string(i) << " Pavarde" + std::__cxx11::to_string(i);
        for (int j = 0; j < 6; j++){
            fk << " " <<  std::__cxx11::to_string(dist(mt));
        }
        fk << endl;
    }
}
void ArKietas(vector<Kolega> &koleg, bool arVidurkiu) {

    for (auto &k : koleg){
        if (arVidurkiu){
            double suma{};
            for (auto paz : k.nDarbai)
                suma += paz;
            k.arKietas = suma / k.nDarbai.size() >= 6.0;
        } else{
            double med{};
            sort(k.nDarbai.begin(), k.nDarbai.end());
            med = k.nDarbai.size() % 2 == 0 ? (k.nDarbai[k.nDarbai.size() / 2] + k.nDarbai[k.nDarbai.size() / 2 - 1]) / 2
                                            : k.nDarbai[k.nDarbai.size() / 2];

            k.arKietas = med >= 6;
        }
    }
}

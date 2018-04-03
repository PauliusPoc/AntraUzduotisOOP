//
// Created by augus on 18/02/27.
//

#include "../headers/PerformanceProfiling.h"
#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>

using laikas = std::chrono::high_resolution_clock;
using ns = std::chrono::microseconds;
using std::chrono::time_point;

using std::uniform_int_distribution;
using std::mt19937;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::cout;

bool RibaV (Kolega& val) {
    return val.galBalasV >= 6.0;
}
bool RibaM (Kolega& val) {
    return val.galBalasM >= 6.0;
}

void StartTesting(const unsigned int nTestu) {
    ofstream pr, prL, prD;
    try {
        pr.open("ProfilingResultVector.txt", std::ios_base::out);
        if (!pr.good()) throw "Error opening file"; // NOLINT
    } catch (string &e){
        cout << e << endl;
        std::terminate();
    }
    try {
        prL.open("ProfilingResultList.txt", std::ios_base::out);
        if (!prL.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        std::terminate();
    }
    try {
        prD.open("ProfilingResultDeque.txt", std::ios_base::out);
        if (!prD.good()) throw "Error opening file";
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
    if (metod != 1 && metod != 2) {
        cout << "Toks pasirinkimas negalimas" << endl;
        goto  c2;
    }

    for (unsigned int i = 1; i <= nTestu; i++){
        StartProfiling(i, pr, static_cast<unsigned int>(metod));
        StartProfilingL(i,prL,static_cast<unsigned int>(metod));
        StartProfilingD(i,prD,static_cast<unsigned int>(metod));
    }
}

void GeneruokTestui(unsigned int n, ofstream &fk) {
    std::mt19937 mt(static_cast<long unsigned int>(std::chrono::_V2::system_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1, 10);

    for (unsigned int i = 1; i <= n; i++){
        fk << "Vardas" + std::__cxx11::to_string(i) << " Pavarde" + std::__cxx11::to_string(i);
        for (int j = 0; j < 6; j++){
            fk << " " <<  std::__cxx11::to_string(dist(mt));
        }
        fk << endl;
    }
}

void StartProfiling(unsigned int n, ofstream &pr, const unsigned int met) {

    vector<Kolega> kolegos{}, geek{}, los{};

    auto dydis = (unsigned int)std::pow(10,n);
    kolegos.reserve(dydis);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    pr << "------------------------------------------------------------------------------------" << endl;
    pr << "Dirbame su " + std::to_string(dydis) + " įrašų" << endl;

    ofstream fr(fi);
    GeneruokTestui(dydis, fr);
    auto start = laikas::now();
    Nuskaitymas(kolegos, fi);
    auto end = laikas::now();
    std::chrono::duration<double> diff = end - start;
    auto grandTotal = diff;
    pr <<"Nuskaitymas užtruko  "<< (diff).count()<<" s."<<endl;
    /*
    start = laikas::now();
    ArKietas(kolegos,geek,los, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;
    */
    start = laikas::now();
    ArKietas(kolegos,geek, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko (ištrinant)  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;
    pr <<"Iš viso:  "<< (grandTotal).count()<<" s."<<endl;


    pr << "------------------------------------------------------------------------------------" << endl;

}

template<typename T>
void ArKietas(T &koleg, T &geek, T &lose, bool arVidurkiu) {
    for (auto &k : koleg){
        if (arVidurkiu){
            double suma{};
            for (auto paz : k.nDarbai)
                suma += paz;
            if(suma / k.nDarbai.size() >= 6.0) geek.push_back(k);
            else lose.push_back(k);
        } else{
            double med{};
            std::sort(k.nDarbai.begin(), k.nDarbai.end());
            med = k.nDarbai.size() % 2 == 0 ? (k.nDarbai[k.nDarbai.size() / 2] + k.nDarbai[k.nDarbai.size() / 2 - 1]) / 2
                                            : k.nDarbai[k.nDarbai.size() / 2];

            if(med >= 6) geek.push_back(k);
            else lose.push_back(k);
        }
    }
}

void StartProfilingL(unsigned int n, ofstream &pr, const unsigned int met) {

    list<Kolega> kolegos, geek, los;
    auto dydis = (unsigned int)std::pow(10,n);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    pr << "------------------------------------------------------------------------------------" << endl;
    pr << "Dirbame su " + std::to_string(dydis) + " įrašų" << endl;

    auto start = laikas::now();
    Nuskaitymas(kolegos, fi);
    auto end = laikas::now();
    std::chrono::duration<double> diff = end - start;
    auto grandTotal = diff;
    pr <<"Nuskaitymas užtruko  "<< (diff).count()<<" s."<<endl;

    /*
    start = laikas::now();
    ArKietas(kolegos,geek,los, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;
    */
    start = laikas::now();
    ArKietas(kolegos,geek, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko (ištrinant)  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;

    pr <<"Iš viso:  "<< (grandTotal).count()<<" s."<<endl;


    pr << "------------------------------------------------------------------------------------" << endl;

}

void StartProfilingD(unsigned int n, ofstream &pr, const unsigned int met) {

    deque<Kolega> kolegos, geek, los;
    auto dydis = (unsigned int)std::pow(10,n);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    pr << "------------------------------------------------------------------------------------" << endl;
    pr << "Dirbame su " + std::to_string(dydis) + " įrašų" << endl;

    auto start = laikas::now();
    Nuskaitymas(kolegos, fi);
    auto end = laikas::now();
    std::chrono::duration<double> diff = end - start;
    auto grandTotal = diff;
    pr <<"Nuskaitymas užtruko  "<< (diff).count()<<" s."<<endl;

    /*
    start = laikas::now();
    ArKietas(kolegos,geek,los, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;
    */
    start = laikas::now();
    ArKietas(kolegos,geek, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko (ištrinant)  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;

    pr <<"Iš viso:  "<< (grandTotal).count()<<" s."<<endl;


    pr << "------------------------------------------------------------------------------------" << endl;

}

template<typename T>
void ArKietas(T &koleg, T &geek, bool arVidurkiu) {

    for (auto &k : koleg){
        if (arVidurkiu){
            double suma{};
            suma = std::accumulate(k.nDarbai.begin(), k.nDarbai.end(), 0.0);
            k.galBalasV = suma / k.nDarbai.size();
            if (k.galBalasV >= 6) geek.push_back(k);
        } else {
            std::sort(k.nDarbai.begin(), k.nDarbai.end());
            k.galBalasM = k.nDarbai.size() % 2 == 0 ? (k.nDarbai[k.nDarbai.size() / 2] + k.nDarbai[k.nDarbai.size() / 2 - 1]) / 2
                                             : k.nDarbai[k.nDarbai.size() / 2];
            if (k.galBalasM >= 6) geek.push_back(k);
        }
    }
    if (arVidurkiu) koleg.erase(std::remove_if(koleg.begin(), koleg.end(), RibaV), koleg.end());
    else koleg.erase(std::remove_if(koleg.begin(), koleg.end(), RibaM), koleg.end());
}


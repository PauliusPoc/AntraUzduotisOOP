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
    ofstream pr, prL, prD;
    try {
        pr.open("ProfilingResultVector.txt", std::ios_base::out);
        if (!pr.good()) throw "Error opening file";
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

void StartProfiling(unsigned int n, ofstream &pr, const unsigned int met) {

    vector<Kolega> kolegos, geek, los;
    auto dydis = (unsigned int)std::pow(10,n);
    kolegos.reserve(dydis);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    pr << "------------------------------------------------------------------------------------" << endl;
    pr << "Dirbame su " + std::to_string(dydis) + " įrašų" << endl;

    auto start = laikas::now();
    Nuskaitymas(kolegos, fi);
    auto end = laikas::now();
    std::chrono::duration<double> diff = end - start;
    auto grandTotal = diff;
    pr <<"Nuskaitymas užtruko  "<< (diff).count()<<" s."<<endl;

    start = laikas::now();
    ArKietas(kolegos,geek,los, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;

    pr <<"Iš viso:  "<< (grandTotal).count()<<" s."<<endl;


    pr << "------------------------------------------------------------------------------------" << endl;

}
void ArKietas(vector<Kolega> &koleg, vector<Kolega> &geek, vector<Kolega> &lose, bool arVidurkiu) {

    for (auto &k : koleg){
        if (arVidurkiu){
            double suma{};
            for (auto paz : k.nDarbai)
                suma += paz;
            if(suma / k.nDarbai.size() >= 6.0) geek.push_back(k);
            else lose.push_back(k);
        } else{
            double med{};
            sort(k.nDarbai.begin(), k.nDarbai.end());
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

    start = laikas::now();
    ArKietas(kolegos,geek,los, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;

    pr <<"Iš viso:  "<< (grandTotal).count()<<" s."<<endl;


    pr << "------------------------------------------------------------------------------------" << endl;

}
void ArKietas(list<Kolega> &koleg, list<Kolega> &geek, list<Kolega> &lose, bool arVidurkiu) {

    for (auto &k : koleg){
        if (arVidurkiu){
            double suma{};
            for (auto paz : k.nDarbai)
                suma += paz;
            if(suma / k.nDarbai.size() >= 6.0) geek.push_back(k);
            else lose.push_back(k);
        } else{
            double med{};
            sort(k.nDarbai.begin(), k.nDarbai.end());
            med = k.nDarbai.size() % 2 == 0 ? (k.nDarbai[k.nDarbai.size() / 2] + k.nDarbai[k.nDarbai.size() / 2 - 1]) / 2
                                            : k.nDarbai[k.nDarbai.size() / 2];

            if(med >= 6) geek.push_back(k);
            else lose.push_back(k);
        }
    }
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

    start = laikas::now();
    ArKietas(kolegos,geek,los, met == 1);
    end = laikas::now();
    diff = end - start;
    pr <<"Rūšiavimas užtruko  "<< (diff).count()<<" s."<<endl;
    grandTotal += diff;

    pr <<"Iš viso:  "<< (grandTotal).count()<<" s."<<endl;


    pr << "------------------------------------------------------------------------------------" << endl;

}
void ArKietas(deque<Kolega> &koleg, deque<Kolega> &geek, deque<Kolega> &lose, bool arVidurkiu) {

    for (auto &k : koleg){
        if (arVidurkiu){
            double suma{};
            for (auto paz : k.nDarbai)
                suma += paz;
            if(suma / k.nDarbai.size() >= 6.0) geek.push_back(k);
            else lose.push_back(k);
        } else{
            double med{};
            sort(k.nDarbai.begin(), k.nDarbai.end());
            med = k.nDarbai.size() % 2 == 0 ? (k.nDarbai[k.nDarbai.size() / 2] + k.nDarbai[k.nDarbai.size() / 2 - 1]) / 2
                                            : k.nDarbai[k.nDarbai.size() / 2];

            if(med >= 6) geek.push_back(k);
            else lose.push_back(k);
        }
    }
}

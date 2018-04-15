//
// Created by augus on 18/04/15.
//

#include "../headers/Performance.h"
#include "../headers/DarbasFailai.h"

bool RibaV (Studentas& val) {
    return val.galBalas(true) >= 6.0;
}
bool RibaM (Studentas& val) {
    return val.galBalas(false) >= 6.0;
}

void StartTesting(const unsigned int nTestu) {
    std::ofstream pr, prL, prD;
    try {
        pr.open("ProfilingResultVector.txt", std::ios_base::out);
        if (!pr.good()) throw "Error opening file"; // NOLINT
    } catch (string &e){
        cout << e << endl;
        //std::terminate();
    }
    try {
        prL.open("ProfilingResultList.txt", std::ios_base::out);
        if (!prL.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        //std::terminate();
    }
    try {
        prD.open("ProfilingResultDeque.txt", std::ios_base::out);
        if (!prD.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        //std::terminate();
    }

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

    for (unsigned int i = 1; i <= nTestu; i++){
        StartProfiling(i, pr, static_cast<unsigned int>(metod));
        StartProfilingL(i,prL,static_cast<unsigned int>(metod));
        StartProfilingD(i,prD,static_cast<unsigned int>(metod));
    }
}

void GeneruokTestui(unsigned int n, std::ofstream &fk) {
    std::mt19937 mt(static_cast<long unsigned int>(std::chrono::_V2::system_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1, 10);

    for (unsigned int i = 1; i <= n; i++){
        fk << "Vardas" + std::to_string(i) << " Pavarde" + std::to_string(i);
        for (int j = 0; j < 6; j++){
            fk << " " <<  std::to_string(dist(mt));
        }
        fk << endl;
    }
}

void StartProfiling(unsigned int n, std::ofstream &pr, const unsigned int met) {

    vector<Studentas> kolegos, geek;

    auto dydis = (unsigned int)std::pow(10,n);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    kolegos.reserve(dydis);

    pr << "------------------------------------------------------------------------------------" << endl;
    pr << "Dirbame su " + std::to_string(dydis) + " įrašų" << endl;

    std::ofstream fr(fi);
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
void StartProfilingL(unsigned int n, std::ofstream &pr, const unsigned int met) {

    std::list<Studentas> kolegos, geek, los;
    auto dydis = (unsigned int)std::pow(10,n);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    kolegos.resize(dydis);

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
void StartProfilingD(unsigned int n, std::ofstream &pr, const unsigned int met) {

    std::deque<Studentas> kolegos, geek, los;
    auto dydis = (unsigned int)std::pow(10,n);
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    kolegos.resize(dydis);

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
void ArKietas(T &koleg, T &geek, T &lose, bool arVidurkiu) {
    for (Studentas &k : koleg){
            if(k.galBalas(arVidurkiu) >= 6.0) geek.push_back(k);
            else lose.push_back(k);
    }
}

template<typename T>
void ArKietas(T &koleg, T &geek, bool arVidurkiu) {
    for (Studentas &k : koleg) if(k.galBalas(arVidurkiu) >= 6.0) geek.push_back(k);
    if (arVidurkiu) koleg.erase(std::remove_if(koleg.begin(), koleg.end(), RibaV), koleg.end());
    else koleg.erase(std::remove_if(koleg.begin(), koleg.end(), RibaM), koleg.end());
}
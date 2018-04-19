//
// Created by augus on 18/04/15.
//

#include "../headers/Performance.h"
#include "../headers/DarbasFailai.h"

bool RibaV (Studentas& val) {
    return val.vidurkis() >= 6.0;
}
bool RibaM (Studentas& val) {
    return val.mediana() >= 6.0;
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
    kolegos.reserve(dydis);
    cout << dydis << endl;
    string fi = "perf" + std::__cxx11::to_string(dydis) + "_IN.txt";

    std::ofstream fr (fi);
    GeneruokTestui(dydis,fr);

    pr << "------------------------------------------------------------------------------------" << endl;
    pr << "Dirbame su " + std::to_string(dydis) + " įrašų" << endl;

    auto start = laikas::now();
    Nuskaitymas(kolegos, fi);
    auto end = laikas::now();
    std::chrono::duration<double> diff = end - start;
    auto grandTotal = diff;
    pr <<"Nuskaitymas užtruko  "<< (diff).count()<<" s."<<endl;
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
    auto fx = RibaV;
    if (!arVidurkiu) fx = RibaM;
    auto it = std::stable_partition(koleg.begin(),koleg.end(),fx);
    geek.resize(std::distance(koleg.begin(),it));
    std::copy(koleg.begin(),it,geek.begin());
    koleg.erase(it, koleg.end());
}
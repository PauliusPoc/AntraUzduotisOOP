//
// Created by auma4493 on 2018-02-20.
//

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>

using std::endl;
using std::string;
using std::vector;
using std::mt19937;
using std::uniform_real_distribution;
using std::ifstream;
using std::ofstream;

struct Kolega {
    string vardas{};
    string pavard{};
    vector<double> nDarbai{};
    double galBalasV{};
    double galBalasM{};
    double egzam{};
};

void Nuskaitymas(vector<Kolega> &kolegos) {
    double *p = new double[5], egzam;
    vector<double> darbai{};
    string v, pa;
    Kolega k{};
    ifstream fd("kursiokai.txt");

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


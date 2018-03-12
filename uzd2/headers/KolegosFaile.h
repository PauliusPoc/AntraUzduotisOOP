//
// Created by auma4493 on 2018-02-20.
//

#ifndef UZD2_KOLEGOSFAILE_H
#define UZD2_KOLEGOSFAILE_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <list>
#include <deque>

using std::list;
using std::deque;
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
    bool arKietas = true;

    void printKolega(unsigned int dv, unsigned int dp, ofstream &fr) {
        fr << std::left << std::setw(dp + 4) << pavard << std::setw(dv + 4) << vardas
           << std::setprecision(2) << std::fixed << std::setw(18 + 4)
           << galBalasV << std::setw(17 + 3) << galBalasM << endl;
    }
};

void Nuskaitymas(vector<Kolega> &kolegos, string s = "kursiokai.txt");
bool KolegosCompare(Kolega lhs, Kolega rhs);
void Rasymas(vector<Kolega> &kolegos);

void Nuskaitymas(list<Kolega> &kolegos, string s);
void Nuskaitymas(deque<Kolega> &kolegos, string s);

#endif //UZD2_KOLEGOSFAILE_H

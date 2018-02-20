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

void Nuskaitymas(vector<Kolega> &kolegos);
bool KolegosCompare(Kolega lhs, Kolega rhs);
void Rasymas(vector<Kolega> &kolegos);

#endif //UZD2_KOLEGOSFAILE_H

//
// Created by auma4493 on 2018-02-20.
//

#ifndef UZD2_KOLEGOSFAILE_H
#define UZD2_KOLEGOSFAILE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

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

#endif //UZD2_KOLEGOSFAILE_H

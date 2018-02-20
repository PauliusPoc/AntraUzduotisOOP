//
// Created by auma4493 on 2018-02-20.
//

#include "../headers/Skaiciavimai.h"

double PagalVidurki(double egzam, vector<double> &pazymiai) {

    double suma{};
    sort(pazymiai.begin(), pazymiai.end());
    for (auto paz : pazymiai) {
        suma += paz;
    }

    return 0.4 * suma / pazymiai.size() + 0.6 * egzam;

}

double PagalVidurki(double &egzam, double pazym[], int size) {
    double suma = 0;
    sort(pazym, pazym + size);
    for (int i = 0; i < size; i++) {
        suma += pazym[i];
    }

    return 0.4 * suma / size + 0.6 * egzam;
}

double PagalMediana(double egzam, vector<double> &pazymiai) {
    double med{};
    sort(pazymiai.begin(), pazymiai.end());
    med = pazymiai.size() % 2 == 0 ? (pazymiai[pazymiai.size() / 2] + pazymiai[pazymiai.size() / 2 - 1]) / 2
                                   : pazymiai[pazymiai.size() / 2];
    return 0.4 * med + 0.6 * egzam;
}

double PagalMediana(double &egzam, double pazym[], int size) {
    double med{};
    sort(pazym, pazym + size);
    med = size % 2 == 0 ? (pazym[size / 2] + pazym[size / 2 - 1]) / 2
                        : pazym[size / 2];
    return 0.4 * med + 0.6 * egzam;
}


//
// Created by augus on 18/04/15.
//

#ifndef ANTRAUZDUOTIS_STUDENTAS_H
#define ANTRAUZDUOTIS_STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

using std::string;
using std::vector;
using std::istream;
using std::endl;
using std::cout;

using std::mt19937;
using std::uniform_real_distribution;

class Studentas {
    private:
        string vardas_{};
        string pavard_{};
        vector<double> nDarbai_{};
        double egzam_{};
        void Auto(istream &fd);
        void ByHand(istream &fd);

    public:
        Studentas();

        string vardas() const { return vardas_; }
        string pavarde() const { return pavard_; }

        void print(unsigned int dv, unsigned int dp, std::ostream &fr);

        void readFromKonsole(istream &fd, const unsigned int choice);
        void printToKonsole(std::ostream &fr, const unsigned int metod);

        friend istream &operator>>( istream  &input, Studentas &S );
        bool compare(Studentas rhs);
        double galBalas(bool arVidurkis);
};


#endif //ANTRAUZDUOTIS_STUDENTAS_H

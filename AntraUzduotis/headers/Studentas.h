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
using std::ostream;
using std::endl;
using std::cout;

typedef double (*fun)();

class Studentas {
    private:
        string vardas_{};
        string pavard_{};
        vector<double> nDarbai_{};
        double egzam_{};
    public:
        Studentas() : egzam_(0){}

        inline string vardas() const { return vardas_; }
        inline string pavarde() const { return pavard_; }

        void print(unsigned int, unsigned int, std::ostream&);
        friend istream &operator>>( istream&, Studentas& );
        friend ostream &operator<<( ostream&, Studentas&);
        double vidurkis() const;
        double mediana();
        double galBalas(fun F);
};

bool compare(const Studentas&, const Studentas&);



#endif //ANTRAUZDUOTIS_STUDENTAS_H

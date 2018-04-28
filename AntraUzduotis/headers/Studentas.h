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

/// Studentus apibrėžianti klasė
class Studentas {
private:
    /// Studento vardas
    string vardas_{};
    /// Studnto pavardė
    string pavard_{};
    /// Studento namų darbų įverčiai
    vector<double> nDarbai_{};
    /// Studento gautas egzamino įvertinimas
    double egzam_;
public:
    /**
     * Sukonstruoja studento objektą
     */
    Studentas() : egzam_(0){}
    /**
     * Sukonstruoja Studento objektą iš duomenų įvesties stream'o.
     * @param input įvesties stream'as
     */
    explicit Studentas(istream& input);

    /**
     * Gražinamas studento vardas
     * @return Studento vardas
     */
    inline string vardas() const { return vardas_; }
    /**
     * Gražinama studento pavardė
     * @return Studento pavardė
     */
    inline string pavarde() const { return pavard_; }

    /**
     *  Studento informacijos išvedimas lygiuojant duomenis
     * @param dv Studento, kurio vardas ilgiausias, vardo ilgis
     * @param dp Studento, kurio pavardė ilgiausia, pavardės ilgis
     * @param fr išvesties stream'as
     */
    void print(unsigned int dv, unsigned int dp, std::ostream &fr);

    /**
     * Studento informacijos išvedimas
     * @return išvesties stream'as
    */
    friend ostream &operator<<(ostream&, Studentas&);
    /**
     * Pažiūrima ar studento vardas ir pavardė abeceliškai eina pirmiau nei kito
     * @return Ar studento vardas ir pavardė abeceliškai eina pirmiau nei kito
     */
    bool operator< (const Studentas& rhs);
    /**
     * Pažiūrima ar studento vardas ir pavardė abeceliškai eina vėliau nei kito
     * @return Ar studento vardas ir pavardė abeceliškai eina vėliau nei kito
     */
    bool operator> (const Studentas& rhs);
    /**
     * Pažiūrima ar studento vardas ir sutampa su kito Studento
     * @return Ar studento vardas ir sutampa su kito Studento
     */
    bool operator== (const Studentas& rhs);
    /**
     * Pažiūrima ar studento vardas ir nesutampa su kito Studento
     * @return Ar studento vardas ir nesutampa su kito Studento
     */
    bool operator!= (const Studentas& rhs);

    /**
    * Suskaičiuoja galutinį balą pagal vidurkį
    * @return galutinis balas
    */
    double vidurkis();
    /**
    * Suskaičiuoja galutinį balą pagal medianą
    * @return galutinis balas
    */
    double mediana();

};

#endif //ANTRAUZDUOTIS_STUDENTAS_H

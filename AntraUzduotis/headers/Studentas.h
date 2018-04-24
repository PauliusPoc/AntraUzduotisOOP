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

typedef double(*fun)();
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
     * Sukonsyruoja studento objektą
     */
    Studentas() : egzam_(0){}

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
    * Nuskaito studento informaciją iš įvesties stream'o
    * @return input stream'as
    */
    friend istream &operator>>( istream&, Studentas& );

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
    friend ostream &operator<<( ostream&, Studentas&);

    /**
    * Suskaičiuoja namų darbų įvertinimų vidurkį
    * @return namų darbų įvertinimų vidurkis
    */
    double vidurkis() const;

    /**
    * Suskaičiuoja namų darbų įvertinimų medianą
    * @return namų darbų įvertinimų mediana
    */
    double mediana();

    /**
     * Skaičiuojamas studento galutinis balas
     * @param F Funkcija pagal kurią skaičiuojame balą (vidurkis arba mediana)
     * @return Studento galutinis balas
     */
    double galBalas(fun F);

};
/**
 * Lygina du studentus pagal vardus ir pavardes abeceliškai
 * @return true, jei pirmo studento vardas ir pavarde yra pirmesni pagal abecele, false - jei ne
 */
bool comparePagalPav(Studentas& lhs, Studentas& rhs);

#endif //ANTRAUZDUOTIS_STUDENTAS_H

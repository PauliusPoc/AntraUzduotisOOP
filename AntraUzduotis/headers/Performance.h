//
// Created by augus on 18/04/15.
//

#ifndef ANTRAUZDUOTIS_PERFORMANCE_H
#define ANTRAUZDUOTIS_PERFORMANCE_H

#include "Studentas.h"
#include <fstream>
#include <list>
#include <deque>
#include <random>



using std::uniform_int_distribution;
using std::mt19937;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

/// Funkcija, tikrinanti ar studento gal. balas >= 5, pasitelkus vidurkį
bool RibaV (Studentas& val);
/// Funkcija, tikrinanti ar studento gal. balas >= 5, pasitelkus medianą
bool RibaM (Studentas& val);

/**
 * Funckciją nustatanti parametrus ir vykdanti profiliavimą
 * @param nTestu vykdomų testų skaičius
 */
void StartTesting(unsigned int nTestu);
/**
 * Funkcija, generuojanti atsitiktinius duomenis profiliavimui
 * @param n  generuojamų įrašų skaičius
 * @param fk išvesties strem'as
 */
void GeneruokTestui(unsigned int n, std::ofstream &fk);

/**
 * Profiliavimo funkciją
 * @param n 10 laipsnio rodiklis (kiek įrašų bus faile = 10 ^ n)
 * @param met  Profiliavimo metodo numeris (vidurkis ar mediana)
 */
void StartProfiling(unsigned int n, unsigned int met);

/**
 * Rūšiavimo funkcija
 * @tparam T Studentų konteinerio tipas
 * @param koleg Studentų konteineris
 * @param geek  gerų Studentų konteinerio
 * @param arVidurkiu Profiliavimo metodas(vidurkis(true) ar mediana(false))
 */
vector<Studentas> ArKietas(vector<Studentas> &koleg, bool arVidurkiu);

#endif //ANTRAUZDUOTIS_PERFORMANCE_H

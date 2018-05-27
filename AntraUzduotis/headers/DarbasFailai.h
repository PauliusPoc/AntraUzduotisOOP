//
// Created by augus on 18/04/15.
//

#ifndef ANTRAUZDUOTIS_DARBASFAILAI_H
#define ANTRAUZDUOTIS_DARBASFAILAI_H

#include "../headers/Studentas.h"
#include <fstream>
#include <list>
#include <deque>
#include "../StrongVector.h"

/**
 * Funkcija nuskaitanti Studentų duomenis iš failo
 * @param kolegos Studentų konteineris
 * @param s duomenų failo pavadinimas
 */
void Nuskaitymas(StrongVector<Studentas> &kolegos, string s);
/**
 * Funkcija išrašanti studentus
 * @param kolegos Studentų konteineris
 */
void Rasymas(StrongVector<Studentas> &kolegos);

#endif //ANTRAUZDUOTIS_DARBASFAILAI_H

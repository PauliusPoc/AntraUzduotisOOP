//
// Created by augus on 18/02/20.
//

#ifndef UZD2_DARBASKONSOLE_H
#define UZD2_DARBASKONSOLE_H


#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>

using std::sort;
using std::vector;
using std::mt19937;
using std::uniform_real_distribution;
using std::cout;
using std::cin;
using std::endl;
using std::string;

void Choices(double &choice, double &metod, double &masOrVector);
void MasyvasRasymas(const string &varpav,  double choice,  double metod, double egzam);
void VektoriusRasymas(const string &varpav, double choice, double metod, double egzam);

void Auto(double &egzam, vector<double> &pazym);

void ByHand(double &egzam, vector<double> &pazymiai);

void Auto(double &egzam, double *&pazym, int &size);

void ByHand(double &egzam, double *&pazym, int &size);

#endif //UZD2_DARBASKONSOLE_H

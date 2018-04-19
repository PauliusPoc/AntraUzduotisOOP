//
// Created by augus on 18/04/15.
//

#ifndef ANTRAUZDUOTIS_PERFORMANCE_H
#define ANTRAUZDUOTIS_PERFORMANCE_H

#include "Studentas.h"
#include <fstream>
#include <list>
#include <deque>

using laikas = std::chrono::high_resolution_clock;
using ns = std::chrono::microseconds;
using std::chrono::time_point;

using std::uniform_int_distribution;
using std::mt19937;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

bool RibaV (Studentas& val);
bool RibaM (Studentas& val);

void StartTesting(const unsigned int nTestu);

void GeneruokTestui(unsigned int n, std::ofstream &fk);

void StartProfiling(unsigned int n, const unsigned int met);

template<typename T>
void ArKietas(T &koleg, T &geek, T &lose, bool arVidurkiu);

template<typename T>
void ArKietas(T &koleg, T &geek, bool arVidurkiu);

#endif //ANTRAUZDUOTIS_PERFORMANCE_H

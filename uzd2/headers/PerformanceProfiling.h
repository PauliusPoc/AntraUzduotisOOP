//
// Created by augus on 18/02/27.
//

#ifndef UZD2_PERFORMANCEPROFILING_H
#define UZD2_PERFORMANCEPROFILING_H

#include "KolegosFaile.h"
#include <list>
#include <deque>

using std::list;
using std::deque;


template<typename T>
void ArKietas(T &koleg, T &geek, T &lose, bool arVidurkiu);

void StartProfiling(unsigned int n, ofstream &pr, unsigned int met);
void GeneruokTestui(unsigned int n, ofstream &fk);

void StartTesting(const unsigned int nTestu);
void StartProfilingL(unsigned int n, ofstream &pr, const unsigned int met);
void StartProfilingD(unsigned int n, ofstream &pr, const unsigned int met);

template<typename T>
void ArKietas(T &koleg, T &geek, bool arVidurkiu);

#endif //UZD2_PERFORMANCEPROFILING_H

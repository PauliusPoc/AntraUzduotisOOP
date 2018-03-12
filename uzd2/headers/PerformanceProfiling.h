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


void ArKietas(vector<Kolega> &koleg, vector<Kolega> &geek, vector<Kolega> &lose, bool arVidurkiu);
void StartProfiling(unsigned int n, ofstream &pr, unsigned int met);
void GeneruokTestui(unsigned int n, ofstream &fk);
void StartTesting(const unsigned int nTestu);

void StartProfilingL(unsigned int n, ofstream &pr, const unsigned int met);
void ArKietas(list<Kolega> &koleg, list<Kolega> &geek, list<Kolega> &lose, bool arVidurkiu);

void StartProfilingD(unsigned int n, ofstream &pr, const unsigned int met);
void ArKietas(deque<Kolega> &koleg, deque<Kolega> &geek, deque<Kolega> &lose, bool arVidurkiu);

#endif //UZD2_PERFORMANCEPROFILING_H

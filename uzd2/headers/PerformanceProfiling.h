//
// Created by augus on 18/02/27.
//

#ifndef UZD2_PERFORMANCEPROFILING_H
#define UZD2_PERFORMANCEPROFILING_H

#include "KolegosFaile.h"

void ArKietas(vector<Kolega> &koleg, bool arVidurkiu);
void StartProfiling(unsigned int n, ofstream &pr, unsigned int met);
void GeneruokTestui(unsigned int n, ofstream &fk);
void IsrasykTesta(const vector<Kolega> &kolegos, const string &fo);
void StartTesting(const unsigned int nTestu);

#endif //UZD2_PERFORMANCEPROFILING_H

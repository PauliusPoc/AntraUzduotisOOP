#include <fstream>
#include <iomanip>
#include <iostream>
#include <cassert>

#include "../headers/KolegosFaile.h"
#include "../headers/DarbasKonsole.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

void Konsole();
void DarbasSuFailais();

int main() {

    int fileOrNot{};
    cout << "Pasirinkite funkcija. 1 - duomenis rink is failo, 2 - duomenis rink is konsoles: ";
    cin >> fileOrNot;
    assert(fileOrNot == 1 || fileOrNot == 2);

    if (fileOrNot == 1) DarbasSuFailais();
    else Konsole();
}

void DarbasSuFailais() {
    vector<Kolega> kolegos{};
    Nuskaitymas(kolegos);
    Rasymas(kolegos);
}

void Konsole() {
    cin.ignore();
    cout << "Ivesk studento varda ir pavarde: ";
    string varpav{};
    getline(cin, varpav);

    double choice{}, metod{}, masOrVector{};
    Choices(choice, metod, masOrVector);

    double egzam{};

    if (masOrVector == 1) {
        MasyvasRasymas(varpav, choice, metod, egzam);
    } else {
        VektoriusRasymas(varpav, choice, metod, egzam);
    }
}

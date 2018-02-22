//
// Created by augus on 18/02/20.
//

#include <iomanip>
#include <cassert>
#include "../headers/DarbasKonsole.h"
#include "../headers/Skaiciavimai.h"

void MasyvasRasymas(const string &varpav, double choice,  double metod, double egzam) {
    auto *nDarbas = new double[1];
    int size = 0;
    if (choice == 1) Auto(egzam, nDarbas, size);
    else ByHand(egzam, nDarbas, size);

    double galBalas{};
    if (metod == 1) galBalas = PagalVidurki(egzam, nDarbas, size);
    else galBalas = PagalMediana(egzam, nDarbas, size);

    cout << endl << varpav << endl << "Pazymiai: " << endl;
    for (int i = 0; i < size; i++) {
        cout << std::setprecision(2) << std::fixed << nDarbas[i] << endl;
    }
    cout << "Egzaminas - " << egzam << endl << std::fixed << std::setprecision(2) << "Galutinis - " << galBalas
         << endl;
}

void VektoriusRasymas(const string &varpav, const double choice, const double metod, double egzam) {
    vector<double> nDarbas{};
    if (choice == 1) Auto(egzam, nDarbas);
    else ByHand(egzam, nDarbas);

    double galBalas{};
    if (metod == 1)galBalas = PagalVidurki(egzam, nDarbas);
    else galBalas = PagalMediana(egzam, nDarbas);

    cout << endl << endl << endl << varpav << endl << "Pazymiai: " << endl;
    for (auto paz :nDarbas) {
        cout << std::setprecision(2) << std::fixed << paz << endl;
    }
    cout << "Egzaminas - " << egzam << endl << std::fixed << std::setprecision(2) << "Galutinis - " << galBalas
         << endl;
}

void Auto(double &egzam, vector<double> &pazym) {

    cout << "Kiek pazymiu generuoti? ";
    int kiekis{};
    cin >> kiekis;

    mt19937 mt(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_real_distribution<double> dist(1, 10);

    egzam = dist(mt);
    for (int i = 0; i < kiekis; i++) {
        pazym.push_back(dist(mt));
    }
}

void Auto(double &egzam, double *&pazym, int &size) {
    cout << "Kiek pazymiu generuoti? ";
    int kiekis{};
    cin >> kiekis;

    size = kiekis;
    pazym = new double[kiekis];

    mt19937 mt(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_real_distribution<> dist(1.0, 10.0);

    egzam = dist(mt);
    for (int i = 0; i < kiekis; i++) {
        pazym[i] = dist(mt);
    }
}

void ByHand(double &egzam, vector<double> &pazymiai) {


    cout << "Ivesk egzamino rezultata desimtbaleje sistemoje: ";
    cin >> egzam;
    assert(egzam >= 1.0 && egzam <= 10.0);

    double pazym = 0;
    cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
    while(cin >> pazym){
        assert(pazym >= 1.0 && pazym <= 10.0);
        if (pazym >= 1 && pazym <= 10) pazymiai.push_back(pazym);
        else if (pazym) cout << "Toks skaičius negalimas." << endl;
        cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
    }
}

void ByHand(double &egzam, double *&pazymiai, int &size) {

    cout << "Ivesk egzamino rezultata desimtbaleje sistemoje: ";
    cin >> egzam;
    assert(egzam >= 1.0 && egzam <= 10.0);

    auto capacity = 1;

    double pazym = 0;
    cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
    while(cin >> pazym) {
        assert(pazym >= 1.0 && pazym <= 10.0);
        if (pazym >= 1 && pazym <= 10) {
            if (size < capacity) {
                pazymiai[size] = pazym;
                size++;
            } else {
                capacity *= 2;
                auto *t = new double[capacity];
                for (int i = 0; i < size; i++) {
                    *(t + i) = *(pazymiai + i);
                }
                pazymiai = t;
                pazymiai[size] = pazym;
                size++;
            }
        } else if (pazym) cout << "Toks skaičius negalimas." << endl;
        cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
    }
}

void Choices(double &choice, double &metod, double &masOrVector) {

    cout << "Pasirinkite funkcija. 1 - pazymius generuok automatiskai, 2 - pazymius vesti ranka: ";
    cin >> choice;
    assert(choice == 1 || choice == 2);

    cout << "Pasirinkite funkcija. 1 - skaiciuok pagal vidurki, 2 - skaiciuok pagal mediana: ";
    cin >> metod;
    assert(metod == 1 || metod == 2);

    cout << "Pasirinkite funkcija. 1 - naudok masyvus, 2 - naudok vektorius: ";
    cin >> masOrVector;
    assert(masOrVector == 1 || masOrVector == 2);
}
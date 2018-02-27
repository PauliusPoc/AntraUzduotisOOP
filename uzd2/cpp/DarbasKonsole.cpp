//
// Created by augus on 18/02/20.
//

#include <iomanip>
#include "../headers/Skaiciavimai.h"
#include "../headers/DarbasKonsole.h"

using std::exception;

void MasyvasRasymas(const string &varpav, double choice,  double metod, double egzam) {
    auto *nDarbas = new double[1];
    int size = 0;
    if (choice == 1) Auto(egzam, nDarbas, size);
    else ByHand(egzam, nDarbas, size);

    double galBalas{};
    if (metod == 1) galBalas = PagalVidurki(egzam, nDarbas, size);
    else galBalas = PagalMediana(egzam, nDarbas, size);

    cout << endl << varpav << endl << "Pazymiai: " << endl;
    for (auto i = 0; i < size; i++) {
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
    a1:
    int kiekis{};
    if (cout << "Kiek pazymiu generuoti? " && !(cin >> kiekis)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto a1;
    }

    mt19937 mt(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_real_distribution<double> dist(1, 10);

    egzam = dist(mt);
    for (int i = 0; i < kiekis; i++) {
        pazym.push_back(dist(mt));
    }
}

void Auto(double &egzam, double *&pazym, int &size) {
    a1:
    int kiekis{};
    if (cout << "Kiek pazymiu generuoti? " && !(cin >> kiekis)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto a1;
    }

    try{
        if (kiekis > SIZE_MAX){
            throw "Size too large.";
        } else{
            pazym = new double[kiekis];
            size = kiekis;
        }
    } catch (string &ex){
        cout << ex << endl;
        goto a1;
    }

    mt19937 mt(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_real_distribution<> dist(1.0, 10.0);

    egzam = dist(mt);
    for (int i = 0; i < kiekis; i++) {
        try {
            pazym[i] = dist(mt);
        } catch (exception &exception){
            cout << exception.what() << endl;
        }
    }
}

void ByHand(double &egzam, vector<double> &pazymiai) {

    e1:
    if (cout << "Ivesk egzamino rezultata desimtbaleje sistemoje: " && !(cin >> egzam)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto e1;
    }
    if (egzam < 1 || egzam > 10) {
        cout << "Toks skaičius negalimas." << endl;
        goto e1;
    }

    double pazym = 0;
    while(cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: " && (cin >> pazym)){
        if (pazym >= 1 && pazym <= 10) pazymiai.push_back(pazym);
        else cout << "Toks skaičius negalimas." << endl;
    }
    cin.clear(); //clear bad input flag
    cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
}

void ByHand(double &egzam, double *&pazymiai, int &size) {

    e1:
    if (cout << "Ivesk egzamino rezultata desimtbaleje sistemoje: " && !(cin >> egzam)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto e1;
    }
    if (egzam < 1 || egzam > 10) {
        cout << "Toks skaičius negalimas." << endl;
        goto e1;
    }

    auto capacity = 1;
    double daug = 1.0;

    double pazym = 0;
    cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
    while(cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: " && (cin >> pazym)) {
        if (pazym >= 1 && pazym <= 10) {
            if (size < capacity) {
                try {
                    pazymiai[size] = pazym;
                    size++;
                } catch (exception &exception){
                    cout << exception.what() << endl;
                }
            } else {
                c1:
                capacity *= 1 + daug;
                double *t;
                try{
                    if (capacity > SIZE_MAX){
                        throw "Size too big";
                    }
                    t = new double[capacity];
                } catch (string &e){
                    if (e == "Size too big") daug /= 2;
                    goto c1;
                }

                for (int i = 0; i < size; i++) {
                    *(t + i) = *(pazymiai + i);
                }
                pazymiai = t;
                try {
                    pazymiai[size] = pazym;
                    size++;
                } catch (exception &exception){
                    cout << exception.what() << endl;
                }
            }
        } else cout << "Toks skaičius negalimas." << endl;
    }
    cin.clear(); //clear bad input flag
    cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
}

void Choices(double &choice, double &metod, double &masOrVector) {

    c1:

    if (cout << "Pasirinkite funkcija. 1 - pazymius generuok automatiskai, 2 - pazymius vesti ranka: " && !(cin >> choice)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto c1;
    }
    if (choice != 1 && choice != 2) {
        cout << "Toks pasirinkimas negalimas" << endl;
        goto  c1;
    }

    c2:
    if (cout << "Pasirinkite funkcija. 1 - skaiciuok pagal vidurki, 2 - skaiciuok pagal mediana: " && !(cin >> metod)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto c2;
    }
    if (metod != 1 && metod != 2) {
        cout << "Toks pasirinkimas negalimas" << endl;
        goto  c2;
    }

    c3:
    if (cout << "Pasirinkite funkcija. 1 - naudok masyvus, 2 - naudok vektorius: " && !(cin >> masOrVector)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto c3;
    }
    if (masOrVector != 1 && masOrVector != 2){
        cout << "Toks pasirinkimas negalimas" << endl;
        goto  c3;
    }
}
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::sort;
using std::ifstream;
using std::ofstream;

void Auto(double &egzam, vector<double> &pazym);

void ByHand(double &egzam, vector<double> &pazymiai);

double PagalVidurki(double egzam, vector<double> &pazymiai);

double PagalMediana(double egzam, vector<double> &pazymiai);

void Auto(double &egzam, double *&pazym, int &size);

void ByHand(double &egzam, double *&pazym, int &size);

double PagalVidurki(double &egzam, double pazym[], int size);

double PagalMediana(double &egzam, double pazym[], int size);

struct Kolega {
    string vardas{};
    string pavard{};
    vector<double> nDarbai{};
    double galBalasV{};
    double galBalasM{};
    double egzam{};
};

void Nuskaitymas(vector<Kolega> &kolegos);
bool KolegosCompareV(Kolega lhs, Kolega rhs);


void Konsole();

void DarbasSuFailais();

int main() {

    int fileOrNot{};
    f1:
    cout << "Pasirinkite funkcija. 1 - duomenis rink is failo, 2 - duomenis rink is konsoles: ";
    cin >> fileOrNot;
    if (fileOrNot < 1 || fileOrNot > 2) {
        cout << "Toks pasirinkimas negalimas." << endl;
        goto f1;
    }

    if (fileOrNot == 1) DarbasSuFailais();
    else Konsole();
}

void DarbasSuFailais() {
    vector<Kolega> kolegos{};
    Nuskaitymas(kolegos);
    sort(kolegos.begin(), kolegos.end(), KolegosCompareV);

    auto dv = dv = kolegos[0].vardas.length(), dp
    kolegos[0].pavard.length();
    for (int i = 0; i < kolegos.size(); i++) {
                if (kolegos[i].vardas.length() > dv) dv = kolegos[i].vardas.length();
                if (kolegos[i].pavard.length() > dp) dp = kolegos[i].pavard.length();
            }
    if (dv < 6) dv = 6;
    if (dp < 7) dp = 7;

    ofstream fr("output.txt");
    fr << std::left << std::setw(dp + 5) << "Pavardė" << std::setw(dv + 4) << "Vardas"
       << std::setw(18 + 4) << "Galutinis-vidurkis" << std::setw(17 + 4) << "Galutinis-mediana" << endl;
    for (auto k : kolegos) {
                k.galBalasM = PagalMediana(k.egzam, k.nDarbai);
                k.galBalasV = PagalVidurki(k.egzam, k.nDarbai);
                fr << std::left << std::setw(dp + 4) << k.pavard << std::setw(dv + 4) << k.vardas
                   << std::setprecision(2) << std::fixed << std::setw(18 + 4)
                   << k.galBalasV << std::setw(17 + 3) << k.galBalasM << endl;
            }
}

void Konsole() {
    cin.ignore(::std::numeric_limits<long long int>::max(), '\n');
    cout << "Ivesk studento varda ir pavarde: ";
    string varpav{};
    getline(cin, varpav);

    double choice{}, metod{}, masOrVector{};
    c1:
        cout << "Pasirinkite funkcija. 1 - pazymius generuok automatiskai, 2 - pazymius vesti ranka: ";
    cin >> choice;
    if (choice < 1 || choice > 2) {
            cout << "Toks pasirinkimas negalimas." << endl;
            goto c1;
        }
    c2:
        cout << "Pasirinkite funkcija. 1 - skaiciuok pagal vidurki, 2 - skaiciuok pagal mediana: ";
    cin >> metod;
    if (metod < 1 || metod > 2) {
            cout << "Toks pasirinkimas negalimas." << endl;
            goto c2;
        }
    c3:
        cout << "Pasirinkite funkcija. 1 - naudok masyvus, 2 - naudok vektorius: ";
    cin >> masOrVector;
    if (masOrVector < 1 || masOrVector > 2) {
            cout << "Toks pasirinkimas negalimas." << endl;
            goto c3;
        }

    double egzam{};

    if (masOrVector == 1) {
            double *nDarbas = new double[1];
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

        } else {
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

    e1:
    cout << "Ivesk egzamino rezultata: ";
    cin >> egzam;
    if (!(egzam >= 1 && egzam <= 10)) {
        cout << "Toks skaičius negalimas." << endl;
        goto e1;
    }

    double pazym = 0;
    do {

        cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
        cin >> pazym;
        if (pazym >= 1 && pazym <= 10) pazymiai.push_back(pazym);
        else if (pazym) cout << "Toks skaičius negalimas." << endl;
    } while (pazym);
}

void ByHand(double &egzam, double *&pazymiai, int &size) {

    e1:
    cout << "Ivesk egzamino rezultata: ";
    cin >> egzam;
    if (!(egzam >= 1 && egzam <= 10)) {
        cout << "Toks skaičius negalimas." << endl;
        goto e1;
    }

    auto capacity = 1;

    double pazym = 0;
    do {
        cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
        cin >> pazym;
        if (pazym >= 1 && pazym <= 10) {
            if (size < capacity) {
                pazymiai[size] = pazym;
                size++;
            } else {
                capacity *= 2;
                double *t = new double[capacity];
                for (int i = 0; i < size; i++) {
                    *(t + i) = *(pazymiai + i);
                }
                pazymiai = t;
                pazymiai[size] = pazym;
                size++;
            }
        } else if (pazym) cout << "Toks skaičius negalimas." << endl;
    } while (pazym);
}

double PagalVidurki(double egzam, vector<double> &pazymiai) {

    double suma{};
    sort(pazymiai.begin(), pazymiai.end());
    for (auto paz : pazymiai) {
        suma += paz;
    }

    return 0.4 * suma / pazymiai.size() + 0.6 * egzam;

}

double PagalVidurki(double &egzam, double pazym[], int size) {
    double suma = 0;
    sort(pazym, pazym + size);
    for (int i = 0; i < size; i++) {
        suma += pazym[i];
    }

    return 0.4 * suma / size + 0.6 * egzam;
}

double PagalMediana(double egzam, vector<double> &pazymiai) {
    double med{};
    sort(pazymiai.begin(), pazymiai.end());
    med = pazymiai.size() % 2 == 0 ? (pazymiai[pazymiai.size() / 2] + pazymiai[pazymiai.size() / 2 - 1]) / 2
                                   : pazymiai[pazymiai.size() / 2];
    return 0.4 * med + 0.6 * egzam;
}

double PagalMediana(double &egzam, double pazym[], int size) {
    double med{};
    sort(pazym, pazym + size);
    med = size % 2 == 0 ? (pazym[size / 2] + pazym[size / 2 - 1]) / 2
                        : pazym[size / 2];
    return 0.4 * med + 0.6 * egzam;
}

void Nuskaitymas(KolegaM *&kolegos, int &size) {

    double *p = new double[5], egzam;
    string v, pa;
    int cap = 1;
    KolegaM k{};
    ifstream fd("kursiokai.txt");

    while (fd >> pa >> v >> p[0] >> p[1] >> p[2] >> p[3] >> p[4] >> egzam) {
        k.vardas = v;
        k.pavard = pa;
        for (int i = 0; i < 5; i++) { k.nDarbai[i] = p[i]; }
        k.egzam = egzam;
        if (size < cap) {
            kolegos[size] = k;
            size++;
        } else {
            cap *= 2;
            KolegaM *temp = new KolegaM[cap];
            for (int i = 0; i < size; i++) {
                temp[i] = kolegos[i];
            }
            kolegos = temp;
            kolegos[size] = k;
            size++;
        }
    }
}

void Nuskaitymas(vector<KolegaV> &kolegos) {
    double *p = new double[5], egzam;
    vector<double> darbai{};
    string v, pa;
    KolegaV k{};
    ifstream fd("kursiokai.txt");

    while (fd >> pa >> v >> p[0] >> p[1] >> p[2] >> p[3] >> p[4] >> egzam) {
        k.vardas = v;
        k.pavard = pa;
        for (int i = 0; i < 5; i++) darbai.push_back(p[i]);
        k.nDarbai = darbai;
        darbai.clear();
        k.egzam = egzam;
        kolegos.push_back(k);
    }
}

bool KolegosCompareM(KolegaM lhs, KolegaM rhs) {
    if (lhs.pavard <= rhs.pavard) {
        if (lhs.pavard == rhs.pavard) {
            if (lhs.vardas < rhs.vardas) return true;
            else return false;
        } else return true;
    } else return false;
}

bool KolegosCompareV(KolegaV lhs, KolegaV rhs) {
    if (lhs.pavard <= rhs.pavard) {
        if (lhs.pavard == rhs.pavard) {
            if (lhs.vardas < rhs.vardas) return true;
            else return false;
        } else return true;
    } else return false;
}

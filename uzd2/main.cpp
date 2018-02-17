#include <algorithm>
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
using std::uniform_int_distribution;
using std::sort;

void Auto(int &egzam, vector<int> &pazym);
void ByHand(int &egzam, vector<int> &pazymiai);
double PagalVidurki(int egzam, vector<int> &pazymiai);
double PagalMediana(int egzam, vector<int> &pazymiai);

void Auto(int &egzam, int* &pazym, int &size);
void ByHand(int &egzam, int* &pazym, int &size);
double PagalVidurki(int &egzam, int* &pazym, int size);
double PagalMediana(int &egzam, int* &pazym, int size);


int main() {


    cout << "Ivesk studento varda ir pavarde: ";
    string varpav{};
    getline(cin, varpav);

    int choice{}, metod{}, masOrVector{};
    c1:
    cout << "Pasirinkite funkcija. 1 - pazymius generuok automatiskai, 2 - pazymius vesti ranka: ";
    cin >> choice;
    if (choice < 1 || choice > 2){
        cout << "Toks pasirinkimas negalimas." << endl;
        goto c1;
    }
    c2:
    cout << "Pasirinkite funkcija. 1 - skaiciuk pagal vidurki, 2 - skaiciuk pagal mediana: ";
    cin >> metod;
    if (metod < 1 || metod > 2){
        cout << "Toks pasirinkimas negalimas." << endl;
        goto c2;
    }
    c3:
    cout << "Pasirinkite funkcija. 1 - naudok masyvys, 2 - naudok vectors: ";
    cin >> masOrVector;
    if (masOrVector < 1 || masOrVector > 2){
        cout << "Toks pasirinkimas negalimas." << endl;
        goto c3;
    }


    int egzam{};

    if (masOrVector == 1){

        int* nDarbas = new int[1];
        int size = 0;

        if (choice == 1) Auto(egzam,nDarbas, size);
        else ByHand(egzam,nDarbas,size);

        double galBalas{};
        if (metod == 1) galBalas =  PagalVidurki(egzam,nDarbas, size);
        else galBalas = PagalMediana(egzam,nDarbas, size);


        cout << endl << varpav << endl << "Pazymiai: " << endl;
        for(int i = 0; i < size; i++){
            cout << nDarbas[i] << endl;
        }
        cout << "Egzaminas - " << egzam << endl << std::fixed << std::setprecision(2) << "Galutinis - " << galBalas << endl;
    }
    else {
        vector<int> nDarbas{};

        if (choice == 1) Auto(egzam,nDarbas);
        else ByHand(egzam,nDarbas);

        double galBalas{};
        if (metod == 1) galBalas =  PagalVidurki(egzam,nDarbas);
        else galBalas = PagalMediana(egzam,nDarbas);


        cout << endl << endl << endl << varpav << endl << "Pazymiai: " << endl;
        for(auto paz : nDarbas){
            cout << paz << endl;
        }
        cout << "Egzaminas - " << egzam << endl << std::fixed << std::setprecision(2) << "Galutinis - " << galBalas << endl;
    }
}

void Auto(int &egzam, vector<int> &pazym) {

    cout << "Kiek pazymiu generuoti? ";
    int kiekis{};
    cin >> kiekis;

    mt19937 mt(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1,10);

    egzam = dist(mt);
    for (int i = 0; i < kiekis; i++){
        pazym.push_back(dist(mt));
    }
}

void Auto(int &egzam, int* &pazym, int &size) {
    cout << "Kiek pazymiu generuoti? ";
    int kiekis{};
    cin >> kiekis;

    size = kiekis;
    pazym = new int[kiekis];

    mt19937 mt(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> dist(1,10);

    egzam = dist(mt);
    for (int i = 0; i < kiekis; i++){
        *(pazym + i) = dist(mt);
    }
}

void ByHand(int &egzam, vector<int> &pazymiai) {

    e1:
    cout << "Ivesk egzamino rezultata: ";
    cin >> egzam;
    if (!(egzam >= 1 && egzam <= 10)){
        cout << "Toks skaičius negalimas." << endl;
        goto e1;
    }

    int  pazym = 0;
    do{

        cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
        cin >> pazym;
        if(pazym >= 1 && pazym <= 10) pazymiai.push_back(pazym);
        else if (pazym) cout << "Toks skaičius negalimas." << endl;
    }while (pazym);
}

void ByHand(int &egzam, int* &pazymiai, int &size) {

    e1:
    cout << "Ivesk egzamino rezultata: ";
    cin >> egzam;
    if (!(egzam >= 1 && egzam <= 10)) {
        cout << "Toks skaičius negalimas." << endl;
        goto e1;
    }

    auto capacity = 1;

    int pazym = 0;
    do {
        cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
        cin >> pazym;
        if (pazym >= 1 && pazym <= 10) {
            if (size < capacity) {
                pazymiai[size] = pazym;
                size++;
            } else {
                capacity *= 2;
                int *t = new int[capacity];
                for (int i = 0; i < size; i++) {
                    *(t + i) = *(pazymiai + i);
                }
                *pazymiai = *t;
                pazymiai[size] = pazym;
                size++;
            }
        } else if (pazym) cout << "Toks skaičius negalimas." << endl;
    } while (pazym);
}

double PagalVidurki(int egzam, vector<int> &pazymiai) {

    double  suma{};
    sort(pazymiai.begin(), pazymiai.end());
    for(auto paz : pazymiai){
        suma += paz;
    }

    return 0.4 * suma/pazymiai.size() +  0.6 * egzam;

}

double PagalVidurki(int &egzam, int* &pazym, int size) {
    double  suma{};
    sort(pazym, pazym + size);
    for(int i = 0; i < size; i++){
        suma += pazym[i];
    }

    return 0.4 * suma/size +  0.6 * egzam;
}

double PagalMediana(int egzam, vector<int> &pazymiai) {
    double med{};
    sort(pazymiai.begin(), pazymiai.end());
    med = pazymiai.size() % 2 == 0 ? (pazymiai[pazymiai.size() / 2] + pazymiai[pazymiai.size() / 2 - 1]) / 2
                                   : pazymiai[pazymiai.size() / 2];
    return 0.4 * med +  0.6 * egzam;
}

double PagalMediana(int &egzam, int* &pazym, int size) {
    double med{};
    sort(pazym, pazym + size);
    med = size % 2 == 0 ? (pazym[size / 2] + pazym[size / 2 - 1]) / 2
                        : pazym[size / 2];
    return 0.4 * med +  0.6 * egzam;
}





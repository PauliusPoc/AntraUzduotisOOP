#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>

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


int main() {


    cout << "Ivesk studento varda ir pavarde: ";
    string varpav{};
    cin >> varpav;

    cout << "Pasirinkite funkcija. 1 - pazymius generuok automatiskai, 2 - pazymius vesti ranka: ";
    int choice{}, metod{};
    cin >> choice;
    cout << "Pasirinkite funkcija. 1 - skaiciuk pagal vidurki, 2 - skaiciuk pagal mediana: ";
    cin >> metod;

    int egzam{};
    vector<int> pazymiai{};

    if (choice == 1) Auto(egzam,pazymiai);
    else ByHand(egzam,pazymiai);

    double galut{};
    if (metod == 1) galut =  PagalVidurki(egzam,pazymiai);
    else galut = PagalMediana(egzam,pazymiai);


    cout << endl << endl << endl << varpav << endl << "Pazymiai: " << endl;
    for(auto paz : pazymiai){
        cout << paz << endl;
    }
    cout << "Egzaminas - " << egzam << endl << std::fixed << std::setprecision(2) << "Galutinis - " << galut << endl;

    return 0;
}

void Auto(int &egzam, vector<int> &pazym) {

    cout << "Kiek pazymiu generuoti? ";
    int kiekis{};
    cin >> kiekis;

    random_device rd;
    mt19937 mt(rd() * time(0) + rd());
    uniform_int_distribution<int> dist(1,10);

    egzam = dist(mt);
    for (int i = 0; i < kiekis; i++){

        pazym.push_back(dist(mt));
    }
}

void ByHand(int &egzam, vector<int> &pazymiai) {

    cout << "Ivesk egzamino rezultata: ";
    cin >> egzam;

    int  pazym = 0;
    do{
        cout << "Ivesk pazymi arba bet koki kita simboli, noredamas uzbaigti ivedima: ";
        cin >> pazym;
        if(pazym) pazymiai.push_back(pazym);
    }while (pazym);
}

double PagalVidurki(int egzam, vector<int> &pazymiai) {

    double  suma{};
    sort(pazymiai.begin(), pazymiai.end());
    for(auto paz : pazymiai){
        suma += paz;
    }

    return 0.4 * suma/pazymiai.size() +  0.6 * egzam;

}

double PagalMediana(int egzam, vector<int> &pazymiai) {
    double med{};
    sort(pazymiai.begin(), pazymiai.end());
    med = pazymiai.size() % 2 == 0 ? (pazymiai[pazymiai.size() / 2] + pazymiai[pazymiai.size() / 2 - 1]) / 2
                                   : pazymiai[pazymiai.size() / 2];
    return 0.4 * med +  0.6 * egzam;
}



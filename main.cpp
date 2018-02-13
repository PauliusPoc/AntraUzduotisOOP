#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;


int main() {


    cout << "Ivesk studento varda ir pavarde: ";
    string varpav;
    cin >> varpav;

    cout << "Ivesk egzamino rezultata: ";
    double egzam{};
    cin >> egzam;

    vector<double> pazymiai;
    double  pazym;
    do{
        cin >> pazym;
        if(pazym) pazymiai.push_back(pazym);
    }while (pazym);

    double  suma{};
    for(auto paz : pazymiai){
        suma += paz;
    }

    double galut{};
    galut = 0.4 * suma/pazymiai.size() +  0.6 * egzam;

    cout << endl << endl << endl << varpav << endl << "Pazymiai: " << endl;
    for(auto paz : pazymiai){
        cout << paz << endl;
    }
    cout << std::fixed << std::setprecision(2) << "Egzaminas - " << egzam << endl << "Galutinis - " << galut << endl;

    return 0;
}
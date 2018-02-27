#include "../headers/KolegosFaile.h"
#include "../headers/DarbasKonsole.h"
#include "../headers/PerformanceProfiling.h"

void Konsole();
void DarbasSuFailais();
void Performance();

int main() {
    f1:
    int fileOrNot{};
    if (cout << "Pasirinkite funkcija. 1 - duomenis rink is failo, 2 - duomenis rink is konsoles, 3 - performance profiler: " && !(cin >> fileOrNot)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto f1;
    }
    if (fileOrNot >= 1 && fileOrNot <= 3) {

        if (fileOrNot == 1) DarbasSuFailais();
        else if (fileOrNot == 2) Konsole();
        else Performance();
    } else {
        cout << "Toks pasirinkimas negalimas" << endl;
        goto f1;
    }
}

void DarbasSuFailais() {
    vector<Kolega> kolegos{};

    Nuskaitymas(kolegos,"kursiokai.txt");
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

void Performance(){
    const unsigned int nTestu = 7; // kiek testų failų generuoti
    StartTesting(nTestu);

}

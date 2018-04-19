#include "../headers/Studentas.h"
#include "../headers/DarbasFailai.h"
#include "../headers/Performance.h"

void DarbasSuFailais();
void Performance();

int main() {
    f1:
    int fileOrNot;
    if (cout << "Pasirinkite funkcija.\n1 - duomenis rink is failo (v0.2),\n2 - performance profiler: " && !(cin >> fileOrNot)) {
        cin.clear(); //clear bad input flag
        cin.ignore(::std::numeric_limits<int>::max(), '\n'); //discard input
        cout << "Neteisinga įvestis\n";
        goto f1;
    }
    if (fileOrNot >= 1 && fileOrNot <= 2) {

        if (fileOrNot == 1) DarbasSuFailais();
        else Performance();
    } else {
        cout << "Toks pasirinkimas negalimas" << endl;
        goto f1;
    }
}

void DarbasSuFailais() {
    vector<Studentas> kolegos{};
    Nuskaitymas(kolegos,"kursiokai.txt");
    Rasymas(kolegos);
}

void Performance(){
    const unsigned int nTestu = 6; // kiek testų  atlkti?
    StartTesting(nTestu);
}
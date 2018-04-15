#include "../headers/DarbasKonsole.h"
#include "../headers/Studentas.h"
#include "../headers/DarbasFailai.h"
#include "../headers/Performance.h"

void Konsole();
void DarbasSuFailais();
void Performance();

int main() {
    f1:
    int fileOrNot;
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
    vector<Studentas> kolegos{};
    Nuskaitymas(kolegos,"kursiokai.txt");
    Rasymas(kolegos);
}
void Konsole() {
    unsigned int choice{}, metod{};
    Choices(choice, metod);

    Studentas S;
    S.readFromKonsole(cin, choice);
    S.printToKonsole(cout, metod);
}
void Performance(){
    const unsigned int nTestu = 4; // kiek testų  atlkti?
    StartTesting(nTestu);
}
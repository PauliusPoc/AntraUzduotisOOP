//
// Created by augus on 18/04/15.
//

#include "../headers/DarbasKonsole.h"

void Choices(unsigned int &choice, unsigned int &metod) {

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
}

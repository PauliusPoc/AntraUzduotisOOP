//
// Created by augus on 18/04/15.
//

#include <chrono>
#include "../headers/Studentas.h"

Studentas::Studentas() {
    egzam_ = 0;
    vardas_ = "Vardnis";
    pavard_ = "Pavardenis";
}

void Studentas::print(unsigned int dv, unsigned int dp, std::ostream &fr) {
    fr << std::left << std::setw(dp + 4) << pavarde() << std::setw(dv + 4) << vardas()
       << std::setprecision(2) << std::fixed << std::setw(18 + 4)
       << galBalas(true) << std::setw(17 + 3) << galBalas(false) << std::endl;
}

void Studentas::readFromKonsole(std::istream &fd, const unsigned int choice) {
    cout << "Studento vardas: ";
    fd >> vardas_ ;
    cout << "Sudento pavarde: ";
    fd >> pavard_;
    if (choice == 1) Auto(fd);
    else ByHand(fd);
}
void Studentas::ByHand(istream &fd){
    e1:
        if (cout << "Ivesk egzamino rezultata desimtbaleje sistemoje: " && !(fd >> egzam_)) {
            fd.clear(); //clear bad input flag
            fd.ignore(std::numeric_limits<int>::max(), '\n'); //discard input
            cout << "Neteisinga įvestis\n";
            goto e1;
        }
    if (egzam_ < 1 || egzam_ > 10) {
            cout << "Toks skaičius negalimas." << endl;
            goto e1;
        }

    double pazym = 0;
    while(cout << "Ivesk pazymi nuo 1 iki 10 arba bet koki kita simboli, noredamas uzbaigti ivedima: " && (fd >> pazym)){
            if (pazym >= 1 && pazym <= 10) nDarbai_.push_back(pazym);
            else cout << "Toks skaičius negalimas." << endl;
        }
    fd.clear(); //clear bad input flag
    fd.ignore(std::numeric_limits<int>::max(), '\n'); //discard input
}
void Studentas::Auto(istream &fd) {
    a1:
        int kiekis{};
    if (cout << "Kiek pazymiu generuoti? " && !(fd >> kiekis)) {
            fd.clear(); //clear bad input flag
            fd.ignore(std::numeric_limits<int>::max(), '\n'); //discard input
            cout << "Neteisinga įvestis\n";
            goto a1;
        }

    mt19937 mt(static_cast<long unsigned int>(std::chrono::_V2::system_clock::now().time_since_epoch().count()));
    uniform_real_distribution<double> dist(1, 10);

    egzam_ = dist(mt);
    for (int i = 0; i < kiekis; i++) {
            nDarbai_.push_back(dist(mt));
        }
}

void Studentas::printToKonsole(std::ostream &fr, const unsigned int metod) {
    fr << endl << endl << endl << vardas() << " " << pavarde() << endl << "Pazymiai: " << endl;
    for (auto paz : nDarbai_) {
        fr << std::setprecision(2) << std::fixed << paz << endl;
    }
    fr << "Egzaminas - " << egzam_ << endl << std::fixed << std::setprecision(2) << "Galutinis - " << galBalas(metod == 1)
         << endl;
}

bool Studentas::compare(Studentas rhs) {
    return pavard_ <= rhs.vardas_ && (!(pavard_ == rhs.pavarde()) || vardas_ < rhs.vardas());
}
double Studentas::galBalas(bool arVidurkis) {
    if (arVidurkis){
        double suma{};
        suma = std::accumulate(nDarbai_.begin(), nDarbai_.end(), 0.0);
        return suma / nDarbai_.size();
    }
    else {
        std::sort(nDarbai_.begin(), nDarbai_.end());
        return nDarbai_.size() % 2 == 0 ? (nDarbai_[nDarbai_.size() / 2] + nDarbai_[nDarbai_.size() / 2 - 1]) / 2
                                        : nDarbai_[nDarbai_.size() / 2];
    }
}
istream &operator>>(istream &input, Studentas &S) {
    input >> S.pavard_ >> S.vardas_;
    double t{};
    for (int i = 0; i < 5; i++){
        input >> t;
        S.nDarbai_.push_back(t);
    }
    input >> S.egzam_;
    return input;
}

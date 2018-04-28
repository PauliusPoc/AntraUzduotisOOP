//
// Created by augus on 18/04/15.
//
#include "../headers/Studentas.h"

void Studentas::print(unsigned int dv, unsigned int dp, std::ostream &fr) {
    fr << std::left << std::setw(dp + 4) << pavard_ << std::setw(dv + 4) << vardas_
       << std::setprecision(2) << std::fixed << std::setw(18 + 4)
       << vidurkis() << std::setw(17 + 3) << mediana() << std::endl;
}
Studentas::Studentas(istream &input) {
    input >> pavard_ >> vardas_;
    for (auto i = 0; i < 5; i++){
        double t;
        input >> t;
        nDarbai_.push_back(t);
    }
    input >> egzam_;
}
double Studentas::mediana() {
    std::sort(nDarbai_.begin(), nDarbai_.end());
    return (nDarbai_.size() % 2 == 0 ? (nDarbai_[nDarbai_.size() / 2] + nDarbai_[nDarbai_.size() / 2 - 1]) / 2
                                    : nDarbai_[nDarbai_.size() / 2]) * 0.4 + 0.6 * egzam_;
}
double Studentas::vidurkis(){
    double suma{};
    suma = accumulate(nDarbai_.begin(), nDarbai_.end(), 0.0);
    return (suma / nDarbai_.size()) * 0.4 + 0.6 * egzam_;
}

ostream &operator<<(ostream &output, Studentas &S){
    output << S.vardas_ << " " << S.pavard_ << " " << S.vidurkis() << " " << S.mediana() << endl;
    return output;
}
bool Studentas::operator<(const Studentas &rhs) {
    return pavard_ <= rhs.pavard_ || (pavard_ == rhs.pavard_ && vardas_ < rhs.vardas_);
}
bool Studentas::operator>(const Studentas &rhs) {
    return !operator<(rhs);
}
bool Studentas::operator==(const Studentas &rhs) {
    return vardas_ == rhs.vardas_ && pavard_ == rhs.pavard_;
}
bool Studentas::operator!=(const Studentas &rhs) {
    return !operator==(rhs);
}

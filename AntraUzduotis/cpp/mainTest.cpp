#include <gmock/gmock.h>
#include "../headers/Studentas.h"
#include "../headers/DarbasFailai.h"
#include "../headers/Performance.h"

void DarbasSuFailais();
void Performance();

TEST(reading_test1, read_test){
    StrongVector<Studentas> kolegos;
    Studentas *k;
    std::ifstream fd;

    try {
        fd.open( "test.txt", std::ios::in);
        if (!fd.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        return;
    }catch (char const* e){
        cout << "Duomenu failas neegzistuoja" << endl;
        return;
    }

    while (!fd.eof()) {
        k = new Studentas(fd);
        if (fd.eof()) break;
        try {
            kolegos.push_back(*k);
        }catch (std::exception exc){
            cout << exc.what() << endl;
            std::terminate();
        }
    }
    EXPECT_EQ(10, kolegos.size());
    EXPECT_EQ(kolegos[0].vardas(), "Pavarde1");
}
TEST(calc_test, calculation){

    std::ifstream fd;

    try {
        fd.open( "test.txt", std::ios::in);
        if (!fd.good()) throw "Error opening file";
    } catch (string &e){
        cout << e << endl;
        return;
    }catch (char const* e){
        cout << "Duomenu failas neegzistuoja" << endl;
        return;
    }
    Studentas k(fd);
    EXPECT_DOUBLE_EQ(k.vidurkis(), double(4.32));
}

TEST(rusiavimas, rs){
    StrongVector<Studentas> kolegos, geek;
    Nuskaitymas(kolegos, "test.txt");
    EXPECT_EQ(kolegos.size(), 10);
    ArKietas(kolegos,geek,true);
    EXPECT_LT(kolegos.size(), 10);
    EXPECT_GT(geek.size(), 0);
    EXPECT_EQ(kolegos[0].vardas(), "Pavarde1");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}

void DarbasSuFailais() {
    StrongVector<Studentas> kolegos{};
    Nuskaitymas(kolegos,"kursiokai.txt");
    Rasymas(kolegos);
}

void Performance(){
    const unsigned int nTestu = 5; // kiek testų  atlkti?
    StartTesting(nTestu);
}
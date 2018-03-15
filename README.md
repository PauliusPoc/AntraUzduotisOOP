
# Augustino Makevičiaus objektinio programavimo 2 užduotis. (VU ISI 1 kursas)
# ![Žemėlapis](WordItOut.png)
## Programos tikslas
- Programoje nuskaitomi tokie duomenys:
  - Studento vardas, pavardė
  - Studento n atliktų darbų įverčiai dešimtbalėje sistemoje
  - Galutinio egzamino rezultatas dešimtbalėje sistemmoje
- Pagal įvestus duomenis apskaičiuojamas galutinis balas (pagal vidurkį)
- Surinkti duomenys išvedami į ekraną
- Vartotojui suteikiama galimybė pažymius generuoti automatiškai.
- Vartotojui suteikiama galimybė galutinį balą apskaičiuoti pagal pažymių medianą

## Programos išvedimas 
## ![Programos išvedimas](uzd2/Išvedimas.png)

## Įdiegimas naudojant `GCC`kompiliatorių 

- `git clone https://github.com/AugustinasMKVU/OOP-Task-2.git`
- `cd OOP-Task-2/uzd2/cpp`
- `g++ -std=c++11 *.cpp  -o main`
- `./main`


## Versijų istorija (changelog)

### [Changelog v0.5 (2018-03-12)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.5)
#### Pridėta
- Sukurtos funkcijos, leidžiančios dirbti su
  ```c++ 
   std::list
   std::deque
  ```
- Įkelti atnaujinti analizės rezultatai: ProfilingResultDeque ir ProfilingResultList
#### Pakeista
- Vektorių analizės rezultatai pervadinti į ProfilingResultVector.
- Atnaujintas ReadMe

### [Changelog v0.4.1 (2018-03-12)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.4.1)
#### Pridėta
- Įkelti duomenų failai
- Įkelti atnaujinti analizės rezultatai
#### Pakeista
- Vietoj išrašymo į failą pagal bool reikšmę, studentus deliojame į atitinkamus vektorius.
- Atnaujintas ReadMe
#### Pašalinta
- Panakinta išrašymo funkcija

### [Changelog v0.4 (2018-02-27)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.4)
#### Pridėta
- Sukurtos funkcijos programos spartai testuoti, kurios įdėtą headerį ir source failą
  ```c++
  void ArKietas(vector<Kolega> &koleg, bool arVidurkiu);
  void StartProfiling(unsigned int n, ofstream &pr, unsigned int met);
  void GeneruokTestui(unsigned int n, ofstream &fk);
  void IsrasykTesta(const vector<Kolega> &kolegos, const string &fo);
  void StartTesting(const unsigned int nTestu);
  ```
- Įkelti analizės rezultatai
#### Pakeista
- Uždėtos naujos apsaugos pasirinkimų cin'am. Nebegalima pramušti su stringais.
- Vieno kursioko informacijos išrašymas perkeltas į atitinkamą struktųrą.
#### Pašalinta
- Atsisakyta *assert*. Jis pakeistais if'ais ir goto funkcijomis.

### [Changelog v0.3 (2018-02-26)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.3)
#### Pridėta
- Sukurti *try-catch* sakiniai ties failų atidarymu, vietos atmintyje išskyrimu (masyvams)
- Tikliau nurodomi failų tipai(in ar out).
- Sukurti *labels* neteisingos įvesties valdymui.

### [Changelog v0.2.1 (2018-02-20)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.2.1)
#### Pridėta
- Pridėtos funkcijos, valdančios programą. Jos gautos refactorinimo metu:
  ```c++
  void Konsole();
  void DarbasSuFailais();
  ```
- Pridėtos nuorodos į reikiamus headerius:
  ```c++
  #include "../headers/DarbasKonsole.h"
  #include "../headers/Skaiciavimai.h"
  ```
- Sukurtas headers folderis, į kurį įdėjau tris headerius.
- Sukurtas cpp folderis, į kurį įdėjau tris cpp failus atitinkančius headerius.

#### Pakeista
- main.cpp perkelta į cpp aplankalą
- Funkcijos susijusios su darbu su failais, konsole bei skaičiavimais perkeltos į atitinkamus cpp failus. Jų declare'ai perkelti į atitinkamus headerius.
- Atsižvelgus į dėstytojo pastabas apie std::string::size_type, vietose aprašančiose string ilgius pradėta naudoti auto vietoj int.
-Pakeistas WordRain nuotraukos pavadinimas.

#### Panakinta
- Iš main.cpp ištrintos funkcijos, kurias perkėliau.

### [Changelog v0.2 (2018-02-19)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.2)
#### Pridėta
- [Leidžiama duomenis skaityti iš failų.](https://github.com/AugustinasMKVU/OOP-Task-2/blob/master/uzd2/kursiokai.txt)
- Duomenų iš failų saugojimui sukurtos struktūros:
  ```c++
  void Auto(int &egzam, int* &pazym, int &size);
  void ByHand(int &egzam, int* &pazym, int &size);
  double PagalVidurki(int &egzam, int* &pazym, int size);
  double PagalMediana(int &egzam, int* &pazym, int size);struct KolegaM {
    string vardas{};
    string pavard{};
    double nDarbai[5];
    double galBalasV{};
    double galBalasM{};
    double egzam{};
  };
  struct KolegaV {
    string vardas{};
    string pavard{};
    vector<double> nDarbai{};
    double galBalasV{};
    double galBalasM{};
    double egzam{};
  };
  ```
- [Duomenų išrašymas į rezultatų failą. Duomenys surikiuoti.](https://github.com/AugustinasMKVU/OOP-Task-2/blob/master/uzd2/output.txt)
#### Pakeista
- Atnaujintas readme (pridėtas v0.2 changelog'as)
- Pažymių tipas pakeistas iš int į double

### [Changelog v0.1.2 (2018-02-17)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.1.2)
#### Pridėta
- Leidžiama vietoje vektorių naudoti masyvus.
- Pridėtos funkcijos, skirtos dirbti su masyvais:
  ```c++
  void Auto(int &egzam, int* &pazym, int &size);
  void ByHand(int &egzam, int* &pazym, int &size);
  double PagalVidurki(int &egzam, int* &pazym, int size);
  double PagalMediana(int &egzam, int* &pazym, int size);
  ```
- Pridėti teisingos įvesties patikrinimai.
#### Pakeista
- Atnaujintas readme
- Pakeistas *mt19937* generatoriaus seed generavimas atsitiktinai į laiką nuo epochos pradžios.
#### Pašalinta
- Nebenaudojamas random_device.

### Changelog v0.1.1 (2018-02-13)
#### Pridėta
- Įkelta programos išvesties nuotrauka
#### Pakeista
- Kintamųjų vardai pakeisti į vardus nurodytus reikalavimuose
- Sutaisytas bug'as, kai vartotojas įveda 2 žodžius (vardą ir pavardę)
- Atnaujintas README.md

### [Changelog v0.1.1 (2018-02-13)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.1.1)
#### Pridėta
- Įkelta programos išvesties nuotrauka
#### Pakeista
- Kintamųjų vardai pakeisti į vardus nurodytus reikalavimuose
- Sutaisytas bug'as, kai vartotojas įveda 2 žodžius (vardą ir pavardę)
- Atnaujintas README.md

### [Changelog v0.1 (2018-02-13)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.1)
#### Pridėta
- Programoje leidžiama pasirinkti atsitiktinių pažymių generavimą naudojant **mt19937** generatorių.
- Programoje leidžiama pasirnkti, jog vietoje vidurkio, galutinį balą skaičiuotų pagal pažymių medianą.
- Sukurtos funkcijos:
  ```c++
  void Auto(int &egzam, vector<int> &pazym);
  void ByHand(int &egzam, vector<int> &pazymiai);
  double PagalVidurki(int egzam, vector<int> &pazymiai);
  double PagalMediana(int egzam, vector<int> &pazymiai);
  ```
#### Pakeista
- Pažymių įrašymo ranka kodas perkeltas į funkciją ```ByHand```.
- Galutinio balo skaičiavimo pagal vidurkį kodas perkeltas į funkciją ```PagalVidurki```
- Pažymių vektorius pakeistas iš ```vector<double>``` į ```vector<int>```
#### Pašalinta
- Iš funkcijos ```main``` ištrinti galutinio balo skaičiavimo pagal vidurkį ir pažymių įrašymo ranka kodai.

## Naudingos nuorodos
[Atsitiktinių skaičių generavimas C++ 11](https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful)


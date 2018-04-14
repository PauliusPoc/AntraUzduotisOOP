
# Augustino Makevičiaus objektinio programavimo 3 užduotis. (VU ISI 1 kursas)

## Programos tiklas
Patobulinkite 2-ojo darbo realizaciją:
- Vietoj Studentas (StudentoInfo) structūros atsižvelgdami į Jūsų pačių atliktą antrą užduotį susikurkite Studentas (StudentoInfo) class'ę.

# Antrosios užduoties aprašymas

# ![Žemėlapis](WordItOut.png)

# Vertinimas 

- Viskas labai tvarkingai ir teisingai.

## Programos tikslas
- Programoje nuskaitomi tokie duomenys:
  - Studento vardas, pavardė
  - Studento n atliktų darbų įverčiai dešimtbalėje sistemoje
  - Galutinio egzamino rezultatas dešimtbalėje sistemmoje
- Pagal įvestus duomenis apskaičiuojamas galutinis balas (pagal vidurkį)
- Surinkti duomenys išvedami į ekraną arba į rezultatų failą.
- Vartotojui suteikiama galimybė pažymius generuoti automatiškai.
- Vartotojui suteikiama galimybė galutinį balą apskaičiuoti pagal pažymių medianą
## Programos išvedimas
```shell
Pasirinkite funkcija. 1 - duomenis rink is failo, 2 - duomenis rink is konsoles,3 - performance profiler: 2
Ivesk studento varda ir pavarde: Paulius Pocius
Pasirinkite funkcija. 1 - pazymius generuok automatiskai, 2 - pazymius vesti ranka: 1
Pasirinkite funkcija. 1 - skaiciuok pagal vidurki, 2 - skaiciuok pagal mediana: 1
Pasirinkite funkcija. 1 - naudok masyvus, 2 - naudok vektorius: 2
Kiek pazymiu generuoti? 10

Paulius Pocius
Pazymiai:
1.01
1.08
1.86
2.80
6.28
6.76
7.27
8.96
9.25
9.39
Egzaminas - 2.29
Galutinis - 3.56
```
## Įdiegimas naudojant `GCC`kompiliatorių 

- `git clone https://github.com/AugustinasMKVU/AntraUzduotis.git`
- `cd AntraUzduotis/uzd2`
- `cmake . -G "MinGW Makefiles"`
- `mingw32-make`
- `.\uzd2`

## Veikimo spartos analizė
### Matuojame laiką dirbdami su vektoriais, kur n duomenų skaičius (skirstome į du naujus konteinerius)

|Funkcija                     |n = 10    |n = 100     |n = 1000    |n = 10000   |n = 100000 |
|-----------------------------|----------|------------|------------|------------|-----------|
|Duomenų nuskaitymas iš failo |0.00099 s|0.003 s|0.024074 s |0.237648  s|2.45851  s|
|Duomenų išrikiavimas (skirstant)|0        s|0         s|0.001001 s |0.0110305 s|0.113328 s|
|Duomenų išrikiavimas (trinant)  |0        s|0.001        s|0.007 s |6.63 s|628 s|
|Duomenų išrikiavimas (trinant pasitelkus algoritmus)  |0.002       s|0.003       s|0.03 s |0.3 s|0.09 s|

### Matuojame laiką dirbdami su list, kur n duomenų skaičius

|Funkcija                     |n = 10    |n = 100     |n = 1000    |n = 10000   |n = 100000 |
|-----------------------------|----------|------------|------------|------------|-----------|
|Duomenų nuskaitymas iš failo |0.00100 s|0.003 s|0.0240901 s|0.23163  s|2.44951 s|
|Duomenų išrikiavimas (skirstant)|0        s|0         s|0.0010023 s|0.007019 s|0.0792106 s|
|Duomenų išrikiavimas (trinant)  |0        s|0.0005      s|0.001 s |0.004 s|0.044 s|

### Matuojame laiką dirbdami su deque, kur n duomenų skaičius

|Funkcija                     |n = 10    |n = 100     |n = 1000    |n = 10000   |n = 100000 |
|-----------------------------|----------|------------|------------|------------|-----------|
|Duomenų nuskaitymas iš failo |0 s|0.003007 s|0.0230613 s |0.229609  s|2.42745  s|
|Duomenų išrikiavimas (skirstant)|0        s|0         s|0 s |0.0070187 s|0.067179 s|
|Duomenų išrikiavimas (trinant)  |0        s|0.0005         s|0.03 s |3 s|301 s|

### Išvados:
Jei duomenų skaičius nėra didelis konteinerių sparta yra apyligė, tačiau, kai n >= 100000, pradeda matytis, jog deque yra sparčiausias, jei duomenis skirstome į naujus masyvus. Duomenis skirstant ištrinant netinkamus duomenis iš masyvo, matome aiškų list pranašumą. (Reiktų atsižvelgti, jog list atveju buvo naudojama erase funkcija, o su kitais konteineriais remove).

## Algoritmų analizė
Vietoje remove pritaikius algoritmą ```koleg.erase(std::remove_if(koleg.begin(), koleg.end(), RibaV), koleg.end());``` vektoriui koleg, duomenų išrikiavimo trinant laikas sumažėjo nuo 628 s iki 0.0922454 s. Tokiu būdu vektorius gali laisvai konkuruoti su iki šiol pirmavusiu list.


## Versijų istorija (changelog)

### [Changelog v1.0 (2018-03-22)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v1.0)
#### Pridėta
- Laikas išmatuotas abiejais darbo su konteineriais būdais (perkeliant ir trinant). Atsakymai įrašyti į ReadMe Failą.
- Panaudota STL funkcija std::remove_if ir išmatuotas laikas elementus trinant pagal ją. Rezultatai aprašyti ReadMe.
#### Ištrinta
- Panaikintos compiliatoriaus šiukšlės.

### [Changelog v0.5.1 (2018-03-15)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.5.1) (Naujausia versija)
#### Pridėta
- Sukurtas wiki, į kurį iš ReadMe perkelta versijų istorija.
- ReadMe sukurta nuorodą į pilną versijų istoriją esančia wikije.
- Į ReadMe įrašyti veikimo spartos analizės rezultatai.
#### Pakeista
- Atnaujintas programos įsidiegimo vadovas ReadMe faile.
- Vietoje išvedimo nuotraukos naudojamas tekstas.
- Atnaujintas žodžių lietus.
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



# Augustino Makevičiaus objektinio programavimo 2 užduotis. (VU ISI 1 kursas)
# ![Žemėlapis](WordItOut.png)
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

- `git clone https://github.com/AugustinasMKVU/OOP-Task-2.git`
- `cd OOP-Task-2/uzd2/cpp`
- `g++ -std=c++11 *.cpp  -o main`
- `./main`

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
Vietoje remove pritaikius algoritmą ```koleg.erase(std::remove_if(koleg.begin(), koleg.end(), RibaV), koleg.end());``` vektoriui koleg, duomenų išrikiavimo trinant laikas sumažėjo nuo 628 s iki 0.0922454 s. Tokiu būdu vektorius gali laisvai konkuruoti su iki šiol pirmavusiu list. Reikia atsi=velgti ir į tai, kad kai kurių testų duomenys gali būti palankūs algoritmui, pvz. dydžioji dalis mokinių nėra galvočiai.



## Versijų istorija (changelog)
### [Changelog v0.5.1 (2018-03-15)](https://github.com/AugustinasMKVU/OOP-Task-2/tree/v0.5.1) (Naujausia versija)
#### Pridėta
- Sukurtas wiki, į kurį iš ReadMe perkelta versijų istorija.
- ReadMe sukurta nuorodą į pilną versijų istoriją esančia wikije.
- Į ReadMe įrašyti veikimo spartos analizės rezultatai.
#### Pakeista
- Atnaujintas programos įsidiegimo vadovas ReadMe faile.
- Vietoje išvedimo nuotraukos naudojamas tekstas.
- Atnaujintas žodžių lietus.
### [Pilna versijų istorijos versija](https://github.com/AugustinasMKVU/OOP-Task-2/wiki/Changelog)

## Naudingos nuorodos
[Atsitiktinių skaičių generavimas C++ 11](https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful)


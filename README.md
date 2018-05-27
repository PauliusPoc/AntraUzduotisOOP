
# Augustino Makevičiaus objektinio programavimo 3 užduotis. (VU ISI 1 kursas)

## Programos tiklas
Patobulinkite 2-ojo darbo realizaciją:
- Vietoj Studentas (StudentoInfo) structūros atsižvelgdami į Jūsų pačių atliktą antrą užduotį susikurkite Studentas (StudentoInfo) class'ę.

## Dokumentacija
Norėdami peržiūrėti dokumentaciją, nusiklonuokite repozitoriją, eikite į aplanką Doxygen ir atsidarykite index.html .

## Programos instaliacija
```git clone https://github.com/AugustinasMKVU/AntraUzduotisOOP.git```

```cd AntraUzduotisOOP/AntraUzduotis/```

```mkdir build && cd build```

1. Normali programos realizacija:

    ```cmake .. -G "MinGW Makefiles"```
    
2. Google Test

    ```cp ../test.txt test.txt```
    
    ```cmake .. -DSTART_GTEST=ON -G "MinGW Makefiles"```

```mingw32-make```

```./AntraUzduotis.exe```

## Spartos analizė
### Rezultatai
#### Pirma lentelė - std::vector, antra - Strong Vector.

1. Debug konfiguracija

|Duomenu kiekis                    |Duomenu nuskaitymas|Rusiavimas    |
|----------------------------------|-------------------|--------------|
| n = 10 ^ 1 | 0.0015072 s. | 0 s. |
| n = 10 ^ 2 | 0.0035006 s. | 0 s. |
| n = 10 ^ 3 | 0.0240169 s. | 0.000533 s. |
| n = 10 ^ 4 | 0.213566 s. | 0.0065173 s. |
| n = 10 ^ 5 | 2.12124 s. | 0.0651472 s. |

|Duomenu kiekis                    |Duomenu nuskaitymas|Rusiavimas    |
|----------------------------------|-------------------|--------------|
| n = 10 ^ 1 | 0.0010213 s. | 0 s. |
| n = 10 ^ 2 | 0.0030211 s. | 0 s. |
| n = 10 ^ 3 | 0.0230593 s. | 0.0010047 s. |
| n = 10 ^ 4 | 0.213566 s. | 0.012032 s. |
| n = 10 ^ 5 | 2.10259 s. | 0.115338 s. |



2. Release konfiguracija nenurodant optimatizavimo flag'o

|Duomenu kiekis                    |Duomenu nuskaitymas|Rusiavimas    |
|----------------------------------|-------------------|--------------|
| n = 10 ^ 1 | 0.0010026 s. | 0 s. |
| n = 10 ^ 2 | 0.0040197 s. | 0 s. |
| n = 10 ^ 3 | 0.021056 s. | 0 s. |
| n = 10 ^ 4 | 0.204623 s. | 0.001504 s. |
| n = 10 ^ 5 | 2.0743 s. | 0.0195484 s. |

|Duomenu kiekis                    |Duomenu nuskaitymas|Rusiavimas    |
|----------------------------------|-------------------|--------------|
| n = 10 ^ 1 | 0.0010022 s. | 0 s. |
| n = 10 ^ 2 | 0.0030096 s. | 0 s. |
| n = 10 ^ 3 | 0.0200537 s. | 0 s. |
| n = 10 ^ 4 | 0.197527 s. | 0.003008 s. |
| n = 10 ^ 5 | 1.99733 s. | 0.0340906 s. |

### Išvada
Tinkamai implementavus klasę, sparta šiek tiek padidėjo, bet visumoje išliko tokia pati. Tai reiškia, kad naudodamas klases programuotojas negauna daug spartos ( taip pat ir nepraranda), tačiau kodo rašymas tampa malonesnis.

## Versijų istorija (changelog)

### [Changerlog v1.0 (2018-05-27)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/tree/v1.0)
#### Pridėta
- Implementuotas custom vektorius, veikiantis su su Studento tipo objektais
- Parašyti unit testai naudojantis [google_test](https://github.com/google/googletest) biblioteka.
- Sukurta papildoma konfigūracija testavimui
- Sukurta instaliacijos instrukcija.
#### Pakeista
- Atnaujinta spartos analizė.
#### Pašalinta
- Išrtinti nereikalingi failai


### [Changelog v0.2.1 (2018-05-09)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/tree/v0.2.1)
#### Pridėta 
- Operatoriai <=. >=
- Laiko matavimo klasė Timer
- Release konfiguracija

### [Changelog v0.2 (2018-04-29)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/tree/v0.2)
#### Pridėta
- Sukurta Doxygen dokumentacija
- Aprašyti operatoriai <, >, ==, !=.
#### Pakeista
- Vietoj operatoriaus >> naudojamas konstruktoriu su input stream'o parametru.
- Studentus pradėta rūšiuoti pagal galutinį balą.
#### Pašalinta
- Studentų lyginimo funkcijos ištrintos. Jas pakeitė operatoriai.

### [Changelog v0.1.1 (2018-04-20)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/tree/v0.1.1)
#### Pridėta
- Implementuotas << operatorius Studentas klasėje
#### Pakeista
Pataisyta loginė klaida rūšiavimo funkcijoje.

### [Changelog v0.1 (2018-04-20)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/tree/v0.1)
#### Pridėta
- Vietoj Kolega structūros sukurta Studentas class'ė
- Palyginta abiejų Jūsų programų, naudojančios struct iš ankstesniojo darbos ir naudojančios class tipo Studentus iš dabartinės realizacijos, spartą.
- Atlikta eksperimentinė analizė priklausomai nuo kompiliatoriaus optimizavimo lygio, nurodomo per flag'us: O1, O2, O3 ir papildytas README.md failas gautais rezultatais su optimizavimo flag'ais.
#### Pakeista
- Daugelis funkcijų perrašytos spartos tikslams:
- - Pradėta naudoti std::stable_partition
- - Apsisaugota nuo memory  leak'ų, darbe su failais.
#### Pašalinta
- Panaikinta galimybė dirbti su konsole.
- Panaikinta galimybė dirbti su std::list ir sd::deque.

## [Antrosios užduoties aprašymas](https://github.com/AugustinasMKVU/AntraUzduotisOOP/wiki/Antrosios-u%C5%BEduoties-apra%C5%A1ymas)

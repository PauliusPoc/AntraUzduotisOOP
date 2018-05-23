
# Augustino Makevičiaus objektinio programavimo 3 užduotis. (VU ISI 1 kursas)

## Programos tiklas
Patobulinkite 2-ojo darbo realizaciją:
- Vietoj Studentas (StudentoInfo) structūros atsižvelgdami į Jūsų pačių atliktą antrą užduotį susikurkite Studentas (StudentoInfo) class'ę.

## Dokumentacija
Norėdami peržiūrėti dokumentaciją, nusiklonuokite repozitoriją, eikite į aplanką Doxygen ir atsidarykite index.html .

## Spartos analizė
### Rezultatai
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
| n = 10 ^ 1 | 0.0025086 s. | 0.0010034 s. |
| n = 10 ^ 2 | 0.0085191 s. | 0.0014961 s. |
| n = 10 ^ 3 | 0.101254 s. | 0.0160738 s. |
| n = 10 ^ 4 | 1.0528 s. | 0.160998 s. |
| n = 10 ^ 5 | 10.5791 s. | 1.30318 s. |


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
| n = 10 ^ 1 | 0.0025071 s. | 0.0015715 s. |
| n = 10 ^ 2 | 0.0095253 s. | 0.0015068 s. |
| n = 10 ^ 3 | 0.0987629 s. | 0.013553 s. |
| n = 10 ^ 4 | 1.02123 s. | 0.115808 s. |
| n = 10 ^ 5 | 10.2926 s. | 1.34207 s. |

### Išvada
Tinkamai implementavus klasę, sparta šiek tiek padidėjo, bet visumoje išliko tokia pati. Tai reiškia, kad naudodamas klases programuotojas negauna daug spartos ( taip pat ir nepraranda), tačiau kodo rašymas tampa malonesnis.

## Versijų istorija (changelog)

### Changelog v0.2.i (2018-05-09)
#### Pridėta 
- Operatoriai <=. >=
- Laiko matavimo klasė Timer
- Release konfiguracija

### [Changelog v0.2 (2018-04-29)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/releases/tag/v0.2)
#### Pridėta
- Sukurta Doxygen dokumentacija
- Aprašyti operatoriai <, >, ==, !=.
#### Pakeista
- Vietoj operatoriaus >> naudojamas konstruktoriu su input stream'o parametru.
- Studentus pradėta rūšiuoti pagal galutinį balą.
#### Pašalinta
- Studentų lyginimo funkcijos ištrintos. Jas pakeitė operatoriai.

### [Changelog v0.1.1 (2018-04-20)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/releases/tag/v0.1.1)
#### Pridėta
- Implementuotas << operatorius Studentas klasėje
#### Pakeista
Pataisyta loginė klaida rūšiavimo funkcijoje.

### [Changelog v0.1 (2018-04-20)](https://github.com/AugustinasMKVU/AntraUzduotisOOP/releases/tag/v0.1)
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

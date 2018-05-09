
# Augustino Makevičiaus objektinio programavimo 3 užduotis. (VU ISI 1 kursas)

## Programos tiklas
Patobulinkite 2-ojo darbo realizaciją:
- Vietoj Studentas (StudentoInfo) structūros atsižvelgdami į Jūsų pačių atliktą antrą užduotį susikurkite Studentas (StudentoInfo) class'ę.

## Dokumentacija
Norėdami peržiūrėti dokumentaciją, nusiklonuokite repozitoriją, eikite į aplanką Doxygen ir atsidarykite index.html .

## Spartos analizė
### Rezultatai
Neoptimatizuota
### ![O0](https://github.com/AugustinasMKVU/AntraUzduotisOOP/blob/master/Performance%20Results/O0.png)
Optimatizuota naudojant O1
### ![O1](https://github.com/AugustinasMKVU/AntraUzduotisOOP/blob/master/Performance%20Results/O1.png)
Optimatizuota naudojant O2
### ![O2](https://github.com/AugustinasMKVU/AntraUzduotisOOP/blob/master/Performance%20Results/O2.png)
Optimatizuota naudojant O2
### ![O3](https://github.com/AugustinasMKVU/AntraUzduotisOOP/blob/master/Performance%20Results/O3.png)
### Išvada
Matome, kad tinkamai realizavus klasę, sparta ne tik išliko tokia pat, bet pasitelkus papildomus algoritmus sparta net padidėjo.
Pastebėta, kad tinkamai realizavus klasę, naudojant optimatizavimo flag'us didelio skirtumo nesusidaro (skirtumas sekundės dalyse).
Vadinasi, jei programuotojas tinkamai implementuoja klasę, t.y. naudoja inline funkcijas, nekuria memory leak'ų implementacijos sparta prilygsta ```O3``` optimatizacijos lygiui.


## Versijų istorija (changelog)

### Changelog v0.2.1 (2018-05-09)
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

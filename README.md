# Augustino Makevičiaus objektinio programavimo 2 užduotis. (VU ISI 1 kursas)
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

## Versijų istorija (changelog)

### Changelog v0.1 (2018-02-13)
#### Pridėta
- Programoje leidžiama pasirinkti atsitiktinių pažymių generavimą naudojant **mt19937** generatorių.
- Programoje leidžiama pasirnkti, jog vietoje vidurkio, galutinį balą skaičiuotų pagal pažymių medianą.
- Sukurtos funkcijos:
  - ```void ByHand ```
  - ```void Auto```
  - ```double PagalMediana```
  - ```double PagalVidurki```
#### Pakeista
- Pažymių įrašymo ranka kodas perkeltas į funkciją ```ByHand```.
- Galutinio balo skaičiavimo pagal vidurkį kodas perkeltas į funkciją ```PagalVidurki```
- Pažymių vektorius pakeistas iš ```vector<double>``` į ```vector<int>```
#### Pašalinta
- Iš funkcijos ```main``` ištrinti galutinio balo skaičiavimo pagal vidurkį ir pažymių įrašymo ranka kodai.

## Naudingos nuorodos
[Atsitiktinių skaičių generavimas C++ 11](https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful)


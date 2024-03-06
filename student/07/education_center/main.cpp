/* Kansalaisopisto
 *
 * Kuvaus:
 *   Ohjelma lukee tiedostosta eri paikkakuntien kurssitarjonnan teemoittain.
 *   Käyttäjä voi tutkia kurssitarjontaa eri komentojen avulla
 * Ohjelman komennot:
 * "locations"
 *  --tarkistaa millä paikkakunnilla tarjontaa on
 * "themes in location <paikkakunta>"
 *  --ottaa selvää minkä eri teeman kursseja on tarjolla halutulla paikkakunnalla
 * "courses <paikkakunta><teema>"
 *  --tulostaa tiedon tietyn paikkakunnan ja teeman kaikista kursseista osallistujamäärineen
 * "available"
 *  --tulostaa tiedon kaikkien paikkakuntien kursseista joilla on tilaa (alle 50 ihmistä)
 * "courses_in_theme <teema>"
 *  --tulostaa listan tietyn teeman kursseista kaikilla paikkakunnilla
 * "favorite_theme"
 *  --tulostaa tiedon suosituimmasta teemasta ja sen kokonaisosallistujamäärästä kaikilla paikkakunnilla
 * "quit"
 *  --lopettaa ohjelman suorituksen
 *
 * Ohjelman kirjoittaja
 * Nimi: Sara Nurminen
 * Opiskelijanumero: 50224946
 * Käyttäjätunnus: vhsanu
 * E-Mail: sara.nurminen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * -ohjelma keskeytyy jos luettava tiedosto on tyhjä
 *
 * */
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Kurssi {
    string nimi;
    string teema;
    int osallistujat;
};


int main() {
    string tiedoston_nimi = "";
    cout<< "Input file: " <<endl;
    getline(cin, tiedoston_nimi);


    /// Rakenne, johon kurssitarjotin tallennetaan
    map<string, map<string, map<Kurssi, int>>> kurssitarjotin;

    ifstream tiedosto(tiedoston_nimi);
    if (not tiedosto) {
        cout << " Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    } else {

        string rivi;
        while (getline(tiedosto, rivi)) {
            if (!getline(tiedosto, rivi)){
                cout << "Error: empty field" << endl;
                return EXIT_FAILURE;
            }
            stringstream ss(rivi);
            string paikkakunta;
            string teema;
            string nimi;
            int osallistujien_maara;
            getline(ss, paikkakunta, ';');
            getline(ss, teema, ';');
            getline(ss, nimi, ';');
            ss >> osallistujien_maara;

            Kurssi kurssi{nimi, teema, osallistujien_maara};

            kurssitarjotin[paikkakunta][teema][kurssi] = osallistujien_maara;
            ;
        }
        tiedosto.close();
    }




    return 0;
}

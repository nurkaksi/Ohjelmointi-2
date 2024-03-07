/* Kansalaisopisto
 *
 * Kuvaus:
 *   Ohjelma lukee tiedostosta eri paikkakuntien kurssitarjonnan teemoittain.
 *   Käyttäjä voi tutkia kurssitarjontaa eri komentojen avulla
 *
 * Ohjelman komennot:
 * "locations"
 *      --tarkistaa millä paikkakunnilla tarjontaa on
 * "themes in location <paikkakunta>"
 *      --ottaa selvää minkä eri teeman kursseja on tarjolla halutulla paikkakunnalla
 * "courses <paikkakunta><teema>"
 *      --tulostaa tiedon tietyn paikkakunnan ja teeman kaikista kursseista osallistujamäärineen
 * "available"
 *      --tulostaa tiedon kaikkien paikkakuntien kursseista joilla on tilaa (alle 50 ihmistä)
 * "courses_in_theme <teema>"
 *      --tulostaa listan tietyn teeman kursseista kaikilla paikkakunnilla
 * "favorite_theme"
 *      --tulostaa tiedon suosituimmasta teemasta ja sen kokonaisosallistujamäärästä kaikilla paikkakunnilla
 * "quit"
 *      --lopettaa ohjelman suorituksen
 *
 * Ohjelman kirjoittajat
 * Nimi: Sara Nurminen
 * Opiskelijanumero: 50224946
 * Käyttäjätunnus: vhsanu
 * E-Mail: sara.nurminen@tuni.fi
 *
 * Nimi: Tiia Jaskari
 * Opiskelijanumero: 151441822
 * Käyttäjätunnus: sftija
 * E-Mail: tiia.jaskari@tuni.fi
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
#include <algorithm>
#include <set>

using namespace std;



struct Kurssi {
    string nimi;
    string teema;
    int osallistujat;

    // Vertailuoperaattori
    bool operator<(const Kurssi& other) const {
        // Järjestetään kurssit nimen mukaan aakkosjärjestyksessä
        if (nimi != other.nimi) {
            return nimi < other.nimi;
        }
        // Jos nimet ovat samat, järjestetään teeman mukaan
        if (teema != other.teema) {
            return teema < other.teema;
        }
        // Jos myös teemat ovat samat, järjestetään osallistujamäärän mukaan
        return osallistujat < other.osallistujat;
    }
};



/// split-funktio otettu sellaisenaan tehtävän 6.1.2 koodipohjasta
vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}



int main() {

    map<string, map<string, map<Kurssi, int>>> kurssitarjotin;

    /// Tiedoston lukeminen
    ///
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto(tiedoston_nimi);
    if (!tiedosto) {
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    // jaetaan rivi osiin stringstreamin avulla
    string rivi;
    while (getline(tiedosto, rivi)) {
        stringstream ss(rivi);
        string paikkakunta;
        string teema;
        string nimi;
        string osallistujien_maara_str;
        int osallistujien_maara = 0;

        // Erotetaan rivin osat puolipisteellä
        getline(ss, paikkakunta, ';');
        getline(ss, teema, ';');
        getline(ss, nimi, ';');
        getline(ss, osallistujien_maara_str, ';');

        // Tarkistetaan, että riviltä löytyy kaikki tarvittavat neljä tietoa
        if (paikkakunta.empty() || teema.empty() || nimi.empty() || osallistujien_maara_str.empty()) {
            cout << "Error: empty field" << endl;
            return EXIT_FAILURE;
        }

        // Muunnetaan osallistujien määrä kokonaisluvuksi
        // Jos määrä on "full" laitetaan sen tilalle 50
        if (osallistujien_maara_str == "full")
        {
            osallistujien_maara = 50;
        }
        else
        {
            osallistujien_maara = stoi(osallistujien_maara_str);
        }

        // Tallennetaan rivin tiedot ensin kurssiin, sitten kurssitarjottimeen
        Kurssi kurssi{nimi, teema, osallistujien_maara};
        kurssitarjotin[paikkakunta][teema][kurssi] = osallistujien_maara;
    }



    /// Tähän tulee käyttöliittymä
    while(true) {
        string komento;
        cout << "> ";
        getline(cin, komento);

        // JOs komennon jälkeen on tekstiä, tallennetaan se stringiksi
        string komento2 = "";
        size_t space_position = komento.find(" ");
        if (space_position != string::npos)
        {
            komento2 = komento.substr(space_position + 1);
            komento = komento.substr(0, space_position);
        }
        if ( komento == "quit" )
        {
            return EXIT_SUCCESS;
        }
        else if ( komento == "locations" && komento2 == "" )
        {
             tulosta_paikkakunnat(kurssitarjotin);
        }
        else if ( komento == "themes_in_location" )
        {
            if (komento2.empty()) {
                cout << "Error: missing location" << endl;
            } else {
                paikkakunta_teemat(kurssitarjotin, komento2);
            }
        }

        else if ( komento == "courses" )
        {
            vector<string> parts = split(komento2, ' ');
            if (parts.size() != 2) {
                cout << "Error: error in command courses" << endl;
            } else {
                // tarkistetaan onko lainausmerkit ja poistetaan ne tarvittaessa
                if (parts[1].front() == '"' && parts[1].back() == '"') {
                    parts[1] = parts[1].substr(1, parts[1].size() - 2);
                }
                kurssit_paikka_ja_teema(kurssitarjotin, parts[0], parts[1]);
            }
        }

        else if ( komento == "available" && komento2 == "")
        {
            vapaat_kurssit(kurssitarjotin);
        }
        else if ( komento == "courses_in_theme" )
        {
            teema_kurssit(kurssitarjotin, komento2);
        }

        else if ( komento == "favorite_theme" && komento2 == "")
        {
            suosikkiteema(kurssitarjotin);
        }

        else
        {
            cout << "Error: Unknown command: " << komento << endl;
        }

    }

    tiedosto.close();

    return 0;
}

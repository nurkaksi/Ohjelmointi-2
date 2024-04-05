/**
 * HOSPITAL
 *
 * Tämä ohjelma on sairaalajärjestelmä, jossa potilaita otetaan vastaan ja kotiutetaan
ja henkilökuntaa rekrytoidaan ja lisätään potilaiden hoitojaksoihin.
Potilaat voivat tulla ja lähteä hoitojaksolta useita kertoja.
Potilaat voivat saada lääkkeitä tai niitä voidaan poistaa heiltä.

Saatavilla olevat komennot ovat:
  - HELP H: Tulostaa kaikki saatavilla olevat komennot
  - RECRUIT R: Rekrytoi henkilökunnan jäsen (tarvitsee nimen komennon perään)
  - ENTER E: Kirjaa potilas hoitojaksolle (tarvitsee nimen komennon perään)
  - LEAVE L: Kirjaa potilas ulos ja sulkee hoitojakson (tarvitsee potilaan nimen komennon perään)
  - ASSIGN_STAFF AS: Määritä henkilökunta potilaan hoitojaksolle (tarvitsee henkilökunnan nimen ja potilaan nimen)
  - ADD_MEDICINE AM: Lisää lääke potilaalle (tarvitsee lääkkeen nimen, vahvuuden, annoksen ja potilaan nimen)
  - REMOVE_MEDICINE RM: Poista lääke potilaalta (tarvitsee lääkkeen nimen ja potilaan nimen)
  - PRINT_PATIENT_INFO PPI: Tulostaa yhden potilaan hoitojaksot, henkilökunnan ja lääkkeet (tarvitsee potilaan nimen)
  - PRINT_CARE_PERIODS PCPS: Tulostaa hoitojaksot ja potilaat, joissa henkilökunta on (tarvitsee henkilökunnan nimen)
  - PRINT_ALL_MEDICINES PAM: Tulosta kaikki lääkkeet ja kenelle niitä on määrätty
  - PRINT_ALL_STAFF PAS:
  - PRINT_ALL_PATIENTS PAP: Tulosta kaikki sairaalassa olleet potilaat, heidän hoitojaksonsa, henkilökunta ja lääkkeet
  - PRINT_CURRENT_PATIENTS PCP: Tulosta tiedot potilaista, jotka ovat tällä hetkellä sairaalassa, heidän avoimesta hoitojaksostaan, henkilökunnasta ja lääkkeistä
  - SET_DATE SD: Aseta uusi päivämäärä (tarvitsee päivän, kuukauden ja vuoden)
  - ADVANCE_DATE: Siirrä päivämäärää eteenpäin (tarvitsee numeron, kuinka monta päivää mennään eteenpäin)
  - READ_FROM RF: Lue tiedosto (tarvitsee tiedoston nimen)
  - QUIT Q: Lopeta ohjelma
 *
 * Program author
 * Name: Sara Nurminen
 * Student ID: 50224946
 * Username: vhsanu
 * E-Mail: sara.nurminen@tuni.fi
 * */
#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}

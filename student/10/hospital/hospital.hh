/* Class Hospital
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a hospital. Only a single object created from this
 * class. Implements all commands in hospital program.
 *
 * Note: Students need change this class to implement commands missing
 * in the template code.
 * */
#ifndef HOSPITAL_HH
#define HOSPITAL_HH

#include "person.hh"
#include "careperiod.hh"
#include "date.hh"
#include <map>

// Virhe- ja tiedostotulosteet
const std::string ALREADY_EXISTS = "Virhe: Jo olemassa: ";
const std::string NOT_NUMERIC = "Virhe: Väärä parametrien tyyppi.";
const std::string CANT_FIND = "Virhe: Ei löydy mitään vastaavaa: ";
const std::string STAFF_RECRUITED = "Uusi henkilökunnan jäsen on rekrytoitu.";
const std::string PATIENT_ENTERED = "Uusi potilas on saapunut.";
const std::string PATIENT_LEFT = "Potilas poistui sairaalasta, hoitojakso suljettu.";
const std::string MEDICINE_ADDED= "Lääke lisätty kohteelle: ";
const std::string MEDICINE_REMOVED= "Lääke poistettu kohteelta: ";
const std::string STAFF_ASSIGNED= "Henkilökunta määritetty kohteelle: ";

using Params = const std::vector<std::string>&;

class Hospital
{
public:
    /**
     * @brief Hospital
     */
    Hospital();

    /**
      * @brief destructor
      */
    ~Hospital();


    /**
     * @brief set_date
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     */
    void set_date(Params params);

    /**
     * @brief advance_date
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Siirtää nykyistä päivämäärää annetun päivien määrän verran eteenpäin.
     */
    void advance_date(Params params);

    /**
     * @brief recruit
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Rekrytoi uuden henkilökunnan jäsenen (luo uuden Person-olion)
     */
    void recruit(Params params);

    /**
     * @brief print_all_staff
     */
    void print_all_staff(Params);

    /**
     * @brief add_medicine
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Lisää annetun lääkkeen (nimi, vahvuus, annostus) annetulle potilaalle.
     * Jos annetulla potilaalla on jo lääke,
     * määräys (vahvuus, annostus) saattaa muuttua.
     * Jos annetulla potilaalla on jo sama määräys samasta lääkkeestä,
     * mitään ei tapahdu.
     */
    void add_medicine(Params params);

    /**
     * @brief remove_medicine
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Poistaa annetun lääkkeen potilaalta.
     * Jos potilaalla ei ole lääkettä, mitään ei tapahdu.
     */
    void remove_medicine(Params params);

    /**
     * @brief enter
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Lisää potilaan sairaalaan ja luo uuden hoitojakson.
     * Jos parametrina annettu henkilö ei ole aiemmin vieraillut sairaalassa,
     * luo uuden henkilöolion, muussa tapauksessa lisää olemassa olevan henkilön
     * vasta luotuun hoitojaksoon.
     */
    void enter(Params params);

    /**
     * @brief leave
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Poistaa parametrina annetun henkilön sairaalasta ja sulkee
     * henkilön hoitojakson. Hoitojakso kuitenkin edelleen olemassa.
     */
    void leave(Params params);

    /**
     * @brief assign_staff
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Määrittää annetun henkilökunnan jäsenen annetulle potilaalle.
     * Jos potilaalla on jo henkilökunnan jäsen määritettynä
     * (nykyisessä hoitojaksossa), mitään ei tapahdu.
     */
    void assign_staff(Params params);

    /**
     * @brief print_patient_info
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Tulostaa annetun potilaan kaikki hoitojaksot ja niiden nykyiset lääkkeet,
     * eli ne, jotka on lisätty mutta ei poistettu.
     */
    void print_patient_info(Params params);

    /**
     * @brief print_care_periods
     * @param params vektori, joka sisältää vastaavan komennon parametrit
     * Tulostaa annetun henkilökunnan jäsenen hoitojaksot eli ne,
     * joissa annettu henkilökunnan jäsen on työskennellyt.
     */
    void print_care_periods(Params params);

    /**
     * @brief print_all_medicines
     * Tulostaa kaikki lääkkeet, joita on käytetty jonkin potilaan toimesta
     * jossain vaiheessa sairaalassa käydessään, eli nykyisten ja aiempien potilaiden lääkkeet.
     */
    void print_all_medicines(Params);

    /**
     * @brief print_all_patients
     * Tulostaa kaikki sairaalassa käyneet potilaat jossain vaiheessa,
     * eli kaikki nykyiset ja aiemmat potilaat.
     * Tarkemmin sanottuna tulostaa jokaisen potilaan id:n ja potilastiedot
     * (samassa muodossa kuin metodin print_patient_info tiedot).
     */
    void print_all_patients(Params);

    /**
     * @brief print_current_patients
     * Tulostaa kaikki tällä hetkellä sairaalassa olevat potilaat.
     * Tarkemmin sanottuna tulostaa jokaisen potilaan id:n ja potilastiedot
     * (samassa muodossa kuin metodin print_patient_info tiedot).
     */
    void print_current_patients(Params);


private:
    std::map<std::string, Person*> all_patients_;
    std::map<std::string, Person*> current_patients_;
    std::map<std::string, Person*> staff_;
    std::vector<CarePeriod*> care_periods_;

    /**
     * @brief get_period_based_on_patient
     * @param patient_id
     * @return care_period
     * Finds the patients open careperiod
     */
    CarePeriod* get_open_period(std::string patient_id);

    /**
     * @brief get_patients_periods
     * @param patient_id
     * @return vector of care periods
     * Finds all the care periods a patient has been in
     * and saves them in a vector
     */
    std::vector<CarePeriod*> get_patients_periods(std::string patient_id);


    /**
     * @brief medicines_
     * @return medicines
     */
    std::map<std::string, std::vector<std::string>> medicines_();
    };

#endif // HOSPITAL_HH






/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    /**
      * @brief CarePeriod
      * @param alkamispäivämäärä stringinä (ddmmyyyy)
      * @param potilas jolle luodaan hoitojakso
      */
    CarePeriod(const std::string& start, Person* patient);

    /**
      * @brief CarePeriod
      * @param alkamispäivämäärä annettu date-oliona
      * @param potilas jolle hoitojakso luodaan
      */
    CarePeriod(const Date& start, Person* patient);

    /**
      * @brief destructor
      */
    ~CarePeriod();

    /**
     * @brief add_staff
     * @param staff_id
     * @param henkilökunta
     * Lisää henkilökuntaa hoitojaksoon
     */
    void add_staff(std::string staff_id, Person* staff);

    // is_staff(Person* staff) onko joku tietty henkilö työskennellyt täällä

    /**
     * @brief set_end_date
     * @param end
     * Aseta loppumispäivä kun potilas lähtee
     */
    void set_end_date(const Date& end);

    /**
     * @brief get_patient
     * @return potilas
     */
    Person *get_patient();

    /**
     * @brief get_care_period_start_time
     * @return hoitojakson alkamispäivä
     */
    Date get_care_period_start_time();

    /**
     * @brief get_care_period_end_time
     * @return hoitojakson päättymispäivä
     */
    Date get_care_period_end_time();

    /**
     * @brief get_staff_
     * @return potilaan henkilökunta
     */
    std::map<std::string, Person*> get_staff_();

    /**
     * @brief print_dates
     * Tulostaa hoitojakson päivämäärät
     */
    void print_dates();


private:
    Person* patient_;
    Date start_;
    Date end_;

    std::map<std::string, Person*> staff_;

};

#endif // CAREPERIOD_HH

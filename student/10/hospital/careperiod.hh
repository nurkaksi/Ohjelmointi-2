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
      * @param start date given as a string (ddmmyyyy)
      * @param patient whose care period will be created
      */
    CarePeriod(const std::string& start, Person* patient);

    /**
      * @brief CarePeriod
      * @param start date given as a Date object
      * @param patient whose care period will be created
      */
    CarePeriod(const Date& start, Person* patient);

    /**
      * @brief destructor
      */
    ~CarePeriod();

    /**
     * @brief add_staff
     * @param staff_id
     * @param staff
     * Adds staff to careperiod
     */
    void add_staff(std::string staff_id, Person* staff);

    // is_staff(Person* staff) onko joku tietty henkilö työskennellyt täällä

    /**
     * @brief set_end_date
     * @param end
     * Set an end date to careperiod when patient leaves
     */
    void set_end_date(const Date& end);

    /**
     * @brief get_patient
     * @return patient
     */
    Person *get_patient();

    /**
     * @brief get_care_period_start_time
     * @return care period start time
     */
    Date get_care_period_start_time();

    /**
     * @brief get_care_period_end_time
     * @return care period ending time
     */
    Date get_care_period_end_time();

    /**
     * @brief get_staff_
     * @return patients staff
     */
    std::map<std::string, Person*> get_staff_();

    /**
     * @brief print_dates
     * Prints care periods dates
     */
    void print_dates();


private:
    Person* patient_;
    Date start_;
    Date end_;

    std::map<std::string, Person*> staff_;

};

#endif // CAREPERIOD_HH

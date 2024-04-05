#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);


        // Potilaalla on jo käynnissä oleva hoitojakso

        if ( this->current_patients_.find(patient_id) != this->current_patients_.end())
        {
            std::cout << "Error: Already exists: " << patient_id << std::endl;
            return;
        }

        // Tarkistetaan onko potilas jo ollut sairaalassa,
        // jos ei, niin soritetaan add

        if ( this->all_patients_.find(patient_id) == this->all_patients_.end())
        {
            this->all_patients_[patient_id] = new Person(patient_id);
        }

        // Lisätään henkilö current_patients tietoihin ja luodaan uusi hoitojakso
        Person* new_patient = this->all_patients_.find(patient_id)->second;
        this->current_patients_[patient_id] = new_patient;


        CarePeriod* care_period = new CarePeriod(utils::today, new_patient);
        this->care_periods_.push_back(care_period);

        std::cout << "A new patient has entered." << std::endl;

}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);

    // Potilasta ei löydy
    if ( this->current_patients_.find(patient_id) == this->current_patients_.end() )
    {
        std::cout << "Error: Can't find anything matching: " << patient_id
                  << std::endl;
        return;
    }

    // Asetetaan hoitojaksolle loppumispäivämäärä ja poistetaan
    // potilas current_patients tiedoista

    CarePeriod* care_period = get_open_period(patient_id);
    care_period->set_end_date(utils::today);

    this->current_patients_.erase(patient_id);

    std::cout << "Patient left hospital, care period closed." << std::endl;
}

void Hospital::assign_staff(Params params)
{

}

void Hospital::print_patient_info(Params params)
{

}

void Hospital::print_care_periods(Params params)
{

}

void Hospital::print_all_medicines(Params)
{

}

void Hospital::print_all_patients(Params)
{

}

void Hospital::print_current_patients(Params)
{

}


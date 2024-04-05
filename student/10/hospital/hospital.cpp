#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    //Deallocating staff map
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
        iter->second = nullptr;
    }

    // Deallocating all patients map

    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
        iter->second = nullptr;
    }

    for( auto
         iter = care_periods_.begin();
         iter != care_periods_.end();
         ++iter )
    {
        delete *iter;
        *iter = nullptr;
    }
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

    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    // Jos henkilökunnan jäsentä ei löydy
    if ( staff_.find(staff_id) == staff_.end() )
    {
        std::cout << "Error: Can't find anything matching: " << staff_id
                  << std::endl;
        return;
    }

    // Jos potilasta ei löydy
    if ( this->current_patients_.find(patient_id) == this->current_patients_.end() )
    {
        std::cout << "Error: Can't find anything matching: " << patient_id
                  << std::endl;
        return;
    }

    // Lisää henkilökuntaa hoitojaksolle
    CarePeriod* care_period = get_open_period(patient_id);
    care_period->add_staff(staff_id, staff_[staff_id]);

    std::cout << "Staff assigned for: " << patient_id << std::endl;
}


/// Tulostaa potilaan tiedot
void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);

    // Jos potilaan tietoja ei löydy (potilas
    // ei ole ollut sairaalassa)
    if ( this->all_patients_.find(patient_id) == this->all_patients_.end() )
    {
        std::cout << "Error: Can't find anything matching: " << patient_id
                  << std::endl;
        return;
    }

    // Tallennetaan hoitojaksot vektoriin ja tulostetaan
    std::vector<CarePeriod*> patient_periods = get_patients_periods(patient_id);

    for ( auto& period : patient_periods )
    {
        std::cout << "* Care period: ";
        period->print_dates();

        std::cout << "  - Staff:";
        if ( period->get_staff_().empty() )
        {
            std::cout << " None" << std::endl;
        }
        else
        {
            for ( auto& staff : period->get_staff_() )
            {
                std::cout << " " << staff.first;
            }
            std::cout << std::endl;
        }
    }

    std::cout << "* Medicines:";

    if ( patient_periods[0]->get_patient()->get_medicines().empty())
    {
        std::cout << " None" << std::endl;
    }
    else
    {
        for ( auto period : patient_periods )
        {
            period->get_patient()->print_medicines("  - ");
            break;
        }
    }
    return;
}

void Hospital::print_care_periods(Params params)
{
    bool found = false;
    std::string staff_id = params.at(0);

    // Henkilökunnan jäsentä ei löydy
    if ( this->staff_.find(staff_id) == this->staff_.end() )
    {
        std::cout << "Error: Can't find anything matching: " << staff_id
                  << std::endl;
        return;
    }

    // Tulostaa hoitojakson ja potilaan
    for ( auto period : care_periods_ )
    {
        if (period->get_staff_().find(staff_id) != period->get_staff_().end())
        {
            period->print_dates();
            std::cout << "* Patient: " << period->get_patient()->get_id()
                      << std::endl;
            found = true;
        }
    }

    // Jos henkilökunnan jäsenellä ei ole potilaita
    if ( !found )
    {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_medicines(Params)
{
    bool medicines_prescriped = false;

    // Lääkkeet ja potilaat tallennetaan map-tietorakenteeseen
    std::map<std::string, std::vector<std::string>> patients_medicines =
            medicines_();

    for ( auto& medicine : patients_medicines )
    {
         std::cout << medicine.first << " prescribed for" << std::endl;
         std::vector<std::string> patients = medicine.second;
         std::sort(patients.begin(), patients.end());

         for (const auto& patient : patients)
         {
             std::cout << "* " << patient << std::endl;
         }
         medicines_prescriped = true;
    }

    // Ei määrättyjä lääkkeitä
    if ( !medicines_prescriped )
    {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    // No one has been in the hospital
    if ( all_patients_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for ( auto& patient : this->all_patients_ )
    {
        std::vector<CarePeriod*> patient_periods =
                get_patients_periods(patient.second->get_id());

        std::cout << patient.second->get_id() << std::endl;
        for ( auto period : patient_periods )
        {
            std::cout << "* Care period: ";
            period->print_dates();

            std::cout << "  - Staff:";
            if ( period->get_staff_().empty())
            {
                std::cout << " None";
            }
            else
            {
            for ( auto& staff : period->get_staff_() )
                {
                    std::cout << " " << staff.first;
                }
            }
        std::cout << std::endl;
        }

    std::cout << "* Medicines:";
    patient.second->print_medicines("  - ");
    }
}

void Hospital::print_current_patients(Params)
{
    if ( this->current_patients_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for ( auto& patient : this->current_patients_ )
    {
        std::vector<CarePeriod*> patient_periods =
                get_patients_periods(patient.second->get_id());
        std::cout << patient.second->get_id() << std::endl;

        for ( auto care_period : patient_periods )
        {
            std::cout << "* Care period: ";
            care_period->print_dates();

            std::cout << "  - Staff:";
            if ( care_period->get_staff_().empty())
            {
                std::cout << " None";
            }
            else
            {
                for ( auto& staff : care_period->get_staff_() )
                {
                    std::cout << " " << staff.first;
                }
            }
            std::cout << std::endl;
            }

     std::cout << "* Medicines:";
     patient.second->print_medicines("  - ");
     }
}
std::vector<CarePeriod*> Hospital::get_patients_periods(std::string patient_id)
{
    std::vector<CarePeriod*> patients_care_periods;
    for ( auto period : this->care_periods_ )
    {
        if ( period->get_patient()->get_id() == patient_id )
        {
            patients_care_periods.push_back(period);
        }
    }
    return patients_care_periods;
}

CarePeriod *Hospital::get_open_period(std::string patient_id)
{
    for ( auto period : this->care_periods_ )
    {
        if ( period->get_patient()->get_id() == patient_id )
        {
            return period;
        }
    }
    return nullptr;
}

std::map<std::string, std::vector<std::string>> Hospital::medicines_()
{
    std::map<std::string, std::vector<std::string>> patients_medicines;
    for( auto& patients : all_patients_ )
    {
        std::vector<std::string> medicines = patients.second->get_medicines();
        for ( auto& medicine : medicines )
        {
            if ( patients_medicines.find(medicine) == patients_medicines.end() )
            {
                patients_medicines[medicine].push_back(patients.second->get_id());
            }
            else
            {
               patients_medicines.find(medicine)->second.push_back(patients.second->get_id());
            }
        }
    }
    return patients_medicines;
}



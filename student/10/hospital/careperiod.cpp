#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}


void CarePeriod::add_staff(std::string staff_id, Person* staff)
{
    this->staff_.insert(std::make_pair(staff_id,staff));
}

void CarePeriod::set_end_date(const Date &end)
{
    this->end_ = end;
}

Person *CarePeriod::get_patient()
{
    return this->patient_;
}

Date CarePeriod::get_care_period_start_time()
{
    return this->start_;
}

Date CarePeriod::get_care_period_end_time()
{
    return this->end_;
}

std::map<std::string, Person *> CarePeriod::get_staff_()
{
    return this->staff_;
}

void CarePeriod::print_dates()
{
    this->start_.print();
    std::cout << " -";

    if ( this->end_.is_default() )
    {
        std::cout << std::endl;
    }
    else
    {
        std::cout << " ";
        this->end_.print();
        std::cout << std::endl;
    }
}


#include "queue.hh"
#include <iostream>

using namespace std;

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle) :
    cycle_(cycle)
{

}

Queue::~Queue()
{

    while (first_ != nullptr)
    {
        Vehicle* temp = first_;
        first_ = first_->next;
        delete temp;
    }
    // first_ = nullptr;
    // last_ = nullptr;

}


void Queue::enqueue(const string &reg)
{
    // if the light is red adds the register number to the queue
    if ( !is_green_)
    {
        Vehicle* new_vehicle = new Vehicle();
        new_vehicle->reg_num = reg;
        new_vehicle->next = nullptr;

        // If no queue
        if ( first_ == nullptr )
        {
            first_ = new_vehicle;
            last_ = new_vehicle;
        }
        else
        {
            // Otherwise, update the last_ pointer and link the new vehicle
            // to the end of the queue
            last_->next = new_vehicle;
            last_ = new_vehicle;
        }
        ++count_;
    }
    else
    {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    }
}


void Queue::switch_light()
{
    if ( !is_green_)
    {
        is_green_ = true;
    }
    else
    {
        is_green_ = false;
    }
    print();

}


void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}



void Queue::print()
{
    if ( !is_green_)
    {
        if ( first_ != nullptr )
        {
            cout  << "RED: Vehicle(s) ";

            Vehicle* current = first_;
            while ( current != nullptr )
            {
                cout << current->reg_num << " ";
                current = current->next;
            }
        cout << "waiting in traffic lights" << endl;
        }
        else
        {
            cout << "RED: No vehicles waiting in traffic lights" << endl;
        }
    }
    else
    {
        if ( first_ != nullptr )
        {
            cout << "GREEN: Vehicle(s) ";
            // first 3 cars can go and switches the light to red if 3 goes.
            if ( count_ >= cycle_ )
            {
                for ( unsigned int i = 0; i < cycle_; ++i )
                {

                    if(first_ == nullptr)
                    {
                        break;
                    }
                    cout << first_->reg_num << " ";
                    Vehicle* temp = first_;
                    first_ = first_->next;
                    delete temp;
                    count_ -= 1;

                }
                cout << "can go on" << endl;
                is_green_ = false;
            }
            else
            {
                unsigned int loopCount = 0;
                for ( unsigned int i = 0; i < count_; ++i )
                {
                    if(first_ == nullptr)
                    {
                        break;
                    }
                    cout << first_->reg_num << " ";
                    Vehicle* temp = first_;
                    first_ = first_->next;
                    delete temp;
                    loopCount += 1;
                }
                count_ -= loopCount;
                cout << "can go on" << endl;
                is_green_ = false;
            }
        }
        else
        {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        }
    }


}

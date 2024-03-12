#include "cards.hh"

using namespace std;


Cards::Cards() :
    top_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data();

    new_card->data = id;
    new_card->next = top_;

    top_ = new_card;
}

void Cards::print_from_top_to_bottom(ostream &s)
{
    Card_data* current = top_;
    int current_num = 1;

    while ( current != nullptr )
    {
        s << current_num << ": " << current->data << endl;

        current = current->next;
        ++current_num;
    }
}

bool Cards::remove(int &id)
{
    // Pinossa ei kortteja
    if ( top_ == nullptr )
    {
        return false;
    }
    id = top_->data;
    Card_data* removable = top_;
    top_ = top_->next;
    delete removable;
    removable = nullptr;

    return true;
}

bool Cards::bottom_to_top()
{
    if (top_ == nullptr || top_->next == nullptr)
    {
        // Jos ei ole tarpeeksi kortteja, palauta false ja älä tee mitään
        return false;
    }
    // etsi  viimeinen kortti
    Card_data* movable = top_;
    while ( movable->next != nullptr )
    {
        movable = movable->next;
    }

    // etsi toisiksiviimeinen kortti
    Card_data* new_bottom = top_;
    while ( new_bottom->next != movable)
    {
        new_bottom = new_bottom->next;
    }
    // päivitä päällimmäinen kortti ja toisiksi viimeinen kortti viimeiseksi
    movable->next = top_;
    top_ = movable;
    new_bottom->next = nullptr;

    return true;
}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr || top_->next == nullptr)
    {
        // Jos ei ole tarpeeksi kortteja, palauta false ja älä tee mitään
        return false;
    }
    Card_data* movable = top_;

    Card_data* bottom = top_;
    while ( bottom->next != nullptr )
    {
        bottom = bottom->next;
    }

    // päivitä ylin ja alin kortti
    top_ = top_->next;
    bottom->next = movable;
    movable->next = nullptr;

    return true;
}

void Cards::print_from_bottom_to_top(ostream &s)
{
    recursive_print(top_,s);
}

Cards::~Cards()
{
    Card_data* current = top_;
    Card_data* others = nullptr;

    while ( current != nullptr )
    {
        others = current->next;
        delete current;
        current = others;
    }

    top_ = nullptr;
}

int Cards::recursive_print(Card_data *top, ostream &s)
{
     if ( top == nullptr )
     {
        return 0;
     }
     int num_printed = recursive_print(top->next, s);
    s << num_printed + 1 << ": " << top ->data << endl;
    return num_printed+1;
}


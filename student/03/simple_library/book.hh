#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"
using namespace std;

class Book
{
public:
    Book(const string writer, const string book_name);
    void print();
    void loan(Date the_day);
    void renew();
    void give_back();

private:
    string writer_;
    string book_name_;
    string loaned_;
    Date loan_date_;
    Date return_date_;

};

#endif // BOOK_HH

#include "book.hh"
#include <iostream>
#include "date.hh"


Book::Book(const string writer, const string book_name):
    writer_(writer), book_name_(book_name), loaned_("no")
{
}
    void Book::print() {
        cout << writer_ << " : " << book_name_ << endl;
        if ( loaned_ == "no" ) {
            cout << "- available" << endl;
        } else {
            cout << "- loaned: ";
            loan_date_.print();
            cout << "- to be returned: ";
            return_date_.print();
        }
    }

    void Book::loan(Date the_day) {
        if (loaned_ == "yes" ) {
            cout << "Already loaned: cannot be loaned" << endl;
        } else {
            loaned_ = "yes";
            loan_date_ = Date(the_day);
            return_date_ = Date(the_day);
            return_date_.advance(28);
            }

    }

    void Book::renew() {
        if ( loaned_ == "no" ) {
            cout << "Not loaned: cannot be renewed" << endl;
        } else {
            return_date_.advance(28);
        }

    }

    void Book::give_back() {
        loaned_ = "no";
    }

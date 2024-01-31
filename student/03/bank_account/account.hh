#ifndef ACCOUNT_HH
#define ACCOUNT_HH
#include <string>
using namespace std;


class Account
{
public:
    // Constructor
    Account(const string& owner, bool has_credit = false);

    void print() const;
    void set_credit_limit(int credit);
    void save_money(int number);
    bool take_money(int number);
    void transfer_to(Account& to_account, int number);


private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    string owner_;
    bool credit_card_;
    string iban_;
    bool has_credit_;
    int account_money_;
    int limit_;

};


#endif // ACCOUNT_HH

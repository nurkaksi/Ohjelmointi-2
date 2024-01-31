#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), credit_card_(has_credit)
{
    generate_iban();
    account_money_ = 0;
    limit_ = 0;
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const {
    cout << owner_ << " : " << iban_ << " : " << account_money_ << " euros" << endl;

}

void Account::set_credit_limit(int credit)
{
    if (credit_card_) {
        limit_ = credit;
    } else {
        cout << "Cannot set credit limit: the account has no credit card" << endl;
    }

}

void Account::save_money(int number)
{
    account_money_ += number;
}

bool Account::take_money(int number) {


    if (!(credit_card_) && (account_money_ >= number)){
        account_money_ -= number;
        cout << number << " euros taken: new balance of " << iban_ << " is "<<
                         account_money_ << " euros" << endl;
        return true;

    } else if (credit_card_ && account_money_ + limit_ < number) {
        cout << "Cannot take money: credit limit overflow" << endl;
        return false;

    } else if (account_money_ + limit_ >= number && (credit_card_)){
        account_money_ -= number;
        cout << number << " euros taken: new balance of " << iban_ << " is "<< account_money_ << " euros" << endl;
        return true;
    } else {
        cout << "Cannot take money: balance underflow!" << endl;
        return false;
    }
}

void Account::transfer_to(Account& to_account, int number) {
    if ( take_money(number)) {
        to_account.save_money(number);
    } else {
        cout << "Transfer from " << iban_ << " failed" << endl;
    }
}

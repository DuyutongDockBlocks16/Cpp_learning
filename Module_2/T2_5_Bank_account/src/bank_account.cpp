
#include "bank_account.hpp"
#include <iostream>
#include <cmath>


BankAccount::BankAccount(const std::string &owner, const std::string &account_number, double balance) {
    owner_ = owner;
    account_number_ = account_number;
    balance_ = balance;
}

std::string BankAccount::GetOwner() const {
    return owner_;
}

double BankAccount::GetBalance() const {

    if (fabs(balance_ - 0.0) < 1e-15){
        return 0.0;
    } else {
        return balance_;
    }

}

std::string BankAccount::GetNumber() const {
    return account_number_;
}

void BankAccount::Deposit(double amount) {
    balance_ += amount;
}

bool BankAccount::Withdraw(double amount) {
    if(amount<=balance_){
        balance_ -= amount;
        return true;
    } else {
        return false;
    }
}
//Account num: <account number>, owned by: <owner>, balance: <balance> eur.
void BankAccount::Print() const {

    double correct_balance;
    if (fabs(balance_ - 0.0) < 1e-15){
        correct_balance = 0.0;
    } else {
        correct_balance = balance_;
    }


    std::cout << "Account num: " << account_number_ << ", owned by: " << owner_<<", balance: "<<correct_balance<<" eur."<< std::endl;
}

bool Transfer(BankAccount& source_account, BankAccount& target_account, double amount){
    double source_account_balance = source_account.GetBalance();
    if(amount<=source_account_balance){

        source_account.Deposit(amount*-1);
        target_account.Deposit(amount);
        return true;

    } else {
        return false;

    }
}
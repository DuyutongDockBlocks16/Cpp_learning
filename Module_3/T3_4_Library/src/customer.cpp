#include <iostream>
#include "customer.hpp"
#include <algorithm>

Customer::Customer(std::string const &name, std::string const &id) {
    name_ = name;
    customer_id_ = id;
}

std::string Customer::GetName() const {
    return name_;
}

std::string Customer::GetID() const {
    return customer_id_;
}

int Customer::GetLoanAmount() const {
    return static_cast<int>(loaned_books_.size());
}

std::vector<Book> Customer::GetLoans() const {
    return loaned_books_;
}

bool Customer::LoanBook(Book &b){
    if (b.Loan()){
        loaned_books_.push_back(b);
        return true;
    }

    return false;
}

void Customer::ReturnBook(Book &b){

    Book elementToRemove = b; // 要删除的元素
    auto it = std::find(loaned_books_.begin(), loaned_books_.end(), elementToRemove);
    if (it != loaned_books_.end()) {
        loaned_books_.erase(it); // 删除找到的元素
    }

    b.Restore();
}

void Customer::Print() const {

    std::cout << "Customer: " << name_ << ", " << customer_id_ <<", has " << loaned_books_.size() << " books on loan:" << std::endl;

    for(const auto & loaned_book : loaned_books_){
        std::cout<<"- Book: "<< loaned_book.GetName() <<", author: "<< loaned_book.GetAuthor() <<", ISBN: "<< loaned_book.GetISBN() <<", loaned "<< loaned_book.GetStatus() <<", due date: "<< loaned_book.GetDueDate().day <<"."<< loaned_book.GetDueDate().month << "."<< loaned_book.GetDueDate().year <<std::endl;
    }

}

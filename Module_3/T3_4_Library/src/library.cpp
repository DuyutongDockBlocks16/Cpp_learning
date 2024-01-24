#include "library.hpp"

#include <iostream>

#include "book.hpp"
#include "customer.hpp"


Library::Library(const std::string &name, const std::vector<Book> &books, const std::vector<Customer> &customers) {
    name_ = name;
    books_ = books;
    customers_ = customers;
}

std::string Library::GetName() const {
    return name_;
}

std::vector<Book> &Library::GetBooks(){
    return books_;
}

std::vector<Customer> &Library::GetCustomers() {
    return customers_;
}

Book Library::FindBookByName(const std::string &name) {
    for (const auto &book: books_){
        std::string book_name = book.GetName();
        if(book_name == name){
            return book;
        }
    }

    return Book{"", "", ""};
}

std::vector<Book> Library::FindBooksByAuthor(const std::string &name) {

    std::vector<Book> found_vec;
    found_vec.clear();

    for (const auto &book: books_){
        std::string book_author = book.GetAuthor();
        if(book_author == name){
            found_vec.push_back(book);
        }
    }

    return found_vec;
}

std::vector<Book> Library::FindAllLoanedBooks() {

    std::vector<Book> found_vec;
    found_vec.clear();

    for (const auto &book: books_){
        bool book_status = book.GetStatus();
        if(book_status){
            found_vec.push_back(book);
        }
    }

    return found_vec;
}

std::vector<Customer> Library::FindCustomer(const std::string &id) {

    std::vector<Customer> found_vec;
    found_vec.clear();

    for (const auto &customer: customers_){
        std::string customer_id = customer.GetID();
        if(customer_id==id){
            found_vec.push_back(customer);
        }
    }

    return found_vec;
}




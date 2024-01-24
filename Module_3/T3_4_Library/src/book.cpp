#include "book.hpp"

#include <ctime>
#include <iostream>
#include <chrono>

Book::Book(const std::string& name, const std::string& author, const std::string& isbn, bool loaned, Date due_date) {

    name_ = name;
    author_ = author;
    isbn_ = isbn;
    loaned_ = loaned;
    due_date_ = due_date;

}

std::string Book::GetName() const{
    return name_;
}

std::string Book::GetAuthor() const{
    return author_;
}

std::string Book::GetISBN() const{
    return isbn_;
}

bool Book::GetStatus() const{
    return loaned_;
}

Date Book::GetDueDate() const{
    return due_date_;
}

bool Book::Loan() {

    if(loaned_ == false){

        loaned_ = true;

//        // 获取当前日期和时间
//        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//
//        // 获取当前日期的年、月和日
//        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
//        std::tm* now_tm = std::localtime(&now_time);
//        int currentYear = now_tm->tm_year + 1900;
//        int currentMonth = now_tm->tm_mon + 1;
//        int currentDay = now_tm->tm_mday;

        // 计算下一个月的年和月
        int nextYear = Date::Today().year;
        int nextMonth = Date::Today().month+1;
        if (nextMonth > 12) {
            nextMonth = 1;
            nextYear++;
        }
        int nextDay = Date::Today().day;
//        int nextYear = currentYear;
//        int nextMonth = currentMonth + 1;
//        if (nextMonth > 12) {
//            nextMonth = 1;
//            nextYear++;
//        }
//        int nextDay = currentDay;

        due_date_ = Date{nextDay, nextMonth, nextYear};
        return true;
    }

    return false;
}

void Book::Restore() {
    loaned_ = false;
}

void Book::Print() {

    std::cout<<"Book: "<< name_ <<", author: "<<author_<<", ISBN: "<< isbn_ <<", loaned "<< loaned_ <<", due date: "<< due_date_.year <<"."<< due_date_.month << "."<< due_date_.day <<std::endl;

}

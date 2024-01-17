#include "person.hpp"

// define your Person class' functions here
#include <iostream>

Person::Person(std::string name, int birth_year) : Name(name), birthyear(birth_year) {
    // 在构造函数的初始化列表中初始化成员变量
}

std::string Person::GetName() {
    return Name;
}

int Person::GetAge(int year) {
    return year - birthyear;
}
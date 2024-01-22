#include "list.hpp"

#include <iostream>

// Implement the functions here

std::istream& GetLines(std::istream& is, std::list<std::string>& list) {

    std::string line;

    list.clear();

    while(std::getline(is,line)){
        list.push_back(line);
    }
    return is;
  
}

void Print(const std::list<std::string>& list) {

    for (const std::string& str : list) {
        std::cout << str << std::endl;
    }

}

void SortAndUnique(std::list<std::string>& list) {

    list.sort();
    list.unique();
  
}
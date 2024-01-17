#ifndef AALTO_ELEC_CPP_PERSON
#define AALTO_ELEC_CPP_PERSON

#include <string>

// declare your Person class here
class Person {
public:
    std::string Name;
    int birthyear;

    Person(std::string name, int birth_year);
    std::string GetName();
    int GetAge(int year);
};


#endif
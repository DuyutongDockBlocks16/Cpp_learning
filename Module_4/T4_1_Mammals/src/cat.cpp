#include "cat.hpp"


Cat::Cat(std::string name, double weight1) : Mammal(weight1) {
    weight_ = weight1;
    name_ = name;
}

std::string Cat::GetName() {
    return name_;
}

std::string Cat::MakeSound() {
    return "Meow";
}


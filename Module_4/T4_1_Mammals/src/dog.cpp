#include "dog.hpp"


std::string Dog::GetName() {
    return name_;
}

std::string Dog::MakeSound() {
    return "Wuff!";
}

Dog::Dog(std::string name, double weight) : Mammal(weight){
    weight_ = weight;
    name_ = name;
}

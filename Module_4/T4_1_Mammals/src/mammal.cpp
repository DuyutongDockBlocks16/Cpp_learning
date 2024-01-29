#include "mammal.hpp"

Mammal::Mammal(double weight) : weight_(weight) {
    weight_ = weight;
}

double Mammal::GetWeight() {
    return weight_;
}
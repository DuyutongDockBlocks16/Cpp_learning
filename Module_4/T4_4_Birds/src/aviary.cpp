#include "aviary.hpp"

void Aviary::Add(Bird *bird) {
    if (bird == nullptr) {
        throw std::logic_error("Cannot add a null bird to the aviary");
    }
    birds.push_back(bird);
}

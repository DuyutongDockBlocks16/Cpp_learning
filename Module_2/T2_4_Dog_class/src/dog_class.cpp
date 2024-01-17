#include "dog_class.hpp"

// Definitions of class functions with some errors

/**
 * \brief Construct a new Dog object
 *
 * \param a age of the dog
 * \param n name of the dog
 */

  Dog::Dog(int a, std::string n) {
  age_ = a; 
  name_ = n; 
}

/**
 * \brief Sets the age of the dog
 *
 * \param a The age of the dog
 */

  void Dog::SetAge(int a) {
      age_ = a; 
}

/**
 * \brief Returns the age of the dog
 *
 * \return The age of the dog
 */

  int Dog::GetAge() {
      return age_; 
}

/**
 * \brief Sets the name of the dog
 *
 * \param n The name of the dog
 */

  void Dog::SetName(std::string n) {
      name_ = n; 
}

/**
 * \brief Returns the name of the dog
 *
 * \return The name of the dog as std::string
 */

  std::string Dog::GetName() {
      return name_; 
}

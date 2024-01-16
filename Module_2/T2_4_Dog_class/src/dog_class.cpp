#include "dog_class.hpp"

// Definitions of class functions with some errors

/**
 * \brief Construct a new Dog object
 *
 * \param a age of the dog
 * \param n name of the dog
 */

  Dog(int a, string n) { 
  age_ = a; 
  name_ = n; 
}

/**
 * \brief Sets the age of the dog
 *
 * \param a The age of the dog
 */

  Dog::setAge(int a) {
      age_ = a; 
}

/**
 * \brief Returns the age of the dog
 *
 * \return The age of the dog
 */

  Dog::GetAge() {
      return age_; 
}

/**
 * \brief Sets the name of the dog
 *
 * \param n The name of the dog
 */

  Dog::setName(string n) {
      name_ = n; 
}

/**
 * \brief Returns the name of the dog
 *
 * \return The name of the dog as std::string
 */

  Dog::getName() {
      return name_; 
}

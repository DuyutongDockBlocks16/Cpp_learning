#ifndef AALTO_ELEC_CPP_DOG_CLASS
#define AALTO_ELEC_CPP_DOG_CLASS

#include <string>

/**
 * \brief A simple class to represent a dog
 *
 */
class Dog {
  
  Dog(int age, std::string name);

  void SetAge(int age);
  int GetAge();
  void SetName(std::string name);
  std::string GetName();

 private:
  int age_;
  std::string name_;
} 

#endif

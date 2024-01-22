#include "vector_it.hpp"

#include <iostream>
#include <vector>
#include <limits>

// Implement the functions here

std::vector<int> ReadVector() {
  std::vector<int> v;

  int input_int;

  while(std::cin >> input_int){
      v.push_back(input_int);
  }

  std::cin.clear();

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  return v;
}

void PrintSum1(const std::vector<int>& v) {

    for(unsigned i=0; i<v.size()-1; i++){
        std::cout<<v[i]+v[i+1]<<" ";
    }

    std::cout<<std::endl;
  
}

void PrintSum2(const std::vector<int>& v) {
    int vector_size = v.size();
    int portion = 2;

    int cycle_time = vector_size / portion;

//    std::cout << cycle_time<<std::endl;

    for(unsigned i=0; i < cycle_time; i++ ){
        std::cout << v[i] + v[v.size()-1-i]<<" ";
    }

    std::cout<<std::endl;

  
}

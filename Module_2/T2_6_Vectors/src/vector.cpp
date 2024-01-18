#include "vector.hpp"

#include <vector>

int GetMin(std::vector<int> v) {

    int min = v[0];

    for(unsigned i = 0; i<v.size(); i++){
        if(v[i] < min){
            min = v[i];
        }
    }

    return min;

}

int GetMax(std::vector<int> v) {

    int max = v[0];

    for(unsigned i = 0; i<v.size(); i++){
        if(v[i] > max){
            max = v[i];
        }
    }

    return max;

}

double GetAvg(std::vector<int> v) {

    double sum = 0.0;

    for(unsigned i = 0; i<v.size(); i++){

        sum += v[i];

    }

    return sum/v.size();

}

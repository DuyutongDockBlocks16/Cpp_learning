#include "matrix.hpp"

#include <iostream>
#include <vector>

// Implement the functions here
// Remember to use auto and ranged for-loops when they can be used!

// Assumes 'm' is a square matrix
Matrix ReadMatrix(int n) {
    int dimension_number = n * n;
    std::vector<int> elements;
    elements.clear();
    int input_number;

//    collect elements
    for(int i = 0; i < dimension_number; i++){

        std::cin >> input_number;

        elements.push_back(input_number);
    }

//    test:
//    for (int element : elements) {
//        std::cout << element << " ";
//    }
//    std::cout << std::endl;

//    break down elements to matrix
    Matrix matrix;
    auto element = elements.begin();
    for(int i = 0; i < n; ++i){
        std::vector<int> row;
        for(int j=0; j < n; ++j){
            if(element != elements.end()){
                row.push_back(*element);
                element++;
            }
        }
        matrix.push_back(row);
    }

//    // print for test
//    for (const auto& row : matrix) {
//        for (int element : row) {
//            std::cout << element << " ";
//        }
//        std::cout << std::endl;
//    }

    return matrix;

}

Matrix Rotate90Deg(const Matrix &m) {

    int rows = m.size();
    int cols = m[0].size();
    Matrix rotated(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = m[i][j];
        }
    }

    return rotated;

}

void Print(const Matrix &m) {
    for (const auto& row : m) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}
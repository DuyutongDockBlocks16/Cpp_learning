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

    if (m.empty() || m[0].empty()){
        return Matrix();
    }

    unsigned long long rows = m.size();
    unsigned long long cols = m[0].size();//59行
    Matrix rotated(cols, std::vector<int>(rows));

    for (unsigned long long i = 0; i < rows; ++i) {
        if (m[i].size() != cols) {
            // 处理不一致的行长度
            // 可以抛出异常或以其他方式处理
            throw std::runtime_error("Inconsistent row sizes in matrix");
        }
        for (unsigned long long j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = m[i][j];
        }
    }

    return rotated;

}

void Print(const Matrix &m) {

    if (m.empty()) {
        std::cout << "Printing out a 0 x 0 matrix:" << std::endl;
        return;
    }

    // 假设矩阵的所有行都有相同的长度
    unsigned long long cols = m[0].size();
    for (const auto& row : m) {
        if (row.size() != cols) {
            std::cout << "Inconsistent row sizes in matrix." << std::endl;
            return;
        }
    }

    std::cout << "Printing out a "<< m.size() << " x "<< m[0].size() <<" matrix:" << std::endl;

    for (const auto& row : m) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}
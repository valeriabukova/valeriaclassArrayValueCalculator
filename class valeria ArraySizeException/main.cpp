//
//  main.cpp
//  class valeria ArraySizeException
//
//  Created by Valeria  Bukova on 25.11.2024.
//

#include <iostream>


class Exception {
public:
    virtual const char* what() const {
        return "An error occurred.";
    }
};


class ArraySizeException : public Exception {
public:
    const char* what() const override {
        return "Array size must be 4x4.";
    }
};


class ArrayDataException : public Exception {
private:
    const char* message;
public:
    explicit ArrayDataException(const char* msg) : message(msg) {}
    const char* what() const override {
        return message;
    }
};

class ArrayValueCalculator {
public:
    int doCalc(const char* array[4][4], size_t rows, size_t cols) {
        if (rows != 4 || cols != 4) {
            throw ArraySizeException();
        }

        int sum = 0;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                try {
                    sum += toInt(array[i][j]);
                } catch (const ArrayDataException& e) {
                    throw ArrayDataException("Invalid data at specified position.");
                }
            }
        }
        return sum;
    }

private:
    int toInt(const char* str) {
        int num = 0;
        bool isNegative = false;
        if (*str == '-') {
            isNegative = true;
            ++str;
        }
        while (*str) {
            if (*str < '0' || *str > '9') {
                throw ArrayDataException("Invalid number format.");
            }
            num = num * 10 + (*str - '0');
            ++str;
        }
        return isNegative ? -num : num;
    }
};

int main() {
    ArrayValueCalculator calculator;

   
    const char* validArray[4][4] = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

  
    const char* invalidSizeArray[4][3] = {
        {"1", "2", "3"},
        {"4", "5", "6"},
        {"7", "8", "9"},
        {"10", "11", "12"}
    };

    
    const char* invalidDataArray[4][4] = {
        {"1", "2", "3", "4"},
        {"5", "6", "seven", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    try {
        std::cout << "Sum of valid array: " << calculator.doCalc(validArray, 4, 4) << std::endl;
    } catch (const Exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        std::cout << "Sum of invalid size array: " << calculator.doCalc(invalidSizeArray, 4, 3) << std::endl;
    } catch (const Exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        std::cout << "Sum of invalid data array: " << calculator.doCalc(invalidDataArray, 4, 4) << std::endl;
    } catch (const Exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}

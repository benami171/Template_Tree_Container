#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <sstream>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
class Complex {
   public:
    double real;
    double imag;

    Complex() : real(0.0), imag(0.0) {}
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    // Copy constructor
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    // Destructor
    ~Complex() {}

    // Assignment operator
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    // Equality operators
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // Inequality operator
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // Addition
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Subtraction
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Multiplication
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    // Division
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    // Magnitude
    double magnitude() const {
        return std::hypot(real, imag);
    }

    double magnitudeSquared() const {
        return real * real + imag * imag;
    }

    // Phase
    double phase() const {
        return atan2(imag, real);
    }

    // Comparison operators (for the sake of completeness)
    bool operator<(const Complex& other) const {
        return std::hypot(real, imag) < std::hypot(other.real, other.imag);
    }

    bool operator>(const Complex& other) const {
        return std::hypot(real, imag) > std::hypot(other.real, other.imag);
    }

    bool operator<=(const Complex& other) const {
        return !(*this > other);
    }

    bool operator>=(const Complex& other) const {
        return !(*this < other);
    }

    string to_string() const {
        std::ostringstream out;

        if (real != 0) {
            out << real;
        }

        if (imag != 0) {
            if (imag > 0 && real != 0) {
                out << "+";
            }
            out << imag << "i";
        }

        if (real == 0 && imag == 0) {
            out << "0";
        }

        return out.str();
    }


    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "{" << c.real << "," << c.imag << "}";
        return os;
    }
};

#endif  // COMPLEX_HPP
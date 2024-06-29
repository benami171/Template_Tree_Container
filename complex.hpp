// Created by: Gal Ben Ami
// email: benami171@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <cmath>
#include <iostream>
#include <sstream>
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

    double get_real() const { return real; }
    double get_imag() const { return imag; }

    // Equality operators
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // Inequality operator
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // Comparison operators (for the sake of completeness)
    // hypot == sqrt(real^2 + imag^2)
    bool operator<(const Complex& other) const {
        return hypot(real, imag) < hypot(other.real, other.imag);
    }

    bool operator>(const Complex& other) const {
        return other < *this;
    }

    bool operator<=(const Complex& other) const {
        return !(*this > other);
    }

    bool operator>=(const Complex& other) const {
        return !(*this < other);
    }

    friend ostream& operator<<(ostream& out, const Complex& comp) {
        out << comp.to_string();
        return out;
    }

    string to_string() const {
        ostringstream oss;
        oss << real << "+" << imag << "i";
        return oss.str();
    }
};

#endif  // COMPLEX_HPP
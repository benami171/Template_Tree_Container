// Created by: Gal Ben Ami
// email: benami171@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

class Complex {
public:
    double real;
    double imag;

    Complex() : real(0.0), imag(0.0) {}
    Complex(double r, double i) : real(r), imag(i) {}
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const {
        return std::hypot(real, imag) < std::hypot(other.real, other.imag);
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

    friend std::ostream& operator<<(std::ostream& out, const Complex& comp) {
        out << comp.to_string();
        return out;
    }

    std::string to_string() const {
        std::ostringstream oss;
        if (real == 0 && imag == 0) {
            oss << "0";
        } else if (real == 0) {
            oss << "i" << imag;
        } else if (imag == 0) {
            oss << real;
        } else {
            oss << real << (imag > 0 ? "+i" : "-i") << std::abs(imag);
        }
        return oss.str();
    }
};

#endif  // COMPLEX_HPP

#pragma once

#include <iostream>

using namespace std;

// This will represent a term of the polynomial for example 3x^2 will
// be represented as a term with the coefficient value set to 3 and the exponent set to 2.
class Term {
public:

    Term() {
        coef = -1;
        exp = -1;
    }

    Term(const int coefficient, const int exponent) {
        coef = coefficient;
        exp = exponent;
    }

    // This method overloads the << operator so that we can display 
    // the content of the circularQueue using cout << term.
    friend ostream& operator<<(ostream& os, const Term& term)
    {
        os << term.coef << "x^" << term.exp;
        return os;
    }

public:
    int coef;
    int exp;
};
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "Term.h"
#include "Stack.h"
#include "CircularQueue.h"

using namespace std;


class PolynomialOperations {
public:
     void readPolynomsFromCmd() {
        cout << "Insert the value X for which the polynomial will be computed\n";
        cin >> X;

        // Initialize the first polynomial
        cout << "Insert the first polynomial degree:\n";
        cin >> firstPolynomialDeg;

        firstPoly = new CircularQueue<Term>((firstPolynomialDeg + 1));

        for (int i = 0; i <= firstPolynomialDeg; i++) {
            cout << "Enter the coefficient for the " << i << " exponent:\n";
            int coefficient;
            cin >> coefficient;
            Term polyTerm(coefficient, i);

            firstPoly->enqueue(polyTerm);
        }

        // Initialize the second polynomial
        cout << "Insert the second polynomial degree:\n";
        cin >> secondPolynomialDeg;

        secondPoly = new CircularQueue<Term>((secondPolynomialDeg + 1));

        for (int i = 0; i <= secondPolynomialDeg; i++) {
            cout << "Enter the coefficient for the " << i << " exponent:\n";
            int coefficient;
            cin >> coefficient;
            Term polyTerm(coefficient, i);

            secondPoly->enqueue(polyTerm);
        }
    }

    void initTestPolynoms(int X, int firstPolDeg, int secPolDeg,
        int firstPolCoef, int secPolCoef) {
        this->X = X;
        firstPolynomialDeg = firstPolDeg;
        firstPoly = new CircularQueue<Term>((firstPolynomialDeg + 1));
        for (int i = 0; i <= firstPolynomialDeg; i++) {
            //cout << "Enter the coefficient for the " << i << " exponent:\n";
            int coefficient = rand() % 5;
            Term polyTerm(coefficient, i);
            firstPoly->enqueue(polyTerm);
        }

        secondPolynomialDeg = secPolDeg;
        secondPoly = new CircularQueue<Term>((secondPolynomialDeg + 1));
        for (int i = 0; i <= secondPolynomialDeg; i++) {
            int coefficient = rand() % 5;
            Term polyTerm(coefficient, i);
            secondPoly->enqueue(polyTerm);
        }
    }

    void displayPolynom(CircularQueue<Term> polynom) {

        cout << "Display polynomial from queue: ";

        while (polynom.currentSize != 1) {
            cout << polynom.dequeue() << " + ";
        }

        cout << polynom.dequeue() << "\n";
    }

    void displayPolynomFromStack(Stack<Term> stackResult) {
        cout << "Display polynomial from stack: ";

        while (stackResult.topLevel != 0) {
            Term *stackTerm = stackResult.pop();
            if(stackTerm->coef != 0){
                cout << *stackTerm << " + ";
            }
        }

        Term *stackTerm = stackResult.pop();
        if (stackTerm->coef != 0) {
            cout << *stackTerm << "\n";
        }
    }

    int polynomValue(CircularQueue<Term> polynom) {
        Stack<int> stackPartialSum(1);
        stackPartialSum.push(0);

        Term polynomTerm = polynom.dequeue();

        // The term (-1, -1) represents the empty term.
        // The empty term will be returned when the queue is empty
        while (polynomTerm.exp != -1 && polynomTerm.coef != -1) {
            int polynomTermValue = polynomTerm.coef * pow(X, polynomTerm.exp);
            stackPartialSum.push(*stackPartialSum.pop() + polynomTermValue);
            polynomTerm = polynom.dequeue();

        }
        return *stackPartialSum.pop();
    }


    CircularQueue<Term> invertPolynom(CircularQueue<Term> polynom) {
            Stack<Term> invertedPolyStack(polynom.currentSize);

            // Add all the polynomTerms to a stack
            Term polynomTerm = polynom.dequeue();
            // The term (-1, -1) represents the empty term.
            // The empty term will be returned when the queue is empty
            while (polynomTerm.exp != -1 && polynomTerm.coef != -1) {
                invertedPolyStack.push(polynomTerm);
                polynomTerm = polynom.dequeue();
            }

            Term *polynomTermP = invertedPolyStack.pop();
            // Extract all the terms from the stack and add them to a new
            // inverted polynom

            int exponent = 0;
            CircularQueue<Term> invertedPoly(polynom.maxSize);
            // The term (-1, -1) represents the empty term.
            // The empty term will be returned when the queue is empty
            while (polynomTermP != nullptr ) {
                Term invertedTerm(polynomTermP->coef, exponent);
                invertedPoly.enqueue(invertedTerm);

                polynomTermP = invertedPolyStack.pop();
                exponent++;
            }

            return invertedPoly;
    }

    void substractPolynoms(CircularQueue<Term> firstPoly, CircularQueue<Term> secondPoly) {
        Stack<Term> stackResult(max(firstPoly.maxSize, secondPoly.maxSize));
        Term firstPolyTerm = firstPoly.dequeue();
        Term secondPolyTerm = secondPoly.dequeue();

        while (firstPolyTerm.exp != -1 && secondPolyTerm.exp != -1) {
            int substrCoef = firstPolyTerm.coef - secondPolyTerm.coef;
            Term substrTerm(substrCoef, firstPolyTerm.exp);
            stackResult.push(substrTerm);
            firstPolyTerm = firstPoly.dequeue();
            secondPolyTerm = secondPoly.dequeue();
        }
        if (firstPolyTerm.exp != -1) {
            while (firstPolyTerm.exp != -1) {

                stackResult.push(firstPolyTerm);
                firstPolyTerm = firstPoly.dequeue();
            }
        }

        if (secondPolyTerm.exp != -1) {
            while (secondPolyTerm.exp != -1) {

                stackResult.push(secondPolyTerm);
                secondPolyTerm = secondPoly.dequeue();
            }
        }

        displayPolynomFromStack(stackResult);

    }

    void multiplyPolynoms(CircularQueue<Term> firstPoly, CircularQueue<Term> secondPoly) {

        Stack<Term> stackResult(firstPoly.maxSize*secondPoly.maxSize);
        Term firstPolyTerm = firstPoly.dequeue();

        while (firstPolyTerm.exp != -1) {
            CircularQueue<Term> auxQueue = secondPoly;
            Term secondPolyTerm = auxQueue.dequeue();
            while (secondPolyTerm.exp != -1) {
                int newCoef = firstPolyTerm.coef*secondPolyTerm.coef;
                int newExp = firstPolyTerm.exp + secondPolyTerm.exp;
                Term newTerm(newCoef, newExp);
                stackResult.push(newTerm);
                secondPolyTerm = auxQueue.dequeue();
            }

            firstPolyTerm = firstPoly.dequeue();
        }

        int solvedExponents[200];

        Stack<Term> finalStack(firstPoly.maxSize*secondPoly.maxSize);
        Term *firstStackResultTerm = stackResult.pop();

        while (firstStackResultTerm != nullptr) {
            if (solvedExponents[firstStackResultTerm->exp] == 1) {
                firstStackResultTerm = stackResult.pop();
            }
            else {
                solvedExponents[firstStackResultTerm->exp] = 1;

                Stack<Term> auxStackResult = stackResult;
                Term *auxResultTerm = auxStackResult.pop();

                int summedCoef = firstStackResultTerm->coef;

                while (auxResultTerm != nullptr) {
                    if (firstStackResultTerm->exp == auxResultTerm->exp)
                    {
                        summedCoef = summedCoef + auxResultTerm->coef;
                    }
                    auxResultTerm = auxStackResult.pop();
                }

                Term finalTerm(summedCoef, firstStackResultTerm->exp);
                finalStack.push(finalTerm);
            }

            firstStackResultTerm = stackResult.pop();
        }

        displayPolynomFromStack(finalStack);
    }


    CircularQueue<Term> *firstPoly;
    CircularQueue<Term> *secondPoly;
    int X;
private:
    int firstPolynomialDeg;
    int secondPolynomialDeg;
};

int main() {
    int stop;

    PolynomialOperations polyOp;

    //polyOp.initTestPolynoms(2, 2, 1, 2, 2);

    polyOp.readPolynomsFromCmd();

    polyOp.displayPolynom(*polyOp.firstPoly);
    polyOp.displayPolynom(*polyOp.secondPoly);

    // Compute the value in one point
    cout << "First polynomial value in point x = " << polyOp.X << " is: " <<
        polyOp.polynomValue(*polyOp.firstPoly) << "\n";

    cout << "Second polynomial value in point x = " << polyOp.X << " is: " <<
        polyOp.polynomValue(*polyOp.secondPoly) << "\n";

    // Invert polynom
    CircularQueue<Term> invertedPoly = polyOp.invertPolynom(*polyOp.firstPoly);

    cout << "Inverted polynomial - ";
    polyOp.displayPolynom(invertedPoly);

    // Substract polynoms
    cout << "Substract polynomials -";
    polyOp.substractPolynoms(*polyOp.firstPoly, *polyOp.secondPoly);

    // Multiply polynoms
    cout << "Multiply polynomials - ";
    polyOp.multiplyPolynoms(*polyOp.firstPoly, *polyOp.secondPoly);

    cout << "\nstop";
    cin >> stop;
    return 0;
}

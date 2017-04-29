#pragma once

/// This will represent the stack template stack. We can define a stack 
// in the following way 
// Stack<int> myStack;

template<typename T>
class Stack {
public:
    Stack(int size) {
        stackArray = new T[size];
        maxSize = size;
        topLevel = -1;
    }

    void push(T numberToAdd) {
        if (topLevel >= maxSize - 1) {
           // cout << "The stack has already" << maxSize << "elements! \n";
            return;
        }
        topLevel++;
        stackArray[topLevel] = numberToAdd;
     };

    T* pop() {
        if (topLevel == -1) {
           // cout << "The stack is empty! \n";
            return nullptr;
        }

        T* varTemp = new T;
        *varTemp = stackArray[topLevel];
        topLevel--;
        return varTemp;
    };

    void display() {
        cout << "The elements of the stack:";
        for (int i = topLevel; i>=0; i--) {
            cout <<stackArray[i]<< " ";
        }
        cout << "\n";
    };

    //copy constructor
    Stack<T>(const Stack<T>& stack2)
    {
        maxSize = stack2.maxSize;
        topLevel = stack2.topLevel;
        stackArray = new T[maxSize];
        std::memcpy(stackArray, stack2.stackArray, sizeof(T)*maxSize);
    }

    //copy assignment operator overload
    Stack<T>& operator=(const Stack<T>& stack2)
    {
        if (this == &stack2)
            return *this; //self assignment
        if (stackArray != NULL)
            delete[] stackArray; //clean up already allocated memory

        maxSize = stack2.maxSize;
        topLevel = stack2.topLevel;
        stackArray = new T[maxSize];
        std::memcpy(stackArray, stack2.stackArray, sizeof(T)*maxSize);

        return *this;
    }

    ~Stack() {
        delete[] stackArray;
    };

    int topLevel;
private:
    T *stackArray;
    int maxSize;
};

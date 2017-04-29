#pragma once

/// This class will represent the circular queue template. We can define a queue 
// in the following way 
// Stack<int> myStack;


#include <iostream>

using namespace std;

template<typename T>
class CircularQueue {

public:

    CircularQueue(int size) {
        maxSize = size;
        head = tail = -1;
        queueArray = new T[size];
        currentSize = 0;
    }

    // This method adds an element in the back of the queue
    void enqueue(T polyTermToAdd) {
        int nextTail = tail + 1;
        if ((nextTail) % maxSize == head) {
            //cout << "The queue is full! \n";
            return;
       }
        else
        {
            tail=(tail + 1) % maxSize;
        };
        
        queueArray[tail] = polyTermToAdd;
        currentSize++;

        if (head == -1) {
            head = 0;
        }
    };
    
//     // This method returns the head of the queue;
    T dequeue() {
        if (tail == head && head  == -1) {
           // cout << "The queue is empty! \n";
            T emptyTerm;
            return emptyTerm;
        }
        T varTemp = queueArray[head];
        
        if (head == tail) {
            head = tail = -1;
        }
        else {
            head = (head + 1) % maxSize;
        }

        currentSize--;
        return varTemp;
   };

    //copy constructor
    CircularQueue<T>(const CircularQueue<T>& queue2)
    {
        maxSize = queue2.maxSize;
        head = queue2.head;
        tail = queue2.tail;
        queueArray = new T[maxSize];
        currentSize = queue2.currentSize;
        std::memcpy(queueArray, queue2.queueArray, sizeof(T)*maxSize);
    }

    //copy assignment operator overload
    CircularQueue<T>& operator=(const CircularQueue<T>& queue2)
    {
        if (this == &queue2)
            return *this; //self assignment
        if (queueArray != NULL)
            delete[] queueArray; //clean up already allocated memory

        maxSize = queue2.maxSize;
        head = queue2.head;
        tail = queue2.tail;
        currentSize = queue2.currentSize;
        queueArray = new T[maxSize];
        std::memcpy(queueArray, queue2.queueArray, sizeof(T)*maxSize);
        return *this;
    }

    void display() {
        cout << "The elements of the queue are: \n";
        for (int i = head; i != tail; i = (i + 1) % maxSize) {
            cout << queueArray[i] << " ";
       }
        cout << queueArray[tail];

    };

    ~CircularQueue() {
        delete[] queueArray;
    }

    int currentSize;
    int maxSize;
private:
    T *queueArray;
    int head;
    int tail;
};

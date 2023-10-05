#ifndef jobProcessing_hpp
#define jobProcessing_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#endif /* header_hpp */

struct job {
    char type;
    int arrival;
    int process;
    int countType;  // Job type ranking
    int countJob;   // total job ranking
    job* next;
};

class Queue {
private:
    job* front;
    job* back;
    int size;
public:
    Queue();    // default constructor
    Queue(job &j);  // constructor with one parameter
    Queue(const Queue &original);   // copy constructor
    Queue& operator=(const Queue & objToCopy);  // copy constructor
    void enqueue(job* j);   // add job at the end of the queue
    void dequeue();        // delete job at the beginning of the queue
    void putBack(job* j);   // put back the job at the beginning
    void printAll();    // print all jobs in the queue (TESTING)
    int getSize();     // return number of jobs in the queue
    job* first();    // return the first in queue
    job* last();     // return the last in queue
    bool isEmpty();     // check if the queue is empty
    void addPriority(job* j); // add to work queue with D is priority
    void clear();   // destroy the Queue
    ~Queue();   // destructor
};

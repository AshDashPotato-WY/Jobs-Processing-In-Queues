#include "jobProcessing.hpp"

Queue::Queue() {
    front = nullptr;
    back = front;
    size = 0;
}

Queue::Queue(job &j) {
    j.next = nullptr;
    front = &j;
    back = &j;
    size = 1;
}

// copy constructor
Queue::Queue(const Queue &original) {
    job* newJob;
    job* current;
    if (front != nullptr) clear();  // delete everything in the queue
    if (original.front == nullptr) {
        front = nullptr;
        back = nullptr;
        size = 0;
    }
    else {
        size = original.size;
        front = new job;
        current = original.front;
        *front = *(original.front);
        front->next = nullptr;
        back = front;
        current = current->next;
        while (current != nullptr) {
            newJob = new job;
            *newJob = *(current);
            newJob->next = nullptr;
            back->next = newJob;
            back = newJob;
            current = current->next;
        }
    }
}

// operator overload
Queue& Queue::operator=(const Queue &objToCopy) {
    if (objToCopy.size == 0) {
        clear();
        front = nullptr;
        back = front;
        size = 0;
    }
    else if (objToCopy.size == 1) {
        delete front;
        front = new job;
        *front = *(objToCopy.front);
        back = front;
        size = 1;
    }
    else if (this != &objToCopy) {  // traverse through the queue and copy each element
        job* newJob;
        job* current;
        size = objToCopy.size;
        front = new job;
        current = objToCopy.front;
        *front = *(objToCopy.front);
        front->next = nullptr;
        back = front;
        current = current->next;
        while (current != nullptr) {
            newJob = new job;
            *newJob = *(current);
            newJob->next = nullptr;
            back->next = newJob;
            back = newJob;
            current = current->next;
        }
    }
    return *this;
}

void Queue::enqueue(job* j) {
    j->next = nullptr;
    if (front == nullptr) {
        front = j;
        back = j;
    }
    else {
        back->next = j;
        back = j;
    }
    size += 1;
}

void Queue::dequeue() {
    if (front == nullptr)   return; // empty queue
    else if (front == back) {   // only one in the queue
        delete front;
        front = nullptr;
        back = nullptr;
        // cout << "Now the queue is empty." << endl;
    }
    else {
        job* temp;
        temp = front;
        front = front->next;
        delete temp;
        temp = nullptr;
    }
    size -= 1;
}

// putback job always will be A, B, C
// putback job will be put behind the last high priority job and before the first regular job
void Queue::putBack(job* j) {
    j->next = nullptr;
    if (front == nullptr) { // no job in the queue
        front = j;
        back = j;
    }
    if (front->type != 'D') {   // first job in the queue is not high priority, then put here
        j->next = front;
        front = j;
    }
    else {      // there exist high priority jobs in the queue
        job* temp = front;
        job* prev = front;
        while (temp->type == 'D' && temp->next != nullptr) {    // traverse through high priotity jobs
            prev = temp;
            temp = temp->next;
        }
        if (temp->type == 'D' && temp->next == nullptr) {   // put behind last D
            back->next = j;
            back = j;
            size += 1;
            return;
        }
        // there are mor jobs behind last D
        prev->next = j;
        j->next = temp;
    }
    size += 1;
}

void Queue::printAll() {
    job* temp;
    temp = front;
    while (temp != nullptr) {
        cout << temp->type << " " << temp->arrival << " " << temp->process << " " << temp->countType << endl;
        temp = temp->next;
    }
}

int Queue::getSize() {
    return size;
}

job* Queue::first() {
    if (front == nullptr) {
        job emptyJob = {' ', 0, 0, 0, 0};
        job* j = &emptyJob;
        return j;
    }
    return front;
}

job* Queue::last() {
    if (back == nullptr) {
        job emptyJob = {' ', 0, 0, 0, 0};
        job* j = &emptyJob;
        return j;
    }
    return back;
}

bool Queue::isEmpty() {
    return (!front);    // true means empty;
}

void Queue::addPriority(job* j) {
    j->next = nullptr;
    if (front == nullptr) {     // when queue is empty
        front = j;
        back = j;
    }
    else if (j->type != 'D') {   // when job type is not high priority
        back->next = j;
        back = j;
    }
    // when job type is high priority
    else if (front->type != 'D') {   // first job in the queue is not priority
        j->next = front;
        front = j;
    }
    else {  // first job in the queue is priority
        job* temp = front;
        job* prev = front;
        while (temp->type == 'D' && temp->next != nullptr) {    // traverse through high priotity jobs
            prev = temp;
            temp = temp->next;
        }
        if (temp->type == 'D' && temp->next == nullptr) {   // only D jobs exist in the queue
            back->next = j;
            back = j;
            size += 1;
            return;
        }
        prev->next = j;
        j->next = temp;
    }
    size += 1;
}
    
void Queue::clear() {
    if (front == nullptr) {
        // cout << "Finish the queue.\n";
        return;
    }
    // more than one in the queue
    else {
        job* temp = front;
        while (temp != nullptr) {
            front = front->next;
            delete temp;
            temp = front;
        }
        back = front;
    }
}

Queue::~Queue() {
    clear();
}

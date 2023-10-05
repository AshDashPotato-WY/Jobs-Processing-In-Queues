#include "jobProcessing.hpp"
#include <fstream>

int main() {
    //ifstream jobFile("randomJobs.txt");
    //ofstream logFile("logFile.txt");
    
    // read data from the file into queue
    ifstream jobFile("/Users/ashley/Dropbox (University of Michigan)/Ashley Yu’s files/Home/CIS 200/Lab/Project 2/Program 1/randomJobs.txt", ios::in);
    if (!jobFile.is_open()) {
        jobFile.open("/Users/ashley/Dropbox (University of Michigan)/Ashley Yu’s files/Home/CIS 200/Lab/Project 2/Program 1/randomJobs.txt", ios::in);
    }
    
    // create log file, rewrite file everytime the program runs until last time to change it back
    ofstream logFile("/Users/ashley/Dropbox (University of Michigan)/Ashley Yu’s files/Home/CIS 200/Lab/Project 2/Program 1/logFile.txt", ios::out | ios::trunc);
    if (!logFile.is_open()) {
        logFile.open("/Users/ashley/Dropbox (University of Michigan)/Ashley Yu’s files/Home/CIS 200/Lab/Project 2/Program 1/logFile.txt", ios::out | ios::trunc);
    }
    
    
    // declare regular queue and high priority queue
    Queue normalQ;
    //job readJob;
    string tab;
    int countA = 0;
    int countB = 0;
    int countC = 0;
    int countD = 0;
    int total = 0;
    
    /*---------------------Read file into normal Queues----------------------------*/
    while (!jobFile.eof()) {
        job* j = new job;
        jobFile >> j->type >> j->arrival >> j->process;
        j->next = nullptr;
        total++;
        j->countJob = total;
        if (j->type == 'D') {
            countD++;
            j->countType = countD;
            normalQ.enqueue(j);
        }
        else if (j->type == 'A') {
            countA++;
            j->countType = countA;
            normalQ.enqueue(j);
        }
        else if (j->type == 'B') {
            countB++;
            j->countType = countB;
            normalQ.enqueue(j);
        }
        else if (j->type == 'C') {
            countC++;
            j->countType = countC;
            normalQ.enqueue(j);
        }
    }
    
    /*----------------------------Start work Queue---------------------------------*/
    Queue workQ;
    bool processor1, processor2, processor3, processor4, processor5, processor6, processor7, processor8;     // true means free, false means processor is working
    processor1 = processor2 = processor3 = processor4 = processor5 = processor6 = processor7 = processor8 = true;
    int pro1_IdleTime, pro2_IdleTime, pro3_IdleTime, pro4_IdleTime, pro5_IdleTime, pro6_IdleTime, pro7_IdleTime, pro8_IdleTime;    // CPU waiting time
    pro1_IdleTime = pro2_IdleTime = pro3_IdleTime = pro4_IdleTime = pro5_IdleTime = pro6_IdleTime = pro7_IdleTime = pro8_IdleTime = 0;
    int pro1_RunTime, pro2_RunTime, pro3_RunTime, pro4_RunTime, pro5_RunTime, pro6_RunTime, pro7_RunTime, pro8_RunTime; // CPU time count
    pro1_RunTime = pro2_RunTime = pro3_RunTime = pro4_RunTime = pro5_RunTime = pro6_RunTime = pro7_RunTime = pro8_RunTime = -1;
    int currentTime = 0;    // current time count
    job* processor1Job = nullptr;   // assign job to processor 1
    job* processor2Job = nullptr;   // assign job to processor 2
    job* processor3Job = nullptr;   // assign job to processor 3
    job* processor4Job = nullptr;   // assign job to processor 4
    string empty = " ";
    string message1, message2, message3, message4, message5, message6, message7, message8;
    message1 = message2 = message3 = message4 = message5 = message6 = message7 = message8 = " ";
    int jobCount = 0;   // total arrival job
    
    // Metrics varibles
    long total_IdleTime, total_RunTime, total_jobInQTime, avg_jobInQTime;
    total_IdleTime = total_RunTime = total_jobInQTime = avg_jobInQTime = 0;
    int completeA, completeB, completeC, completeD;
    completeA = completeB = completeC = completeD = 0;
    int arrivalA, arrivalB, arrivalC, arrivalD;
    arrivalA = arrivalB = arrivalC = arrivalD = 0;
    int jobMax;
    jobMax = 0;
    long total_QueSize;
    total_QueSize = 0;
    
    // there are jobs in the normalQ or processor is still working
    // while (!normalQ.isEmpty() || !workQ.isEmpty() || !processor1 || !processor2 || !processor3 || !processor4)
     while (currentTime < 500) // initial metrics report condition
    // while (currentTime < 10000) // final metrics report condidtion
    {
        currentTime++;
        
        if (!workQ.isEmpty()) ++total_jobInQTime; // calculate total time jobs are in the work queue
        
        
        // when multiple jobs' arrival time is up, job goes to workQ from the normalQ
        while (normalQ.first()->arrival == currentTime) {
            jobCount++;
            job* jobPtr = new job;  // peek first job from normalQ
            *jobPtr = *(normalQ.first());       // pass value to a new varibale so dequeue won't delete copy value
            workQ.addPriority(jobPtr);
            normalQ.dequeue();
            cout << "Time " << currentTime << ":  Arrival: Overall Job:" << workQ.getSize() << ", Job " << jobPtr->type<< ":" << jobPtr->countType << ", Processing Time " << jobPtr->process << endl;
            logFile << "Time " << currentTime << ":  Arrival: Overall Job:" << workQ.getSize() << ", Job " << jobPtr->type<< ":" << jobPtr->countType << ", Processing Time " << jobPtr->process << endl;
            // calculate metrics
            if (workQ.getSize() >= jobMax) jobMax = workQ.getSize();
            if (jobPtr->type == 'A') ++arrivalA;
            else if (jobPtr->type == 'B') ++arrivalB;
            else if (jobPtr->type == 'C') ++arrivalC;
            else if (jobPtr->type == 'D') ++arrivalD;
            
        }
        // start processing job if workQ is not empty, or processor 1 is still working
        if (!workQ.isEmpty() || !processor1) {
            // processor 1 is free
            if (processor1 == true) {
                processor1Job = new job;
                *processor1Job = *(workQ.first());
                cout << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor1Job->type << ":" << processor1Job->countType << " in CPU 1" << endl;
                logFile << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor1Job->type << ":" << processor1Job->countType << " in CPU 1" << endl;
                workQ.dequeue();
                pro1_RunTime++;
                processor1 = false;
            }
            
            // processor1 is not free
            else {
                pro1_RunTime++;
                // if D comes in first and other processors are occupied, then interrupt current job then start processing D
                if (workQ.first()->type == 'D' && processor1Job->type != 'D' && !processor2 && !processor3 && !processor4) {
                    processor1Job->process = processor1Job->process - pro1_RunTime + 1; // recalculate current job processing time
                    workQ.putBack(processor1Job);
                    processor1Job = new job;
                    *processor1Job = *(workQ.first());  // resign D to processor
                    workQ.dequeue();
                    pro1_RunTime = -1;
                    pro1_RunTime++;
                }
                // job is finished, set processor free
                else if (pro1_RunTime == processor1Job->process) {
                    // calculate completed jobs
                    if (processor1Job->type == 'A') completeA += 1;
                    else if (processor1Job->type == 'B') completeB += 1;
                    else if (processor1Job->type == 'C') completeC += 1;
                    else if (processor1Job->type == 'D') completeD += 1;
                    // log file
                    cout << "Time " << currentTime << ":  Complete Processing Job:" << processor1Job->countJob << ", Job " << processor1Job->type << ":" << processor1Job->countType << endl;
                    logFile << "Time " << currentTime << ":  Complete Processing Job:" << processor1Job->countJob << ", Job " << processor1Job->type << ":" << processor1Job->countType << endl;
                    processor1 = true;
                    total_RunTime += pro1_RunTime; // add up total Run Time
                    pro1_RunTime = -1;
                    delete processor1Job;
                    processor1Job = nullptr;
                }
            }
        }
        // start processing job if workQ is not empty, or processor 2 is still working
        if (!workQ.isEmpty() || !processor2) {
            // processor 2 is free
            if (processor2 == true) {
                processor2Job = new job;
                *processor2Job = *(workQ.first());
                cout << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor2Job->type << ":" << processor2Job->countType << " in CPU 2" << endl;
                logFile << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor2Job->type << ":" << processor2Job->countType << " in CPU 2" << endl;
                workQ.dequeue();
                pro2_RunTime++;
                processor2 = false;
            }
            // processor 2 is not free
            else {
                pro2_RunTime++;
                // if D comes in first and other processors are occupied, then interrupt current job then start processing D
                if (workQ.first()->type == 'D' && processor2Job->type != 'D' && !processor3 && !processor4) {
                    processor2Job->process = processor2Job->process - pro2_RunTime + 1; // recalculate current job processing time
                    workQ.putBack(processor2Job);
                    processor2Job = new job;
                    *processor2Job = *(workQ.first());  // resign D to processor
                    workQ.dequeue();
                    pro2_RunTime = -1;
                    pro2_RunTime++;
                }
                // job is finished, set processor free
                else if (pro2_RunTime == processor2Job->process) {
                    // calculate completed jobs
                    if (processor2Job->type == 'A') completeA += 1;
                    else if (processor2Job->type == 'B') completeB += 1;
                    else if (processor2Job->type == 'C') completeC += 1;
                    else if (processor2Job->type == 'D') completeD += 1;
                    // log file
                    cout << "Time " << currentTime << ":  Complete Processing Job:" << processor2Job->countJob << ", Job " << processor2Job->type << ":" << processor2Job->countType << endl;
                    logFile << "Time " << currentTime << ":  Complete Processing Job:" << processor2Job->countJob << ", Job " << processor2Job->type << ":" << processor2Job->countType << endl;
                    processor2 = true;
                    total_RunTime += pro2_RunTime; // add up total Run Time
                    pro2_RunTime = -1;
                    delete processor2Job;
                    processor2Job = nullptr;
                }
            }
        }
        // start processing job if workQ is not empty, or processor 3 is still working
        if (!workQ.isEmpty() || !processor3) {
            // processor 3 is free
            if (processor3 == true) {
                processor3Job = new job;
                *processor3Job = *(workQ.first());
                cout << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor3Job->type << ":" << processor3Job->countType << " in CPU 3" << endl;
                logFile << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor3Job->type << ":" << processor3Job->countType << " in CPU 3" << endl;
                workQ.dequeue();
                pro3_RunTime++;
                processor3 = false;
            }
            // processor 3 is not free
            else {
                pro3_RunTime++;
                // if D comes in first and other processors are occupied, then interrupt current job then start processing D
                if (workQ.first()->type == 'D' && processor3Job->type != 'D' && !processor4) {
                    processor3Job->process = processor3Job->process - pro3_RunTime + 1; // recalculate current job processing time
                    workQ.putBack(processor3Job);
                    processor3Job = new job;
                    *processor3Job = *(workQ.first());  // resign D to processor
                    workQ.dequeue();
                    pro3_RunTime = -1;
                    pro3_RunTime++;
                }
                // job is finished, set processor free
                else if (pro3_RunTime == processor3Job->process) {
                    // calculate completed jobs
                    if (processor3Job->type == 'A') completeA += 1;
                    else if (processor3Job->type == 'B') completeB += 1;
                    else if (processor3Job->type == 'C') completeC += 1;
                    else if (processor3Job->type == 'D') completeD += 1;
                    // log file
                    cout << "Time " << currentTime << ":  Complete Processing Job:" << processor3Job->countJob << ", Job " << processor3Job->type << ":" << processor3Job->countType << endl;
                    logFile << "Time " << currentTime << ":  Complete Processing Job:" << processor3Job->countJob << ", Job " << processor3Job->type << ":" << processor3Job->countType << endl;
                    processor3 = true;
                    total_RunTime += pro3_RunTime; // add up total Run Time
                    pro3_RunTime = -1;
                    delete processor3Job;
                    processor3Job = nullptr;
                }
            }
        }
        // start processing job if workQ is not empty, or processor 4 is still working
        if (!workQ.isEmpty() || !processor4) {
            // processor 4 is free
            if (processor4 == true) {
                processor4Job = new job;
                *processor4Job = *(workQ.first());
                cout << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor4Job->type << ":" << processor4Job->countType << " in CPU 4" << endl;
                logFile << "Time " << currentTime << ":- Begin Processing Job:" << jobCount << ", Job " << processor4Job->type << ":" << processor4Job->countType << " in CPU 4" << endl;
                workQ.dequeue();
                pro4_RunTime++;
                processor4 = false;
            }
            // processor 4 is not free
            else {
                pro4_RunTime++;
                // if D comes in first and other processors are occupied, then interrupt current job then start processing D
                if (workQ.first()->type == 'D' && processor4Job->type != 'D') {
                    processor4Job->process = processor4Job->process - pro4_RunTime + 1; // recalculate current job processing time
                    workQ.putBack(processor4Job);
                    processor4Job = new job;
                    *processor4Job = *(workQ.first());  // resign D to processor
                    workQ.dequeue();
                    pro4_RunTime = -1;
                    pro4_RunTime++;
                }
                // job is finished, set processor free
                else if (pro4_RunTime == processor4Job->process) {
                    // calculate completed jobs
                    if (processor4Job->type == 'A') completeA += 1;
                    else if (processor4Job->type == 'B') completeB += 1;
                    else if (processor4Job->type == 'C') completeC += 1;
                    else if (processor4Job->type == 'D') completeD += 1;
                    // log file
                    cout << "Time " << currentTime << ":  Complete Processing Job:" << processor4Job->countJob << ", Job " << processor4Job->type << ":" << processor4Job->countType << endl;
                    logFile << "Time " << currentTime << ":  Complete Processing Job:" << processor4Job->countJob << ", Job " << processor4Job->type << ":" << processor4Job->countType << endl;
                    processor4 = true;
                    total_RunTime += pro4_RunTime; // add up total Run Time
                    pro4_RunTime = -1;
                    delete processor4Job;
                    processor4Job = nullptr;
                }
            }
        }
        
        // print out runtime and idle time
        if (workQ.isEmpty() == true) empty = "Empty";
        else empty = to_string(workQ.getSize()) + " Job";
        if (pro1_RunTime == -1) {    // if processor run time is 0
            ++pro1_IdleTime;  // idel time only increase once
            ++total_IdleTime; // add up total Idle Time
            message1 = "; CPU 1 Idle Time:" + to_string(pro1_IdleTime);
        }
        else {
            message1 = "; CPU 1 Run Time:" + to_string(pro1_RunTime);
            pro1_IdleTime = -1; // reset waiting time
        }
        if (pro2_RunTime == -1) {
            ++pro2_IdleTime;  // idel time only increase once
            ++total_IdleTime; // add up total Idle Time
            message2 = "; CPU 2 Idle Time:" + to_string(pro2_IdleTime);
        }
        else {
            message2 = "; CPU 2 Run Time:" + to_string(pro2_RunTime);
            pro2_IdleTime = -1; // reset waiting time
        }
        if (pro3_RunTime == -1) {
            ++pro3_IdleTime;  // idel time only increase once
            ++total_IdleTime; // add up total Idle Time
            message3 = "; CPU 3 Idle Time:" + to_string(pro3_IdleTime);
        }
        else {
            message3 = "; CPU 3 Run Time:" + to_string(pro3_RunTime);
            pro3_IdleTime = -1; // reset waiting time
        }
        if (pro4_RunTime == -1) {
            ++pro4_IdleTime;  // idel time only increase once
            ++total_IdleTime; // add up total Idle Time
            message4 = "; CPU 4 Idle Time:" + to_string(pro4_IdleTime);
        }
        else {
            message4 = "; CPU 4 Run Time:" + to_string(pro4_RunTime);
            pro4_IdleTime = -1; // reset waiting time
        }
        cout << "Time " << currentTime << ":  Queue: " << empty << message1 << message2 << message3 << message4 << endl;
        logFile << "Time " << currentTime << ":  Queue: " << empty << message1 << message2 << message3 << message4 << endl;
        
        total_QueSize += (workQ.getSize() + normalQ.getSize()); // calculate total normalQ size every time unit
    }
    
    // if (!workQ.isEmpty()) avg_jobInQTime = total_jobInQTime / workQ.getSize();  // total wait time divided by count of jobs that had to wait in queue if workQ is not empty
    avg_jobInQTime = total_jobInQTime / (completeA + completeB + completeC + completeD);  // total wait time divided by count of jobs processed over that time
    
    // metrics report
    cout << endl << "Metrics:" << endl;
    cout << "--------------------------------------------------------------\n";
    cout << "Number of processor(s) being used: 4" << endl;
    cout << "Current queue size: " << normalQ.getSize() + workQ.getSize() << endl;
    cout << "Average queue size: " << total_QueSize / currentTime << endl;
    cout << "Maximum jobs in queue: " << jobMax << endl;
    cout << "Total time jobs are in queue: " << total_jobInQTime << " time units" << endl;
    cout << "Average time jobs are in queue: " << avg_jobInQTime << " time units" << endl;
    cout << "Total number of A jobs arrived:   " << arrivalA << endl;
    cout << "Total number of A jobs completed: " << completeA << endl;
    cout << "Total number of B jobs arrived:   " << arrivalB << endl;
    cout << "Total number of B jobs completed: " << completeB << endl;
    cout << "Total number of C jobs arrived:   " << arrivalC << endl;
    cout << "Total number of C jobs completed: " << completeC << endl;
    cout << "Total number of D jobs arrived:   " << arrivalD << endl;
    cout << "Total number of D jobs completed: " << completeD << endl;
    cout << "Total jobs completed: " << completeA + completeB + completeC + completeD << endl;
    cout << "Total time CPU(s) were processing: " << total_RunTime << " time units" << endl;
    cout << "Total time CPU(s) were idle:       " << total_IdleTime << " time units" << endl;
    cout << "--------------------------------------------------------------\n";
    
    
    logFile.close();
    jobFile.close();
    return 0;
}

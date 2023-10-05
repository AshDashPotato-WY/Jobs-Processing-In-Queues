#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

const int SIZE_A = 2500;
const int SIZE_B = 1670;
const int SIZE_C = 1250;
const int SIZE_D = 500;
const int SIZE_ABC = SIZE_A + SIZE_B + SIZE_C;
const int MASTER_SIZE = SIZE_A + SIZE_B + SIZE_C + SIZE_D;

struct JobsA {
	char jobName = 'A';
	int jobA_Arrival = { 0 };
	int jobA_Processing = { 0 };
};

struct JobsB {
	char jobName = 'B';
	int jobB_Arrival = { 0 };
	int jobB_Processing = { 0 };
};

struct JobsC {
	char jobName = 'C';
	int jobC_Arrival = { 0 };
	int jobC_Processing = { 0 };
};

struct JobsD {
	char jobName = 'D';
	int jobD_Arrival = { 0 };
	int jobD_Processing = { 0 };
};

struct masterJobs {
	char jobName = 'Z';
	int master = { 0 };
	int masterJobProcessing = { 0 };
};

bool comparisonUnsorted(masterJobs a, masterJobs b);
void sortArray(masterJobs randJobs[MASTER_SIZE], const int counter);

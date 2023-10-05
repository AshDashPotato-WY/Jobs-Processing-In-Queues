#include "randomJobs.hpp"

int main() {
	int i = 0, j = 0, k = 0, count = 0;
	JobsA randomJobsA[SIZE_A];
	JobsB randomJobsB[SIZE_B];
	JobsC randomJobsC[SIZE_C];
	JobsD randomJobsD[SIZE_D];
	ofstream data;
	data.open("/Users/ashley/Dropbox (University of Michigan)/Ashley Yu’s files/Home/CIS 200/Lab/Project 2/Program 1/randomJobs.txt");

	//---------------------------------generate random jobs--------------------------------------
	for (i = 0; i < SIZE_A; ++i) {
		randomJobsA[i].jobA_Arrival = 4 + rand() % 3;
		randomJobsA[i].jobA_Processing = 1 + rand() % 5;
	}
	for (i = 0; i < SIZE_B; ++i) {
		randomJobsB[i].jobB_Arrival = 6 + rand() % 3;
		randomJobsB[i].jobB_Processing = 2 + rand() % 7;
	}
	for (i = 0; i < SIZE_C; ++i) {
		randomJobsC[i].jobC_Arrival = 4 + rand() % 15;
		randomJobsC[i].jobC_Processing = 6 + rand() % 7;
	}

	for (i = 0; i < SIZE_D; ++i) {
		randomJobsD[i].jobD_Arrival = 14 + rand() % 11;
		randomJobsD[i].jobD_Processing = 7 + rand() % 11;
	}

	//-------------------------------------load into master jobs-------------------------------------
	masterJobs masterList[MASTER_SIZE];
	masterList[0] = { randomJobsA[0].jobName, randomJobsA[0].jobA_Arrival, randomJobsA[0].jobA_Processing }; //load first item
	count = randomJobsA[0].jobA_Arrival; 
	for (i = 1; i < SIZE_A; ++i) {
		count = count + randomJobsA[i].jobA_Arrival; //add to previous arrival time
		masterList[i] = {randomJobsA[i].jobName, count, randomJobsA[i].jobA_Processing};
	}
	masterList[SIZE_A] = { randomJobsB[0].jobName, randomJobsB[0].jobB_Arrival, randomJobsB[0].jobB_Processing };
	count = randomJobsB[0].jobB_Arrival;
	for (i = SIZE_A + 1, j = 1; i < SIZE_A + SIZE_B; ++i, ++j) {
		count = count + randomJobsB[j].jobB_Arrival;
		masterList[i] = { randomJobsB[j].jobName, count, randomJobsB[j].jobB_Processing };
	}
	masterList[SIZE_A + SIZE_B] = { randomJobsC[0].jobName, randomJobsC[0].jobC_Arrival, randomJobsC[0].jobC_Processing };
	count = randomJobsC[0].jobC_Arrival;
	for (i = SIZE_A + SIZE_B + 1, j = 1; i < SIZE_ABC; ++i, ++j) {
		count = count + randomJobsC[j].jobC_Arrival;
		masterList[i] = { randomJobsC[j].jobName, count, randomJobsC[j].jobC_Processing };
	}
	masterList[SIZE_ABC] = { randomJobsD[0].jobName, randomJobsD[0].jobD_Arrival, randomJobsD[0].jobD_Processing };
	count = randomJobsD[0].jobD_Arrival;
	for (i = SIZE_ABC+1, j = 1; i < MASTER_SIZE; ++i, ++j) {
		count = count + randomJobsD[j].jobD_Arrival;
		masterList[i] = { randomJobsD[j].jobName, count, randomJobsD[j].jobD_Processing };
	}

	//-------------------------------------sort array------------------------------------------
	sortArray(masterList, MASTER_SIZE);

	//---------------------------------make Job Type D the top of the list--------------------------
	k = 3; //max 3 times swap between A->D, B->D and C->D
	while (k != 0) {
		for (i = 0, j = 1; i < MASTER_SIZE; ++i, ++j) {
			while (masterList[i].master == masterList[j].master && masterList[j].jobName == 'D') { //swap 2 data if D is involved && both arrival times are the same
				masterJobs temp = masterList[i];
				masterList[i] = masterList[j];
				masterList[j] = temp;
			}
		}
		k--;
	}

	//-----------------------------------------write to file--------------------------------------------
	for (i = 0; i < MASTER_SIZE; ++i) {
		data << masterList[i].jobName << "\t" << masterList[i].master << "\t" << masterList[i].masterJobProcessing << "\n";
	}
	return 0;
}

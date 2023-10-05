#include "randomJobs.hpp"

bool comparisonUnsorted(masterJobs a, masterJobs b) {
	if (a.master < b.master)
	{
		return 1;
	}
	else {
		return 0;
	}
}
void sortArray(masterJobs randJobs[SIZE_ABC], const int counter) {
	sort(randJobs, randJobs + counter, comparisonUnsorted);
}

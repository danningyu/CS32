//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//int calledCounter = 0; //remove before submitting
////check for capitalization!!

// Return the number of ways that all n2 elements of a2 appear
	  // in the n1 element array a1 in the same order (though not
	  // necessarily consecutively).  The empty sequence appears in a
	  // sequence of length n1 in 1 way, even if n1 is 0.
	  // For example, if a1 is the 7 element array
	  //    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
	  // then for this value of a2            the function must return
	  //    "stan" "kenny" "cartman"                      1
	  //    "stan" "cartman" "butters"                    2
	  //    "kenny" "stan" "cartman"                      0
	  //    "kyle" "cartman" "butters"                    3
int countIncludes(const string a1[], int n1, const string a2[], int n2){
	int counter = 0;
	if (n2 <= 0) {
		// cout << "Reached base case" << endl;
		return 1;
	}
	if (n1 <= 0) {
		return 0;
	}
	if (n1 <= 0 && n2 != 0) { //no matches found
		// cout << "No matches found" << endl;
		return 0;
	}
	if (a2[n2 - 1] == a1[n1 - 1]) { //match found
		// cout << "Match found for " << a2[n2 - 1] << endl;
		counter = counter + countIncludes(a1, n1 - 1, a2, n2);
		// cout << "Counter inside found: " << counter << endl;
		return counter + countIncludes(a1, n1 - 1, a2, n2 - 1); //check the next element
	}

	// cout << "Match not found, checking next element" << endl;
	// cout << "Counter outside found: " << counter << endl;
	return countIncludes(a1, n1 - 1, a2, n2); //equality not found, move on to next value in a1	
}

// Exchange two strings
void exchange(string& x, string& y){
	string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator, int& firstNotLess, int& firstGreater){
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < separator
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > separator

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n){
	int firstNotLess = 0; //set whatever values cause separate() will adjust them correctly
	int firstGreater = 0;
	if (n <= 1) { //base case and catches bad n input
		// cout << "Reached base case" << endl;
		return;
	}
	
	separate(a, n, a[n / 2], firstNotLess, firstGreater);
	// cout << "Ordering subarrays" << endl;
	order(a, firstNotLess); //first half of array
	order(a + firstGreater, n-firstGreater); //start at second half, only go the remaining elements
}
//
//int main() {
//	string arr6[] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters", "cartman" };
//	string arr7[] = { "stan", "kenny", "cartman" };
//	string arr8[] = { "stan", "cartman", "butters" };
//	string arr9[] = { "kenny", "stan", "cartman" };
//	string arr10[] = { "kyle", "cartman", "butters" };
//	string arr11[] = { "kyle", "cartman" };
//	calledCounter = 0;
//	assert(countIncludes(arr6, 7, arr7, 3) == 1);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	calledCounter = 0;
//	assert(countIncludes(arr6, 7, arr8, 3) == 2);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	calledCounter = 0;
//	assert(countIncludes(arr6, 7, arr9, 3) == 0);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	calledCounter = 0;
//	assert(countIncludes(arr6, 7, arr10, 3) == 3);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	calledCounter = 0;
//	assert(countIncludes(arr6, 8, arr11, 2) == 5);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	string arr12[] = { "CS32", "Math 32B", "CS30", "Math 33A", "CS31", "", "CS33", "Phys 1A" };
//	order(arr12, 8);
//	assert(arr12[0] == "");
//	assert(arr12[1] == "CS30");
//	assert(arr12[2] == "CS31");
//	assert(arr12[3] == "CS32");
//	assert(arr12[4] == "CS33");
//	assert(arr12[5] == "Math 32B");
//	assert(arr12[6] == "Math 33A");
//	assert(arr12[7] == "Phys 1A");
//	string arr13[] = { "CS32", "Math 32B", "CS30", "Math 33A", "CS31", "CS33", "", "Phys 1A" };
//	order(arr13, 0);
//	order(arr13, 1);
//	assert(arr13[0] == "CS32"); //elements should be unchanged
//	assert(arr13[1] == "Math 32B");
//	assert(arr13[2] == "CS30");
//	assert(arr13[3] == "Math 33A");
//	assert(arr13[4] == "CS31");
//	assert(arr13[5] == "CS33");
//	assert(arr13[6] == "");
//	assert(arr13[7] == "Phys 1A");
//	string arr14[] = { "1", "1", "1", "3", "3", "2", "3", "2", "2", "3" };
//	//size = 9
//	string arr15[] = { "1" };
//	string arr16[] = { "1", "2" };
//	string arr17[] = { "3", "2" };
//	string arr18[] = { "1", "2", "3" };
//	calledCounter = 0;
//	assert(countIncludes(arr14, 10, arr15, 1) == 3);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	calledCounter = 0;
//	assert(countIncludes(arr14, 10, arr16, 2) == 9);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	calledCounter = 0;
//	assert(countIncludes(arr14, 10, arr17, 2) == 8);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	calledCounter = 0;
//	assert(countIncludes(arr14, 10, arr18, 3) == 12);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	string arr19[] = { "5", "6", "7", "8" };
//	calledCounter = 0;
//	assert(countIncludes(arr14, 10, arr18, 4) == 0);
//	cout << "STRING EQUALITY TESTED " << calledCounter << " TIMES" << endl;
//	order(arr14, 10);
//	for (int i = 0; i < 10; i++) {
//		cout << arr14[i] << ", ";
//	}
//	cout << endl;
//	string arr20[] = { "a", "a", "d", "d" };
//	string arr21[] = { "a", "d" };
//	assert(countIncludes(arr20, 4, arr21, 2) == 4);
//
//	cout << "Passed all tests! Yay!" << endl;
//
//	string scrambled[] = { "x", "r", "z", "a", "k" };
//	order(scrambled, 5);
//	assert(scrambled[0] == "a");
//	assert(scrambled[1] == "k");
//	assert(scrambled[2] == "r");
//	assert(scrambled[3] == "x");
//	assert(scrambled[4] == "z");
//
//	string b1[] = { "stan", "kyle", "cartman", "kenny",
//					"kyle", "cartman", "butters" };
//	string test1[] = { "stan", "kenny", "cartman" };
//	string test2[] = { "stan", "cartman", "butters" };
//	string test3[] = { "kenny", "stan", "cartman" };
//	string test4[] = { "kyle", "cartman", "butters" };
//
//	assert(countIncludes(b1, 7, test1, 3) == 1);
//	assert(countIncludes(b1, 7, test2, 3) == 2);
//	assert(countIncludes(b1, 7, test3, 3) == 0);
//	assert(countIncludes(b1, 7, test4, 3) == 3);
//	assert(countIncludes(b1, 7, test1, 0) == 1);
//	assert(countIncludes(b1, 0, test1, 0) == 1);
//	assert(countIncludes(b1, 7, test1, -10) == 1);
//	assert(countIncludes(b1, -10, test1, -10) == 1);
//	assert(countIncludes(b1, 0, test1, 3) == 0);
//
//	cout << "Passed all test cases!" << endl;
//}
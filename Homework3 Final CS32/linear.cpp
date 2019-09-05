//#include <string>
//#include <cassert>
//#include <iostream>
//using namespace std;
//IF ALL DIGITS RETURN FALSE
//bool somePredicate(string s)
//{
//	int nDigits = 0;
//	for (int k = 0; k != s.size(); k++)
//	{
//		if (isdigit(s[k]))
//			nDigits++;
//	}
//	return nDigits == 3;
//}

//bool somePredicate(string s) {
//	cout << "string passed in: " << s << endl;
//	// cout << "Returning " << s.empty() << endl;
//	return s.empty();
//}

// Return false if the somePredicate function returns false for at
	  // least one of the array elements; return true otherwise.
//aka if one of the strings is NOT empty, return false
bool allTrue(const string a[], int n){
	// cout << "Calling allTrue with n = " << n << endl;
	if (n <= 0) { //edge case
		return true;
	}
	if (n<2) {
		return somePredicate(a[n - 1]);
	}
	return allTrue(a, n - 1) && somePredicate(a[n-1]);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
//false is 0 and true is 1
int countFalse(const string a[], int n){
	if (n <= 0) { //edge case
		return 0;
	}
	int counter = 0;
	// cout << "Calling counterFalse with n = " << n << endl;
	if (n < 2) {
		return !somePredicate(a[n - 1]);
	}
	// cout << "Counter is equal to " 
	// << counter + countFalse(a, n - 1) + somePredicate(a[n - 1]) << endl;
	return counter + countFalse(a, n - 1) + !somePredicate(a[n - 1]);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
//FIRST ELEMENT THAT'S NOT EMPTY
int firstFalse(const string a[], int n) {
	if (n <= 0) { //edge case
		return -1;
	}
	// cout << "Calling firstFalse for n = " << n << endl;
	if (n == 1 && somePredicate(a[0]) == false) { //first element is false
		// cout << "Base case reached" << endl;
		return 0;
	}
	else if (n == 1) {
		// cout << "First element returns true" << endl;
		return -1;
	}
	if (somePredicate(a[n - 1]) == false) {
		// cout << "False case found for n = " << n - 1 << endl;
		int index = firstFalse(a, n - 1);
		if (index < n - 1 && index != -1) {
			return index;
		}
		return n - 1;
	}
	// cout << "True case found for n = " << n - 1 << endl;
	return firstFalse(a, n - 1);
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n){
	if (n <= 0) {
		return -1;
	}
	// cout << "Calling indexOfLeast for n = " << n << endl;
	if (n == 1) {
		// cout << "Base case reached" << endl;
		return 0;
	}
	int index = indexOfLeast(a, n - 1);
	if (a[index] <= a[n-1]) {
		// cout << "Making comparison between" <<a[index] << " and " <<a[n-1] << endl;
		return index;
	}
	return n-1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2){
	if (n2 <= 0) { //base case
		return true;
	}
	if (n1 <= 0) {
		return false;
	}
	if (n1 < 0 && n2!=0) { //searched through list and not all a2 match
		// cout << "Base case reached" << endl;
		return false;
	}
	if (a2[n2 - 1] == a1[n1 - 1]) { //equality found, so move on to next value
		// cout << "Match found for " << a2[n2 - 1] << endl;
		return includes(a1, n1 - 1, a2, n2 - 1);
	}
	// cout << "Match not found, checking next element" << endl;
	return includes(a1, n1 - 1, a2, n2); //equality not found, move on to next value in a1
}

//int main() {
//	//// my somePredicate: return s.empty(); That is, TRUE if string is empty
//	//string arr1[] = { "CS31", "CS32", "CS33", "", "CS33" };
//	//string arr2[] = { "", "", "", "" };
//	//string arr3[] = { "CS31", "", "", "" };
//	//string arr4[] = { "", "", "", "CS31" };
//	//string arr5[] = { "CS31", "CS333", "CS32", "CS33" };
//	//string arr5A[] = { "", "CS31", "" };
//	//string arr5B[] = { "CS33", "CS333", "CS32", "CS33", "CS31", "CS31" };
//	//{assert(allTrue(arr1, 5) == false);
//	//assert(allTrue(arr2, 4) == true);
//	//assert(allTrue(arr3, 4) == false);
//	//assert(allTrue(arr4, 4) == false);
//	//assert(allTrue(arr5, 4) == false);
//	//assert(allTrue(arr5A, 3) == false);
//	//assert(allTrue(arr5A, 1) == true);
//	//assert(allTrue(arr1, -1) == true);
//	//assert(allTrue(arr1, 0) == true); 
//	//assert(allTrue(arr5B, 6) == false); }
//
//	//{assert(countFalse(arr1, 5) == 4);
//	//assert(countFalse(arr2, 4) == 0);
//	//assert(countFalse(arr3, 4) == 1);
//	//assert(countFalse(arr4, 4) == 1);
//	//assert(countFalse(arr5, 4) == 4);
//	//assert(countFalse(arr5A, 1) == 0);
//	//assert(countFalse(arr5A, 3) == 1);
//	//assert(countFalse(arr1, -1) == 0);
//	//assert(countFalse(arr1, 0) == 0); 
//	//assert(countFalse(arr5B, 6) == 6); }
//	//assert(firstFalse(arr1, 5) == 0);
//	//assert(firstFalse(arr2, 4) == -1);
//	//assert(firstFalse(arr3, 4) == 0);
//	//assert(firstFalse(arr4, 4) == 3);
//	//assert(firstFalse(arr5, 4) == 0);
//	//assert(firstFalse(arr5A, 1) == -1);
//	//assert(firstFalse(arr5A, 3) == 1);
//	//assert(firstFalse(arr1, -1) == -1);
//	//assert(firstFalse(arr1, 0) == -1);
//	//
//	//
//	//
//	//assert(indexOfLeast(arr5, 4) == 0);
//	//assert(indexOfLeast(arr1, 5) == 3);
//	//assert(indexOfLeast(arr2, 4) == 0);
//	//assert(indexOfLeast(arr3, 4) == 1);
//	//assert(indexOfLeast(arr4, 4) == 0);
//	//assert(indexOfLeast(arr5A, 3) == 0);
//	//assert(indexOfLeast(arr5A, 1) == 0);
//	//assert(indexOfLeast(arr5B, 6) == 4);
//	//assert(indexOfLeast(arr1, 0) == -1);
//	//assert(indexOfLeast(arr1, -1) == -1);
//	//assert(indexOfLeast(arr5B, 6) == 4);
//	//string arr6[] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
//	//string arr7[] = { "kyle", "kenny", "butters" };
//	//string arr8[] = { "kyle", "cartman", "cartman" };
//	//string arr9[] = { "kyle", "butters", "kenny" };
//	//string arr10[] = { "stan", "kenny", "kenny" };
//	//assert(includes(arr6, 7, arr7, 3));
//	//assert(includes(arr6, 7, arr8, 3));
//	//assert(!includes(arr6, 7, arr9, 3));
//	//assert(!includes(arr6, 7, arr10, 3));
//	//assert(!includes(arr6, 0, arr10, 3)); //n1 = 0 
//	//assert(includes(arr6, 7, arr10, 0)); //n2 = 0
//	//assert(includes(arr6, 0, arr10, 0)); //n1 = n2 = 0, n2 = 0 takes precedence
//	//cout << "All tests passed! Yay!" << endl;
//	return 0;
//}

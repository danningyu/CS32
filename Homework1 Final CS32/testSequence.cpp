#include "Sequence.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(){
	Sequence s;
	unsigned long temp = 100;
	//check the sequence is empty:
	assert(s.empty() == true);
	assert(s.size() == 0);
	assert(s.get(0, temp) == false);
	assert(s.set(0, temp) == false);
	assert(s.find(100)== -1);
	//now insert elements using insert() with 2 parameters
	assert(s.insert(0, 2) == 0); //cs31
	assert(s.insert(0, 3) == 0); //cs32, cs31
	assert(s.insert(1, 4) == 1); //cs32, cs33, cs31
	assert(s.insert(2, 6) == 2); //cs32, cs33, math 32a, cs31
	assert(s.insert(0, 7) == 0); //math 32b, cs32, cs33, math 32a, cs31
	assert(s.insert(6, 50) == -1);
	assert(s.insert(-2, 50)== -1);
	assert(s.empty() == false);
	assert(s.size() == 5);
	assert(s.find(7) == 0);
	assert(s.find(3) == 1);
	assert(s.find(4) == 2);
	assert(s.find(6) == 3);
	assert(s.find(2) == 4);
	s.get(0, temp);
	assert(temp == 7);
	s.get(1, temp);
	assert(temp == 3);
	s.get(2, temp);
	assert(temp == 4);
	s.get(3, temp);
	assert(temp == 6);
	s.get(4, temp);
	assert(temp == 2);
	assert(s.erase(0) == true); //cs32, cs33, math 32a, cs31
	s.get(0, temp);
	assert(temp == 3);
	s.get(1, temp);
	assert(temp == 4);
	s.get(2, temp);
	assert(temp == 6);
	s.get(3, temp);
	assert(temp == 2);
	assert(s.insert(6) == 2); //cs32, cs33, math 32a, math 32a, cs31
	assert(s.find(6) == 2); //should find 1st element at 2, not 2nd at 3
	assert(s.insert(5) == 2); //cs32, cs33, math 32, math 32a, math 32a, cs31
	assert(s.remove(6) == 2); //cs32, cs33, math 32, cs31
	s.get(0, temp);
	assert(temp == 3);
	s.get(1, temp);
	assert(temp == 4);
	s.get(2, temp);
	assert(temp == 5);
	s.get(3, temp);
	assert(temp == 2);
	assert(s.erase(-1) == false);
	assert(s.erase(5) == false);
	assert(s.size() == 4);
	assert(s.empty() == false);
	assert(s.find(6) == -1);
	assert(s.find(3) == 0);
	assert(s.find(4) == 1);
	assert(s.find(5) == 2);
	assert(s.find(2) == 3);
	assert(s.find(1) == -1);
	assert(s.set(0, 4) == true); //cs33, cs33, math 32, cs31
	assert(s.size() == 4); //# of elements unchanged
	assert(s.find(4) == 0); //first cs33 occurs at 0
	assert(s.empty() == false);
	assert(s.set(-1, 4) == false);
	assert(s.set(10, 4) == false);
	assert(s.remove(4) == 2); // math 32, cs31
	assert(s.size() == 2);
	assert(s.empty() == false);
	assert(s.erase(0) == true); //cs31
	assert(s.find(2) == 0);
	assert(s.get(1, temp) == false); //element 1 no longer exists
	assert(s.remove(2) == 1); //now s is empty
	assert(s.size() == 0);
	assert(s.empty() == true);
	cerr << "Passed all tests!" << endl;
	return 0;
}
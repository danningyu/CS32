#include "ScoreList.h"
#include <iostream>
#include <cassert>

int main() {
	//want: 0, 1, 2, 3, 10, 10, 25, 30, 45, 50, 90, 95, 99, 100
	ScoreList s;
	assert(s.add(1));
	assert(s.size() == 1);
	assert(s.add(3));
	assert(s.add(10));
	assert(s.add(10));
	assert(s.add(30));
	assert(s.size() == 5);
	assert(s.add(25));
	assert(s.add(45));
	assert(s.add(50));
	assert(s.add(99));
	assert(s.add(90));
	assert(s.add(95));
	assert(s.size() == 11);
	assert(s.add(-100) == false);
	assert(s.add(-1) == false);
	assert(s.add(101) == false);
	assert(s.size() == 11); //size should be unchanged
	assert(s.minimum() == 1);
	assert(s.maximum() == 99);
	assert(s.add(100));
	assert(s.add(0));
	assert(s.add(2));
	assert(s.size() == 14);
	assert(s.minimum() == 0);
	assert(s.maximum() == 100);
	assert(s.remove(1)); // 0, 2, 3, 10, 10, 25, 30, 45, 50, 90, 95, 99, 100
	assert(s.size() == 13);
	assert(s.remove(1) == false); //1 is no longer there
	assert(s.size() == 13);
	assert(s.remove(0));
	assert(s.remove(0) == false);
	assert(s.minimum() == 2);
	assert(s.remove(10)); // 2, 3, 10, 25, 30, 45, 50, 90, 95, 99, 100
	assert(s.remove(10)); // 2, 3, 25, 30, 45, 50, 90, 95, 99, 100
	assert(s.remove(10) == false);
	assert(s.size() == 10);
	assert(s.remove(100)); // 2, 3, 25, 30, 45, 50, 90, 95, 99
	assert(s.size() == 9);
	assert(s.maximum() == 99);
	
	s.remove(2);
	s.remove(3);
	s.remove(25);
	s.remove(30);
	s.remove(50);
	s.remove(45);
	s.remove(90);
	s.remove(95);
	s.remove(99);
	assert(s.size() == 0);
	assert(s.maximum() == NO_SCORE);
	assert(s.minimum() == NO_SCORE);
	assert(s.remove(1) == false);
	std::cerr << "All tests passed for ScoreList!" << std::endl;
	return 0;
}
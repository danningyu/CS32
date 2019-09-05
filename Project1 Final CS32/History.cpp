#include "History.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
{
	m_nRows = nRows;
	m_nCols = nCols;
	for (int i = 0; i < m_nRows; i++) {
		for (int j = 0; j < m_nCols; j++) {
			history[i][j] = '.';
		}
	}
}

bool History::record(int r, int c) {
	if (r > m_nRows || c > m_nCols || r < 1 || c < 1) { //check if within grid
		return false;
	}
	if (history[r-1][c-1] == '.') { //if currently "0" there
		//need -1 because arrays count from 0
		history[r-1][c-1] = 'A';
	}
	else if (history[r-1][c-1] == 'Z') { //don't change it...
		return true; //...and then terminate it right here
	}
	else {
		(history[r-1][c-1])++; //increment to next letter
	}
	return true;
}
void History::display() const {
	clearScreen();
	//add in modifications as needed
	//print grid
	for (int i = 0; i < m_nRows; i++) {
		for (int j = 0; j < m_nCols; j++) {
			cout << history[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole):m_holesPerSide(nHoles) {
	//initial beans per hole is 4 as per project spec
	//nHoles is 6 as per project spec
	int nHolesFixed = nHoles;
	if (nHolesFixed <= 1) {
		nHolesFixed = 1;
		m_holesPerSide = 1; //fix value of m_holesPerSide
	}
	//minimum array size should always be 2
	int temp = nInitialBeansPerHole; //temp = nInitialBeansPerHoleFixed
	if (temp < 0) {
		temp = 0;
	}
	m_northBeans = new int[nHolesFixed +1]; //# of holes, plus 1 for the pot	
	//0 is pot, holes are 6-1, proceed in decreasing order
	m_southBeans = new int[nHolesFixed +1];
	//0 is pot, holes are 1-6, proceed in increasing order
	//S1, S2...S6, S0, N6, N5...N1, N0, S1, S2...repeat
	for (int i = 1; i < nHolesFixed + 1; i++) {
		m_northBeans[i] = temp;
		m_southBeans[i] = temp;
	}
	m_northBeans[0] = 0;
	m_southBeans[0] = 0;
}

Board::Board(const Board& other):m_holesPerSide(other.m_holesPerSide) {
	m_northBeans = new int[m_holesPerSide + 1];
	m_southBeans = new int[m_holesPerSide + 1];
	for (int i = 0; i < m_holesPerSide + 1; i++) {
		m_northBeans[i] = other.m_northBeans[i];
		m_southBeans[i] = other.m_southBeans[i];
	}
}

Board& Board::operator=(const Board& rhs) {
	if (this != &rhs) {
		Board temp(rhs);
		swap(temp);
	}
	return *this;
}

void Board::swap(Board& other) {
	int tempHoles = m_holesPerSide;
	m_holesPerSide = other.m_holesPerSide;
	other.m_holesPerSide = tempHoles;
	int* tempPtr1 = m_northBeans;
	int* tempPtr2 = m_southBeans;
	m_northBeans = other.m_northBeans;
	m_southBeans = other.m_southBeans;
	other.m_northBeans = tempPtr1;
	other.m_southBeans = tempPtr2;
}

Board::~Board() {
	delete[] m_northBeans;
	delete[] m_southBeans;
}
int Board::holes() const {
	return m_holesPerSide;
}
int Board::beans(Side s, int hole) const {
	// cerr << "Calling Board::beans" << endl;
	if (hole <0 || hole >= m_holesPerSide + 1) { //hole is out of bounds
		//can't access if index is < 0 or >= size of array
		return -1;
	}
	if (s == Side::NORTH) {
		return m_northBeans[hole];
	}
	return m_southBeans[hole];
}
int Board::beansInPlay(Side s) const {
	int counter = 0;
	if (s == Side::NORTH) {
		for (int i = 1; i < m_holesPerSide + 1; i++) {
			counter = counter + m_northBeans[i];
		}
		// cerr << "Current number of beans in play for NORTH: " << counter << endl;
		return counter;
	}
	//if not NORTH, then it's SOUTH
	for (int i = 1; i < m_holesPerSide + 1; i++) {
		counter = counter + m_southBeans[i];
	}
	// cerr << "Current number of beans in play for SOUTH: " << counter << endl;
	return counter;
}
int Board::totalBeans() const {
	int counter = 0;
	for (int i = 0; i < m_holesPerSide + 1; i++) {
		counter = counter + m_northBeans[i];
		counter = counter + m_southBeans[i];
	}
	return counter;
}
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	// cerr << "CALLING SOW FOR " <<hole << endl;
	if (hole <= 0 || hole >= m_holesPerSide + 1) { //invalid or a pot
		return false;
	}
	int beans = -100; //some impossible value
	if (s == Side::NORTH) {
		beans = m_northBeans[hole];
	}
	else if (s == Side::SOUTH) {
		beans = m_southBeans[hole];
	}
	if (beans == 0) {
		return false;
	}
	//beans guaranteed to be nonzero
	//CASE 1: MAKES IT TO YOUR OWN POT OR LESS
	//CASE 2: ENDS ON YOUR OWN POT
	//CASE 2: MAKES IT TO OTHER SIDE (AFTER LOOPING AROUND)
	//CASE 3: MAKES IT TO YOUR SIDE (AFTER LOOPING AROUND)
	if (s == Side::NORTH) {
		// cerr << "Sowing for north side" << endl;
		m_northBeans[hole] = 0;
		for (int i = hole - 1; i >= 0; --i) { //north goes backwards
			++m_northBeans[i]; //add a bean
			--beans;
			if (beans == 0) { //no more beans to shuffle
				endHole = i;
				endSide = Side::NORTH;
			// 	cerr << "REACHED CASE 1, N" << endl;
				return true; //CASE 1
			}
		}
		//the last one filled was north's pot, take this as the new start point
		int addToAll = beans / (2 * m_holesPerSide + 1);
		int remainder = beans % (2*m_holesPerSide + 1);
		// cerr << "Reached this point, beans left is " << beans << endl;
		// cerr << "addToAll is " << addToAll << " and remainder is " << remainder << endl;
		//(2*m_holesPerSide + 1)
		if (addToAll > 0) {
			for (int i = 1; i < m_holesPerSide + 1; ++i) {
				m_northBeans[i] += addToAll;
				m_southBeans[i] += addToAll;
			}
			m_northBeans[0] += addToAll;
		}
		if (remainder == 0) { //no more beans to distribute
			endHole = 0;
			endSide = Side::NORTH;
			// cerr << "REACHED CASE 2, N" << endl;
			return true; //CASE 2
		}
		//remainder is greater than 0
		if (remainder <= m_holesPerSide) { // 1<remainder<=6
			int i;
			for (i = 1; remainder>0; ++i) { //south goes forwards
				++m_southBeans[i];
				--remainder;
			}
			endHole = i-1;
			endSide = Side::SOUTH;
			// cerr << "REACHED CASE 3, N" << endl;
			return true; //CASE 3
		}
		else if (remainder > m_holesPerSide) { // 7<=remainder<13 if using 6 holes per side
			//first fill south
			for (int i = 1; i <= m_holesPerSide; ++i) {
				++m_southBeans[i];
				--remainder;
			}
			int i;
			for ( i = m_holesPerSide; remainder>0 && i>0; --i) {
				++m_northBeans[i];
				--remainder;
			}
			endHole = i+1;
			endSide = Side::NORTH;
			// cerr << "REACHED CASE 4, N" << endl;
			return true; //CASE 4
		}
	}

	else if(s == Side::SOUTH){//STARTING SIDE IS SOUTH
		// cerr << "Sowing for south side" << endl;
		m_southBeans[hole] = 0;
		int j = hole + 1;
		for (; j < m_holesPerSide + 1; ++j) { //south moves upwards
			++m_southBeans[j]; //add a bean
			--beans;
			
			if (beans == 0) { //no more beans to shuffle
				endHole = j;
				endSide = Side::SOUTH;
				// cerr << "REACHED CASE 1, S" << endl;
				return true;
			}
		}
		if (j == m_holesPerSide + 1 && beans > 0) {
			//becuase order is 1, 2, ...6, 0 for south
			++m_southBeans[0];
			--beans;
		}
		if (beans == 0) { //no more beans to shuffle
			endHole = 0;
			endSide = Side::SOUTH;
			// cerr << "REACHED CASE 1A, S, ENDING ON POT" << endl;
			return true;
		}
		//the last one filled was south's pot, take this as new start point
		int addToAll = beans / (2 * m_holesPerSide + 1);
		int remainder = beans % (2 * m_holesPerSide + 1);
		//(2*m_holesPerSide + 1) = 13 if using 6 holes per side
		// cerr << "Reached this point, beans left is "  <<beans << endl;
		// cerr << "addToAll is " << addToAll << " and remainder is " << remainder << endl;
		if (addToAll > 0) {
			for (int i = 1; i < m_holesPerSide + 1; ++i) {
				m_southBeans[i] += addToAll;
				m_northBeans[i] += addToAll;			
			}
			m_southBeans[0] += addToAll;
		}
		if (remainder == 0) { //no more beans to distribute
			endHole = 0;
			endSide = Side::SOUTH;
			// cerr << "REACHED CASE 2, S" << endl;
			return true;
		}
		//remainder is greater than 0
		if (remainder <= m_holesPerSide) { //1<remainder<=6
			int i;
			for (i = m_holesPerSide; remainder > 0 && i>0; --i) { //north loops backwards
				++m_northBeans[i];
				--remainder;
			}
			endHole = i+1; //+1 to adjust for the decrement earlier
			endSide = Side::NORTH;
			// cerr << "REACHED CASE 3, S" << endl;
			// cerr << "Endhole is " << i << endl;
			return true;
		}
		else if (remainder > m_holesPerSide) { //7<=remainder<13 if using 6 holes per side
			//first fill north
			for (int i = m_holesPerSide; i > 0; i--) { //north loops backwards
				++m_northBeans[i];
				--remainder;
			}
			int i;
			for (i = 0; remainder > 0 && i < m_holesPerSide + 1; ++i) {
			//possible alternative: for (i = 0; remainder > 0; i++) {
				++m_southBeans[i];
				--remainder;
			}
			endHole = i-1;
			endSide = Side::SOUTH;
			// cerr << "REACHED CASE 3, S" << endl;
			return true;
		}
	}
	return true;
}
bool Board::moveToPot(Side s, int hole, Side potOwner) {
	if (hole <= 0 || hole >= m_holesPerSide + 1) { //invalid or a pot
		return false;
	}
	if (potOwner == Side::NORTH) {
		if (s == Side::NORTH) {
			m_northBeans[0] = m_northBeans[0] + m_northBeans[hole];
			m_northBeans[hole] = 0;
		}
		else if (s == Side::SOUTH) {
			m_northBeans[0] = m_northBeans[0] + m_southBeans[hole];
			m_southBeans[hole] = 0;
		}
		return true;
	}
	//otherwise, potowner is SOUTH
	if (s == Side::NORTH) {
			m_southBeans[0] = m_southBeans[0] + m_northBeans[hole];
			m_northBeans[hole] = 0;
	}
	else if (s == Side::SOUTH) {
			m_southBeans[0] = m_southBeans[0] + m_southBeans[hole];
			m_southBeans[hole] = 0;
	}	
	return true;
}

bool Board::setBeans(Side s, int hole, int beans) {
// 	cerr << "Calling setBeans" << endl;
	if (hole < 0 || hole >= m_holesPerSide + 1 || beans<0) { //invalid value
		return false;
	}
	if (s == Side::NORTH) {
	// 	cerr << "Setting beans for north side" << endl;
		m_northBeans[hole] = beans;
	}
	else if (s == Side::SOUTH) {
		// cerr << "Setting beans for south side" << endl;
		m_southBeans[hole] = beans;
	}
	return true;
}
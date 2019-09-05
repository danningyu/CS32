#ifndef BOARD_H
#define BOARD_H
#include "Side.h"

//need to implement copy constructor and assignment operator!!!
class Board {
public:
	Board(int nHoles, int nInitialBeansPerHole);
	Board(const Board& other);
	Board& operator=(const Board& rhs);
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
	~Board();
private:
	void swap(Board& other);

	int m_holesPerSide;
	int* m_northBeans; //pointer to array for north's beans
	//0 is the pot, then proceed 6 to 1
	int* m_southBeans; //pointer to array for south's beans
	//0 is the pot, then proceed 1 to 6	
};

#endif

#ifndef GAME_H
#define GAME_H
#include "Board.h"

class Player;

class Game { //make copy constructor and assignment operator??
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const;
private:
	bool moveBeansToPot();
	Board m_b;
	bool southsTurn;
	Player* m_south; //goes first
	Player* m_north;	
};
#endif
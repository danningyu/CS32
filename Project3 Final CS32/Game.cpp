#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north):m_b(b), 
	m_south(south), m_north(north) {
	southsTurn = true;
}

void Game::display() const {
	cout << endl << " ";
	cout << m_north->name() << endl;
	for (int i = 1; i < m_b.holes()+1; i++) {
		cout << "  " << m_b.beans(Side::NORTH, i);
	}
	cout << endl;
	cout << m_b.beans(Side::NORTH, 0);
	for (int i = 0; i < m_b.holes() + 6; i++) { //+6 for spacing
		cout << "  ";
	}
	cout << m_b.beans(Side::SOUTH, 0) << endl;
	for (int i = 1; i < m_b.holes() + 1; i++) {
		cout << "  " << m_b.beans(Side::SOUTH, i);
	}
	cout << endl;
	cout << m_south->name() << endl;
	cout << endl;
}
void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	// cerr << "Checking status of game" << endl;
	// display();
	if (m_b.beansInPlay(Side::NORTH) != 0 && m_b.beansInPlay(Side::SOUTH) != 0) {
		// cerr << "Game not over" << endl;
		over = false;
		return;
	}
	over = true;
	if (m_b.beans(Side::NORTH, 0) == m_b.beans(Side::SOUTH, 0)) { //0 is the pot
		// cerr << "Tie status detected" << endl;
		hasWinner = false; //tie
	}
	else if (m_b.beans(Side::NORTH, 0) > m_b.beans(Side::SOUTH, 0)){
		// cerr << "Status: North wins" << endl;
		hasWinner = true; //not a tie
		winner = Side::NORTH;
	}
	else if (m_b.beans(Side::NORTH, 0) < m_b.beans(Side::SOUTH, 0)) {
		// cerr << "Status: South wins" << endl;
		hasWinner = true; //not a tie
		winner = Side::SOUTH;
	}
	return;
}
bool Game::move() {
	string temp = "";
	if (m_b.beansInPlay(Side::NORTH) == 0 || m_b.beansInPlay(Side::SOUTH) == 0) { //game over
		moveBeansToPot();
		return false;
	}
	if (southsTurn == true) { //first do the moves, SOUTH's turn
		bool goAgain = false;
		Side sideResult;
		int holeResult = 0;
		Board oldBoard = m_b;
		// display();
		while (holeResult == 0 && moveBeansToPot() == false) { //go again if you end up in your pot
			cout << m_south->name() << "'s turn." << endl;
			if (m_south->isInteractive() == false && goAgain == true) {				
				cout << m_south->name() << " going again." << endl;
			}
			goAgain = true;
			oldBoard = m_b;
			if (moveBeansToPot() == true) {
				//one side of board is empty, so end the turn
				display();
				break;
			}
			int choice = m_south->chooseMove(m_b, Side::SOUTH);
			while (m_b.sow(Side::SOUTH, choice, sideResult, holeResult) == false) { //bad move
				cout << "Invalid hole." <<endl;
				choice = m_south->chooseMove(m_b, Side::SOUTH);
			}
			if (oldBoard.beans(sideResult, holeResult) == 0 && sideResult == Side::SOUTH &&
				m_b.beans(opponent(sideResult), holeResult) != 0 &&
				oldBoard.beans(Side::SOUTH, choice) < (2*m_b.holes() + 1) ) {
				//resulting hole on old board had no stones
				//opponent's hole across from it has stones
				//and hole  you picked up stones from has less than twice the # of holes, plus 1 (for pot)
				//if >= 13, you'll end up populating all the holes
				cout << "Capturing North's stones in hole " << holeResult << endl;
				m_b.moveToPot(opponent(sideResult), holeResult, sideResult);
				m_b.moveToPot(sideResult, holeResult, sideResult); //move the 1 bean over too
				southsTurn = false; //end of turn
				display();
				break;
			}
			display();
		}
		southsTurn = false;
	}
	else if (southsTurn == false ) { //NORTH's turn
		bool goAgain = false;
		Side sideResult;
		int holeResult = 0;
		Board oldBoard = m_b;
		// display();
		while (holeResult == 0 && moveBeansToPot() == false) { //go again if you end up in your pot
			cout << m_north->name() << "'s turn." << endl;
			if (m_north->isInteractive() == false && goAgain == true) {			
				cout << m_north->name() <<" going again." <<endl;				
			}
			goAgain = true;
			oldBoard = m_b;
			if (moveBeansToPot() == true) {
				//one side of board is empty, so end the turn
				display();
				break;
			}
			int choice = m_north->chooseMove(m_b, Side::NORTH);
			while (m_b.sow(Side::NORTH, choice, sideResult, holeResult) == false) { //bad move
				cout << "Invalid hole." << endl;
				choice = m_north->chooseMove(m_b, Side::NORTH);
			}
			if (oldBoard.beans(sideResult, holeResult) == 0 && sideResult == Side::NORTH &&
				m_b.beans(opponent(sideResult), holeResult) != 0 &&
				oldBoard.beans(Side::NORTH, choice) < (2 * m_b.holes() + 1)) {
				cout << "Capturing South's stones in hole " << holeResult << endl;
				m_b.moveToPot(opponent(sideResult), holeResult, sideResult);
				m_b.moveToPot(sideResult, holeResult, sideResult); //move the 1 bean over too
				southsTurn = true; //end of turn
				display();
				break;
			}
			display();
		}
		southsTurn = true;
	}
	//now check if any side is empty
	moveBeansToPot();
	return true;
}

void Game::play() {
	string temp = "";
	bool gameOver = false;
	bool winnerExists = false;
	Side winningSide;
	display();
	while (gameOver == false) {
			move();
			status(gameOver, winnerExists, winningSide);
			if (m_south->isInteractive() == false && m_north->isInteractive() == false) {
				cout << "A computer just went. Press ENTER to continue.";
				getline(cin, temp);
			}
	}	
	display();
	cout << "The game is over." << endl;
	if (gameOver == true && winnerExists == false) {
		cout << "The game is over. There is a tie." << endl;
		return;
	}
	if (winningSide == Side::NORTH && gameOver == true) {
		cout << "North has won the game." << endl;
	}
	else if (winningSide == Side::SOUTH && gameOver == true) {
		cout << "South has won the game." << endl;
	}
	return;
}
int Game::beans(Side s, int hole) const {
	if (hole < 0 || hole >= m_b.holes() + 1) { //hole is out of bounds
	//can't access if index is < 0 or >= size of array
		return -1;
	}
	if (s == Side::NORTH) {
		return m_b.beans(s, hole);
	}
	return m_b.beans(s, hole);
}

bool Game::moveBeansToPot() {
	//cerr << "Done with the turn, checking for empty sides" << endl;
	// display(); 
	bool northEmpty = true;
	bool southEmpty = true;
	for (int i = 1; i < m_b.holes() + 1; i++) {
		if (m_b.beans(Side::NORTH, i) != 0) {
			northEmpty = false;
		}
		if (m_b.beans(Side::SOUTH, i) != 0) {
			southEmpty = false;
		}
	}
	//cerr << northEmpty << endl;
	//cerr << southEmpty << endl;
	// display();
	if (northEmpty == false && southEmpty == true) {
		for (int i = 1; i < m_b.holes() + 1; i++) {
			m_b.moveToPot(Side::NORTH, i, Side::NORTH);
		}
		// cerr << "All empty on south side" << endl;
		return true;
	}
	else if (northEmpty == true && southEmpty == false) {
		for (int i = 1; i < m_b.holes() + 1; i++) {
			m_b.moveToPot(Side::SOUTH, i, Side::SOUTH);
			// cerr << "All empty on north side" << endl;
		}
		return true;
	}
	if (northEmpty == false && southEmpty == false) {
		// cerr << "No empty sides found." << endl;
	}
	if (northEmpty && southEmpty) {
		// cerr << "Both sides empty, doing nothing" << endl;
	}
	return false;
	//if both false, nothing should be done
	//if both true, then the if and else-if will not affect anything
	// display();
}
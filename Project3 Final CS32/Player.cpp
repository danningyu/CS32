#include "Player.h"
#include <iostream>
using namespace std;
//Player implementations
Player::Player(std::string name):m_name(name) {}

std::string Player::name() const {return m_name;}

bool Player::isInteractive() const {return false;}

Player::~Player() {}

//HumanPlayer implementations
HumanPlayer::HumanPlayer(std::string name):Player(name) {}

bool HumanPlayer::isInteractive() const {return true;}

int HumanPlayer::chooseMove(const Board& b, Side s) const {
	int hole;
	Side aSide = s;
	cout << "Select a hole, " << name() << ": ";
	cin >> hole;
	cin.ignore(100000, '\n');
	while (hole <= 0 || hole > b.holes()) {
		cout << "Invalid hole. Enter a hole number (positive number): ";
		cin >> hole;
		cin.ignore(100000, '\n');
	}
	return hole; //play the stones in this hole
}
HumanPlayer::~HumanPlayer() {}

//BadPlayer implementations
BadPlayer::BadPlayer(std::string name):Player(name){}

bool BadPlayer::isInteractive() const {return false;}

int BadPlayer::chooseMove(const Board& b, Side s) const {
	//moves the first hole where there's beans (starting from 1)
	for (int i = 1; i < b.holes() + 1; i++) {
		if (b.beans(s, i) != 0) {
			return i;
		}
	}
	return 1;
}

BadPlayer::~BadPlayer() {}

//SmartPlayer implementations
SmartPlayer::SmartPlayer(std::string name):Player(name){}

bool SmartPlayer::isInteractive() const {return false;}

int SmartPlayer::chooseMove(const Board& b, Side s) const {	
	AlarmClock ac(4900);
	// cerr  << "Calling smartPlayer" << endl;
	int aHole = -2;
	int valueOfMove = 0; //0 is "neutral"
	
	moveHelper(b, s, s, aHole, valueOfMove, 1, ac); //start from 0th layer
	// cerr << "Value of hole after helper is " << aHole << endl;
	if (aHole == 0 ||aHole == -1 ||aHole == -2) { //already won, so do whatever
	// 	cerr << "BAD HOLE WAS FOUND" << endl;
		for (int i = 1; i < b.holes() + 1; i++) {
			if (b.beans(s, i) != 0) {
				aHole = i;
				break;
			}
		}
	}
	// cerr << name() << " is picking hole " << aHole <<"." <<endl;
	return aHole;
}
SmartPlayer::~SmartPlayer() {}

void SmartPlayer::moveHelper(const Board& b, Side s, const Side& origSide, int& bestHole, int& value, int layer, AlarmClock& clock) const {
	//need to add moving all beans to other side when one side is empty
	// cerr << "Current board for side " << s << endl;
	// cerr << endl;
	// cerr << "Calling the moveHelper" << endl;
	
	//dont calculate value unlesss layer is reached??
	//if (layer == 8) {
	//	value = determineValue(b, Side::SOUTH);  //off by 1?? check
	//}	
	// cerr << "Value for current board, layer " << layer << " is " << value << endl;
	if (clock.timedOut()) {
		// cerr << "Passed time limit! Location 1" << endl;
		return;
	}
	if (b.beansInPlay(Side::SOUTH) == 0 || b.beansInPlay(Side::NORTH) == 0) {
		Board temp = b;
		for (int i = 1; i < b.holes() + 1; i++) {
			temp.moveToPot(Side::SOUTH, i, Side::SOUTH);
			temp.moveToPot(Side::NORTH, i, Side::NORTH);
		}
		if (temp.beans(Side::NORTH, 0) > temp.beans(Side::SOUTH, 0)) {
			value = -1000;
		}
		else if (temp.beans(Side::SOUTH, 0) < temp.beans(Side::NORTH, 0)) {
			value = 1000;
		}
		else if (temp.beans(Side::SOUTH, 0) == temp.beans(Side::NORTH, 0)) {
			value = 0;
		}
		bestHole = -1;
		return; 
	}
	if (layer == 5) { //don't search more than this many layers
		value = b.beans(s, 0) - b.beans(opponent(s), 0);
		bestHole = -1;
		return;
	}
	for (int i = 1; i < b.holes() + 1; i++) {
		if (b.beans(s, i) != 0) { 
			Board anotherBoard = b;
			Side sideResult = s;
			int holeResult = -2;
			int h2 = 0;
			int v2 = value;
		// 	cerr << "Making the next move from hole " << i << " for layer " << layer << endl;
			anotherBoard.sow(s, i, sideResult, holeResult);
			if (holeResult == 0 && sideResult == s) { //if lands in player's own pot
		// 	cerr << "Landed in own pot moving from hole " << i << endl;
				if (clock.timedOut()) {
				//if you hit this one you're way over the time limit
				// 	cerr << "Passed time limit! Location 3" << endl;
					return;
				}
				moveHelper(anotherBoard, s, s, h2, v2, layer, clock); //go again
			}
			else if (sideResult == s && anotherBoard.beans(opponent(sideResult), holeResult) != 0 &&
				anotherBoard.beans(sideResult, holeResult) == 1) {
				// cerr << "Performing a capture" << endl;				
				anotherBoard.moveToPot(opponent(sideResult), holeResult, sideResult);
				anotherBoard.moveToPot(sideResult, holeResult, sideResult); //move the 1 bean over too
				// cerr << "After capture: " << endl; 
				if (clock.timedOut()) {
				// 	cerr << "Passed time limit! Location 4" << endl; //129 seconds
					return;
				}
				moveHelper(anotherBoard, opponent(s), origSide, h2, v2, layer + 1, clock); //then the next side gets to go
			}
			else {
				if (clock.timedOut()) {
					//4.9 sec, 5.44, 5 sec (ac of 4900)
					// cerr << "Passed time limit! Location 5" << endl;
					return;
				}
				moveHelper(anotherBoard, opponent(s), origSide, h2, v2, layer + 1, clock);
			}
			// cerr << "Value for move from hole " << i << " and layer " << layer + 1 << " is " << v2 << endl;
			if (clock.timedOut()) {
			// 	cerr << "Passed time limit! Location 2" << endl;
				return;
			}
			if (bestHole == -2 || (v2 > value && origSide == Side::SOUTH)) {
			//maximize south, minimize north
				bestHole = i;
				value = v2;
			}
			else if (bestHole == -2 || (v2 < value && origSide == Side::NORTH) ) {
				//maximize south, minimize north		
				bestHole = i;
				value = v2;
			}
		}
	}
	//TEST 3, 2 BOARD, 1 LAYER, WHICH HOLE IT PICKS

	if (clock.timedOut()) {
		// cerr << "Passed time limit! Location 6" << endl;
		return;
	}
	// cerr << "The best hole with moveHelper: " << bestHole << endl;
	return;
}
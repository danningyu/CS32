#include <iostream>
#include <cassert>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Game.h"
#include "Side.h"
using namespace std;

#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

int main() {
	//{//Test Board.cpp

	////testing if you pass in bad parameters to the constructor
	//	Board bad1(-1, -1); //first is holes, second is beans per hole
	//	Board bad2(0, -1);
	//	Board bad3(-1, 0);
	//	Board bad4(0, 0);
	//	assert(bad1.beans(Side::NORTH, 0) == 0);
	//	assert(bad1.beans(Side::SOUTH, 0) == 0);
	//	assert(bad2.beans(Side::NORTH, 0) == 0);
	//	assert(bad2.beans(Side::SOUTH, 0) == 0);
	//	assert(bad3.beans(Side::NORTH, 0) == 0);
	//	assert(bad3.beans(Side::SOUTH, 0) == 0);
	//	assert(bad4.beans(Side::NORTH, 0) == 0);
	//	assert(bad4.beans(Side::SOUTH, 0) == 0);

	//	assert(bad1.holes() == 1);
	//	assert(bad1.beansInPlay(Side::SOUTH) == 0);
	//	assert(bad1.beansInPlay(Side::NORTH) == 0);
	//	assert(bad1.totalBeans() == 0);

	//	assert(bad2.holes() == 1);
	//	assert(bad2.beansInPlay(Side::SOUTH) == 0);
	//	assert(bad2.beansInPlay(Side::NORTH) == 0);
	//	assert(bad2.totalBeans() == 0);

	//	assert(bad3.holes() == 1);
	//	assert(bad3.beansInPlay(Side::SOUTH) == 0);
	//	assert(bad3.beansInPlay(Side::NORTH) == 0);
	//	assert(bad3.totalBeans() == 0);

	//	assert(bad3.holes() == 1);
	//	assert(bad3.beansInPlay(Side::SOUTH) == 0);
	//	assert(bad3.beansInPlay(Side::NORTH) == 0);
	//	assert(bad3.totalBeans() == 0);

	//	//now test everything else for Board
	//	Board b1(3, 2); //3 holes, 2 beans per pot
	//	//  NORTH
	//	//  2 2 2
	//	//0       0
	//	//  2 2 2
	//	//  SOUTH
	//	assert(b1.beans(Side::NORTH, 0) == 0); //pots should start with 0 beans
	//	assert(b1.beans(Side::SOUTH, 0) == 0);
	//	assert(b1.beansInPlay(Side::NORTH) == 6); //3 holes * 2 beans per hole = 6 beans
	//	assert(b1.beansInPlay(Side::SOUTH) == 6);
	//	assert(b1.totalBeans() == 12); //6 beans per side * 2 sides = 12 beans
	//	assert(b1.holes() == 3); //number of holes should be set to 3
	//	assert(b1.beans(Side::SOUTH, -1) == -1); //-1 is invalid hole #
	//	assert(b1.beans(Side::SOUTH, 4) == -1); //4 is out of bounds
	//	assert(b1.beans(Side::SOUTH, 1) == 2); //should be 2 beans per hole
	//	assert(b1.beans(Side::NORTH, -1) == -1); //repeat above tests for north side
	//	assert(b1.beans(Side::NORTH, 4) == -1); //4 is out of bounds
	//	assert(b1.beans(Side::NORTH, 1) == 2); //should be 2 beans per hole
	//	assert(b1.moveToPot(Side::SOUTH, 0, Side::SOUTH) == false); //cannot move from pot to pot
	//	assert(b1.moveToPot(Side::SOUTH, 4, Side::SOUTH) == false); //cannot move from out of bounds hole
	//	assert(b1.moveToPot(Side::SOUTH, 0, Side::NORTH) == false); //repeat above tests with other side
	//	assert(b1.moveToPot(Side::SOUTH, 4, Side::NORTH) == false);
	//	assert(b1.moveToPot(Side::SOUTH, 3, Side::SOUTH) == true); //should work, 3 is within bounds
	//	//  NORTH
	//	//  2 2 2
	//	//0       2
	//	//  2 2 0
	//	//  SOUTH
	//	assert(b1.beansInPlay(Side::SOUTH) == 4); //beans in play should be decreased
	//	assert(b1.beansInPlay(Side::NORTH) == 6); //beans in play for other side should be unchanged
	//	assert(b1.beans(Side::SOUTH, 3) == 0); //all the beans should have been moved
	//	assert(b1.beans(Side::NORTH, 3) == 2); //beans on other side shouldn't be affected
	//	assert(b1.totalBeans() == 12); //total # of beans should be unchanged
	//	assert(b1.setBeans(Side::NORTH, -1, 3) == false); //-1 is out of bounds
	//	assert(b1.setBeans(Side::NORTH, 1, -3) == false); //cannot set beans to be negative
	//	assert(b1.setBeans(Side::NORTH, -1, -1) == false); //combination of two test cases above
	//	assert(b1.setBeans(Side::NORTH, 0, 5) == true); //0 is the pot, beans is positive, should succeed
	//	//  NORTH
	//	//  2 2 2
	//	//5       2
	//	//  2 2 0
	//	//  SOUTH
	//	assert(b1.totalBeans() == 17); //total # of beans should have changed
	//	assert(b1.beans(Side::NORTH, 0) == 5); //beans in north's pot should now be 5
	//	assert(b1.beans(Side::SOUTH, 0) == 2); //beans in south's pot should be changed
	//	assert(b1.setBeans(Side::NORTH, 3, 1)); //change up some values of the board
	//	assert(b1.setBeans(Side::SOUTH, 1, 4));
	//	assert(b1.setBeans(Side::SOUTH, 3, 1));
	//	//  NORTH
	//	//  2 2 1
	//	//5       2
	//	//  4 2 1
	//	//  SOUTH
	//	assert(b1.totalBeans() == 19); //test if total beans is updated
	//	assert(b1.beansInPlay(Side::NORTH) == 5); //check the totals
	//	assert(b1.beansInPlay(Side::SOUTH) == 7); //check the totals
	//	assert(b1.beans(Side::SOUTH, 0) == 2); //check all the values of the board
	//	assert(b1.beans(Side::SOUTH, 1) == 4);
	//	assert(b1.beans(Side::SOUTH, 2) == 2);
	//	assert(b1.beans(Side::SOUTH, 3) == 1);
	//	assert(b1.beans(Side::NORTH, 0) == 5);
	//	assert(b1.beans(Side::NORTH, 1) == 2);
	//	assert(b1.beans(Side::NORTH, 2) == 2);
	//	assert(b1.beans(Side::NORTH, 3) == 1);

	//	Board b2(b1); //test copy constructor
	//	assert(b2.totalBeans() == 19); //test if total beans is copied correctly
	//	assert(b2.beansInPlay(Side::NORTH) == 5); //check the totals
	//	assert(b2.beansInPlay(Side::SOUTH) == 7); //check the totals
	//	assert(b2.beans(Side::SOUTH, 0) == 2); //check all the values of the board
	//	assert(b2.beans(Side::SOUTH, 1) == 4);
	//	assert(b2.beans(Side::SOUTH, 2) == 2);
	//	assert(b2.beans(Side::SOUTH, 3) == 1);
	//	assert(b2.beans(Side::NORTH, 0) == 5);
	//	assert(b2.beans(Side::NORTH, 1) == 2);
	//	assert(b2.beans(Side::NORTH, 2) == 2);
	//	assert(b2.beans(Side::NORTH, 3) == 1);
	//	assert(b2.holes() == 3); //check # of holes were set correctly
	//	assert(b2.moveToPot(Side::SOUTH, 2, Side::SOUTH) == true); //move some beans
	//	assert(b2.moveToPot(Side::NORTH, 1, Side::SOUTH) == true);
	//	//  NORTH (Board b2)
	//	//  0 2 1
	//	//5       6
	//	//  4 0 1
	//	//  SOUTH
	//	assert(b2.beans(Side::SOUTH, 0) == 6); //pot beans should be updated
	//	assert(b2.beans(Side::NORTH, 1) == 0); //# of beans in hole should be updated
	//	assert(b2.beans(Side::SOUTH, 2) == 0);
	//	assert(b1.beans(Side::SOUTH, 0) == 2); //pot for b1 should be unchanged
	//	assert(b1.beans(Side::NORTH, 1) == 2); //board for b1 should be unchanged
	//	assert(b1.beans(Side::SOUTH, 2) == 2);

	//	b2 = b2; //test assignment operator, this should do nothing
	//	assert(b2.beans(Side::SOUTH, 0) == 6); //check all the values of the board, should be unchanged
	//	assert(b2.beans(Side::SOUTH, 1) == 4);
	//	assert(b2.beans(Side::SOUTH, 2) == 0);
	//	assert(b2.beans(Side::SOUTH, 3) == 1);
	//	assert(b2.beans(Side::NORTH, 0) == 5);
	//	assert(b2.beans(Side::NORTH, 1) == 0);
	//	assert(b2.beans(Side::NORTH, 2) == 2);
	//	assert(b2.beans(Side::NORTH, 3) == 1);

	//	Board b3(6, 6); //make some other board to test assignment operator
	//	assert(b3.totalBeans() == 72);
	//	assert(b3.holes() == 6);
	//	assert(b3.beansInPlay(Side::SOUTH) == 36);
	//	b3 = b1;
	//	assert(b3.totalBeans() == 19); //test if total beans is updated
	//	assert(b3.holes() == 3); //test if # of holes is updated
	//	assert(b3.beansInPlay(Side::NORTH) == 5); //check the totals
	//	assert(b3.beansInPlay(Side::SOUTH) == 7); //check the totals
	//	assert(b3.beans(Side::SOUTH, 0) == 2); //check all the values of the board
	//	assert(b3.beans(Side::SOUTH, 1) == 4);
	//	assert(b3.beans(Side::SOUTH, 2) == 2);
	//	assert(b3.beans(Side::SOUTH, 3) == 1);
	//	assert(b3.beans(Side::NORTH, 0) == 5);
	//	assert(b3.beans(Side::NORTH, 1) == 2);
	//	assert(b3.beans(Side::NORTH, 2) == 2);
	//	assert(b3.beans(Side::NORTH, 3) == 1);
	//	assert(b3.moveToPot(Side::SOUTH, 2, Side::SOUTH) == true); //move some beans
	//	assert(b3.moveToPot(Side::NORTH, 1, Side::SOUTH) == true);
	//	//  NORTH (Board b3)
	//	//  0 2 1
	//	//5       6
	//	//  4 0 1
	//	//  SOUTH

	//	//  NORTH (Board b2)
	//	//  0 2 1
	//	//5       6
	//	//  4 0 1
	//	//  SOUTH

	//	//  NORTH (board b1)
	//	//  2 2 1
	//	//5       2
	//	//  4 2 1
	//	//  SOUTH

	//	assert(b1.beans(Side::SOUTH, 0) == 2); //pot for b1 should be unchanged
	//	assert(b1.beans(Side::NORTH, 1) == 2); //board for b1 should be unchanged
	//	assert(b1.beans(Side::SOUTH, 2) == 2);
	//	assert(b2.beans(Side::SOUTH, 0) == 6); //check all the values of the board are updated
	//	assert(b2.beans(Side::SOUTH, 1) == 4);
	//	assert(b2.beans(Side::SOUTH, 2) == 0);
	//	assert(b2.beans(Side::SOUTH, 3) == 1);
	//	assert(b2.beans(Side::NORTH, 0) == 5);
	//	assert(b2.beans(Side::NORTH, 1) == 0);
	//	assert(b2.beans(Side::NORTH, 2) == 2);
	//	assert(b2.beans(Side::NORTH, 3) == 1);
	//	Board temp(b1); //make a copy of b1
	//	int holeResult = -99;
	//	Side endSide = Side::SOUTH;
	//	assert(b1.sow(Side::SOUTH, -1, endSide, holeResult) == false);
	//	assert(b1.sow(Side::SOUTH, 0, endSide, holeResult) == false);
	//	assert(holeResult == -99 and endSide == Side::SOUTH); //values of holeResult and endSide should be uncahnged
	//	assert(b1.sow(Side::SOUTH, 1, endSide, holeResult) == true);
	//	//  NORTH (board b1)
	//	//  2 2 (2) //parentheses indicates ending hole
	//	//5        3 
	//	//  0 3 2
	//	//  SOUTH
	//	assert(endSide == Side::NORTH && holeResult == 3);
	//	assert(b1.beans(Side::SOUTH, 0) == 3); //check all the values of the board are updated
	//	assert(b1.beans(Side::SOUTH, 1) == 0);
	//	assert(b1.beans(Side::SOUTH, 2) == 3);
	//	assert(b1.beans(Side::SOUTH, 3) == 2);
	//	assert(b1.beans(Side::NORTH, 0) == 5);
	//	assert(b1.beans(Side::NORTH, 1) == 2);
	//	assert(b1.beans(Side::NORTH, 2) == 2);
	//	assert(b1.beans(Side::NORTH, 3) == 2);
	//	b1.setBeans(Side::NORTH, 1, 20);
	//	assert(b1.beans(Side::NORTH, 1) == 20); //check beans were set correctly
	//	//  NORTH (board b1)
	//	//  20 2 2 
	//	//5        3 
	//	//  0 3 2
	//	//  SOUTH
	//	b1.sow(Side::NORTH, 1, endSide, holeResult); //test sow for a large number
	//	cerr << "Ending side is " << endSide << " holeResult is " << holeResult << endl;
	//	//  NORTH (board b1)
	//	//  2 5 5 //parentheses indicates ending hole
	//	//8        3 
	//	//  3 6 5
	//	//  SOUTH
	//	assert(endSide == Side::NORTH && holeResult == 2);
	//	assert(b1.beans(Side::SOUTH, 0) == 3); //check all the values of the board are updated
	//	assert(b1.beans(Side::SOUTH, 1) == 3);
	//	assert(b1.beans(Side::SOUTH, 2) == 6);
	//	assert(b1.beans(Side::SOUTH, 3) == 5);
	//	assert(b1.beans(Side::NORTH, 0) == 8);
	//	assert(b1.beans(Side::NORTH, 1) == 2);
	//	assert(b1.beans(Side::NORTH, 2) == 5);
	//	assert(b1.beans(Side::NORTH, 3) == 5);

	//	b1 = temp; //revert b1 back to starting state
	//	holeResult = -99; //reset holeResult and endSide
	//	endSide = Side::SOUTH;
	//	//  NORTH (board b1)
	//	//  2 2 1
	//	//5       2
	//	//  4 2 1
	//	//  SOUTH
	//	assert(b1.sow(Side::NORTH, -1, endSide, holeResult) == false); //now repeat all tests for other side
	//	assert(b1.sow(Side::NORTH, 0, endSide, holeResult) == false);
	//	assert(holeResult == -99 and endSide == Side::SOUTH); //values of holeResult and endSide should be uncahnged
	//	assert(b1.sow(Side::NORTH, 1, endSide, holeResult) == true);
	//	//  NORTH (board b1)
	//   //   0  2 1
	//   //6         2
	//   //  (5) 2 1
	//   //  SOUTH
	//	assert(endSide == Side::SOUTH && holeResult == 1);
	//	assert(b1.beans(Side::SOUTH, 0) == 2); //check all the values of the board are updated
	//	assert(b1.beans(Side::SOUTH, 1) == 5);
	//	assert(b1.beans(Side::SOUTH, 2) == 2);
	//	assert(b1.beans(Side::SOUTH, 3) == 1);
	//	assert(b1.beans(Side::NORTH, 0) == 6);
	//	assert(b1.beans(Side::NORTH, 1) == 0);
	//	assert(b1.beans(Side::NORTH, 2) == 2);
	//	assert(b1.beans(Side::NORTH, 3) == 1);
	//	b1.setBeans(Side::SOUTH, 1, 20);
	//	assert(b1.beans(Side::SOUTH, 1) == 20); //check beans were set correctly
	//	//  NORTH (board b1)
	//	//  0  2 1 
	//	//6        2 
	//	//  20 2 1
	//	//  SOUTH
	//	b1.sow(Side::SOUTH, 1, endSide, holeResult); //test sow for a large number
	//	cerr << "Ending side is " << endSide << " holeResult is " << holeResult << endl;
	//	//  NORTH (board b1)
	//	// (3) 5 4 //parentheses indicates ending hole
	//	//6        5 
	//	//  2   5 4
	//	//  SOUTH
	//	assert(endSide == Side::NORTH && holeResult == 1);
	//	assert(b1.beans(Side::SOUTH, 0) == 5); //check all the values of the board are updated
	//	assert(b1.beans(Side::SOUTH, 1) == 2);
	//	assert(b1.beans(Side::SOUTH, 2) == 5);
	//	assert(b1.beans(Side::SOUTH, 3) == 4);
	//	assert(b1.beans(Side::NORTH, 0) == 6);
	//	assert(b1.beans(Side::NORTH, 1) == 3);
	//	assert(b1.beans(Side::NORTH, 2) == 5);
	//	assert(b1.beans(Side::NORTH, 3) == 4);

	//	//test Player.cpp

	//	SmartPlayer sp("Test 1");
	//	HumanPlayer hp("Test 2");
	//	BadPlayer bp1("Test 3");
	//	BadPlayer bp2("Test 4");
	//	assert(sp.name() == "Test 1");
	//	assert(hp.name() == "Test 2");
	//	assert(bp1.name() == "Test 3");
	//	assert(bp2.name() == "Test 4");
	//	assert(sp.isInteractive() == false);
	//	assert(hp.isInteractive() == true);
	//	assert(bp1.isInteractive() == false);
	//	assert(bp2.isInteractive() == false);

	//	//test Game.cpp
	//	Game g(b1, &bp1, &bp2);
	//	//  NORTH (board b1)
	//	// 3 5 4
	//	//6      5 
	//	// 2 5 4
	//	//  SOUTH
	//	g.display();
	//	bool gameOver = true;
	//	bool hasWinner = true;
	//	Side winningSide = Side::NORTH;
	//	g.status(gameOver, hasWinner, winningSide);
	//	assert(gameOver == false); //game is not over
	//	assert(hasWinner == true); //hasWinner should be unchanged
	//	assert(winningSide == Side::NORTH); //side should be unchanged
	//	g.move(); //south should move from hole 1
	//	//  NORTH (board b1)
	//	// 3 5 4
	//	//6      5 
	//	// 0 6 5
	//	//  SOUTH
	//	assert(g.beans(Side::SOUTH, 0) == 5); //check all the values of the board are updated
	//	assert(g.beans(Side::SOUTH, 1) == 0);
	//	assert(g.beans(Side::SOUTH, 2) == 6);
	//	assert(g.beans(Side::SOUTH, 3) == 5);
	//	assert(g.beans(Side::NORTH, 0) == 6);
	//	assert(g.beans(Side::NORTH, 1) == 3);
	//	assert(g.beans(Side::NORTH, 2) == 5);
	//	assert(g.beans(Side::NORTH, 3) == 4);
	//	g.status(gameOver, hasWinner, winningSide);
	//	assert(gameOver == false); //game is not over
	//	assert(hasWinner == true); //hasWinner should be unchanged
	//	assert(winningSide == Side::NORTH); //side should be unchanged
	//	g.move(); //north goes
	//	//  NORTH (board b1)
	//	// 0 5 4
	//	//7      5 
	//	// 1 7 5
	//	//  SOUTH
	//	assert(g.beans(Side::SOUTH, 0) == 5); //check all the values of the board are updated
	//	assert(g.beans(Side::SOUTH, 1) == 1);
	//	assert(g.beans(Side::SOUTH, 2) == 7);
	//	assert(g.beans(Side::SOUTH, 3) == 5);
	//	assert(g.beans(Side::NORTH, 0) == 7);
	//	assert(g.beans(Side::NORTH, 1) == 0);
	//	g.status(gameOver, hasWinner, winningSide);
	//	assert(gameOver == false); //game is not over
	//	assert(hasWinner == true); //hasWinner should be unchanged
	//	assert(winningSide == Side::NORTH); //side should be unchanged
	//	g.move(); //south goes
	//	//  NORTH (board b1)
	//	// 0 5 4
	//	//7      5 
	//	// 0 8 5
	//	//  SOUTH
	//	g.move(); //north goes
	//	//  NORTH (board b1)
	//	// 1 0 4
	//	//8      5 
	//	// 1 9 6
	//	//  SOUTH
	//	assert(g.beans(Side::SOUTH, 0) == 5); //check all the values of the board are updated
	//	assert(g.beans(Side::SOUTH, 1) == 1);
	//	assert(g.beans(Side::SOUTH, 2) == 9);
	//	assert(g.beans(Side::SOUTH, 3) == 6);
	//	assert(g.beans(Side::NORTH, 0) == 8);
	//	assert(g.beans(Side::NORTH, 1) == 1);
	//	assert(g.beans(Side::NORTH, 2) == 0);
	//	assert(g.beans(Side::NORTH, 3) == 4);
	//	g.move(); //south goes
	//	//  NORTH (board b1)
	//	// 1 0  4
	//	//8       5 
	//	// 0 10 6
	//	g.move(); //north goes
	//	//  NORTH (board b1)
	//	// 0 0  4
	//	//9       5 
	//	// 1 10 6
	//	//  SOUTH

	//	//NORTH GOES AGAIN
	//	//  NORTH (board b1)
	//	//   1 1  0
	//	//10         5 
	//	//   1 10 6
	//	//  SOUTH
	//	assert(g.beans(Side::SOUTH, 0) == 5); //check all the values of the board are updated
	//	assert(g.beans(Side::SOUTH, 1) == 1);
	//	assert(g.beans(Side::SOUTH, 2) == 10);
	//	assert(g.beans(Side::SOUTH, 3) == 6);
	//	assert(g.beans(Side::NORTH, 0) == 10);
	//	assert(g.beans(Side::NORTH, 1) == 1);
	//	assert(g.beans(Side::NORTH, 2) == 1);
	//	assert(g.beans(Side::NORTH, 3) == 0);
	//	for (int i = 0; i < 14; i++) { g.move(); }
	//	//move 14 times, will be 1 move away from game over
	//	g.status(gameOver, hasWinner, winningSide);
	//	assert(gameOver == false); //game is not over
	//	assert(hasWinner == true); //hasWinner should be unchanged
	//	assert(winningSide == Side::NORTH); //side should be unchanged
	//	g.move(); //last move, south goes
	//	assert(g.move() == false); //game is now over, cannot do any more moves
	//	g.status(gameOver, hasWinner, winningSide);
	//	assert(gameOver == true); //game is not over
	//	assert(hasWinner == true); //hasWinner should be unchanged
	//	assert(winningSide == Side::NORTH); //side should be unchanged
	//	g.display();

	//	Board b4(2, 2); //2 holes
	//	b4.setBeans(Side::NORTH, 0, 5);
	//	b4.setBeans(Side::SOUTH, 0, 5);
	//	b4.setBeans(Side::SOUTH, 1, 0);
	//	b4.setBeans(Side::SOUTH, 2, 0);
	//	b4.setBeans(Side::NORTH, 1, 0);
	//	b4.setBeans(Side::NORTH, 2, 0);
	//	//  NORTH (board b4)
	//	// 0 0
	//	//5    5 
	//	// 0 0
	//	//  SOUTH
	//	Game g2(b4, &bp1, &bp2);
	//	assert(g2.move() == false); //game is already over
	//	gameOver = false;
	//	hasWinner = true;
	//	winningSide = Side::NORTH;
	//	g2.status(gameOver, hasWinner, winningSide);
	//	assert(gameOver == true && hasWinner == false); //game is over but no winner (tie)
	//	assert(winningSide == Side::NORTH); //winning side should be unchanged

	//	Board b5 = b4;
	//	b5.setBeans(Side::SOUTH, 0, 6); //make south win now
	//	Game g3(b5, &bp1, &bp2);

	//	g3.display();
	//	//  NORTH (board b4)
	//	// 0 0
	//	//5    6 
	//	// 0 0
	//	//  SOUTH
	//	gameOver = false;
	//	hasWinner = true;
	//	winningSide = Side::NORTH;
	//	g3.status(gameOver, hasWinner, winningSide);
	//	assert(gameOver == true && hasWinner == true); //game is over, winner exists
	//	assert(winningSide == Side::SOUTH); //winning side should be changed

	//	//now test capturing
	//	//  NORTH (Board b2)
	//	//  0 2 1
	//	//5       6
	//	//  4 0 1
	//	//  SOUTH
	//	b2.setBeans(Side::SOUTH, 1, 1); //add beans to a hole
	//	b2.setBeans(Side::SOUTH, 2, 0); //clear out a hole for captuing
	//	b2.setBeans(Side::SOUTH, 3, 2); //add beans to a hole
	//	b2.setBeans(Side::NORTH, 1, 0);
	//	b2.setBeans(Side::NORTH, 2, 4); //make opposing hole nonempty
	//	b2.setBeans(Side::NORTH, 3, 1);
	//	//  NORTH (Board b2)
	//	//  0 4 1
	//	//5       6
	//	//  1 0 2
	//	//  SOUTH
	//	Game g4(b2, &bp1, &bp2);
	//	g4.move();
	//	//  NORTH (Board b2)
	//	//  0 0 1
	//	//5       11
	//	//  0 0 2
	//	//  SOUTH
	//	//capture occurs, beans in north's hole 2 are cpatured
	//	assert(g4.beans(Side::SOUTH, 0) == 11); //check all the values of the board are updated
	//	assert(g4.beans(Side::SOUTH, 1) == 0);
	//	assert(g4.beans(Side::SOUTH, 2) == 0);
	//	assert(g4.beans(Side::SOUTH, 3) == 2);
	//	assert(g4.beans(Side::NORTH, 0) == 5);
	//	assert(g4.beans(Side::NORTH, 1) == 0);
	//	assert(g4.beans(Side::NORTH, 2) == 0);
	//	assert(g4.beans(Side::NORTH, 3) == 1);
	//	cerr << "All tests passed! Yay!" << endl;
	//}
	Board b(6, 6);
	SmartPlayer sp1("SMART COMPUTER 1");
	HumanPlayer hp("HUMAN PLAYER");
	SmartPlayer sp2("SMART COMPUTER 2");
	Game g(b, &sp1, &sp2);
	g.play();

	//b.setBeans(Side::NORTH, 0, 22);
	//b.setBeans(Side::NORTH, 1, 0);
	//b.setBeans(Side::NORTH, 2, 1);
	//b.setBeans(Side::NORTH, 3, 0);
	//b.setBeans(Side::NORTH, 4, 0);
	//b.setBeans(Side::NORTH, 5, 2);
	//b.setBeans(Side::NORTH, 6, 0);
	//b.setBeans(Side::SOUTH, 0, 20);
	//b.setBeans(Side::SOUTH, 1, 0);
	//b.setBeans(Side::SOUTH, 2, 0);
	//b.setBeans(Side::SOUTH, 3, 2);
	//b.setBeans(Side::SOUTH, 4, 0);
	//b.setBeans(Side::SOUTH, 5, 1);
	//b.setBeans(Side::SOUTH, 6, 0);
	////   North
	////     0  1  0  0  2  0
	////	22                    20
	////	   0  0  2  0  1  0
	//// 	South
	//Game g(b, &sp1, &sp2);
	//g.play();
	//SmartPlayer hp("Marge");
	//SmartPlayer bp("Homer");
	//Board b(3, 2);
	//Game g(b, &hp, &bp);
	//	g.play();
	return 0;
}
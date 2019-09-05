#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stack>
using namespace std;
//use 'E' for encountered
class Coord{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	stack<Coord> coordStack; //a stack of coordinates
	Coord start(sr, sc);
	Coord end(er, ec);
	coordStack.push(start);
	maze[sr][sc] = 'E';
	while (coordStack.empty() == false) {
		Coord curr = coordStack.top();
		// cout << "Current coordinates: " << curr.r() << ", " << curr.c() << endl;
		coordStack.pop();
		if (curr.r() == end.r() && curr.c() == end.c()) {
			return true;
		}
		else {
			if (maze[curr.r() + 1][curr.c()] != 'X' && maze[curr.r() + 1][curr.c()] != 'E') { //can move south
				Coord temp(curr.r() + 1, curr.c());
				coordStack.push(temp);
				maze[curr.r() + 1][curr.c()] = 'E';
			}
			if (maze[curr.r()][curr.c() - 1] != 'X' && maze[curr.r()][curr.c() - 1] != 'E') { //can move west
				Coord temp(curr.r(), curr.c() - 1);
				coordStack.push(temp);
				maze[curr.r()][curr.c() - 1] = 'E';
			}
			if (maze[curr.r() - 1][curr.c()] != 'X' && maze[curr.r() - 1][curr.c()] != 'E') { //can move north
				Coord temp(curr.r() - 1, curr.c());
				coordStack.push(temp);
				maze[curr.r() - 1][curr.c()] = 'E';
			}
			
			if (maze[curr.r()][curr.c()+1] != 'X' && maze[curr.r()][curr.c()+1] != 'E') { //can move east
				Coord temp(curr.r(), curr.c()+1);
				coordStack.push(temp);
				maze[curr.r()][curr.c()+1] = 'E';
			}
		}
	}
	return false;
}

int main(){
		// cout << "Calling STACK version" << endl;
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};
	char maze2[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};
	char maze3[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};
	char maze4[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};
	char maze5[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};
	char maze6[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};
	for (int i = 0; i < 10; i++) { //print contents of the maze
		for (int j = 0; j < 10; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
	assert(pathExists(maze, 3, 5, 8, 8) == true);
	assert(pathExists(maze2, 1, 1, 1, 4) == true);
	assert(pathExists(maze3, 5, 8, 1, 1) == true);
	assert(pathExists(maze4, 1, 8, 1, 1) == false);
	assert(pathExists(maze5, 5, 1, 1, 1) == true);
	assert(pathExists(maze6, 1, 7, 8, 1) == false);
	cout << "All tests passed!" << endl;
	return 0;
}
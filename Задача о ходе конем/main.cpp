#include <iostream>
using namespace std;

const int X_SIZE = 5;
const int Y_SIZE = 5;
int board[X_SIZE][Y_SIZE];

struct Point{
	int x;
	int y;

	Point(){ x = 0; y = 0; }
	Point(int x, int y){ this->x = x; this->y = y; }
	void print_info(){ cout << "(" << x << ", " << y << ")" << endl; }
	bool test_board_occupied(){
		if (board[x][y] == 1)
			return true;
		return false;
	}
	bool test_in_bounds(){
		if (x < X_SIZE && x >= 0 && y < Y_SIZE && y >= 0)
			return true;
		return false;
	}
	bool operator==(Point& other){
		if (x == other.x && y == other.y)
			return true;
		return false;
	}
	Point operator+(Point& other){
		Point p(*this);
		p.x+=other.x;
		p.y+=other.y;
		return p;
	}
};

Point moves[8] = { Point(1, 2), Point(-1, 2), Point(2, 1), Point(-2, 1),
                   Point(1, -2), Point(-1, -2), Point(2, -1), Point(-2, -1)};
int move_order[8] = {7,6,5,4,3, 2,1,0};
int start_x = X_SIZE/2;
int start_y = Y_SIZE/2;

void print_board(Point k){
	for (int i = 0; i < Y_SIZE; i++){
		for (int j = 0; j < X_SIZE; j++){
			if (Point(j, i) == k)
				cout << "K";
			else if (board[j][i] == 1) cout << "x";
			else cout << ".";
		}
		cout << endl;
	}
}

bool flag = false;
void move_knight(Point last_move, int move_number = 1){
	for (int i = 0; i < 8; i++){
		Point move_here = last_move + moves[i];

		if (move_here.test_in_bounds() && !move_here.test_board_occupied()){ // проверка, что клетка, на которую пойдет конь не занята
			board[move_here.x][move_here.y] = 1; // на доске ставится 1

			move_knight(move_here, move_number+1);

			if (flag || move_number == X_SIZE * Y_SIZE-1) {
				flag = true;
				print_board(move_here);
				board[move_here.x][move_here.y] = 0;
				cout << "algorithm move: " << move_number << endl << endl;
				break;
			}
			board[move_here.x][move_here.y] = 0;
		}
	}
}

int main(){
	for (int i = 0; i < Y_SIZE; i++)
		for (int j = 0; j < X_SIZE; j++)
			board[j][i] = 0;

	board[start_x][start_y] = 1;
	move_knight(Point(start_x, start_y));
}

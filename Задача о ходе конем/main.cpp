#include <iostream>
using namespace std;

const int X_SIZE = 6;
const int Y_SIZE = 6;
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
int start_x = 5;
int start_y = 2;

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

int biggest_move_number = 0;
int* arrange_moves_by_priority(Point move_here);
bool finished_statement = false;
void move_knight(Point last_move, int move_number = 1){
	int* move_priority = arrange_moves_by_priority(last_move);
	for (int i = 0; i < 8; i++){
		Point move_here = last_move + moves[move_priority[i]];

		if (move_here.test_in_bounds() && !move_here.test_board_occupied()){ // проверка, что клетка, на которую пойдет конь не занята
			if (move_number > biggest_move_number){
				biggest_move_number=move_number;
				cout << "move encountoured: " << biggest_move_number << endl;
			}

			board[move_here.x][move_here.y] = 1; // на доске ставится 1

			move_knight(move_here, move_number+1);


			if (finished_statement || move_number == X_SIZE * Y_SIZE - 1) {
				finished_statement = true;
				print_board(move_here);
				board[move_here.x][move_here.y] = 0;
				cout << "algorithm move: " << move_number << endl << endl;
				break;
			}
			board[move_here.x][move_here.y] = 0;
		}
	}
}

int* arrange_moves_by_priority(Point move_here){
	int allowed_moves_for_each_move[8];
	int* result = new int[8];
	for (int i = 0; i < 8; i++){
		result[i] = i;
		int allowed_moves = 0;
		for (int j = 0; j < 8; j++){
			if ((move_here + moves[i]).test_in_bounds() && !(move_here + moves[i]).test_board_occupied())
				allowed_moves++;
		}
		allowed_moves_for_each_move[i] = allowed_moves;
	}
	bool flag = false;
	while (!flag){
		flag = true;
		for (int i = 0; i < 7; i++){
			if (allowed_moves_for_each_move[i] < allowed_moves_for_each_move[i+1]) {
				flag = false;
				allowed_moves_for_each_move[i] += allowed_moves_for_each_move[i+1];
				allowed_moves_for_each_move[i+1] = allowed_moves_for_each_move[i] - allowed_moves_for_each_move[i+1];
				allowed_moves_for_each_move[i] -= allowed_moves_for_each_move[i+1];

				result[i] += result[i+1];
				result[i+1] = result[i] - result[i+1];
				result[i] -= result[i+1];
			} else { flag = true; }
		}
	}
	return result;
}

int main(){
	for (int i = 0; i < Y_SIZE; i++)
		for (int j = 0; j < X_SIZE; j++)
			board[j][i] = 0;

	board[start_x][start_y] = 1;
	move_knight(Point(start_x, start_y));
}

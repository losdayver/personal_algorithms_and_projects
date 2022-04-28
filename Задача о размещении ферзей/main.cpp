#include <iostream>
#include <ctime>
using namespace std;

const int n = 8;
int board[n][n];
int final_board[n][n];
bool win_condition = false;

struct Point;
void draw_board(Point q);

struct Point{
	int x;
	int y;

	Point(int x ,int y){
		this->x = x;
		this->y = y;
	}

	bool operator==(const Point &other){
		return (this->x == other.x) && (this->y == other.y);
	}
};

bool test_occupied(Point p){
	return board[p.x][p.y] != 0;
}

bool test_in_bounds(Point p){
	return p.x < n && p.x >= 0 && p.y < n && p.y >= 0;
}

void fill_check_lines(Point p, int i){
	for (int x = 0; x < n; x++)
		if (board[x][p.y] == 0)
			board[x][p.y] = i;

	for (int y = 0; y < n; y++)
		if (board[p.x][y] == 0)
			board[p.x][y] = i;

	for (int x = 0; x < n; x++){
		Point p1(x, x - p.x + p.y);
		if (test_in_bounds(p1) && !test_occupied(p1))
			board[p1.x][p1.y] = i;
	}
	for (int x = 0; x < n; x++){
		Point p1(x, -(x - p.x) + p.y);
		if (test_in_bounds(p1) && !test_occupied(p1))
			board[p1.x][p1.y] = i;
	}
}

void erase_check_lines(Point p, int i){
	for (int x = 0; x < n; x++)
		if (board[x][p.y] == i)
			board[x][p.y] = 0;

	for (int y = 0; y < n; y++)
		if (board[p.x][y] == i)
			board[p.x][y] = 0;

	for (int x = 0; x < n; x++){
		Point p1(x, x - p.x + p.y);
		if (test_in_bounds(p1) && board[p1.x][p1.y] == i)
			board[p1.x][p1.y] = 0;
	}
	for (int x = 0; x < n; x++){
		Point p1(x, -(x - p.x) + p.y);
		if (test_in_bounds(p1) && board[p1.x][p1.y] == i)
			board[p1.x][p1.y] = 0;
	}
}

void place_queen(const Point q = Point(0, 0), int i = 1){
	for (int y = q.y; y < n; y++){
		for (int x = q.x; x < n; x++){
			Point p(x, y);
			if (!test_occupied(p)){
				fill_check_lines(p, i);

				place_queen(Point(0,0), i + 1);

				if (win_condition || i == n){
					win_condition = true;
					final_board[p.x][p.y] = 1;
					break;
				}
				erase_check_lines(p, i);
			}
		}
	}
}

void draw_final_board(){
	for (int y = 0; y < n; y++){
		for (int x = 0; x < n; x++){
			if (final_board[x][y] == 1) cout << "Q";
			else cout << "⃞";
		}
		cout << endl;
	}
}

int main() {
	auto start = clock();

	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			board[x][y] = 0;
			final_board[x][y] = 0;
		}

	place_queen();
	draw_final_board();
	cout << endl;

	auto end = clock();

	cout << "time passed: " << end - start;

	return 0;
}

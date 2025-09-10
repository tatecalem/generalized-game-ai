#pragma once
#include "TwoPlayerGame.h"
#include <iostream>
using std::cout;
using std::endl;

/*
Space numbers and what they mean
0=empty
1=p1
2=p2
3=p1 horizontal connection
4=p1 vertical connection
5=p1 both connection
6=p2 horizontal connection
7=p2 vertical connection
8=p2 both connection
9=p1 horiz, p2 vert
10=p2 horiz, p1 vert
*/

class Inline : public TwoPlayerGame
{
public:
	Inline();
	int eog_check();  // end of game check
	void update_score();
	double score();
	double heuristic();  // evaluation function
	vector<string> get_moves();
	void do_move(string move);
	void undo_move(string move);
	void raw_print();
	void print();

	static const int BOARD_SIZE = 5;
	void draw_connection(int center, int direc);
	void undo_connection(int center, int direc);
	void update_space(int space, int turn, int direc);
	void change_score(int turn, int amount);

private:
	short _board[BOARD_SIZE*BOARD_SIZE+1];  // 0 doesn't matter, 1-25 as if you're reading.
	int _p1_score;
	int _p2_score;
};


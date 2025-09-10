#pragma once
#include "TwoPlayerGame.h"
#include <iostream>
using std::cout;
using std::endl;
#include <utility>
using std::pair;

/* 
a[x][y] is in the xth row and yth column, like in matrices (but indexed at 0)
The move strings are like you were reading starting with 1.
Player 1 goes with 1s and Player 2 goes with 2s.
*/
class TicTacToe : public TwoPlayerGame
{
public:
	TicTacToe();
	int eog_check();  // end of game check
	void update_score();
	double score();
	double heuristic();  // evaluation function
	vector<string> get_moves();
	void do_move(string move);
	void undo_move(string move);
	void print();

	// moves are internally coords and interface-wise strings, so we need to convert
	static pair<int, int> move_string_to_coord(string s);
	static string move_coord_to_string(pair<int, int> p);

private:
	short _board[3][3];
	// _turn is implemented in parent
	vector<string> _win_arrs = { "123","456","789","147","258","369","159","357" };
	vector<pair<double, vector<string>>> _space_values;
};


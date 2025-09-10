#pragma once

#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;

class TwoPlayerGame
{
public:
	// constructor TODO

	virtual int eog_check();  // end of game check
	virtual void update_score();
	virtual double score();
	virtual double heuristic();  // the evaluation function
	virtual vector<string> get_moves();
	virtual void do_move(string move);
	virtual void undo_move(string move);
	virtual void switch_turn();
	virtual void play();  // for player vs player
	virtual void print();
	virtual int other_turn();

	// implementation of _board is left to child classes
	short _turn;  // TODO: should this be protected or private?
};


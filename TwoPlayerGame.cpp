#include "TwoPlayerGame.h"

int TwoPlayerGame::eog_check()  // end of game check
{
	return 0;
}

void TwoPlayerGame::update_score()
{
	cout << "TwoPlayerGame update_score()" << endl;
}

double TwoPlayerGame::score()
{
	cout << "TwoPlayerGame score()" << endl;
	return -1;
}

double TwoPlayerGame::heuristic()
{
	cout << "TwoPlayerGame heuristic()" << endl;
	return -1;
}

vector<string> TwoPlayerGame::get_moves()
{
	cout << "TwoPlayerGame get_moves()" << endl;
	return vector<string>({ "hi" });
}

void TwoPlayerGame::do_move(string move)
{
	cout << "TwoPlayerGame do_move()" << endl;
}

void TwoPlayerGame::undo_move(string move)
{
	cout << "TwoPlayerGame undo_move()" << endl;
}

void TwoPlayerGame::switch_turn()
{
	if (_turn == 1)
		_turn = 2;
	else
		_turn = 1;
}

void TwoPlayerGame::play()
{

}

void TwoPlayerGame::print()
{
	cout << "TwoPlayerGame print()" << endl;
}

int TwoPlayerGame::other_turn()
{
	if (_turn == 1)
		return 2;
	else
		return 1;
}
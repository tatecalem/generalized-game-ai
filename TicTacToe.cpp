#include "TicTacToe.h"

TicTacToe::TicTacToe()
{
	//cout << "TicTacToe constructor" << endl;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_board[i][j] = 0;  // set all spaces to 0
	_turn = 1;  // p1 goes first

	// generate space values for evaluation
	// corners and center are worth more than edges.
	vector<string> center;
	center.push_back(to_string(5));
	_space_values.push_back(pair<double, vector<string>>(0.15, center));
	vector<string> corners;
	corners.push_back(to_string(1));
	corners.push_back(to_string(3));
	corners.push_back(to_string(7));
	corners.push_back(to_string(9));
	_space_values.push_back(pair<double, vector<string>>(0.1, corners));
	vector<string> edges;
	edges.push_back(to_string(2));
	edges.push_back(to_string(4));
	edges.push_back(to_string(6));
	edges.push_back(to_string(8));
	_space_values.push_back(pair<double, vector<string>>(0.05, edges));
}

// -1=still going, 0=tie, 1=p1 win, 2=p2 win
int TicTacToe::eog_check()
{
	//cout << "TicTacToe eog_check()" << endl;

	// check to see if there are any winning arrangements
	for (auto& arr : _win_arrs)
	{
		pair<int, int> p0 = move_string_to_coord(arr.substr(0, 1));
		pair<int, int> p1 = move_string_to_coord(arr.substr(1, 1));
		pair<int, int> p2 = move_string_to_coord(arr.substr(2, 1));
		int match = _board[p0.first][p0.second];

		// if the whole arrangement matches and isn't 0s
		if (match != 0 && _board[p1.first][p1.second] == match && _board[p2.first][p2.second] == match)
		{
			return match;  // return the player's number that had the match
		}
	}

	// if there are no winning arrangements, check to see if the game ended in a tie
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			if (_board[x][y] == 0)  // if there's still an empty spot on the board
			{
				return -1;
			}

	return 0; // else, the game is a tie.
}

void TicTacToe::update_score()
{
	//cout << "TicTacToe update_score()" << endl;
}

double TicTacToe::score()
{
	//cout << "TicTacToe get_score()" << endl;
	return -1;
}

double TicTacToe::heuristic()
{
	//cout << "TicTacToe heuristic()" << endl;
	double eval = 0;
	// small adjustment for whose turn it is
	if (_turn == 1)
		eval += 0.05;
	else
		eval -= 0.05;
	//cout << "eval after turn adjustment:" << eval << endl;

	// adjust based on where players have gone
	for (auto& space_type : _space_values)
	{
		vector<string> spaces = space_type.second;
		for (auto& space : spaces)
		{
			pair<int, int> coord = move_string_to_coord(space);
			if (_board[coord.first][coord.second] == 1)
			{
				//cout << "Because of space " << space << " eval +" << space_type.first << endl;
				eval += space_type.first;
			}
			if (_board[coord.first][coord.second] == 2)
			{
				//cout << "Because of space " << space << " eval -" << space_type.first << endl;
				eval -= space_type.first;
			}
		}
	}
	//cout << "eval after space adjustment:" << eval << endl;
	if (-0.001 < eval && eval < 0.001) // set eval to 0 if double precision threw it off
		eval = 0;
	//cout << "eval after 0 adjustment:" << eval << endl;
	return eval;
}

vector<string> TicTacToe::get_moves()
{
	//cout << "TicTacToe get_moves()" << endl;
	vector<string> v;
	for (int i = 1; i <= 9; i++)
	{
		pair<int, int> move = move_string_to_coord(to_string(i));
		if (_board[move.first][move.second] == 0)  // if the space is 0
		{
			v.push_back(to_string(i));  // add the move to the vector.
		}
	}
	return v;
}

void TicTacToe::do_move(string move)
{
	//cout << "TicTacToe do_move()" << endl;

	pair<int, int> p = move_string_to_coord(move);  // convert move from string to coord
	_board[p.first][p.second] = _turn;  // change _board
	switch_turn();  // flip turn
}

void TicTacToe::undo_move(string move)
{
	//cout << "TicTacToe undo_move()" << endl;
	pair<int, int>p = move_string_to_coord(move);  // convert move from string to coord
	_board[p.first][p.second] = 0;  // make that space empty (0)
	switch_turn();  // flip turn
}

void TicTacToe::print()
{
	//cout << "TicTacToe print()" << endl;
	cout << "player " << _turn << ", it's your move" << endl;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
			cout << " " << _board[x][y];
		cout << endl;
	}
}

pair<int, int> TicTacToe::move_string_to_coord(string s)
{
	//cout << "TicTacToe move_string_to_coord" << endl;

	int temp = s[0] - '0'; // getting the move as a number

	// turning it into coordinates
	int row = (temp-1) / 3;
	int col = (temp-1) % 3;
	//cout << "row: " << row << " col: " << col << endl;

	return pair<int, int>(row, col);
}

string TicTacToe::move_coord_to_string(pair<int, int> p)
{
	//cout << "TicTacToe move_coord_to_string" << endl;
	return to_string(p.first*3+p.second+1);
}


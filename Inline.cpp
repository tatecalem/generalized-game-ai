#include "Inline.h"

Inline::Inline()
{
	for (int i = 1; i <= 25; i++)
	{
		_board[i] = 0; // initialize all spaces to empty
	}
	_turn = 1;  // p1 goes first

	// set both scores to 0
	_p1_score = 0;
	_p2_score = 0;
}

int Inline::eog_check()  // end of game check
{
	// are there any empty squares?  If so, return -1.
	for (int i = 1; i <= 25; i++)
	{
		if (_board[i] == 0)
			return -1;
	}
	if (_p1_score == _p2_score)  // If tied, return 0
		return 0;
	if (_p1_score > _p2_score)  // If p1 wins, return 1
		return 1;
	if (_p1_score < _p2_score)  // If p2 wins, return 2
		return 2;

	cout << "program execution should never get here" << endl;
	return -1;
}

void Inline::update_score()
{

}

double Inline::score()
{
	return 0.0;
}

double Inline::heuristic()  // evaluation function
{
	return _p1_score - _p2_score;
}

vector<string> Inline::get_moves()
{
	//cout << "Inline get_moves() called" << endl;
	vector<string> v;
	for (int i = 1; i <= BOARD_SIZE * BOARD_SIZE; i++)
	{
		if (_board[i] == 0)
			v.push_back(to_string(i));
	}
	return v;
}

void Inline::do_move(string move)
{
	int i = std::stoi(move);
	_board[i] = _turn;

	// draw connections
	draw_connection(i,-5); // up
	draw_connection(i,1); // right
	draw_connection(i,5); // down
	draw_connection(i,-1); // left

	switch_turn();
}

void Inline::undo_move(string move)
{
	int i = std::stoi(move);
	//cout << "undoing move: " << i << endl;

	switch_turn(); // do this first so undo_connection() works properly

	undo_connection(i, -5); // up
	undo_connection(i, 1); // right
	undo_connection(i, 5); // down
	undo_connection(i, -1); // left

	_board[i] = 0; // set center to 0
}

void Inline::raw_print()
{
	cout << "Inline raw_print()" << endl;
	cout << "turn: " << _turn << endl;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 1; y <= BOARD_SIZE; y++)
		{
			cout << " " << _board[BOARD_SIZE * x + y];
		}
		cout << endl;
	}
	cout << " Scores:   p1:" << _p1_score << " p2:" << _p2_score << endl;
}

void Inline::print()
{
	cout << "Inline print()" << endl;
	cout << "turn: " << _turn << endl;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 1; y <= BOARD_SIZE; y++)
		{
			int current = _board[BOARD_SIZE * x + y];
			string s = to_string(current);
			if (current == 3 || current == 6)
				s = "-";
			else if (current == 4 || current == 7)
				s = "|";
			else if (current == 5 || current == 8 || current == 9 || current == 10)
				s = "+";
			cout << " " << s;
		}
		cout << endl;
	}
	cout << " Scores:   p1:" << _p1_score << " p2:" << _p2_score << endl;
}

// direc is -5 for up, +1 for right, +5 for down, -1 for left
void Inline::draw_connection(int center, int direc)
{
	// set limits to what's needed for up or down
	int lower_limit=1;
	int upper_limit=25;
	if (direc == -1 || direc == 1) // if we're moving left or right, change the limits.
	{
		int row = ((center - 1) / 5 + 1);
		//cout << "row:" << row << endl;
		lower_limit = (row - 1) * 5 + 1;
		upper_limit = lower_limit + 4;
	}
	//cout << "center:" << center << " direc:" << direc << endl;
	//cout << " lower limit:" << lower_limit << " upper limit:" << upper_limit << endl;

	int cursor = center+direc;
	// scan out for another piece to connect to
	while (cursor >= lower_limit && cursor <= upper_limit)
	{
		//cout << "cursor currently points at " << cursor << endl;
		if (_board[cursor] == other_turn())  // if you run into an opponent's piece, no connection.
		{
			//cout << "blocked by opponent piece" << endl;
			return;
		}
		if (_board[cursor] == _board[center])  // if you encounter your own piece, draw a connection
		{
			//cout << "connection point found" << endl;
			// as you head back to the center, draw the connection
			if (cursor != center)
				cursor -= direc;
			while (cursor != center)
			{
				//cout << "updating _board[" << cursor << "]" << endl;
				update_space(cursor, _turn, direc);
				cursor -= direc;
			}
			return;
		}
		cursor += direc;
	}
	//cout << "cursor went oob" << endl;
}

void Inline::undo_connection(int center, int direc)
{
	// set limits to what's needed for up or down
	int lower_limit = 1;
	int upper_limit = 25;
	if (direc == -1 || direc == 1) // if we're moving left or right, change the limits.
	{
		int row = ((center - 1) / 5 + 1);
		//cout << "row:" << row << endl;
		lower_limit = (row - 1) * 5 + 1;
		upper_limit = lower_limit + 4;
	}
	//cout << "center:" << center << " direc:" << direc << endl;
	//cout << " lower limit:" << lower_limit << " upper limit:" << upper_limit << endl;

	int cursor = center + direc;
	// scan out for another piece to connect to
	while (cursor >= lower_limit && cursor <= upper_limit)
	{
		//cout << "  _board[" << cursor << "] is " << _board[cursor] << endl;
		if (_board[cursor] <= 2)  // if you are at a piece or an empty square you're done
		{
			//cout << "    not a connection" << endl;
			return;
		}
		else {  // make a change
			//cout << "    maybe making a change" << endl;
			if (_board[cursor] == 9 || _board[cursor] == 10)
				change_score(_turn, -1);  // if undoing a cross move, take away that bonus point.

			if (direc == 1 || direc == -1)  // if you're moving horizontally
			{
				if (_board[cursor] == 3 || _board[cursor] == 6)  // if it was just a horizontal connection
				{
					_board[cursor] = 0;  // remove it
					change_score(_turn, -1);
				}
				else if (_board[cursor] == 5 || _board[cursor] == 10)  // if the vertical component is p1
				{
					_board[cursor] = 4;  // set it to p1 vertical
					change_score(_turn, -1);
				}
				else if (_board[cursor] == 8 || _board[cursor] == 9)  // if the vertical component is p2
				{
					_board[cursor] = 7;  // set it to p2 vertical
					change_score(_turn, -1);
				}
				else
					return;  // if you're here you haven't seen anything with a horizontal component, so don't keep looking.
			}
			else // if you're moving vertically
			{
				if (_board[cursor] == 4 || _board[cursor] == 7)  // if it was just a vertical connection
				{
					_board[cursor] = 0;  // remove it
					change_score(_turn, -1);
				}
				else if (_board[cursor] == 5 || _board[cursor] == 9)  // if the horizontal component is p1
				{
					_board[cursor] = 3;  // set it to p1 horizontal
					change_score(_turn, -1);
				}
				else if (_board[cursor] == 8 || _board[cursor] == 10)  // if the horizontal component is p2
				{
					_board[cursor] = 6;  // set it to p2 horizontal
					change_score(_turn, -1);
				}
				else
					return;  // if you're here you haven't seen anything with a vertical component, so don't keep looking.
			}
		}
		cursor += direc;
	}
	//cout << "    cursor (" << cursor << ") went oob" << endl;
}

void Inline::update_space(int space, int turn, int direc)
{
	change_score(_turn, 1); // a connection is being made so the player gets 1pt

	//cout << "update_space() with space:" << space << " turn:" << turn << " direc:" << direc << endl;
	//cout << " _board[space]=" << _board[space] << endl;
	if (_board[space] == 0)  // the space is currently empty
	{
		_board[space] = turn * 3;  // 3 is p1 horiz, 6 is p2 horiz
		if (direc == 5 || direc == -5)
			_board[space] += 1;  // 4 is p1 vert, 7 is p2 vert
	}
	else if (_board[space] / 3 == turn)  // if its crossing over itself
	{
		if (direc == 5 || direc == -5)
			_board[space] += 2;  // 5 is p1 both, 8 is p2 both
		else
			_board[space] += 1;  // same as above
	}
	else  // this means it's crossing over the other player
	{
		_board[space] = 9;
		change_score(_turn, 1);  // bonus point

		// there's two cases where the space needs to be 10
		if (turn == 1 && (direc == 5 || direc == -5))  // if we're adding vertical p1
		{
			_board[space] += 1;
		}
		if (turn == 2 && (direc == 1 || direc == -1))  // if we're adding horizontal p2
		{
			_board[space] += 1;
		}
	}
}

void Inline::change_score(int turn, int amount)
{
	if (turn == 1)
		_p1_score += amount;
	else
		_p2_score += amount;
}
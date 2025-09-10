#include "rungame.h"

void play(TwoPlayerGame& game)
{
	//cout << "TicTacToe play()" << endl;
	while (true)
	{
		cout << "Currently player " << game._turn << "'s turn" << endl;

		vector<string> possible_moves = game.get_moves();
		string s;
		while (true)
		{
			// the player enters a legal move
			cout << "What space do you want to play in?" << endl;
			std::cin >> s;
			bool is_legal = false;
			for (auto& move : possible_moves)
			{
				if (move == s)
					is_legal = true;
			}
			if (is_legal)
			{
				cout << "You selected " << s << endl;
				break;
			}
			else {
				cout << "That move isn't one of the legal moves.  Try again." << endl;
			}
		}

		// make the move
		game.do_move(s);
		game.print();
		int eog_check = game.eog_check();
		if (eog_check == 0)
		{
			cout << "The game ended in a tie." << endl;
			return;
		}
		else if (eog_check == 1)
		{
			cout << "Player 1 wins!" << endl;
			return;
		}
		else if (eog_check == 2)
		{
			cout << "Player 2 wins!" << endl;
			return;
		}
	}
}

void play_vs_ai(TwoPlayerGame& game, string(*ai)(TwoPlayerGame&, int, bool), int depth)
{
	//cout << "TicTacToe play_vs_ai()" << endl;
	cout << "Do you want to be p1 or p2?  Type p1 or p2" << endl;
	string temp;
	std::cin >> temp;

	string player_or_ai[3] = { "","","" };
	if (temp == "p1")
	{
		player_or_ai[1] = "player";
		player_or_ai[2] = "ai";
	}
	else if (temp == "p2")
	{
		player_or_ai[1] = "ai";
		player_or_ai[2] = "player";
	}
	else {
		cout << "invalid response." << endl;
		return;
	}

	while (true)
	{
		cout << "Currently player " << game._turn << "'s turn" << endl;
		cout << "That player is " << player_or_ai[game._turn] << endl;

		string s;
		if (player_or_ai[game._turn] == "player")
		{
			vector<string> possible_moves = game.get_moves();
			while (true)
			{
				// the player enters a legal move
				cout << "What space do you want to play in?" << endl;
				cout << "  The top left space is 1, then reading right-to-left it counts up (so 5 is the middle)" << endl;
				std::cin >> s;
				bool is_legal = false;
				for (auto& move : possible_moves)
				{
					if (move == s)
						is_legal = true;
				}
				if (is_legal)
				{
					cout << "You selected " << s << endl;
					break;
				}
				else {
					cout << "That move isn't one of the legal moves.  Try again." << endl;
				}
			}
		}
		else {  // it's currently ai's turn
			if (game._turn == 1)
			{
				s = ai(game, depth, true);
			}
			else {
				s = ai(game, depth, false);
			}
		}

		// make the move
		game.do_move(s);
		game.print();
		int eog_check = game.eog_check();
		if (eog_check == 0)
		{
			cout << "The game ended in a tie." << endl;
			return;
		}
		else if (eog_check == 1)
		{
			cout << "Player 1 wins!" << endl;
			return;
		}
		else if (eog_check == 2)
		{
			cout << "Player 2 wins!" << endl;
			return;
		}
	}
}


void ai_vs_ai(TwoPlayerGame& game, string(*ai)(TwoPlayerGame&, int, bool), int depth)
{
	string s;	
	while (true)
	{
		// get the best move for the given player
		if (game._turn == 1)
		{
			s = ai(game, depth, true);
		}
		else {
			s = ai(game, depth, false);
		}

		// make the move
		game.do_move(s);
		game.print();
		int eog_check = game.eog_check();
		if (eog_check == 0)
		{
			cout << "The game ended in a tie." << endl;
			return;
		}
		else if (eog_check == 1)
		{
			cout << "Player 1 wins!" << endl;
			return;
		}
		else if (eog_check == 2)
		{
			cout << "Player 2 wins!" << endl;
			return;
		}
	}
}


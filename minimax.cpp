#include "minimax.h"
#include "TwoPlayerGame.h"

string minimax_only_move(TwoPlayerGame& game, int depth_to_search, bool is_maximizing_player)
{
	return minimax(game, depth_to_search, is_maximizing_player).second;
}

pair<double,string> minimax(TwoPlayerGame& game, int depth_to_search, bool is_maximizing_player)
{
	// base case 1: is the game over? Has someone won or is it a tie?
	int eog_check = game.eog_check();
	if (eog_check == 0)
	{
		//cout << "    it would be a tie" << endl;
		return pair<double, string>(0, string());
	}
	if (eog_check == 1)
	{
		//cout << "    player 1 would win" << endl;
		return pair<double,string>(100,string());
	}
	if (eog_check == 2)
	{
		//cout << "    player 2 would win" << endl;
		return pair<double, string>(-100, string());
	}

	// base case 2: are we at the depth we meant to search to?
	if (depth_to_search <= 0)
	{
		double h = game.heuristic();
		//cout << "    heuristic=" << h << ". at depth" << endl;
		return pair<double,string>(h,string());
	}

	// recursive case
	//cout << "start minimax recursive case" << endl;
	if (is_maximizing_player)
	{
		//cout << "  Finding best p1 move" << endl;
		double best_eval = -DBL_MAX;
		string best_move = "";

		vector<string> moves = game.get_moves();
		for (auto& move : moves)
		{
			//cout << "  looking at move: " << move << " for p" << game->_turn << endl;
			game.do_move(move);
			pair<double, string> return_pair = minimax(game, depth_to_search - 1, false);
			game.undo_move(move);
			if (return_pair.first > best_eval) // if this move is the best seen so far
			{
				best_eval = return_pair.first;  // update best eval
				best_move = move;  // update best move
				//cout << "  new best move for p1: " << best_move << endl;
			}
		}
		//cout << "end minimax, returning move " << best_move << " with eval " << best_eval << endl;
		return pair<double, string>(best_eval, best_move);
	}
	else // is minimizing player
	{
		//cout << "  Finding best p2 move" << endl;
		double best_eval = DBL_MAX;
		string best_move = "";

		vector<string> moves = game.get_moves();
		for (auto& move : moves)
		{
			//cout << "  looking at move: " << move << " for p" << game->_turn << endl;
			game.do_move(move);
			pair<double, string> return_pair = minimax(game, depth_to_search - 1, true);
			game.undo_move(move);
			if (return_pair.first < best_eval) // if this move is the best seen so far
			{
				best_eval = return_pair.first;  // update best eval
				best_move = move;  // update best move
				//cout << "  new best move for p2: " << best_move << endl;
			}
		}
		//cout << "end minimax, returning move " << best_move << " with eval " << best_eval << endl;
		return pair<double,string>(best_eval,best_move);
	}
	// code never gets here.  There's an if-else
}


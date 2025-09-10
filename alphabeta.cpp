#include "alphabeta.h"

/*
chessprogramming pseudocode
int alphaBetaMax( int alpha, int beta, int depthleft ) {
   if ( depthleft == 0 ) return evaluate();
   for ( all moves) {
      score = alphaBetaMin( alpha, beta, depthleft - 1 );
      if( score >= beta )
         return beta;   // fail hard beta-cutoff
      if( score > alpha )
         alpha = score; // alpha acts like max in MiniMax
   }
   return alpha;
}

int alphaBetaMin( int alpha, int beta, int depthleft ) {
   if ( depthleft == 0 ) return -evaluate();
   for ( all moves) {
      score = alphaBetaMax( alpha, beta, depthleft - 1 );
      if( score <= alpha )
         return alpha; // fail hard alpha-cutoff
      if( score < beta )
         beta = score; // beta acts like min in MiniMax
   }
   return beta;
}



https://ics.uci.edu/~eppstein/180a/990202b.html pseudocode
// fail-soft alpha-beta search
    int alphabeta(int depth, int alpha, int beta)
    {
        move bestmove;
        int current = -WIN;
        if (game over or depth <= 0) return winning score or eval();
        for (each possible move m) {
            make move m;
            score = -alphabeta(depth - 1, -beta, -alpha)
            unmake move m;
            if (score >= current) {
                current = score;
                bestmove = m;
                if (score >= alpha) alpha = score;
                if (score >= beta) break;
            }
        }
        return current;
    }

*/

// alpha is the minimum score that p1 is assured of
// beta is the maximum score that p2 is assured of

string alphabeta_only_move(TwoPlayerGame& game, int depth_to_search, bool is_maximizing_player)
{
    if (game._turn == 1)  // if it's the maximizing player's turn
    {
        return alphabeta_maximizing(game, depth_to_search, -DBL_MAX, DBL_MAX).second;
    }
    else
    {
        return alphabeta_minimizing(game, depth_to_search, -DBL_MAX, DBL_MAX).second;
    }
}

pair<double,string> alphabeta_maximizing(TwoPlayerGame& game, int depth_to_search, double alpha, double beta)
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
        return pair<double, string>(100, string());
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
        //cout << "    heuristic=" << h << "  at depth" << endl;
        return pair<double, string>(h, string());
    }

    // recursive case
    //cout << "start alphabeta_maximizing() recursive case" << endl;
    string best_move;
    double best_eval = -DBL_MAX;
    vector<string> moves = game.get_moves();
    for (auto& move : moves)
    {
        //cout << "  looking at move: " << move << " for p" << game._turn << endl;
        game.do_move(move);
        pair<double, string> return_pair = alphabeta_minimizing(game, depth_to_search - 1, alpha, beta);
        game.undo_move(move);

        if (return_pair.first > best_eval) // if this move is the best seen so far
        {
            best_eval = return_pair.first;  // update best eval
            best_move = move;  // update best move
            //cout << "  new best move for p1: " << best_move << endl;
            if (best_eval > alpha)  // p1 is now assured of a better move, so update alpha.
            {
                //cout << "alpha updated from " << alpha << " to " << best_eval << endl;
                alpha = best_eval;
            }
            if (best_eval >= beta)  // if p2 can guarantee the same or lower score, prune this branch.
            {
                //cout << "best_eval>=beta, so breaking out" << endl;
                break;
            }
        }
        
    }
    return pair<double, string>(best_eval, best_move);
}

pair<double, string> alphabeta_minimizing(TwoPlayerGame& game, int depth_to_search, double alpha, double beta)
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
        return pair<double, string>(100, string());
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
        //cout << "    heuristic=" << h << "  at depth" << endl;
        return pair<double, string>(h, string());
    }

    // recursive case
    //cout << "start alphabeta_minimizing() recursive case" << endl;
    string best_move;
    double best_eval = DBL_MAX;
    vector<string> moves = game.get_moves();
    for (auto& move : moves)
    {
        //cout << "  looking at move: " << move << " for p" << game._turn << endl;
        game.do_move(move);
        pair<double, string> return_pair = alphabeta_maximizing(game, depth_to_search - 1, alpha, beta);
        game.undo_move(move);

        if (return_pair.first < best_eval) // if this move is the best seen so far
        {
            best_eval = return_pair.first;  // update best eval
            best_move = move;  // update best move
            //cout << "  new best move for p2: " << best_move << endl;
            if (best_eval < beta)  // p2 is now assured of a better move, so update beta.
            {
                //cout << "  beta updated from " << beta << " to " << best_eval << endl;
                beta = best_eval;
            }
            if (best_eval <= alpha)  // if p1 can guarantee the same or higher score, prune this branch.
            {
                //cout << "  best_eval<=alpha, so breaking out" << endl;
                break;
            }
        }
    }
    return pair<double, string>(best_eval, best_move);
}



#pragma once

#include "TwoPlayerGame.h"

#include <float.h> // for DBL_MAX
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm> // for max
using std::max;
using std::min;
#include <utility> // for pair
using std::pair;

// alpha is the minimum score that p1 is assured of
// beta is the maximum score that p2 is assured of

string alphabeta_only_move(TwoPlayerGame& game, int depth_to_search, bool is_maximizing_player);
pair<double, string> alphabeta_maximizing(TwoPlayerGame& game, int depth_to_search, double alpha, double beta);
pair<double, string> alphabeta_minimizing(TwoPlayerGame& game, int depth_to_search, double alpha, double beta);

/*
It is my understanding that fail-hard and fail-soft alphabeta return the same move,
but fail-soft returns an eval outside the bounds [alpha,beta] that gives slightly more
accurate information if you do some other stuff (transposition table, other nonsense).
It doesn't look like it really matters what I do initially before I add that nonsense.
I might as well do fail-soft, I think.
https://ics.uci.edu/~eppstein/180a/990202b.html
*/
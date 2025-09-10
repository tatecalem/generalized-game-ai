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

// just returns the best move
string minimax_only_move(TwoPlayerGame& game, int depth_to_search, bool is_maximizing_player);

// returns a pair with first being the eval and second being the move with that eval
pair<double, string> minimax(TwoPlayerGame& game, int depth_to_search, bool is_maximizing_player);


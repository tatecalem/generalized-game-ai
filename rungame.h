#pragma once
#include "TwoPlayerGame.h"
#include "minimax.h"

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;

void play(TwoPlayerGame& game);
void play_vs_ai(TwoPlayerGame& game, string (*ai)(TwoPlayerGame&, int , bool), int depth);
void ai_vs_ai(TwoPlayerGame& game, string(*ai)(TwoPlayerGame&, int, bool), int depth);
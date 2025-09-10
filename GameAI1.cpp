#include "minimax.h"
#include "alphabeta.h"
#include "TwoPlayerGame.h"
#include "TicTacToe.h"
#include "Inline.h"
#include "rungame.h"

#include <iostream>
using std::cout;
using std::endl;

void demonstration();

int main()
{
    demonstration();
    
    return 0;
}


void demonstration()
{
    cout << "Here's a demonstration of some things this code can do." << endl;
    cout << "  It can play TicTacToe against itself, calculating all the way" << endl;
    cout << "   to the end of the game.  It uses alpha-beta tree pruning." << endl;
    TicTacToe g1;
    ai_vs_ai(g1, alphabeta_only_move, 9);
    cout << "  The same code can be reused to play a game I made up." << endl;
    Inline g2;
    ai_vs_ai(g2, alphabeta_only_move, 5);

    cout << "\nAnd, it can play TicTacToe against you!" << endl;
    TicTacToe g3;
    play_vs_ai(g3, alphabeta_only_move, 9);
}
The main function is in GameAI1.cpp.  There is a demonstration() function that shows you the main features of the program.

My program contains 2 different ways of finding the best move in a given situation: minimax (slower) and alphabeta tree pruning (faster).
Both find the optimal move as determined by a (subjective) evaluation function.

I've implemented two games in my program.  TicTacToe, and a custom game called Inline.  Either game can be played against either algorithm.

A brief overview of Inline's rules are as follows.
  Players take turns placing their pieces on empty spaces.  When a piece is played it connects in the 4 cardinal directions to any closest matching pieces, unless blocked by an opponent's piece.
  You get 1pt per unit length of connection made.
  You get 1 extra point each time one of your connections crosses an opponent's connections.
  The game ends when the board is full, and the player with the most points wins.

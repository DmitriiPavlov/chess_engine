#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <vector>
#include <cmath> 
// std::vector<MOVE> generateNegativeMoves(STATE state)
// std::vector<MOVE> generatePositiveMoves(STATE state)
// float evalState(STATE state)
// playMove(STATE state, MOVE move)
// undoMove(STATE state, MOVE move)

struct TicTacToeBoard{
  int array[3][3] = {0};
};

struct TicTacToeMove{
  int x;
  int y;
  //-1 or 1 
  int player;
};

std::vector<TicTacToeMove> generateNegativeMoves(const TicTacToeBoard& board);
std::vector<TicTacToeMove> generatePositiveMoves(const TicTacToeBoard& board);
float evalState(const TicTacToeBoard& board);
void playMove(TicTacToeBoard& board, const TicTacToeMove& move);
void undoMove(TicTacToeBoard& board, const TicTacToeMove& move);





#endif

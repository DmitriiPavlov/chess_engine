// internal
#include "board_representation.h"
#include "minimax/minimax_algorithm.cpp"
#include "minimax/minimax_algorithm.h"
#include "render.h"
#include "tictactoe/tictactoe.cpp"
#include "tictactoe/tictactoe.h"

template class MinimaxSolver<TicTacToeBoard, TicTacToeMove>;

int main() {
  TicTacToeBoard board;
  MinimaxSolver<TicTacToeBoard, TicTacToeMove> solver(board, -1);
  TicTacToeMove move = solver.findBestMove(8);
  std::cout << move.x << "\n";;
  std::cout << move.y << "\n";
  return 0;
}

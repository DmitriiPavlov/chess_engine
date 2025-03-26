// internal
#include "board_representation.h"
#include "connect_four/connect_four.cpp"
#include "connect_four/connect_four.h"
#include "minimax/minimax_algorithm.cpp"
#include "minimax/minimax_algorithm.h"
#include "render.h"
#include <stdio.h>

template class MinimaxSolver<ConnectFourBoard, ConnectFourMove>;

int main() {
  ConnectFourBoard board = {};
  while (true) {
    MinimaxSolver<ConnectFourBoard, ConnectFourMove> solver(board, 1);
    ConnectFourMove move = solver.findBestMove(8);
    move.player = 1;
    std::cout << "Move X:" << move.x << "\n";
    std::cout << "Move Y:" << move.y << "\n";
    playMove(board, move);
    ConnectFourMove newMove;
    newMove.player = -1;
    std::cout<<"Enter Move X:"; 
    std::cin >> newMove.x;
    std::cout<<"Enter Move Y:";
    std::cin >> newMove.y;
    playMove(board,newMove);
  }
  /*while (true) {*/
  /*  MinimaxSolver<ConnectFourBoard, ConnectFourMove> solver(board, -1);*/
  /*  int x, y;*/
  /*  ConnectFourMove move = solver.findBestMove(42);*/
  /*  std::cout << "Move X:" << move.x << "\n";*/
  /*  std::cout << "Move Y:" << move.y << "\n";*/
  /*  std::cout << "Enter your move x: ";*/
  /*  std::cin >> x;*/
  /*  std::cout << "Enter your move y: ";*/
  /*  std::cin >> y;*/
  /*  playMove(board, ConnectFourMove{x, y, 1});*/
  /*}*/
  return 0;
}

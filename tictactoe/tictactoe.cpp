#include "tictactoe.h"


std::vector<TicTacToeMove> generateNegativeMoves(const TicTacToeBoard& board) {
  std::vector<TicTacToeMove> moves = std::vector<TicTacToeMove>();
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (board.array[x][y] == 0) {
        TicTacToeMove move = {};
        move.x = x;
        move.y = y;
        move.player = -1;
        moves.push_back(move);
      }
    }
  }
  return moves;
}

std::vector<TicTacToeMove> generatePositiveMoves(const TicTacToeBoard& board){
  std::vector<TicTacToeMove> moves = std::vector<TicTacToeMove>();
  for (int x = 0; x < 3; x += 1) {
    for (int y = 0; y < 3; y += 1) {
      if (board.array[x][y] == 0) {
        TicTacToeMove move = {};
        move.x = x;
        move.y = y;
        move.player = 1;
        moves.push_back(move);
      }
    }
  }
  return moves;
}

float determineInf(int player){
  if (player == -1){
    return -INFINITY;
  }
  return INFINITY;
}

float evalState(TicTacToeBoard& board){
  for (int x = 0; x < 3; x++){
    if (board.array[x][0] == board.array[x][1] && board.array[x][1] == board.array[x][2] && board.array[x][0] != 0){
      return determineInf(board.array[x][0]);
    }
  }

  for (int y = 0; y < 3; y++){
    if (board.array[0][y] == board.array[1][y] && board.array[1][y] == board.array[2][y] && board.array[0][y] != 0){
      return determineInf(board.array[0][y]);
    }
  }
    
  if (board.array[0][0] == board.array[1][1] && board.array[1][1] == board.array[2][2] && board.array[0][0] != 0){
      return determineInf(board.array[0][0]);
  }

  if (board.array[0][2] == board.array[1][1] && board.array[1][1] == board.array[2][0] && board.array[0][2] != 0){
      return determineInf(board.array[0][0]);
  }

  return 0;

}

void playMove(TicTacToeBoard& board, const TicTacToeMove& move){
  board.array[move.x][move.y] = move.player;
}
void undoMove(TicTacToeBoard& board, const TicTacToeMove& move){
  board.array[move.x][move.y] = 0;
}

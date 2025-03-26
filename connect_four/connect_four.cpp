#include "connect_four.h"

std::vector<ConnectFourMove>
generateNegativeMoves(const ConnectFourBoard &board) {
  std::vector<ConnectFourMove> out;
  for (int x = 0; x < 7; x++) {
    for (int y = 0; y < 6; y++) {
      if (board.array[x][y] == 0) {
        out.push_back(ConnectFourMove{x, y, -1});
        break;
      }
    }
  }
  return out;
}

std::vector<ConnectFourMove>
generatePositiveMoves(const ConnectFourBoard &board) {
  std::vector<ConnectFourMove> out;
  for (int x = 0; x < 7; x++) {
    for (int y = 0; y < 6; y++) {
      if (board.array[x][y] == 0) {
        out.push_back(ConnectFourMove{x, y, 1});
        break;
      }
    }
  }
  return out;
}

int winningPlayerDirection(const ConnectFourBoard &board, int dx, int dy, int x,
                           int y) {
  if (x + 3 * dx >= 7 || y + 3 * dy >= 6 || x + 3 * dx < 0 || y + 3 * dy < 0) {
    return 0;
  }
  int first = board.array[x][y];
  int second = board.array[x + 1 * dx][ y + 1 * dy];
  int third = board.array[x + 2 * dx][ y + 2 * dy];
  int fourth = board.array[x + 3 * dx][ y + 3 * dy];
  if (first != 0 && first == second && first == third && first == fourth) {
    return board.array[x][y];
  }
  return 0;
}

int winningPlayer(const ConnectFourBoard &board) {
  for (int x = 0; x < 7; x++) {
    for (int y = 0; y < 6; y++) {
      int winning_up = winningPlayerDirection(board, 0, 1, x, y);
      if (winning_up != 0)
        return winning_up;

      int winning_right = winningPlayerDirection(board, 1, 0, x, y);
      if (winning_right != 0)
        return winning_right;

      int winning_diagonal_right = winningPlayerDirection(board, 1, 1, x, y);
      if (winning_diagonal_right != 0)
        return winning_diagonal_right;

      int winning_diagonal_left = winningPlayerDirection(board, 1, -1, x, y);
      if (winning_diagonal_left != 0)
        return winning_diagonal_left;
    }
  }
  return 0;
}

float evalState(const ConnectFourBoard &board) {
  int player = winningPlayer(board);
  if (player == 0){
    int score = 0;
    for (int x = 3; x < 4; x++){
      for (int y = 0; y < 6; y++){       
        score += board.array[x][y];
      }
    }
    return score;
  }
  return player * INFINITY;
}
void playMove(ConnectFourBoard &board, const ConnectFourMove &move) {
  if (move.player != 0)
    board.array[move.x][move.y] = move.player;
}
void undoMove(ConnectFourBoard &board, const ConnectFourMove &move) {
  if (move.player != 0)
    board.array[move.x][move.y] = 0;
}

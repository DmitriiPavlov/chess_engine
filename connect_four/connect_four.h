#ifndef CONNECT_FOUR_H
#define CONNECT_FOUR_H

//builtin 
#include <vector>
#include <cmath>

struct ConnectFourBoard{
  int array[7][6] = {0};
  uint64_t pos_bitmask = 0;
  uint64_t neg_bitmask = 0;

  bool operator<(const ConnectFourBoard& other) const {
    for (int x = 0; x < 7; x++){
      for (int y = 0; y < 6; y++){
        if (array[x][y] != other.array[x][y]){
          return array[x][y] < other.array[x][y];
        }
      }
    }
  }
};

struct ConnectFourMove{
  int x;
  int y;
  //-1 or 1 
  int player;
};


std::vector<ConnectFourMove> generateNegativeMoves(const ConnectFourBoard& board);
std::vector<ConnectFourMove> generatePositiveMoves(const ConnectFourBoard& board);
float evalState(const ConnectFourBoard& board);
void playMove(ConnectFourBoard& board, const ConnectFourMove& move);
void undoMove(ConnectFourBoard& board, const ConnectFourMove& move);




#endif

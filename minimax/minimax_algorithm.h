#ifndef MINIMAX_ALGORITHM_H
#define MINIMAX_ALGORITHM_H

// internal
#include <cstdint>
#include <vector>
#include <algorithm>
// assumes the existence of these methods:
//
// std::vector<MOVE> generateNegativeMoves(STATE state)
// std::vector<MOVE> generatePositiveMoves(STATE state)
// float evalState(STATE state)
// playMove(STATE state, MOVE move)
// undoMove(STATE state, MOVE move)
//
//

template <typename STATE, typename MOVE> class MinimaxSolver {
private:
  STATE internal_state;
  int8_t parity;

public:
  MinimaxSolver(STATE current_state, int8_t parity);

  MOVE findBestMove(int depth);
};

template <typename STATE, typename MOVE> struct MinimaxGraphNode {
  float evaluation;
  MinimaxGraphNode<STATE, MOVE> *parent;
  std::vector<MinimaxGraphNode<STATE, MOVE> *> children;
};

#endif

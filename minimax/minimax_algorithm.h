#ifndef MINIMAX_ALGORITHM_H
#define MINIMAX_ALGORITHM_H

// internal
#include <cstdint>
#include <vector>
#include <algorithm>
#include <map>

// assumes the existence of these methods:
//
// std::vector<MOVE> generateNegativeMoves(STATE state)
// std::vector<MOVE> generatePositiveMoves(STATE state)
// float evalState(STATE state)
// playMove(STATE state, MOVE move)
// undoMove(STATE state, MOVE move)
//
//


template <typename STATE, typename MOVE> struct MinimaxGraphNode {
  MOVE move_taken_here;
  float evaluation;
  MinimaxGraphNode<STATE, MOVE> *parent;
  std::vector<MinimaxGraphNode<STATE, MOVE> *> children;
};

template <typename STATE, typename MOVE> class MinimaxSolver {
private:
  STATE internal_state;
  MinimaxGraphNode<STATE,MOVE>* head_node;
  std::map<STATE,MinimaxGraphNode<STATE,MOVE>*> node_cache;
  int8_t parity;


public:
  MinimaxSolver(STATE current_state, int8_t parity);

  MOVE findBestMove(int depth);
};

#endif

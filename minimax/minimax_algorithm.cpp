#include "minimax_algorithm.h"
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

// creates all the children of a given node
template <typename STATE, typename MOVE>
void populateChildren(MinimaxGraphNode<STATE, MOVE> *node, STATE state,
                      int8_t parity) {
  std::vector<MOVE> possible_moves{};

  if (parity < 0) {
    possible_moves = generateNegativeMoves(state);
  }

  if (parity > 0) {
    possible_moves = generatePositiveMoves(state);
  }

  for (MOVE move : possible_moves) {
    MinimaxGraphNode<STATE, MOVE> *new_node =
        new MinimaxGraphNode<STATE, MOVE>();
    new_node->parent = node;
    new_node->move_taken_here = move;
    new_node->children = std::vector<MinimaxGraphNode<STATE, MOVE> *>();

    playMove(state, move);
    new_node->evaluation = evalState(state);
    undoMove(state, move);

    node->children.push_back(new_node);
  }
}

template <typename STATE, typename MOVE>
MinimaxGraphNode<STATE, MOVE> *
minEvaluationNode(std::vector<MinimaxGraphNode<STATE, MOVE> *> node_list) {
  float min = 0;
  MinimaxGraphNode<STATE, MOVE> *out;
  for (auto *node : node_list) {
    if (node->evaluation < min) {
      min = node->evaluation;
      out = node;
    }
  }
  return min;
}

template <typename STATE, typename MOVE>
MinimaxGraphNode<STATE, MOVE> *
maxEvaluationNode(std::vector<MinimaxGraphNode<STATE, MOVE> *> node_list) {
  float max = 0;
  MinimaxGraphNode<STATE, MOVE> *out;
  for (auto *node : node_list) {
    if (node->evaluation > max) {
      max = node->evaluation;
      out = node;
    }
  }
  return max;
}

// this goes through and updates the evaluation of a node recursively, based on
// its children nodes this should be called on the parent of newly created nodes
// parity is the person who has yet to move, so for negative parity the correct
// behavior would be to select the minimum and vice versa
template <typename STATE, typename MOVE>
void updateEvaluation(MinimaxGraphNode<STATE, MOVE> *node, int8_t parity) {
  float original_evaluation = node->evaluation;

  if (parity < 0)
    node->evaluation =
        std::min(node->evaluation, minEvaluationNode(node->children)->evaluation);
  if (parity > 0)
    node->evaluation =
        std::max(node->evaluation, maxEvaluationNode(node->children)->evaluation);

  if (original_evaluation != node->evaluation && node->parent != nullptr)
    updateEvaluation(node->parent);
}

// this magical function is going to do 3 things at once
// create new children nodes from this current node
// compute their evaluations
// update all the evaluations of this node, and of the parent nodes recursively

template <typename STATE, typename MOVE>
void expandNode(MinimaxGraphNode<STATE, MOVE> *node, STATE state,
                int8_t parity) {
  populateChildren(node, state, parity);
  updateEvaluation(node, parity);
}

template <typename STATE, typename MOVE>
void expandNodeWithDepth(MinimaxGraphNode<STATE, MOVE> *node, STATE state,
                         int8_t parity, int depth) {
  if (depth == 0)
    return;
  expandNode(node);

  for (auto *node : node->children) {
    expandNode(node, playMove(state, node->move_taken_here), -1 * parity,
               depth - 1);
  }
}

template <typename STATE, typename MOVE>
MinimaxSolver<STATE, MOVE>::MinimaxSolver(STATE current_state, int8_t parity) {
  this->internal_state = current_state;
  this->parity = parity;

  this->head_node = new MinimaxGraphNode<STATE, MOVE>();
  head_node->evaluation = evalState(current_state);
  head_node->parent = nullptr;
  head_node->children = std::vector<MinimaxGraphNode<STATE, MOVE> *>();
}

template <typename STATE, typename MOVE>
MOVE MinimaxSolver<STATE, MOVE>::findBestMove(int depth) {
  expandNodeWithDepth(head_node, internal_state, parity, depth);
  if (parity < 0) return minEvaluationNode(head_node)->move_taken_here;
  if (parity > 0) return maxEvaluationNode(head_node)->move_taken_here;

}

#include "minimax_algorithm.h"
#include <cmath>
#include <iostream>
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
void populateChildren(
    MinimaxGraphNode<STATE, MOVE> *node, STATE state,
    std::map<STATE, MinimaxGraphNode<STATE, MOVE> *> &node_cache) {
  std::vector<MOVE> possible_moves{};
  int parity = -1 * node->move_taken_here.player;

  if (parity < 0) {
    possible_moves = generateNegativeMoves(state);
  }

  if (parity > 0) {
    possible_moves = generatePositiveMoves(state);
  }

  for (MOVE move : possible_moves) {
    playMove(state, move);
    /*if (node_cache.find(state) != node_cache.end()) {*/
    /*  node->children.push_back(node_cache[state]);*/
    /*}*/
    /*else {*/
      MinimaxGraphNode<STATE, MOVE> *new_node =
          new MinimaxGraphNode<STATE, MOVE>();
      new_node->parent = node;
      new_node->move_taken_here = move;
      new_node->children = std::vector<MinimaxGraphNode<STATE, MOVE> *>();

      new_node->evaluation = evalState(state);
      // TEST::
      if (isnan(new_node->evaluation)) {
        std::cout << new_node->evaluation;
      }

      node->children.push_back(new_node);
    /*  node_cache[state] = new_node;*/
    /*}*/
    undoMove(state, move);
  }

  // WARNING: This should only occur in the case of a draw, but evaluation func
  // alr returns 0. For chess engine this will be an issue
  /*if (possible_moves.size() == 0) {*/
  /*  node->evaluation = 0;*/
  /*}*/
}

// precondition: the node_list MUST NOT BE empty
template <typename STATE, typename MOVE>
MinimaxGraphNode<STATE, MOVE> *
minEvaluationNode(std::vector<MinimaxGraphNode<STATE, MOVE> *> node_list) {
  float min = INFINITY;
  MinimaxGraphNode<STATE, MOVE> *out = node_list.back();
  for (auto *node : node_list) {
    if (node->evaluation < min) {
      min = node->evaluation;
      out = node;
    }
  }
  return out;
}

// precondition: the node_list MUST NOT BE empty
template <typename STATE, typename MOVE>
MinimaxGraphNode<STATE, MOVE> *
maxEvaluationNode(std::vector<MinimaxGraphNode<STATE, MOVE> *> node_list) {
  float max = -INFINITY;
  MinimaxGraphNode<STATE, MOVE> *out = node_list.back();
  for (auto *node : node_list) {
    if (node->evaluation > max) {
      max = node->evaluation;
      out = node;
    }
  }
  return out;
}

// this goes through and updates the evaluation of a node recursively, based on
// its children nodes this should be called on the parent of newly created nodes
// parity is the person who has yet to move, so for negative parity the correct
// behavior would be to select the minimum and vice versa
template <typename STATE, typename MOVE>
void updateEvaluation(MinimaxGraphNode<STATE, MOVE> *node) {
  int parity = -1 * node->move_taken_here.player;
  float original_evaluation = node->evaluation;
  if (parity < 0 && node->children.size() != 0)
    node->evaluation = minEvaluationNode(node->children)->evaluation;
  if (parity > 0 && node->children.size() != 0)
    node->evaluation = maxEvaluationNode(node->children)->evaluation;

  if (original_evaluation != node->evaluation && node->parent != nullptr)
    updateEvaluation<STATE, MOVE>(node->parent);
}

// this magical function is going to do 3 things at once create new children
// nodes from this current node compute their evaluations update all the
// evaluations of this node, and of the parent nodes recursively

template <typename STATE, typename MOVE>
void expandNode(MinimaxGraphNode<STATE, MOVE> *node, STATE state,
                std::map<STATE, MinimaxGraphNode<STATE, MOVE> *> &node_cache) {
  populateChildren<STATE, MOVE>(node, state, node_cache);
  updateEvaluation<STATE, MOVE>(node);
}

template <typename STATE, typename MOVE>
void expandNodeRecursively(
    MinimaxGraphNode<STATE, MOVE> *node, STATE state,int max_depth,
    std::map<STATE, MinimaxGraphNode<STATE, MOVE> *> &node_cache) {
  if (node->evaluation == INFINITY || node->evaluation == -INFINITY) {
    return;
  }

  if (max_depth == 0){
    return;
  }

  if (node->children.size() == 0) {
    expandNode(node, state, node_cache);
    return;
  }

  for (auto *node : node->children) {
    playMove(state, node->move_taken_here);
    expandNodeRecursively<STATE, MOVE>(node, state, max_depth-1,node_cache);
    undoMove(state, node->move_taken_here);
  }
}

template <typename STATE, typename MOVE>
MinimaxSolver<STATE, MOVE>::MinimaxSolver(STATE current_state, int8_t parity) {
  this->internal_state = current_state;
  this->parity = parity;
  this->node_cache = std::map<STATE, MinimaxGraphNode<STATE, MOVE> *>();

  this->head_node = new MinimaxGraphNode<STATE, MOVE>();
  this->head_node->move_taken_here.player = -1 * parity;

  head_node->evaluation = evalState(current_state);
  head_node->parent = nullptr;
  head_node->children = std::vector<MinimaxGraphNode<STATE, MOVE> *>();
}

template <typename STATE, typename MOVE>
MOVE MinimaxSolver<STATE, MOVE>::findBestMove(int depth) {
  for (int i = 0; i < depth; i++) {
    expandNodeRecursively(this->head_node, this->internal_state,depth,this->node_cache);
  }
  if (parity < 0)
    minEvaluationNode(head_node->children)->move_taken_here;
  if (parity > 0)
    return maxEvaluationNode(head_node->children)->move_taken_here;
}

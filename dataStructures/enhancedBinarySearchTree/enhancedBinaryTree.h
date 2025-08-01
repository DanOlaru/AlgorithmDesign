#pragma once
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

struct EnhancedBinaryTree {
  int key;
  EnhancedBinaryTree *left, *right, *successor, *predecessor;
};

vector<int> readFromFile();
vector<int> readFromFile(string fileName);

vector<vector<int>> readMultipleFromFile(string fileName);

EnhancedBinaryTree* createBinaryTreeFromVector(vector<int> inputArray);

void insertValueIntoTree(EnhancedBinaryTree *root, int elementToInsert);
EnhancedBinaryTree* insertValueIntoTreeSimplified(EnhancedBinaryTree *root, int valueToInsert);

EnhancedBinaryTree* insertNodeIntoTreeAndReturnImmediateParent(EnhancedBinaryTree *root, EnhancedBinaryTree *newElement);

EnhancedBinaryTree* insertNodeIntoTreeWithPredecessorAndSuccessor(EnhancedBinaryTree *root, EnhancedBinaryTree *newElement);

void printTreeDepthFirst(EnhancedBinaryTree *root);

void destructTree(EnhancedBinaryTree *root);

void mergeTrees(EnhancedBinaryTree *rootA, EnhancedBinaryTree *rootB);

bool treesAreEqual(EnhancedBinaryTree *rootA, EnhancedBinaryTree *rootB);

bool treesAreEqualNonRecursive(EnhancedBinaryTree *rootA, EnhancedBinaryTree *rootB);



template <typename Func>
EnhancedBinaryTree *createBinaryTreeFromVectorGeneric(vector<int> inputArray, Func insertOp) {
  EnhancedBinaryTree *rootNode = new EnhancedBinaryTree();
  rootNode->key = inputArray.at(0);

  for (int i = 1; i < inputArray.size(); i++) {
    insertOp(rootNode, inputArray.at(i));
  }

  return rootNode;
}
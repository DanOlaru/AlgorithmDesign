#include "enhancedBinaryTree.h"

int main(int argc, char const *argv[]) {
  // #1
  // vector<int> inputArray = readFromFile();

  // EnhancedBinaryTree *rootOfTree = createBinaryTreeFromVector(inputArray);

  // printTreeDepthFirst(rootOfTree);
  // destructTree(rootOfTree);

  //#2
  vector<vector<int>> inputArrays = readMultipleFromFile("./dataInputs/treesToMerge.txt");

  EnhancedBinaryTree *treeA = createBinaryTreeFromVectorGeneric(inputArrays.at(0), insertValueIntoTreeSimplified);
  EnhancedBinaryTree *treeB = createBinaryTreeFromVectorGeneric(inputArrays.at(1), insertValueIntoTreeSimplified);

  printTreeDepthFirst(treeA);
  cout << "separation between trees" << endl;
  printTreeDepthFirst(treeB);

  mergeTrees(treeA, treeB);
  printTreeDepthFirst(treeA);

  destructTree(treeA);
  destructTree(treeB);


  // #3 read from same file on separate lines
  // vector<vector<int>> inputArrays = readMultipleFromFile("./dataInputs/myArrays.txt");

  // EnhancedBinaryTree *treeA = createBinaryTreeFromVector(inputArrays.at(0));
  // EnhancedBinaryTree *treeB = createBinaryTreeFromVector(inputArrays.at(1));

  // cout << "Resulting trees are identick ? " << treesAreEqual(treeA, treeB) << endl;

  // destructTree(treeA);
  // destructTree(treeB);


  // #4 check if trees constructed with the two different construction methods are identical
  // vector<vector<int>> inputArrays = readMultipleFromFile("./dataInputs/myArrays.txt");

  // EnhancedBinaryTree *treeA = createBinaryTreeFromVectorGeneric(inputArrays.at(0), insertValueIntoTree);
  // EnhancedBinaryTree *treeB = createBinaryTreeFromVectorGeneric(inputArrays.at(0), insertValueIntoTreeSimplified);

  // cout << "Resulting trees are identick ? " << treesAreEqual(treeA, treeB) << endl;

  // destructTree(treeA);
  // destructTree(treeB);

  return 0;
}

#include "enhancedBinaryTree.h"

int main(int argc, char const *argv[]) {
  // #1
  // vector<int> inputArray = readFromFile();

  // EnhancedBinaryTree *rootOfTree = createBinaryTreeFromVector(inputArray);

  // printTreeDepthFirst(rootOfTree);
  // destructTree(rootOfTree);

  //#2
  // vector<int> inputArrayA = readFromFile("inputArray.txt");
  // vector<int> inputArrayB = readFromFile("inputArray_new.txt");

  // EnhancedBinaryTree *treeA = createBinaryTreeFromVector(inputArrayA);
  // EnhancedBinaryTree *treeB = createBinaryTreeFromVector(inputArrayB);

  // printTreeDepthFirst(treeA);
  // cout << "separation between trees" << endl;
  // printTreeDepthFirst(treeB);

  // EnhancedBinaryTree *mergedTree = mergeTrees(treeA, treeB);
  // printTreeDepthFirst(mergedTree);

  // destructTree(treeA);
  // destructTree(treeB);
  // destructTree(mergedTree);


  // #3
  // TODO: read from same file on separate lines
  vector<vector<int>> inputArrays = readMultipleFromFile("./dataInputs/myArrays.txt");

  EnhancedBinaryTree *treeA = createBinaryTreeFromVector(inputArrays.at(0));
  EnhancedBinaryTree *treeB = createBinaryTreeFromVector(inputArrays.at(1));

  cout << "Resulting trees are identick ? " << treesAreEqual(treeA, treeB) << endl;

  destructTree(treeA);
  destructTree(treeB);

  return 0;
}

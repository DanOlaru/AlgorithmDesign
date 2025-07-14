#include "enhancedBinaryTree.h"

int main(int argc, char const *argv[]) {
  // vector<int> inputArray = readFromFile();

  // EnhancedBinaryTree *rootOfTree = createBinaryTreeFromVector(inputArray);

  // printTreeDepthFirst(rootOfTree);
  // destructTree(rootOfTree);

  vector<int> inputArrayA = readFromFile("inputArray.txt");
  vector<int> inputArrayB = readFromFile("inputArray_new.txt");

  EnhancedBinaryTree *treeA = createBinaryTreeFromVector(inputArrayA);
  EnhancedBinaryTree *treeB = createBinaryTreeFromVector(inputArrayB);

  printTreeDepthFirst(treeA);
  cout << "separation between trees" << endl;
  printTreeDepthFirst(treeB);

  EnhancedBinaryTree *mergedTree = mergeTrees(treeA, treeB);
  printTreeDepthFirst(mergedTree);

  destructTree(treeA);
  destructTree(treeB);
  destructTree(mergedTree);
  return 0;
}

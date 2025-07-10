#include "enhancedBinaryTree.h"

int main(int argc, char const *argv[]) {
  // vector<int> inputArray = readFromFile();

  EnhancedBinaryTree *rootOfTree = createBinaryTreeFromVector(inputArray);

  printTreeDepthFirst(rootOfTree);

  destructTree(rootOfTree);

  return 0;
}

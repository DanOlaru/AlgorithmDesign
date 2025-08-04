#include <string.h>
#include "enhancedBinaryTree.h"

vector<int> readFromFile(string fileName) {
  FILE *inputFile;
  inputFile = fopen(fileName.c_str(), "r");
  char line[256];
  vector<int> inputArray;

  if (inputFile != NULL) {
    while (fgets(line, sizeof(line), inputFile)) {
      char *token = strtok(line, " ");
      while (token != NULL) {
        inputArray.push_back(stoi(token));
        token = strtok(NULL, " ");
      }
    }

    fclose(inputFile);
  }

  return inputArray;
}

vector<int> readFromFile() {
  return readFromFile("inputArray.txt");
}

vector<vector<int>> readMultipleFromFile(string fileName) {
  FILE *inputFile;
  inputFile = fopen(fileName.c_str(), "r");
  char line[256];

  vector<vector<int>> output;
  vector<int> inputArray;

  if (inputFile != NULL) {
    while (fgets(line, sizeof(line), inputFile)) {
      char *token = strtok(line, " ");
      while (token != NULL) {
        inputArray.push_back(stoi(token));
        token = strtok(NULL, " ");
      }

      output.push_back(inputArray);
      inputArray.clear();
    }

    fclose(inputFile);
  }

  return output;
}

EnhancedBinaryTree *createBinaryTreeFromVector(vector<int> inputArray) {
  EnhancedBinaryTree *rootNode = new EnhancedBinaryTree();
  rootNode->key = inputArray.at(0);

  for (int i = 1; i < inputArray.size(); i++) {
    insertValueIntoTree(rootNode, inputArray.at(i));
  }

  return rootNode;
}

void insertValueIntoTree(EnhancedBinaryTree *root, int valueToInsert) {
  EnhancedBinaryTree *nodeToInsert;
  nodeToInsert = new EnhancedBinaryTree();
  nodeToInsert->key = valueToInsert;

  insertNodeIntoTreeAndReturnImmediateParent(root, nodeToInsert);
}

EnhancedBinaryTree* insertValueIntoTreeSimplified(EnhancedBinaryTree *root, int valueToInsert) {
  EnhancedBinaryTree *nodeToInsert;
  nodeToInsert = new EnhancedBinaryTree();
  nodeToInsert->key = valueToInsert;

  return insertNodeIntoTreeWithPredecessorAndSuccessor(root, nodeToInsert);
}

EnhancedBinaryTree* insertNodeIntoTreeAndReturnImmediateParent(EnhancedBinaryTree *root, EnhancedBinaryTree *newElement) {
  EnhancedBinaryTree *nodeToInsert, *currentNode;
  currentNode = root;

  bool goingLeft, inserted = false;

  nodeToInsert = new EnhancedBinaryTree();
  nodeToInsert->key = newElement->key;

  do {
    goingLeft = currentNode->key >= nodeToInsert->key;

    if (goingLeft) {
      if (!currentNode->predecessor || (currentNode->predecessor->key < nodeToInsert->key)) {
        currentNode->predecessor = nodeToInsert;
      }

      if (!(nodeToInsert->successor) || (currentNode->key < nodeToInsert->successor->key)) {
        nodeToInsert->successor = currentNode;
      }

      if (currentNode->left != NULL) {
        currentNode = currentNode->left;
      }
      else {
        currentNode->left = nodeToInsert;
        inserted = true;
      }
    } else {
      nodeToInsert->predecessor = currentNode;

      if (!(currentNode->successor) || currentNode->successor->key > nodeToInsert->key) {
        currentNode->successor = nodeToInsert;
      }

      if (currentNode->right != NULL) {
        currentNode = currentNode->right;
      }
      else {
        currentNode->right = nodeToInsert;
        inserted = true;
      }
    }
  } while (!inserted);

  return currentNode;
}

template <typename Func>
void travelTreeAndRunOp(EnhancedBinaryTree *root, Func op)
{
  if (root->left != NULL) {
    travelTreeAndRunOp(root->left, op);
  }
  if (root->right != NULL) {
    travelTreeAndRunOp(root->right, op);
  }

  op(root);
}

void destructTree(EnhancedBinaryTree *root) {
  travelTreeAndRunOp(root, [](EnhancedBinaryTree *root) {
    delete root;
    root = nullptr; });
}

void printTreeDepthFirst(EnhancedBinaryTree *root) {
  travelTreeAndRunOp(root, [] (EnhancedBinaryTree *root) {
    cout << "Node " << root->key << endl;
  } );
}

EnhancedBinaryTree* followRightSubtreeToLastLowerThanSuccAndDetachFromTree(EnhancedBinaryTree* root) {
  if (root->successor == NULL) {
    return NULL;
  }

  EnhancedBinaryTree* cursor = root, *lastParent;;

  // TODO : what if equal case?
  while (cursor != NULL && cursor->key < root->successor->key) {
    lastParent = cursor;
    cursor = cursor->right;
  }

  //Detach child from last parent
  lastParent->right = NULL;

  return cursor;
}

EnhancedBinaryTree* followLeftSubtreeToLastHigherThanPredAndDetachFromTree(EnhancedBinaryTree* root) {
  if (root->predecessor == NULL) {
    return NULL;
  }

  EnhancedBinaryTree* cursor = root, *lastParent;

  while (cursor != NULL && cursor->key > root->predecessor->key) {
    lastParent = cursor;
    cursor = cursor->left;
  };

  //Detach child from last parent
  lastParent->left = NULL;

  return cursor;
}


EnhancedBinaryTree* slideDownOppositeSubTreeAndDetachFromTree(EnhancedBinaryTree* parent, EnhancedBinaryTree* firstChild) {
  EnhancedBinaryTree* cursor = firstChild, *lastParent;
  bool goRight = false;

  if (parent->key > firstChild->key) {
    goRight = true;
    // cursor inserted to the left of parent -> slide down its right subtree
    while (cursor != NULL && parent->key > cursor->key) {
      lastParent = cursor;
      cursor = cursor->right;
    };
  } else {
    // cursor inserted to the right of parent -> slide down its left subtree
    while (cursor != NULL && parent->key <= cursor->key) {
      lastParent = cursor;
      cursor = cursor->left;
    };
  }

  // TODO: disambiguate NULL cases and same as firstChild
  if (cursor != NULL) {
    if (goRight) {
      lastParent->right = NULL;
    } else {
      lastParent->left = NULL;
    }
  }
  return cursor;
}

// merge while preserving pred/succ relationships
void mergeTrees(EnhancedBinaryTree *rootToInsert, EnhancedBinaryTree *hostTreeRoot) {
  EnhancedBinaryTree *cursor, *spliceRoot, *nodeToDetach, *formerPred; // TODO: presumably former succ also

  vector<EnhancedBinaryTree*> toMergeStack;
  toMergeStack.push_back(rootToInsert);

  do {
    cursor = toMergeStack.back();
    toMergeStack.pop_back();

    spliceRoot = insertNodeIntoTreeWithPredecessorAndSuccessor(hostTreeRoot, cursor);
    bool insertedLeft = spliceRoot->key > cursor->key;

    if (insertedLeft) {
      // if parent has pred (somewhere to the left), leftmost subtree must not go lower than it
      // travel as far down as the pred, and save anything below to stack, save + break connection with child
      // reverse logic for right insertion

      EnhancedBinaryTree* largestLeftmostChildSmallerThanPred = followLeftSubtreeToLastHigherThanPredAndDetachFromTree(cursor);
      if (largestLeftmostChildSmallerThanPred) {
        toMergeStack.push_back(largestLeftmostChildSmallerThanPred);
      }
    } else {
      EnhancedBinaryTree* smallestRightmostChildSmallerThanSucc = followRightSubtreeToLastLowerThanSuccAndDetachFromTree(cursor);
      if (smallestRightmostChildSmallerThanSucc) {
        toMergeStack.push_back(smallestRightmostChildSmallerThanSucc);
      }
    }

    EnhancedBinaryTree* firstIncompatibleChildFromOppositeSubtree = slideDownOppositeSubTreeAndDetachFromTree(spliceRoot, cursor);
    if (firstIncompatibleChildFromOppositeSubtree) {
      toMergeStack.push_back(firstIncompatibleChildFromOppositeSubtree);
    }
  } while (toMergeStack.size() > 0);
}

string displayInfoOnNode(EnhancedBinaryTree *node) {
  string result;
  if (node) {
    if (node->key) { result += " key " + std::to_string(node->key) + " | "; };
    if (node->predecessor && node->predecessor->key) { result += " pred " + std::to_string(node->predecessor->key) + " | "; }
    if (node->successor && node->successor && node->successor->key) {result += " succ " + std::to_string(node->successor->key) + " | ";}
  }

  return result;
}

bool predAndSuccAreEqual(EnhancedBinaryTree *nodeA, EnhancedBinaryTree *nodeB) {
  bool equal = true;
  if (nodeA->predecessor == NULL) {
    equal = equal && nodeB->predecessor == NULL;
  } else {
    equal = equal && nodeA->predecessor->key == nodeB->predecessor->key;
  }

  if (nodeA->successor == NULL) {
    equal = equal && nodeB->successor == NULL;
  } else {
    equal = equal && nodeA->successor->key == nodeB->successor->key;
  }

  return equal;
}

bool treesAreEqual(EnhancedBinaryTree *rootA, EnhancedBinaryTree *rootB) {
  if (rootA == NULL) {
    return rootB == NULL;
  }

  if (rootA->key != rootB->key || !predAndSuccAreEqual(rootA, rootB) ) {
    cout << "difference found A: " << displayInfoOnNode(rootA) << " | B: " << displayInfoOnNode(rootB) << endl;
    return false;
  }

  return treesAreEqual(rootA->left, rootB->left) && treesAreEqual(rootA->right, rootB->right);
}

// TODO: implement non-recursive variant
bool treesAreEqualNonRecursive(EnhancedBinaryTree *rootA, EnhancedBinaryTree *rootB) {
  return false;
}

EnhancedBinaryTree* insertNodeIntoTreeWithPredecessorAndSuccessor(EnhancedBinaryTree *root, EnhancedBinaryTree *nodeToInsert) {

  EnhancedBinaryTree *cursor;
  cursor = root;

  bool goingLeft;

  do {
    goingLeft = cursor->key >= nodeToInsert->key;

    if (goingLeft) {
      nodeToInsert->successor = cursor;
      if (cursor->left != NULL) {
        cursor = cursor->left;
      } else {
        cursor->left = nodeToInsert;

        // set predecessor's successor and adjust former predecessor
        if (cursor->predecessor) {
          cursor->predecessor->successor = nodeToInsert;
          nodeToInsert->predecessor = cursor->predecessor;
        }
        cursor->predecessor = nodeToInsert;
      }
    } else {
      nodeToInsert->predecessor = cursor;
      if (cursor->right != NULL) {
        cursor = cursor->right;
      } else {
        cursor->right = nodeToInsert;

        //set successor's predecessor and adjust former successor
        if (cursor->successor) {
          cursor->successor->predecessor = nodeToInsert;
          nodeToInsert->successor = cursor->successor;
        }
        cursor->successor = nodeToInsert;
      }
    }
  } while (cursor->left != nodeToInsert && cursor->right != nodeToInsert);

  return cursor;
}
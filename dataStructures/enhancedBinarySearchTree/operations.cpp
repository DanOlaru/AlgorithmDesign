
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

// merge while preserving pred/succ relationships
void mergeTrees(EnhancedBinaryTree *rootToInsert, EnhancedBinaryTree *hostTreeRoot) {
  EnhancedBinaryTree *cursor, *spliceRoot, *nodeToDetach;

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

      EnhancedBinaryTree* smallestLeftmostChildBiggerThanPred = followLeftSubtreeToLastHigherThanPred(spliceRoot);
      if (smallestLeftmostChildBiggerThanPred) {
        nodeToDetach = smallestLeftmostChildBiggerThanPred->left;
        smallestLeftmostChildBiggerThanPred->left = NULL;
        toMergeStack.push_back(nodeToDetach);
      }
    } else {
      EnhancedBinaryTree* largestRightmostChildSmallerThanSucc = followRightSubtreeToLastLowerThanSucc(spliceRoot);
      if (largestRightmostChildSmallerThanSucc) {
        nodeToDetach = largestRightmostChildSmallerThanSucc->right;
        largestRightmostChildSmallerThanSucc->right = NULL;
        toMergeStack.push_back(nodeToDetach);
      }
    }

    EnhancedBinaryTree* lastCompatibleChildFromOppositeSubtree = slideDownOppositeSubTree(spliceRoot, cursor);
    if (lastCompatibleChildFromOppositeSubtree) {
      if (insertedLeft) {
        nodeToDetach = lastCompatibleChildFromOppositeSubtree->right;
        lastCompatibleChildFromOppositeSubtree->right = NULL;
      } else {
        nodeToDetach = lastCompatibleChildFromOppositeSubtree->left;
        lastCompatibleChildFromOppositeSubtree->left = NULL;
      }

      toMergeStack.push_back(nodeToDetach);
    }
  } while (toMergeStack.size() > 0);
}

EnhancedBinaryTree* followRightSubtreeToLastLowerThanSucc(EnhancedBinaryTree* root) {
  if (root->successor == NULL) {
    return NULL;
  }

  EnhancedBinaryTree* cursor = root;

  while (cursor != NULL && cursor->right && cursor->right->key <= root->successor->key) {
    cursor = cursor->right;
  }

  return cursor;
}

EnhancedBinaryTree* followLeftSubtreeToLastHigherThanPred(EnhancedBinaryTree* root) {
  if (root->predecessor == NULL) {
    return NULL;
  }

  EnhancedBinaryTree* cursor = root;

  while (cursor != NULL && cursor->left != NULL && cursor->left->key >= root->predecessor->key) {
    cursor = cursor->left;
  };

  return cursor;
}

EnhancedBinaryTree* slideDownOppositeSubTree(EnhancedBinaryTree* parent, EnhancedBinaryTree* firstChild) {
  EnhancedBinaryTree* cursor;

  if (parent->key > firstChild->key) {
    // cursor inserted to the left of parent -> slide down its right subtree
    cursor = firstChild->right;
    while (cursor != NULL && parent->key > cursor->key) {
      cursor = cursor->right;
    };
  } else {
    // cursor inserted to the right of parent -> slide down its left subtree
    cursor = firstChild->left;
    while (cursor != NULL && parent->key <= cursor->key) {
      cursor = cursor->left;
    };
  }

  return cursor;
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

EnhancedBinaryTree* insertNodeIntoTreeWithPredecessorAndSuccessor(EnhancedBinaryTree *root, EnhancedBinaryTree *newElement) {

  EnhancedBinaryTree *nodeToInsert, *cursor;
  cursor = root;

  bool goingLeft;

  nodeToInsert = new EnhancedBinaryTree();
  nodeToInsert->key = newElement->key;

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
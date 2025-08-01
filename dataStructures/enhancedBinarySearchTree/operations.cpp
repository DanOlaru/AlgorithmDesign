
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

void insertValueIntoTreeSimplified(EnhancedBinaryTree *root, int valueToInsert) {
  EnhancedBinaryTree *nodeToInsert;
  nodeToInsert = new EnhancedBinaryTree();
  nodeToInsert->key = valueToInsert;

  insertNodeIntoTreeWithPredecessorAndSuccessor(root, nodeToInsert);
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

EnhancedBinaryTree* slideDownSubTree(EnhancedBinaryTree* parent, EnhancedBinaryTree* first) {
  EnhancedBinaryTree* cursor = first;

    if (parent->key > cursor->key) {
      // cursor inserted to the left of parent -> slide down its right subtree
      while (cursor->right != NULL && parent->key > cursor->right->key) {
        cursor = cursor->right;
      };
    } else {
      // cursor inserted to the right of parent -> slide down its left subtree
      while (cursor->left != NULL && parent->key <= cursor->left->key) {
        cursor = cursor->left;
      };
    }

    return cursor;
}

EnhancedBinaryTree* mergeTrees(EnhancedBinaryTree *rootA, EnhancedBinaryTree *rootB) {
  EnhancedBinaryTree *cursor = rootA, *currentRootParent;

  do {
    currentRootParent = insertNodeIntoTreeAndReturnImmediateParent(rootB, cursor);
    bool deleteRight = currentRootParent->key > cursor->key;
    cursor = slideDownSubTree(currentRootParent, cursor);

    EnhancedBinaryTree* saveCursor;
    // break connection with child
    if (deleteRight) {
      saveCursor = cursor->right;
      cursor->right = NULL;
    } else {
      saveCursor = cursor->left;
      cursor->left = NULL;
    }
    cursor = saveCursor;
  } while (cursor != NULL);

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
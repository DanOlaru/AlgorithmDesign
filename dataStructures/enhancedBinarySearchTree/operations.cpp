
#include <string.h>
#include "enhancedBinaryTree.h"

vector<int> readFromFile()
{

  FILE *inputFile;
  inputFile = fopen("inputArray.txt", "r");
  char line[256];
  vector<int> inputArray;

  if (inputFile != NULL)
  {
    while (fgets(line, sizeof(line), inputFile))
    {
      char *token = strtok(line, " ");
      while (token != NULL)
      {
        inputArray.push_back(stoi(token));
        token = strtok(NULL, " ");
      }
    }

    fclose(inputFile);
  }

  return inputArray;
}

EnhancedBinaryTree *createBinaryTreeFromVector(vector<int> inputArray)
{
  cout << "SIZE " << inputArray.size() << endl;

  EnhancedBinaryTree *rootNode = new EnhancedBinaryTree();
  rootNode->key = inputArray.at(0);

  for (int i = 1; i < inputArray.size(); i++)
  {
    insertIntoTree(rootNode, inputArray.at(i));
  }

  return rootNode;
}

void insertIntoTree(EnhancedBinaryTree *root, int elementToInsert)
{
  EnhancedBinaryTree *newNode, *currentNode, *immediatePredecessor;
  currentNode = root;

  bool goingLeft = currentNode->key >= elementToInsert;

  while (goingLeft ? currentNode->left != NULL : currentNode->right != NULL)
  {
    if (currentNode->key >= elementToInsert)
    {
      currentNode = currentNode->left;
    }
    else
    {
      immediatePredecessor = currentNode;
      currentNode = currentNode->right;
    }
    goingLeft = currentNode->key >= elementToInsert;
  }

  newNode = new EnhancedBinaryTree();
  newNode->key = elementToInsert;

  if (currentNode->key >= elementToInsert) {
    currentNode->left = newNode;
  } else {
    currentNode->right = newNode;
  }
  // immediatePredecessor->successor = currentNode;
}

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
  immediatePredecessor = currentNode = root;

  bool goingLeft = currentNode->key >= elementToInsert;

  newNode = new EnhancedBinaryTree();
  newNode->key = elementToInsert;

  while (goingLeft ? currentNode->left != NULL : currentNode->right != NULL)
  {
    if (goingLeft &&
        ((!currentNode->predecessor) ||
         (currentNode->predecessor && (currentNode->predecessor->key < elementToInsert))))
    {
      currentNode->predecessor = newNode;
    }

    if (goingLeft)
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

  if (goingLeft)
  {
    // TODO: duplicate code, improve solution
    if ((!currentNode->predecessor) ||
        (currentNode->predecessor && (currentNode->predecessor->key < elementToInsert)))
    {
      currentNode->predecessor = newNode;
    }
    currentNode->left = newNode;
    newNode->successor = currentNode;
  }
  else
  {
    immediatePredecessor = currentNode;
    currentNode->right = newNode;
  }

  if (immediatePredecessor->key < elementToInsert)
  {
    immediatePredecessor->successor = newNode;
    // newNode->predecessor = immediatePredecessor;
  }
}

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

void insertIntoTree(EnhancedBinaryTree *root, int valueToInsert)
{
  EnhancedBinaryTree *nodeToInsert, *currentNode;
  currentNode = root;

  bool goingLeft, inserted = false;

  nodeToInsert = new EnhancedBinaryTree();
  nodeToInsert->key = valueToInsert;

  do
  {
    goingLeft = currentNode->key >= valueToInsert;

    if (goingLeft)
    {
      if (!currentNode->predecessor || (currentNode->predecessor->key < valueToInsert))
      {
        currentNode->predecessor = nodeToInsert;
      }

      if (!(nodeToInsert->successor) || (currentNode->key < nodeToInsert->successor->key))
      {
        nodeToInsert->successor = currentNode;
      }

      if (currentNode->left != NULL)
      {
        currentNode = currentNode->left;
      }
      else
      {
        currentNode->left = nodeToInsert;
        inserted = true;
      }
    }
    else
    {
      nodeToInsert->predecessor = currentNode;

      if (!(currentNode->successor) || currentNode->successor->key > nodeToInsert->key)
      {
        currentNode->successor = nodeToInsert;
      }

      if (currentNode->right != NULL)
      {
        currentNode = currentNode->right;
      }
      else
      {
        currentNode->right = nodeToInsert;
        inserted = true;
      }
    }

  } while (!inserted);
}
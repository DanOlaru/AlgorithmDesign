#pragma once
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

struct EnhancedBinaryTree {
  int key;
  EnhancedBinaryTree *left, *right, *successor, *predecessor;
};

vector<int> readFromFile();
EnhancedBinaryTree* createBinaryTreeFromVector(vector<int> inputArray);
void insertIntoTree(EnhancedBinaryTree *root, int elementToInsert);
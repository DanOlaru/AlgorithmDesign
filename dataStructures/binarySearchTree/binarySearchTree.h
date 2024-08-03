#include <stdio.h>
#include <stdlib.h>

typedef int item_type;

typedef struct BinarySearchTree
{
  item_type item;
  struct BinarySearchTree *left, *right, *parent;
} BinarySearchTree;

void process_node(BinarySearchTree *tree)
{
  printf("node-> %d \n", tree->item);
}

BinarySearchTree *search_tree(BinarySearchTree *tree, item_type quarry)
{
  if ((tree->item == quarry) || (tree == NULL))
  {
    return tree;
  }
  else if (tree->item < quarry)
  {
    return search_tree(tree->right, quarry);
  }
  else
  {
    return search_tree(tree->left, quarry);
  }
}

BinarySearchTree *find_minimum(BinarySearchTree *tree)
{
  BinarySearchTree *cursor;
  cursor = tree;

  while (cursor->left != NULL)
  {
    cursor = cursor->left;
  }
  return cursor;
}

BinarySearchTree *find_maximum(BinarySearchTree *tree)
{
  BinarySearchTree *cursor;
  cursor = tree;

  while (cursor->right != NULL)
  {
    cursor = cursor->right;
  }
  return cursor;
}

void traverse_tree(BinarySearchTree *tree)
{
  if (tree != NULL)
  {
    traverse_tree(tree->left);
    process_node(tree);
    traverse_tree(tree->right);
  }
}

void insert_into_tree(BinarySearchTree **tree, item_type element, BinarySearchTree *parent)
{
  if (*tree == NULL)
  {
    BinarySearchTree *new_element;

    new_element = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));
    new_element->item = element;
    new_element->left = new_element->right = NULL;
    new_element->parent = parent;

    *tree = new_element;
    return;
  }

  if ((*tree)->item > element)
  {
    insert_into_tree(&((*tree)->left), element, *tree);
  }
  else
  {
    insert_into_tree(&((*tree)->right), element, *tree);
  }
}

void delete_from_tree(BinarySearchTree **tree, item_type element)
{
  if ((*tree)->item == element)
  {
    // Delete this
    BinarySearchTree *current_node;
    current_node = *tree;

    if ((*tree)->left == NULL && (*tree)->right == NULL)
    {
      // end node
      *tree = NULL; // update up the parent record
    }
    else if ((*tree)->left == NULL && (*tree)->right != NULL)
    {
      // single-child node — RIGHT
      *tree = (*tree)->right; // update up the parent record
    }
    else if ((*tree)->left != NULL && (*tree)->right == NULL)
    {
      // single-child node — LEFT
      *tree = (*tree)->left; // update up the parent record
    }
    else
    {
      // two children — obtain minimum larger than and replace
      BinarySearchTree *next_minimum = find_minimum((*tree)->right);

      // remove minimum from position where found
      if (next_minimum->right != NULL)
      {
        (next_minimum->right)->parent = next_minimum->parent;
        (next_minimum->parent)->left = next_minimum->right;
      }
      else
      {
        (next_minimum->parent)->left = NULL;
      }

      next_minimum->parent = current_node->parent;
      next_minimum->left = current_node->left;
      next_minimum->right = current_node->right;
      current_node->parent->right = next_minimum;

      *tree = next_minimum; // update the parent record
    }

    free(current_node);
    return;
  }

  if ((*tree)->item > element)
  {
    delete_from_tree(&((*tree)->left), element);
  }
  else
  {
    delete_from_tree(&((*tree)->right), element);
  }
}
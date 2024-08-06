#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

BinarySearchTree **get_parent_branch_pointer(BinarySearchTree *node)
{
  if ((node->parent)->item > node->item)
  {
    return &((node->parent)->left);
  }
  else
  {
    return &((node->parent)->right);
  }
}

bool is_binary_tree(BinarySearchTree *tree)
{
  if (tree == NULL)
    return true;

  bool greater_than_left = true;
  if (tree->left != NULL)
  {
    greater_than_left = tree->item > (tree->left)->item;
  }

  bool less_than_right = true;
  if (tree->right != NULL)
  {
    less_than_right = tree->item < (tree->right)->item;
  }

  return greater_than_left && less_than_right && is_binary_tree(tree->left) && is_binary_tree(tree->right);
}

void delete_from_tree(BinarySearchTree **tree, item_type element)
{
  // Delete this
  BinarySearchTree *current_node;
  current_node = search_tree(*tree, element);

  if (current_node != NULL)
  {
    BinarySearchTree **current_node_parent_branch = get_parent_branch_pointer(current_node);
    if (current_node->left == NULL && current_node->right == NULL)
    // if (current_node->left == current_node->right == NULL)
    {
      // update the parent record
      *current_node_parent_branch = NULL;
    }
    else if (current_node->left == NULL && current_node->right != NULL)
    {
      // single-child node — RIGHT
      *current_node_parent_branch = current_node->right;
      (current_node->right)->parent = current_node->parent;
    }
    else if (current_node->left != NULL && current_node->right == NULL)
    {
      // single-child node — LEFT
      *current_node_parent_branch = current_node->left;
      (current_node->left)->parent = current_node->parent;
    }
    else
    {
      // two children — obtain minimum larger than and replace
      BinarySearchTree *next_minimum = find_minimum((current_node)->right);

      // uncouple minimum out from position where found
      if (next_minimum->left == NULL && next_minimum->right == NULL)
      {

        BinarySearchTree **next_minimum_parent_branch = get_parent_branch_pointer(next_minimum);
        *next_minimum_parent_branch = NULL;
      }
      else
      {
        // minimum has right subtree
        (next_minimum->parent)->left = next_minimum->right;
        (next_minimum->right)->parent = next_minimum->parent;
      }

      // substitute minimum for current node
      *current_node_parent_branch = next_minimum;
      next_minimum->parent = current_node->parent;
      next_minimum->left = current_node->left;

      if (current_node->left)
      {
        (current_node->left)->parent = next_minimum;
      }

      next_minimum->right = current_node->right;
      if (current_node->right)
      {
        (current_node->right)->parent = next_minimum; //???
      }
    }

    free(current_node);
  }
}
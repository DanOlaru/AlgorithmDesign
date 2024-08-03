#include "binarySearchTree.h"

int main(int argc, char const *argv[])
{
  int num;
  FILE *file;
  file = fopen("input.txt", "r");
  char line[256];

  BinarySearchTree *tree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));
  tree->item = 0;

  if (file != NULL)
  {
    while (fgets(line, sizeof(line), file))
    {
      int converted = atoi(line);
      insert_into_tree(&tree, converted, NULL);
    }
    // traverse_tree(tree);

    BinarySearchTree *found = search_tree(tree, 68);
    // printf("FOUND %d \n", found->item);

    // insert_into_tree(&tree, 70, NULL);

    delete_from_tree(&tree, 68);
    traverse_tree(tree);

    fclose(file);
  }
  else
  {
    fprintf(stderr, "Unable to open file!\n");
  }

  free(tree);
  return 0;
}

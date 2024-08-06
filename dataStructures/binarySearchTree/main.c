#include "binarySearchTree.h"

int main(int argc, char const *argv[])
{
  int num;
  FILE *file;
  file = fopen("input.txt", "r");
  char line[256];

  BinarySearchTree *tree = NULL;

  if (file != NULL)
  {
    while (fgets(line, sizeof(line), file))
    {
      int converted = atoi(line);
      insert_into_tree(&tree, converted, NULL);
    }
    // traverse_tree(tree);

    // // BinarySearchTree *found = search_tree(tree, 68);
    // BinarySearchTree *found = search_tree(tree, 5);
    // printf("FOUND %d \n", found->item);

    printf("IS BINARY %b \n", is_binary_tree(tree));
    // // insert_into_tree(&tree, 70, NULL);


    // // delete_from_tree(&tree, 68);
    // delete_from_tree(&tree, 4);
    delete_from_tree(&tree, 10);
    traverse_tree(tree);
    printf("AFTER DELETE \n");
    printf("IS BINARY %b \n", is_binary_tree(tree));
    // // delete_from_tree(&tree, 99);

    fclose(file);
  }
  else
  {
    fprintf(stderr, "Unable to open file!\n");
  }

  free(tree);
  return 0;
}

#include "dataStructures.h"

int main(int argc, char const *argv[])
{
  int input_array[] = {1, 4, 3, 2, 6, 7};

  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  // LinkedList *list;
  list->item = input_array[0];
  printf("%d ", input_array[0]);

  for (int i = 1; i < 6; i++)
  {
    insert(&list, input_array[i]);
  }

  display_list(&list);
  printf("\n");

  printf("20 exists ?");

  printf("\n");
  if (search(list, 20)) {
    printf("YES");
  } else {
    printf("NO");
  }
  printf("\n");

  LinkedList *pred = find_predecessor(list, 2);
  if (pred != NULL) {
    printf("FOUND %d", pred->item);
  } else {
    printf("NOT FOUND");
  }
  printf("\n");

  delete_element(list, 2);
  display_list(&list);
  printf("\n");

  return 0;
}

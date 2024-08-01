#include <stdio.h>
#include <stdlib.h>

// #define NULL nullptr

typedef int item_type;

typedef struct LinkedList
{
  item_type item;
  struct LinkedList *next;
} list;

LinkedList *search_recursive(LinkedList *list, item_type quarry)
{
  if (list == NULL)
    return NULL;

  if (list->item == quarry)
  {
    return list;
  }
  else
  {
    return search_recursive(list->next, quarry);
  }
}

LinkedList *search(LinkedList *list, item_type quarry)
{
  LinkedList *current = list;

  while ((current->item != quarry) && (current->next != NULL))
  {
    current = current->next;
  }
  if (current->item == quarry)
  {
    return current;
  }

  return NULL;
}

void insert(LinkedList **list, item_type new_element)
{
  LinkedList *new_list_node = (LinkedList *)malloc(sizeof(LinkedList));

  new_list_node->item = new_element;
  new_list_node->next = *list;

  *list = new_list_node;
}

LinkedList *find_predecessor(LinkedList *list, item_type quarry)
{
  LinkedList *current = list;

  while (current->next)
  {
    if ((current->next)->item == quarry)
    {
      return current;
    }
    else
    {
      current = current->next;
    }
  }
}

int delete_element(LinkedList *list, item_type target)
{

  LinkedList *target_elem = search_recursive(list, target);

  LinkedList *predecessor = find_predecessor(list, target);

  if (target_elem != NULL)
  {
    if (predecessor == NULL)
    {
      list = list->next;
    }
    else
    {
      predecessor->next = predecessor->next->next;
    }
    free(target_elem);
    return 1;
  }

  return 0;
}

void display_list(LinkedList **list)
{
  LinkedList *current = *list;


  printf("\n");
  printf("Printing linked list \n");
  printf("\n");
  while (current != NULL)
  {
    printf("%d ", current->item);
    current = current->next;
  }
}
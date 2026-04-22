#include <stdio.h>
#include <math.h>
#include <string.h>
#include "heapsort.h"

element_type work_array[MAX_SIZE];

int main(int argc, char const *argv[])
{
  FILE *fp = fopen("input", "r");
  if (fp == NULL)
  {
    printf("Error opening file\n");
    return 1;
  }

  char line[MAX_SIZE];
  size_t line_index = -1;

  if (fgets(line, sizeof(line), fp))
  {
    char *token = strtok(line, " ");

    while (token != NULL)
    {
      work_array[++line_index] = atoi(token);
      token = strtok(NULL, " ");
    }
  }

  fclose(fp);

  print_array(work_array, line_index + 1);

  heapsort(work_array, line_index + 1);

  printf("After sorting \n");
  print_array(work_array, line_index + 1);
  return 0;
}

int parent(size_t index)
{
  if (index == 0)
  {
    return -1;
  }

  return floor(index / 2);
}

size_t left_child(size_t index)
{
  if (index == 0)
  {
    return 1;
  }
  return index * 2;
}

size_t right_child(size_t index)
{
  return index * 2 + 1;
}

void print_array(element_type array[], size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    printf("%zu ", array[i]);
  }
  printf("\n");
}

void insert(priority_queue *pq, element_type element)
{
  pq->size = (pq->size) + 1;
  pq->queue[pq->size - 1] = element;

  bubble_up(pq, pq->size - 1);
}

void bubble_up(priority_queue *pq, size_t index)
{
  if (parent(index) < 0)
  {
    return;
  }

  if (pq->queue[index] < pq->queue[parent(index)])
  {
    swap(pq, index, parent(index));
    bubble_up(pq, parent(index));
  }
}

void swap(priority_queue *pq, size_t first, size_t second)
{
  element_type temp = pq->queue[first];
  pq->queue[first] = pq->queue[second];
  pq->queue[second] = temp;
}

void make_heap(priority_queue *pq, element_type input[], size_t input_length)
{
  pq->size = 0;

  for (int i = 0; i < input_length; i++)
  {
    insert(pq, input[i]);
  }
}

element_type extract_min(priority_queue *pq)
{
  element_type min = NULL;

  if (pq->size > 0)
  {
    min = pq->queue[0];

    pq->queue[0] = pq->queue[pq->size - 1];
    pq->size = pq->size - 1;

    percolate(pq, 0);
  }

  return min;
}

void heapsort(element_type input_array[], size_t input_length)
{
  priority_queue pq;
  make_heap(&pq, input_array, input_length);

  printf("heaps ");
  print_array(pq.queue, pq.size);

  for (int i = 0; i < input_length; i++)
  {
    input_array[i] = extract_min(&pq);
  }
}

void percolate(priority_queue *pq, size_t index)
{
  int min_index = index;

  if ((left_child(index) <= pq->size) && (pq->queue[left_child(index)] < pq->queue[min_index]))
  {
    min_index = left_child(index);
  }

  if ((right_child(index) <= pq->size) && (pq->queue[right_child(index)] < pq->queue[min_index]))
  {
    min_index = right_child(index);
  }

  if (index != min_index)
  {
    swap(pq, index, min_index);
    percolate(pq, min_index);
  }
}
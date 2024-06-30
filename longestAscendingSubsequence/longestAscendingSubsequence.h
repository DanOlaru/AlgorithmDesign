#define MAXLEN 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int SubsequencesMatrix[2][MAXLEN];
typedef int IntegerSequence[MAXLEN];

typedef struct InputSequence
{
  int sequence[MAXLEN];
  int length;
};

InputSequence read_from_file()
{
  FILE *file = fopen("inputSequence.txt", "r");

  InputSequence data;

  // if (file == NULL)
  // {
  //   perror("Failed to open file");
  //   return;
  // }

  int index = -1;
  char line[256];
  const char delimiter[] = " ";

  while (fgets(line, sizeof(line), file))
  {
    char *token = strtok(line, delimiter);

    while (token != NULL) {
        data.sequence[++index] = atoi(token);
        token = strtok(NULL, delimiter); // Get the next token
    }
  }

  data.length = index;

  fclose(file);

  return data;
}

void print_maximums_matrix(IntegerSequence sequence, SubsequencesMatrix matrix, int len)
{

  for (int i = 0; i < len; i++)
  {
    printf("%d, ", sequence[i]);
  }
  printf("\n");

  for (int i = 0; i < len; i++)
  {
    printf("%d, ", matrix[0][i]);
  }

  printf("\n");

  for (int i = 0; i < len; i++)
  {
    printf("%d, ", matrix[1][i]);
  }
  printf("\n");
}

void determine_max_length_and_display_sequence(IntegerSequence input, SubsequencesMatrix matrix, int len)
{

  int max = 0, maxIndex = 0;
  int resultStack[MAXLEN];

  for (int i = 0; i < len; i++)
  {
    if (matrix[0][i] > matrix[0][maxIndex])
    {
      maxIndex = i;
    }
  }

  printf("Result: \n");
  int cursor = maxIndex;
  int stackTop = -1;
  while (cursor >= 0)
  {
    resultStack[++stackTop] = input[cursor];
    cursor = matrix[1][cursor];
  }

  // read stack
  for (; stackTop > 0;)
  {
    printf("%d, ", resultStack[stackTop--]);
  }

  printf("\n");
}
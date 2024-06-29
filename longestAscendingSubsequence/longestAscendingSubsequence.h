#define MAXLEN 100

#include <stdio.h>

typedef int SubsequencesMatrix[2][MAXLEN];

void printMaximumsMatrix(SubsequencesMatrix matrix, int len)
{

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

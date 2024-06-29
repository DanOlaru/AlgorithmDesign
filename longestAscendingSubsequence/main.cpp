#include "longestAscendingSubsequence.h"

int main(int argc, char const *argv[])
{
  int sequence[MAXLEN] = {2, 4, 3, 5, 1, 7, 6, 9, 8};
  int length = 0;
  SubsequencesMatrix subsequences;

  for (int i = 0; sequence[i] != '\0'; i++)
  {
    length++;
    // printf("element %d = %d \n", i, sequence[i]);

    if (i == 0)
    {
      subsequences[0][i] = 1;  // subsequence max length
      subsequences[1][i] = -1; // subsequence last item index
    }
    else
    {
      int maxIndex = 0, maxLen = 1;

      for (int j = 0; j < i; j++)
      {
        if ((sequence[j] < sequence[i]) && (subsequences[0][j] >= maxLen))
        {
          maxLen = subsequences[0][j] + 1;
          maxIndex = j;
        }
      }

      subsequences[0][i] = maxLen;
      subsequences[1][i] = maxIndex;
    }
  }

  printMaximumsMatrix(subsequences, length);

  return 0;
}

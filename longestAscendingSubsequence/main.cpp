#include "longestAscendingSubsequence.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  InputSequence sequence_from_file = read_from_file();

  // if (*sequence_from_file) {
  //   printf("File read error \n");
  //   return -1;
  // }

  SubsequencesMatrix subsequences;


  for (int i = 0; sequence_from_file.sequence[i] != '\0'; i++)
  {
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
        if ((sequence_from_file.sequence[j] < sequence_from_file.sequence[i]) && (subsequences[0][j] >= maxLen))
        {
          maxLen = subsequences[0][j] + 1;
          maxIndex = j;
        }
      }

      subsequences[0][i] = maxLen;
      subsequences[1][i] = maxIndex;
    }
  }

  print_maximums_matrix(sequence_from_file.sequence, subsequences, sequence_from_file.length);
  determine_max_length_and_display_sequence(sequence_from_file.sequence, subsequences, sequence_from_file.length);

  return 0;
}

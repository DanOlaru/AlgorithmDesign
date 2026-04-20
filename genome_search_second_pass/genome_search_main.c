#include <stdio.h>
#include <string.h>
#include "genome_search.h"

int main(int argc, char const *argv[])
{
  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  char search_string[256];
  char genome[256];

  char buffer[256];

  int counter = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL)
  {
    if (counter == 0) {
       strcpy(search_string,buffer);
       search_string[strlen(search_string) - 1] = '\0'; // Remove newline character
    } else if (counter == 1) {
       strcpy(genome,buffer);
    } else {
      break;
    }
    counter++;
  }

  printf("search string %s\n", search_string);
  printf("search string length %lu\n", strlen(search_string));
  // printf("genome %s \n", genome);

  scan_search_string(search_string);

  fclose(file);

  return 0;
}

const int string_to_enum(char c) {
  switch (c) {
    case 'A': return A;
    case 'C': return C;
    case 'G': return G;
    case 'T': return T;
    default: return -1; // Invalid character
  }
}

void scan_search_string(const char *search_string) {

  int state_machine[256][4];
  int full_match_counter = 0;
  int current_cycle_length = 0;

  for (size_t i = 0; i < strlen(search_string); i++)
  {
    if (i > 0 && search_string[current_cycle_length] == search_string[i]) {
        ++current_cycle_length;
      } else {
        current_cycle_length = 0;
      }

    for (size_t j = 0; j < 4; j++) {
      if (search_string[i] == AlphabetArray[j]) {
        state_machine[i][j] = ++full_match_counter;
      } else {
        // state_machine[i][j] = ++current_cycle_length;
        if (search_string[current_cycle_length] == AlphabetArray[j]) {
          state_machine[i+1][j] = current_cycle_length;
        } else {
          state_machine[i][j] = 0;
        }
      }

      // printf("%d ", state_machine[i][j]);
    }
  }


  printf("  ");
  for (size_t i = 0; i < strlen(search_string); i++)
    {
      printf("%c ", search_string[i]);
    }
  printf("\n");

  for (size_t j = 0; j < 4; j++)
    {
      printf("%c ", AlphabetArray[j]);
      for (size_t i = 0; i < strlen(search_string); i++)
      {
        printf("%d ", state_machine[i][j]);
      }

      printf("\n");
    }

}
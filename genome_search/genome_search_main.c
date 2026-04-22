#include <stdio.h>
#include <string.h>
#include "genome_search.h"

int state_machine[MAX_LEN][4];

int main(int argc, char const *argv[])
{
  FILE *file = fopen("input.txt", "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  char search_string[MAX_LEN];
  char genome[MAX_LEN];
  char buffer[MAX_LEN];

  int counter = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL)
  {
    if (counter == 0)
    {
      strcpy(search_string, buffer);
      search_string[strlen(search_string) - 1] = '\0'; // Remove newline character
    }
    else if (counter == 1)
    {
      strcpy(genome, buffer);
    }
    else
    {
      break;
    }
    counter++;
  }


  printf("search string %s\n", search_string);
  printf("search string length %lu\n", strlen(search_string));
  printf("genome %s \n", genome);

  scan_search_string(search_string);

  fclose(file);

  print_state_machine(search_string, state_machine);

  match_found(genome, search_string, state_machine) ? printf("Match found!\n") : printf("No match found.\n");

  return 0;
}

const int string_to_enum(char c)
{
  switch (c)
  {
  case 'A':
    return A;
  case 'C':
    return C;
  case 'G':
    return G;
  case 'T':
    return T;
  default:
    return -1; // Invalid character
  }
}

void scan_search_string(const char *search_string)
{
  int full_match_counter = 0;
  int current_cycle_length = 0;

  for (size_t i = 0; i < strlen(search_string); i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      if (search_string[i] == AlphabetArray[j])
      {
        state_machine[i][j] = ++full_match_counter;
      }
      else
      {
        if (search_string[current_cycle_length] == AlphabetArray[j])
        {
          state_machine[i][j] = current_cycle_length + 1;
        }
        else
        {
          state_machine[i][j] = 0;
        }
      }
    }

    if (i > 0 && search_string[current_cycle_length] == search_string[i])
    {
      ++current_cycle_length;
    }
    else
    {
      current_cycle_length = 0;
    }
  }
}

void print_state_machine(const char *search_string, int state_machine[MAX_LEN][4])
{
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

int match_found(const char *genome, const char *search_string, int state_machine[MAX_LEN][4])
{
  int genome_index = 0;
  int search_string_index = 0;

  while (genome_index < strlen(genome) && search_string_index < strlen(search_string))
  {
    int current_char = string_to_enum(genome[genome_index]);
    search_string_index = state_machine[search_string_index][current_char];
    genome_index++;
  }
  return search_string_index == strlen(search_string);
}
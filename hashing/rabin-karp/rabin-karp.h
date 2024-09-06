#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // For isspace() function

char **read_strings_from_file()
{
  FILE *file = fopen("input.txt", "r");

  // if (file == NULL)
  // {
  //   perror("Failed to open file");
  //   return;
  // }

  int index = -1;
  char line[256];

  static char *strings[2];

  while (fgets(line, sizeof(line), file))
  {
    char *copy = (char *)malloc(strlen(line) + 1);

    strcpy(copy, line);
    strings[++index] = copy;
  }

  fclose(file);

  return strings;
}

char get_char_val(char character)
{
  return character - 65;
}

char *trimWhitespace(char *str)
{
  // Check if the string is empty
  if (str == NULL || *str == '\0')
  {
    return str;
  }

  // Pointer to keep track of the end of the string
  char *end;

  // Trim leading whitespace
  while (isspace((unsigned char)*str))
  {
    str++;
  }

  // If the string is all whitespace, return an empty string
  if (*str == '\0')
  {
    return str;
  }

  // Trim trailing whitespace
  end = str + strlen(str) - 1; // Set end to the last character in the string
  while (end > str && isspace((unsigned char)*end))
  {
    end--;
  }

  // Set the character after the last non-whitespace character to '\0'
  *(end + 1) = '\0';

  return str;
}

int hash_fresh(char *input)
{
  int hash = 0;

  for (int i = 0; i < strlen(input); i++)
  {
    hash += get_char_val(input[i]);
  }

  return hash;
}

char *substring(const char *original, int start, int end)
{
  // Check for valid start and end indexes
  if (start < 0 || end < start || end > strlen(original))
  {
    printf("Invalid indexes!\n");
    return NULL;
  }

  // Calculate the length of the substring
  int length = end - start;

  // Allocate memory for the substring (+1 for the null terminator)
  char *result = (char *)malloc(length + 1);

  if (result == NULL)
  {
    printf("Memory allocation failed!\n");
    return NULL;
  }

  // Copy the substring
  for (int i = 0; i < length; i++)
  {
    result[i] = original[start + i];
  }

  // Add the null terminator
  result[length] = '\0';

  return result;
}

int check_match(char *first, char *second)
{

  return strcmp(first, second);
}

char search_for(char *text_string, char *quarry)
{
  int length_of_difference = strlen(text_string) - strlen(quarry) + 1;
  int quarry_hash = hash_fresh(quarry);

  printf("quarry hash = %d \n", quarry_hash);

  for (int i = 0; i < length_of_difference; i++)
  {
    char *current_substring = substring(text_string, i, i + strlen(quarry));

    printf("substring ='%s', w hash = %d \n", current_substring, hash_fresh(current_substring));

    if (hash_fresh(current_substring) == quarry_hash)
    {
      printf("potential match %s\n", current_substring);
      if (check_match(current_substring, quarry) == 0)
      {
        printf("match confirmed for '%s'\n", current_substring);
      }
    }
  }

  return 0;
}
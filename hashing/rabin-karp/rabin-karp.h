#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char* copy = (char*) malloc(strlen(line) + 1);

    strcpy(copy, line);
    strings[++index] = copy;
  }

  fclose(file);

  return strings;
}



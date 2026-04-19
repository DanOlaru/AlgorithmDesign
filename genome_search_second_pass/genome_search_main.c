#include <stdio.h>

int main(int argc, char const *argv[])
{
  printf("Hellow, World!\n");


  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  char buffer[256];

  while (fgets(buffer, sizeof(buffer), file) != NULL)
  {
    printf("%s", buffer);
  }

  fclose(file);

  return 0;
}

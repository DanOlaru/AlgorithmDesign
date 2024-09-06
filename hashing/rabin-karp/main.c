
#include "rabin-karp.h"

int main(int argc, char const *argv[])
{

  char** input_strings = read_strings_from_file();

  printf("first line %s \n", input_strings[0]);
  printf("second line %s \n", input_strings[1]);

  return 0;
}

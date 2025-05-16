#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<string> readExpressionsFromFile() {
  FILE *inputFile = fopen("input.txt", "r");
  char line[256];
  vector<string> expressions;

  if (inputFile != NULL) {
    while( fgets(line, sizeof(line), inputFile) ) {
      char *newline = strchr(line, '\n');
      if (newline)
      {
        *newline = '\0';
      }
      expressions.push_back(line);

    }

    fclose(inputFile);
  }

  return expressions;
}

int main(int argc, char const *argv[])
{
  /* code */
  vector<string> expressionsFromFile;
  expressionsFromFile = readExpressionsFromFile();

  for (int i=0; i< expressionsFromFile.size(); i++) {

    cout << "returned " << expressionsFromFile.at(i) << endl;
  }


  readExpressionsFromFile();
  return 0;
}

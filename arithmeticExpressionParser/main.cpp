#include "expressionParser.h"
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
  vector<string> expressionsFromFile;
  vector<string> expressionsInPostFixNotation;
  expressionsFromFile = readExpressionsFromFile();

  for (int i = 0; i < expressionsFromFile.size(); i++)
  {
    expressionsInPostFixNotation.push_back(parseToPostfixNotation(expressionsFromFile.at(i)));
    // cout << "returned " << expressionsInPostFixNotation.at(i) << endl;
  }

  writeResultsToFile(expressionsInPostFixNotation, "postfix_output.txt");
  vector<int> results = evaluateExpressions(expressionsInPostFixNotation);
  vector<string> results_parsed(results.size());

  std::transform(
    results.begin(), 
    results.end(), 
    results_parsed.begin(),
    [](int num) { return std::to_string(num); }
  );
  

  writeResultsToFile(results_parsed, "values_output.txt");
  return 0;
}

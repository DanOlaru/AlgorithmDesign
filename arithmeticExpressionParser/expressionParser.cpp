#include <vector>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

vector<string> readExpressionsFromFile()
{
  FILE *inputFile = fopen("input.txt", "r");
  char line[256];
  vector<string> expressions;

  if (inputFile != NULL)
  {
    while (fgets(line, sizeof(line), inputFile))
    {
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

void writeResultsToFile(vector<string> parsed)
{
  FILE *outputFle = fopen("output.txt", "w");

  if (outputFle != NULL)
  {
    for (int i = 0; i < parsed.size(); i++)
    {
      fprintf(outputFle, "%s\n", parsed.at(i).c_str());
    }
    fclose(outputFle);
  }
}

string parseToPostfixNotation(string expressionInInfixNotation)
{
  string parsed;
  string operatorStack;

  // cout << " IN " << expressionInInfixNotation;

  for (int i = 0; i < expressionInInfixNotation.size(); i++)
  {
    char current = expressionInInfixNotation.at(i);
    switch (current)
    {
    case '+':
    case '-':
    {
      if (!operatorStack.empty())
      {
        char lastOpOnStack = operatorStack.back();
        operatorStack.pop_back();

        if (lastOpOnStack != '(')
        {
          parsed.push_back(lastOpOnStack);
        }
        else
        {
          operatorStack += lastOpOnStack;
        }
      }
      operatorStack += current;
    }
    break;
    case '*':
    case '/':
      if (!operatorStack.empty())
      {
        char lastOpOnStack = operatorStack.back();
        operatorStack.pop_back();

        if (lastOpOnStack == '+' || lastOpOnStack == '-' || lastOpOnStack == '(')
        {
          operatorStack += lastOpOnStack;
        }
        else
        {
          parsed.push_back(lastOpOnStack);
        }
      }
      operatorStack += current;
      break;
    case '(':
      operatorStack.push_back(current);
      break;
    case ')':
      while (operatorStack.back() != '(')
      {
        char lastOpOnStack = operatorStack.back();
        operatorStack.pop_back();
        parsed.push_back(lastOpOnStack);
      }
      operatorStack.pop_back();
      break;
    default:
      parsed.push_back(current);
      break;
    }
  }

  while (!operatorStack.empty())
  {
    parsed.push_back(operatorStack.back());
    operatorStack.pop_back();
  }

  // cout << " -> " << parsed << endl;
  return parsed;
}
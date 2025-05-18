#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include "expressionParser.h"

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

void writeResultsToFile(vector<string> parsed, string outputFile)
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

int lookupVariableValue(char variable)
{
  // TODO: also read from file
  if (variable == 'a')
  {
    return 1;
  }
  else if (variable == 'b')
  {
    return 2;
  }
  else if (variable == 'c')
  {
    return 3;
  }
  else if (variable == 'd')
  {
    return 4;
  }
  else if (variable == 'e')
  {
    return 5;
  }
  else if (variable == 'f')
  {
    return 6;
  }

  return -1;
}

int evaluatePostfixExpression(string expression)
{
  string operandStack = "";
  int result = 0;
  bool startedParsing = false;

  vector<int> operandValuesStack;

  for (int i = 0; i < expression.size(); i++)
  {
    char current = expression.at(i);
    cout << " at index " << i << " we have " << current << " and " << operandStack << endl;

    if (current == '+' || current == '-' || current == '*' || current == '/')
    {
      
      int operand_two = operandValuesStack.back();
      operandValuesStack.pop_back();
      int operand_one = operandValuesStack.back();
      operandValuesStack.pop_back();

      switch (current)
      {
      case '+':
        result = operand_one + operand_two;
        break;
      case '-':
        result = operand_one - operand_two;
        break;
      case '*':
        result = operand_one * operand_two;
        break;
      case '/':
        result = operand_one / operand_two;
        break;
      }
      operandValuesStack.push_back(result);
    }
    else
    {
      operandValuesStack.push_back(lookupVariableValue(current));
    }
  }

  // return operandStack.back();
  return result;
}

vector<int> evaluateExpressions(vector<string> postfixExpressions)
{
  vector<int> results;

  for (int i = 0; i < postfixExpressions.size(); i++)
  {
    results.push_back(evaluatePostfixExpression(postfixExpressions.at(i)));
    cout << "result of " << postfixExpressions.at(i) << " equals " << results.back() << endl;
  }
  return results;
}


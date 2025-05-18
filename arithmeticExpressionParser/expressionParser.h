#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <vector>
#include <string>

using namespace std;

vector<string> readExpressionsFromFile();
void writeResultsToFile(vector<string> parsed, string outputFile);
string parseToPostfixNotation(string expressionInInfixNotation);
int lookupVariableValue(char variable);
int evaluatePostfixExpression(string expression);
vector<int> evaluateExpressions(vector<string> postfixExpressions);

#endif
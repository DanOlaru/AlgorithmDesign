#include <iostream>
#include <stdio.h>
#include <cstring>

#include <vector>
#include <string>
#include "utilities.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
  // generateTestData(9, 50000);
  generateTestData(9, 15000);

  const vector<string> substrings = readFromFile();
  auto root = make_unique<SuffixTrie>('r');

  // build suffix trie
  buildTrie(substrings, root);

  combineAndCheckSubstrings(substrings, root);
}
#include <iostream>
#include <stdio.h>
#include <cstring>

#include <vector>
#include <string>
#include "utilities.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char const *argv[])
{

  generateTestData(10, 50000);

  // Start time
  auto start = high_resolution_clock::now();

  const vector<string> substrings = readFromFile();
  auto root = make_unique<SuffixTrie>('r');

  // build suffix trie
  buildTrie(substrings, root);

  combineAndCheckSubstrings(substrings, root);

  // End time
  auto end = high_resolution_clock::now();

  // Duration in microseconds
  auto duration = duration_cast<microseconds>(end - start);
  cout << "Execution time: " << duration.count() / 1000000 << " seconds" << endl;
}
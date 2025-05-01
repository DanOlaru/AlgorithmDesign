#include <iostream>
#include <stdio.h>
#include <cstring>

#include <vector>
#include <string>
// #include "possible2kSubstrings.h"
#include "utilities.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
  const vector<string> substrings = readFromFile();
  int k = substrings.at(0).size() - 1; // length of initial substrings
  // cout << "size " << substrings.size() << endl;
  auto root = make_unique<SuffixTrie>('r');

  // build suffix trie
  for (int i = 0; i < substrings.size(); i++)
  {
    buildSuffixTrie(substrings.at(i), root);
  }

    for (int i = 0; i < substrings.size(); i++)
    {
        for (int j = 0; j < substrings.size(); j++)
        {
            string candidate = substrings[i] + substrings[j];

            cout << "at indexes " << i << " and " << j << " val " << candidate;

            for (int start = 1; start < k; start++)
            {
                const string borderSpanningSubstring = candidate.substr(start, k);
                cout << " substring @" << start << " is " << borderSpanningSubstring;

                for (int l=0;l<substrings.size(); l++) {
                    //TODO: compare with initial substrings, print match if any
                    if (substrings.at(l) == borderSpanningSubstring) {
                        cout << " *found* "; 
                    }
                }
            }
            cout << endl;
        }
    }
}
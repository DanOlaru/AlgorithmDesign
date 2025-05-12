#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "possible2kSubstrings.h"
#include <memory>

using namespace std;

vector<string> readFromFile()
{
  vector<string> results;

  int num;
  FILE *file;
  file = fopen("input.txt", "r");
  char line[256];

  if (file != NULL)
  {
    while (fgets(line, sizeof(line), file))
    {
      char *newline = strchr(line, '\n');
      if (newline) {
          *newline = '\0';
      }
      results.push_back(line);
    }

    fclose(file);
  }
  else
  {
    fprintf(stderr, "Unable to open file!\n");
  }

  return results;
}

SuffixTrie* addToTrie(string suffix, unique_ptr<SuffixTrie> &root)
{
  cout << "suffix " << suffix;

  SuffixTrie *treeCursor = root.get();

  for (int i = 0; i < suffix.size(); i++)
  {
    cout << "level of tree " << treeCursor->letter << endl;
    int j = -1;
    bool found = false;
    int numberOfNodes = treeCursor->children.size();

    if (numberOfNodes > 0)
    {
      while ((j + 1 < numberOfNodes))
      {
        j++;
        if ((treeCursor->children.at(j)->letter == suffix.at(i)))
        {
          found = true;
          break;
        }
      }
    }

    if (found)
    {
      cout << " found elem at " << j << "==" << treeCursor->children.at(j)->letter << " moving one level below" << endl;
      treeCursor = treeCursor->children.at(j).get();
    }
    else
    {
      cout << " not found on level inserting " << suffix.at(i) << endl;

      (treeCursor->children).push_back(make_unique<SuffixTrie>(suffix.at(i)));
      treeCursor = (treeCursor->children).back().get();
    }

    if (i == suffix.size() - 1)
    {
      treeCursor->isFinal = true;
    }
  }

  return treeCursor;
}

void addTermToSuffixTrie(string substring, unique_ptr<SuffixTrie> &root)
{
  SuffixTrie* lastFullString;

  for (int i = 0; i < substring.size(); i++)
  {
    SuffixTrie* lastElementInSubtree = addToTrie(substring.substr(i, substring.size()), root);

    if (i == 0)
    {
      lastFullString = lastElementInSubtree;
    } else if (i==1) {
      lastFullString->longestProperSuffix = unique_ptr<SuffixTrie>(lastElementInSubtree);
    }
    cout << endl;
  }
}

void buildTrie(vector<string> substrings, unique_ptr<SuffixTrie> &root) {
  for (int i = 0; i < substrings.size(); i++)
  {
    addTermToSuffixTrie(substrings.at(i), root);
  }
}

void combineAndCheckSubstrings(vector<string> substrings) {
  int k = substrings.at(0).size(); // length of initial substrings

  for (int i = 0; i < substrings.size(); i++)
  {
    for (int j = 0; j < substrings.size(); j++)
    {
      string candidate = substrings[i] + substrings[j];
      checkAllBorderSpanningSubstringsAreInLibrary(&candidate, k, &substrings);
    }
  }
}

bool checkAllBorderSpanningSubstringsAreInLibrary(string *searchCandidate, int substringLength, const vector<string> *substrings)
{
  bool found = false;
  for (int start = 1; start < substringLength; start++)
  {
    const string borderSpanningSubstring = (*searchCandidate).substr(start, substringLength);

    for (int l = 0; l < (*substrings).size(); l++)
    {
      // TODO: compare with initial substrings, print match if any
      if ((*substrings).at(l) == borderSpanningSubstring)
      {
        // cout << " *found* ";
        found = true;
        break;
      }
    }
    // if (found) break;
    // cout << "|";
  }
  return found;
}
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

  for (int i = 0; i < suffix.size() - 1; i++)
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

    if (i == suffix.size() - 2)
    {
      treeCursor->isFinal = true;
    }
  }

  return treeCursor;
}

void addTermToSuffixTrie(string substring, unique_ptr<SuffixTrie> &root)
{
  SuffixTrie* lastFullString;

  for (int i = 0; i < substring.size() - 1; i++)
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
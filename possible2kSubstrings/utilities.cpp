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

void addToTrie(string suffix, unique_ptr<SuffixTrie> &root)
{
  cout << "suffix " << suffix;

  SuffixTrie *treeCursor = root.get();

  for (int i = 0; i < suffix.size() - 1; i++)
  {
    cout << "level of tree " << treeCursor->letter << endl;
    int j = -1;
    bool found = false;
    int numberOfNodes = treeCursor->next.size();


    if (numberOfNodes > 0)
    {
      while ((j + 1 < numberOfNodes))
      {
        j++;
        if ( (treeCursor->next.at(j)->letter == suffix.at(i))) {
          found = true;
          break;
        }
      }
    }

    if (found)
    {
      cout << " found elem at " << j << "==" << treeCursor->next.at(j)->letter << " moving one level below" << endl;
      treeCursor = treeCursor->next.at(j).get();
    }
    else
    {
      cout << " not found on level inserting " << suffix.at(i) << endl;

      (treeCursor->next).push_back(make_unique<SuffixTrie>(suffix.at(i)));
      treeCursor = (treeCursor->next).back().get();
    }
  }

  // if (i == suffix.size() - 1)
  // {
  //     treeCursor->isFinal = true;
  //     //  make node final
  // }
  // }
}

void buildSuffixTrie(string substring, unique_ptr<SuffixTrie> &root)
{
  for (int i = 0; i < substring.size() - 1; i++)
  {
    addToTrie(substring.substr(i, substring.size()), root);
    cout << endl;
  }
}
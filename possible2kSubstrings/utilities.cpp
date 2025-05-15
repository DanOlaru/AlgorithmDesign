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
      if (newline)
      {
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

SuffixTrie *addToTrie(string suffix, unique_ptr<SuffixTrie> &root)
{
  // cout << "suffix " << suffix;

  SuffixTrie *treeCursor = root.get();

  for (int i = 0; i < suffix.size(); i++)
  {
    // cout << "level of tree " << treeCursor->letter << endl;
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
      // cout << " found elem at " << j << "==" << treeCursor->children.at(j)->letter << " moving one level below" << endl;
      treeCursor = treeCursor->children.at(j).get();
    }
    else
    {
      // cout << " not found on level inserting " << suffix.at(i) << endl;

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
  SuffixTrie *lastFullString;

  for (int i = 0; i < substring.size(); i++)
  {
    SuffixTrie *lastElementInSubtree = addToTrie(substring.substr(i, substring.size()), root);

    if (i == 0)
    {
      lastFullString = lastElementInSubtree;
    }
    else if (i == 1)
    {
      lastFullString->longestProperSuffix = lastElementInSubtree;
    }
    // cout << endl;
  }
}

void addTermAndLongestSuffixToTrie(string substring, unique_ptr<SuffixTrie> &root)
{
  SuffixTrie *lastFullString;

  for (int i = 0; i < substring.size(); i++)
  {
    if (i < 2)
    {
      SuffixTrie *lastElementInSubtree = addToTrie(substring.substr(i, substring.size()), root);

      if (i == 0)
      {
        lastFullString = lastElementInSubtree;
      }
      else if (i == 1)
      {
        lastFullString->longestProperSuffix = lastElementInSubtree;
      }
    }
    // cout << endl;
  }
}

void buildTrie(vector<string> substrings, unique_ptr<SuffixTrie> &root)
{
  for (int i = 0; i < substrings.size(); i++)
  {
    // addTermToSuffixTrie(substrings.at(i), root);
    addTermAndLongestSuffixToTrie(substrings.at(i), root);
  }
}

void combineAndCheckSubstrings(vector<string> substrings, unique_ptr<SuffixTrie> &trieRoot)
{
  int k = substrings.at(0).size(); // length of initial substrings

  for (int i = 0; i < substrings.size(); i++)
  {
    for (int j = 0; j < substrings.size(); j++)
    {
      string candidate = substrings[i] + substrings[j];
      // checkAllBorderSpanningSubstringsAreInLibraryBruteForce(&candidate, k, &substrings);
      checkAllBorderSpanningSubstringsAreInLibraryUsingTrie(&candidate, k, &substrings, trieRoot);
    }
  }
}

bool checkAllBorderSpanningSubstringsAreInLibraryBruteForce(string *searchCandidate, int substringLength, const vector<string> *substrings)
{
  bool found = false;
  for (int start = 1; start < substringLength; start++)
  {
    const string borderSpanningSubstring = (*searchCandidate).substr(start, substringLength);

    for (int l = 0; l < (*substrings).size(); l++)
    {
      if ((*substrings).at(l) == borderSpanningSubstring)
      {
        found = true;
        break;
      }
    }
    if (found)
    {
      cout << "found " << borderSpanningSubstring << " from " << *searchCandidate << endl;
      break;
    }
  }
  return found;
}

bool checkAllBorderSpanningSubstringsAreInLibraryUsingTrie(string *searchCandidate, int substringLength, const vector<string> *substrings, unique_ptr<SuffixTrie> &trieRoot)
{
  SuffixTrie *treeCursor = trieRoot.get();
  bool foundAllSubstringsInTree = true;
  int cursorOnSubstring = 0;

  for (int start = 1; start < substringLength; start++)
  {
    bool endOfSearchStringReached = false;
    bool letterNotFound = false;
    int i = 0;

    const string borderSpanningSubstring = (*searchCandidate).substr(start, substringLength);
    // cout << "borders spanning string " << borderSpanningSubstring << endl;

    while (!endOfSearchStringReached && !letterNotFound)
    {
      bool foundOnLevel = false;
      char currentSearchLetter = borderSpanningSubstring.at(cursorOnSubstring);
      // cout << " current search letter " << currentSearchLetter << endl;
      // Try to travel the trie depth-first to find all the letters in the search candidate
      if (treeCursor->children.size() > 0)
      {
        if (treeCursor->children.at(i)->letter != currentSearchLetter)
        {
          i++;

          if (i == treeCursor->children.size())
          {
            foundAllSubstringsInTree = false;
            letterNotFound = true;
            // cout << "substring " << borderSpanningSubstring << " was NOT found" << endl;
          }
        }
        else
        {
          // cout << "found letter " << currentSearchLetter << " going to next tree level " << endl;
          cursorOnSubstring++;
          treeCursor = treeCursor->children.at(i).get();
          i = 0;
        }
      }
      else
      {
        foundAllSubstringsInTree = false;
        letterNotFound = true;
      }

      if (cursorOnSubstring == borderSpanningSubstring.size())
      {
        endOfSearchStringReached = true;
        treeCursor = treeCursor->longestProperSuffix;
        cursorOnSubstring = substringLength - 1;
        // cout << "substring " << borderSpanningSubstring << " was found, moving to immediate suffix " << endl;
      }
    }
    if (letterNotFound)
    {
      break;
    }
  }

  if (foundAllSubstringsInTree) {
    cout << "Potential 2k substring: " << *searchCandidate << endl;
  }

  return foundAllSubstringsInTree;
}

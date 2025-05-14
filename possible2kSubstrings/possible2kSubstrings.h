#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <memory>

using namespace std;

#ifndef SUFFIX_TRIE_H
#define SUFFIX_TRIE_H

struct SuffixTrie {
    char letter;
    bool isFinal;
    vector<unique_ptr<SuffixTrie>> children;

    SuffixTrie* longestProperSuffix = nullptr;

    SuffixTrie(char c, bool final = false) : letter(c), isFinal(final) {}
};

#endif


bool checkAllBorderSpanningSubstringsAreInLibraryBruteForce(string *searchCandidate, int substringLength, const vector<string> *substrings);
bool checkAllBorderSpanningSubstringsAreInLibraryUsingTrie(string *searchCandidate, int substringLength, const vector<string> *substrings, unique_ptr<SuffixTrie> &trieRoot);

vector<string> readFromFile();
void addTermToSuffixTrie(string substring, unique_ptr<SuffixTrie> &existingTrie);
void buildTrie(vector<string> substrings, unique_ptr<SuffixTrie> &root);
// void combineAndCheckSubstrings(vector<string> substrings);
void combineAndCheckSubstrings(vector<string> substrings, unique_ptr<SuffixTrie> &trieRoot);

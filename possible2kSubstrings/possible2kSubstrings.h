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
    vector<unique_ptr<SuffixTrie>> next;

    SuffixTrie(char c, bool final = false) : letter(c), isFinal(final) {}
};

#endif


bool checkAllBorderSpanningSubstringsAreInLibrary(string *searchCandidate, int substringLength, const vector<string> *substrings);
vector<string> readFromFile();
void buildSuffixTrie(string substring, unique_ptr<SuffixTrie> &existingTrie);
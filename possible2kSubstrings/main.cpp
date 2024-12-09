#include <iostream>
#include <stdio.h>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "yes hello" << endl;
    const vector<string> substrings = {"ACB", "CAA", "CCB", "ACA", "CAC", "BCA"};
    int k = 3; // length of initial substrings
    // TODO: read initial k-length substrings

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
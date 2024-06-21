#include <iostream>
#include <fstream>
#include "string"

#include "stringDistance.h"

using namespace std;



int main(int argc, const char *argv[])
{

    // string line;
    // fstream inputFile("resources/StringsInput.txt");

    // if (inputFile.is_open()) {
    //     cout << "Contents " << endl;

    //     while(inputFile.good()) {

    //         cout << line << " ";
    //         inputFile >> line;
    //     }
    //     cout << endl;
    // } else{
    //     cout << "Unable to open file " << inputFile.good() << endl;
    // }

    char *target = "theXrainYoYMP";
    char *search = "yePrainBPZMP";

    int cost = string_compare_recursive(target, search, strlen(target), strlen(search));

    cout << "cost == " << cost << endl;

    return 0;
}


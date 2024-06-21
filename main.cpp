#include <iostream>
#include <fstream>
#include "string"

#include "recursiveSolution.h"

using namespace std;



int main(int argc, const char *argv[])
{

    cout<< "FML" << endl;
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

    char *target = "the rain";
    char *search = "ye rain";

    int cost = string_compare(target, search, 9, 8);

    cout << "cost == " << cost << endl;

    return 0;
}


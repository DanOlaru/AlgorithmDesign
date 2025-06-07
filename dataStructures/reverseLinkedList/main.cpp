#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

struct LinkedListNode
{
    string word;
    LinkedListNode *next;
};

void printOutList(LinkedListNode *first)
{
    LinkedListNode *cursor = first;

    do
    {
        cout << "element value " << cursor->word << endl;
        cursor = cursor->next;
    } while (cursor->next != nullptr);

    cout << "element value " << cursor->word << endl;

    cout << endl;
}

int main(int argc, char const *argv[])
{
    FILE *inputFile = fopen("input.txt", "r");
    char line[256];

    vector<string> valuesArray;

    if (inputFile != NULL)
    {
        while (fgets(line, sizeof(line), inputFile))
        {
            char *newline = strchr(line, '\n');
            if (newline)
            {
                *newline = '\0';
            }

            std::istringstream iss(line);
            std::string word;

            while (iss >> word)
            {
                // std::cout << word << std::endl;
                valuesArray.push_back(word);
            }
        }
        fclose(inputFile);
    }

    LinkedListNode firstNode;
    firstNode.word = valuesArray.at(0); // TODO if exists
    firstNode.next = nullptr;

    LinkedListNode *current = &firstNode;

    for (int i = 1; i < valuesArray.size(); i++)
    {
        LinkedListNode *newNode = new LinkedListNode;
        newNode->word = valuesArray.at(i);
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }

    // traverse list to show correctness
    printOutList(&firstNode);

    // invert list
    LinkedListNode *previous, *currentElement, *newFirstNode;
    previous = &firstNode;
    currentElement = previous->next;
    previous->next = nullptr;

    while (currentElement != nullptr)
    {
        LinkedListNode *oldNext = currentElement->next;
        currentElement->next = previous;
        previous = currentElement;
        currentElement = oldNext;
        newFirstNode = previous;
    }

    // print again
    printOutList(newFirstNode);

    return 0;
}

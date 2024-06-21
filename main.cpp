
#include <iostream>
#include <fstream>
#include "stringDistance.h"

using namespace std;

void print_cost_matrix(char *target, char *search);
void print_parent_matrix(char *target, char *search);

cell m[MAXLEN + 1][MAXLEN + 1];

int main(int argc, const char *argv[])
{
    char *target = " thou shalt not";
    char *search = " you should not";

    // int cost = string_compare_recursive(target, search, strlen(target), strlen(search));
    int cost = string_compare(target, search, m);

    cout << "cost == " << cost << endl;
    // print_cost_matrix(target, search);
    print_parent_matrix(target, search);

// printf("len s%d\n", strlen(search));
// printf("len T%d\n", strlen(target));

    reconstruct_path(target, search, strlen(search)-1, strlen(target)-1, m);

    return 0;
}

void print_cost_matrix(char *target, char *search)
{
    printf("   ");
    for (size_t l = 0; l < strlen(search); l++)
    {
        printf(" %c, ", search[l]);
    }
    printf("\n");
    for (size_t i = 0; i < strlen(target); i++)
    {
        printf("%c, ", target[i]);

        for (size_t j = 0; j < strlen(search); j++)
        {
            // printf("%d-%d, ", m[i][j].cost, m[i][j].parent);

            m[i][j].cost >= 10
                ? printf("%d, ", m[i][j].cost)
                : printf(" %d, ", m[i][j].cost);
        }
        printf("\n");
    }

    printf("\n");
}

void print_parent_matrix(char *target, char *search)
{
    printf("    ");
    for (size_t l = 0; l < strlen(search); l++)
    {
        printf("%c, ", search[l]);
    }
    printf("\n");

    for (size_t i = 0; i < strlen(target); i++)
    {
        printf("%c, ", target[i]);

        for (size_t j = 0; j < strlen(search); j++)
        {
            if (m[i][j].parent > 0 && j == 0)
            {
                printf(" %d, ", m[i][j].parent);
            }
            else
                printf("%d, ", m[i][j].parent);
        }
        printf("\n");
    }

    printf("\n");
}
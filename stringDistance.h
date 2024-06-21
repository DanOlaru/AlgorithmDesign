#include "string"
#include <iostream>

#define MATCH 0
#define INSERT 1
#define DELETE 2
#define MAXLEN 100

using namespace std;

typedef struct
{
    int cost;
    int parent;
} cell;

int indel(char c)
{
    return (1);
}

int match(char c, char d)
{
    if (c == d)
        return 0;
    else
        return 1;
}

void row_init(int i, cell m[MAXLEN + 1][MAXLEN + 1])
{
    m[0][i].cost = i;

    if (i > 0)
    {
        m[0][i].parent = INSERT;
    }
    else
    {
        m[0][i].parent = -1;
    }
}

void column_init(int i, cell m[MAXLEN + 1][MAXLEN + 1])
{
    m[i][0].cost = i;

    if (i > 0)
    {
        m[i][0].parent = DELETE;
    }
    else
    {
        m[i][0].parent = -1;
    }
}

void goal_cell(char *s, char *t, int *i, int *j)
{
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}

void insert_out(char *t, int j)
{
    printf("I-");
}

void delete_out(char *t, int j)
{
    printf("D-");
}

void match_out(char *s, char *t, int i, int j)
{
    if (s[i] == t[j])
        printf("M-");
    else
        printf("S-");
}

int string_compare(char *s, char *t, cell m[MAXLEN + 1][MAXLEN + 1])
{
    int i, j, k;
    int opt[3];

    for (i = 0; i < MAXLEN; i++)
    {
        row_init(i, m);
        column_init(i, m);
    }

    for (i = 1; i < strlen(s); i++)
    {
        for (j = 1; j < strlen(t); j++)
        {
            opt[MATCH] = m[i - 1][j - 1].cost + match(s[i], t[j]);
            opt[INSERT] = m[i][j - 1].cost + indel(t[j]);
            opt[DELETE] = m[i - 1][j].cost + indel(s[i]);

            m[i][j].cost = opt[MATCH];
            m[i][j].parent = MATCH;
            for (k = INSERT; k <= DELETE; k++)
            {
                if (opt[k] < m[i][j].cost)
                {
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                }
            }
        }
    }

    goal_cell(s, t, &i, &j);
    return (m[i][j].cost);
}

void reconstruct_path(char *s, char *t, int i, int j, cell m[MAXLEN + 1][MAXLEN + 1])
{
    if (m[i][j].parent == -1)
        return;

    // printf("%d %d, \n", i, j);
    printf("%c %c, \n", s[i], t[j]);

    if (m[i][j].parent == MATCH)
    {
        reconstruct_path(s, t, i - 1, j - 1, m);
        match_out(s, t, i, j);
        return;
    }

    if (m[i][j].parent == INSERT)
    {
        reconstruct_path(s, t, i, j - 1, m);
        insert_out(t, j);

        return;
    }
    if (m[i][j].parent == DELETE)
    {
        reconstruct_path(s, t, i - 1, j, m);
        delete_out(s, i);
        return;
    }
}

int string_compare_recursive(char *s, char *t, int i, int j)
{
    int k;      // counter
    int opt[3]; // cost of the 3 options
    int lowest_cost;

    if (i == 0)
        return (j * indel(' '));
    if (j == 0)
        return (i * indel(' '));

    opt[MATCH] = string_compare_recursive(s, t, i - 1, j - 1) + match(s[i], t[j]);
    opt[INSERT] = string_compare_recursive(s, t, i, j - 1) + indel(t[j]);
    opt[DELETE] = string_compare_recursive(s, t, i - 1, j) + indel(s[i]);

    lowest_cost = opt[MATCH];
    for (k = INSERT; k <= DELETE; k++)
        if (opt[k] < lowest_cost)
            lowest_cost = opt[k];
    return (lowest_cost);
}
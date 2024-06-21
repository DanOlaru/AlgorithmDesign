#define MATCH 0
#define INSERT 1
#define DELETE 2

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

int string_compare(char *s, char *t, int i, int j)
{
    int k;      // counter
    int opt[3]; // cost of the 3 options
    int lowest_cost;

    if (i == 0)
        return (j * indel(' '));
    if (j == 0)
        return (i * indel(' '));

    opt[MATCH] = string_compare(s, t, i - 1, j - 1) + match(s[i], t[j]);
    opt[INSERT] = string_compare(s, t, i, j - 1) + indel(t[j]);
    opt[DELETE] = string_compare(s, t, i - 1, j) + indel(s[i]);

    lowest_cost = opt[MATCH];
    for (k = INSERT; k <= DELETE; k++)
        if (opt[k] < lowest_cost)
            lowest_cost = opt[k];
    return (lowest_cost);
}
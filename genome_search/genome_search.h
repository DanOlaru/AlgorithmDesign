#define MAX_LEN 256

enum Alphabet
{
  A,
  C,
  G,
  T
};

const char AlphabetArray[] = {'A', 'C', 'G', 'T'};

void scan_search_string(const char *search_string);
void print_state_machine(const char *search_string, int state_machine[MAX_LEN][4]);
const int string_to_enum(char c);

int match_found(const char *genome, const char *search_string, int state_machine[MAX_LEN][4]);
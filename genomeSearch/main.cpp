#include "genomeSearch.h"
#include <string>

int main(int argc, char const *argv[])
{
  string genome, search_sequence;
  genome = "TCGATCGATTCGATCGAATGC";
  search_sequence = "TCGATCGAA";

  StateMachine state_machine{search_sequence, genome};

  state_machine.run_search();

  return 0;
}

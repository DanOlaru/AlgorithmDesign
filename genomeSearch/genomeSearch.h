#include <iostream>
#include <string>

#define MAXLEN 100

using namespace std;

enum class Alphabet
{
  A,
  C,
  G,
  T
};

char alphabet[] = {'A', 'C', 'G', 'T'};

struct StateMachine
{
  int state = 0;
  int mapping[4][MAXLEN];
  bool found = false;
  string sequence;
  string genome;

  StateMachine(string seq, string gen)
  {
    sequence = seq;
    genome = gen;

    construct_mapping(sequence);
  }

  void run_search()
  {
    print_matrix();

    for (size_t i = 0; ((i < genome.length()) && !found); i++)
    {
      char letter = genome.at(i);
      int index = get_index(letter);

      state = get_next_state(index);

      if (state >= sequence.length())
      {
        found = true;

        cout << "Sequence found " << endl;
      }
    }

    if (!found)
    {
      cout << "Sequence NOT found " << endl;
    }
  }

  void print_matrix()
  {
    for (size_t j = 0; j < 4; j++)
    {
      for (size_t i = 0; i < sequence.length(); i++)
      {
        cout << mapping[j][i] << " ";
      }
      cout << endl;
    }
  }

private:
  int get_index(char letter)
  {
    for (size_t i = 0; i < 4; i++)
    {
      if (alphabet[i] == letter)
      {
        return i;
      }
    }
  }

  int get_next_state(int letter_index)
  {
    return mapping[letter_index][state];
  }

  void construct_mapping(string sequence)
  {
    // find longest substring ending at i which also shows up at the front of the search sequence
    for (size_t i = 0; i < sequence.length(); i++)
    {
      auto letter_at_position = sequence.at(i);

      for (size_t j = 0; j < 4; j++)
      {
        if (alphabet[j] == letter_at_position)
        {
          mapping[j][i] = i + 1;
        }
        else if (alphabet[j] == sequence.at(0))
        {
          mapping[j][i] = 1;
        }
        else
        {
          mapping[j][i] = 0;
        }
      }
    }
  }
};
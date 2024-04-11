// Header inclusions
#include <cstdlib> //rand()
#include <ctime>   //time()
#include <fstream> //File operations
#include <iostream>
#include <string> //String type
using namespace std;

// Variables

int num, diff, num_ans, num_range_min, num_range_max, attempts, attempts_taken;
char ans;
string diffStr, fname;

// Function declarations

int diffChoose();
int rngSet();
unsigned int rng(unsigned int min, unsigned int max);
void game();
void fileAsk();

/* Seed RNG and proceed, or read from score file if an argument is passed. */
int main(int argc, char *argv[]) {
  string ftxt;
  if (argv[1]) {
    ifstream f(argv[1]);
    cout << "Reading score file '" << argv[1] << "'...\n";
    if (!f) {
      cerr << "\a\e[33;1;31mfatal: Unable to open file for reading.\n\e[0m";
      return 2;
    }
    while (getline(f, ftxt))
      cout << ftxt << "\n";
    f.close();
    return 0;
  } else {
    srand(time(NULL));
    return diffChoose();
  }
}

/* Create difficulty prompt and set variables based on response */
int diffChoose() {
  cout << "Choose a difficulty.\n(1) - Easy (10 attempts)\n(2) - Normal (5 "
          "attempts)\n(3) - Hard (1 attempt)\nMake a selection: ";
  cin >> diff;
  switch (diff) {
  case 1:
    attempts = 10;
    diffStr = "Easy";
    break;
  case 2:
    attempts = 5;
    diffStr = "Normal";
    break;
  case 3:
    attempts = 1;
    diffStr = "Hard";
    break;
  default:
    cerr << "\a\n\e[33;1;31mfatal: Invalid difficulty value.\n\e[0m";
    exit(1);
    break;
  }
  cout << "\nYou selected \e[33;1;37m" << diffStr
       << ".\e[0m You will have \e[33;1;37m" << attempts
       << " attempt(s)\e[0m to get the number correct.\nIs this correct? "
          "(y/n): ";
  cin >> ans;
  if (ans == 'n') {
    while (ans != 'y')
      diffChoose();
  }
  return rngSet();
}

/* Generate a random value between unsigned ints min and max */
unsigned int rng(unsigned int min, unsigned int max) {
  return (rand() % ((max + 1) - min) + min);
}

/* Prepare random values and finalize return value chain */
int rngSet() {
  num = rng(1, 100);
  num_range_min = num - rng(1, 10);
  num_range_max = num + rng(1, 10);
  game();
  return 0;
}

/* Prompt for user answer and terminate game if user answer is equal to random
 * num. Otherwise, loop until user is correct or no attempts remain */
void game() {
  if (attempts > 0) {
    cout << "\nNumber is between " << num_range_min << " and " << num_range_max
         << ". (Attempts left: " << attempts << ")\n Answer: ";
    cin >> num_ans;
    if (num_ans == num) {
      attempts--;
      attempts_taken++;
      cout << "\e[33;1;37mCorrect!\nAttempts taken: " << attempts_taken
           << "\n\a\e[0m";
      fileAsk();
    } else {
      while (num_ans != num && attempts > 0) {
        attempts--;
        attempts_taken++;
        game();
      }
    }
  } else
    cout << "\e[33;1;37m\nYou ran out of attempts!\n\aThe correct number was "
         << num << ".\n\e[0m";
}

/* Prompt the user and ask if they wish to write contents about their session to
 * a file. */
void fileAsk() {
  cout << "Do you want to write information about your run to a score file? "
          "(y/n): ";
  cin >> ans;
  if (ans == 'y') {
    cout << "Please enter a name for your save: ";
    cin >> fname;
    ofstream f("scores.txt", ios_base::app); // Append, don't overwrite.
    if (!f) {
      cerr << "\e[33;1;31mfatal: Unable to write to score file. Do you have "
              "write permissions?\e[0m\a\n";
      exit(2);
    }
    f << "\t" << fname << "\t\t\t\tAttempts taken: " << attempts_taken
      << "\t\t\t\tAttempts left: " << attempts
      << "\t\t\t\tDifficulty: " << diffStr << "\n";
    f.close();
    cout << "Information written to 'scores.txt'\n";
  }
  exit(0);
}

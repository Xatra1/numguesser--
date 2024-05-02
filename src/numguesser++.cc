// Header inclusions

#include <cstdlib>    // exit(), rand(), srand(), size_t type
#include <cstring>    // strcmp()
#include <filesystem> // filesystem::path
#include <fstream>    // ifstream, ofstream
#include <iostream>   // cerr, cin, cout, ios_base
#include <string>     // getline(), stoi(), str type
#include <unistd.h>   // getlogin()
using namespace std;

// Aliases

namespace fs = filesystem;
typedef string str;

// Variables

int rand_int, num, diff, num_ans, num_range_min, num_range_max, attempts,
    attempts_taken;
bool prompt_for_name, arg_ignored, show_num = true;
char rand_byte, ans;
str diff_str, fname, ver = "numguesser++ v1.3";

// Function declarations

uint rng(uint min, uint max);
int diff_choose();
int rng_set();
void rng_seed();
void game();
void file_ask();

// Generate a random value between min and max
uint rng(uint min, uint max) { return (rand() % ((max + 1) - min) + min); }

// Handle any arguments that are passed to the program.
int main(int argc, char *argv[]) {
  str ftxt;
  if (argv[1]) {
    if ((!strcmp(argv[1], "-f") || !strcmp(argv[1], "--read-file")) &&
        argv[2]) {
      fs::path file = argv[2];
      ifstream f(argv[2]);
      cout << "Reading score file '" << argv[2] << "'...\n";
      if (f.fail()) {
        cerr << "\a\e[33;1;31mfatal: Unable to open file " << argv[2]
             << " for reading.\e[0m\n";
        return 2;
      } else if (file.extension() != ".scf") {
        cerr << "\a\e[33;1;31mfatal: Score file has file extension "
             << file.extension() << " (expected .scf)\e[0m\n";
        return 3;
      }
      while (getline(f, ftxt))
        cout << ftxt << '\n';
      f.close();
      return 0;
    } else if ((!strcmp(argv[1], "-f") || !strcmp(argv[1], "--read-file")) &&
               !argv[2]) {
      cout << "\e[33;1;33mwarning:\e[0m Expected FILE for argument '" << argv[1]
           << "'. Try 'numguesser++ --help' or 'numguesser++ --usage' for more "
              "information.\n";
      arg_ignored = true;
    } else if (!strcmp(argv[1], "-s"))
      prompt_for_name = true;
    else if (!strcmp(argv[1], "-d") && argv[2]) {
      str arg = argv[2];
      size_t pos;
      try {
        diff = stoi(arg, &pos);
        if (diff < 1 || diff > 3) {
          cout << "\e[33;1;33mwarning:\e[0m Invalid difficulty value (Expected "
                  "1-3 inclusive, got "
               << diff
               << "). Try 'numguesser++ --help' or 'numguesser++ --usage' for "
                  "more information.\n";
          arg_ignored = true;
          diff = 0;
        }
      } catch (invalid_argument const &ex) {
        cout << "\e[33;1;33mwarning:\e[0m Expected integer for argument "
                "'-d'. Try 'numguesser++ --help' or 'numguesser++ --usage' for "
                "more information.\n";
        arg_ignored = true;
        diff = 0;
      } catch (out_of_range const &ex) {
        cout << "\e[33;1;33mwarning:\e[0m Given integer for argument '-d' is "
                "too large. Try 'numguesser++ --help' or 'numguesser++ "
                "--usage' for more information.\n";
        arg_ignored = true;
        diff = 0;
      }
    } else if (!strcmp(argv[1], "-d") && !argv[2]) {
      cout << "\e[33;1;33mwarning:\e[0m Expected integer for argument '-d', "
              "got nothing. Try 'numguesser++ --help' or 'numguesser++ "
              "--usage' for more information.\n";
      arg_ignored = true;
      diff = 0;
    } else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") ||
               !strcmp(argv[1], "--usage")) {
      cout << "Usage: numguesser++ [OPTION...] \n    or ng++ "
              "[OPTION...]\n\nnumguesser++ is a C++ rewrite of numguesser, a "
              "random number guessing game originally\nwritten in C, with some "
              "additional enhancements.\n\n  -d 1-3\t\t     Chooses the "
              "difficulty of the game, skipping the difficulty\n\t\t\t     "
              "select phase. Accepts any value from 1-3 inclusive.\n\n  "
              "-s\t\t\t     Prompts for a custom save name after a victory. If "
              "this\n\t\t\t     option is not passed, the username of the user "
              "who called\n\t\t\t     the program is used instead.\n\n  -f, "
              "--read-file FILE\t     Reads from FILE and exits. FILE must "
              "have the '.scf'\n\t\t\t     extension.\n\n  -n\t\t\t     "
              "Prevents the program from displaying the correct number\n\t\t\t "
              "    after a loss.\n\n  -h, --help, --usage\t     Displays this "
              "help document and exits.\n\n  -v, --version\t\t     Displays "
              "the program's version string and exits.\n\nMandatory or "
              "optional arguments to long options are also mandatory or "
              "optional for\nany corresponding short options.\n\nOnly one "
              "argument can be passed to the program at a time. If multiple "
              "arguments are\npassed, they will be ignored.\n\nReport bugs to "
              "https://github.com/Xatra1/numguesser-plus-plus\n";
      return 0;
    } else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
      cout << ver << '\n';
      return 0;
    } else if (!strcmp(argv[1], "-n"))
      show_num = false;
    else if (argv[1]) {
      cout << "\e[33;1;33mwarning:\e[0m Unknown argument '" << argv[1] << "'\n";
      arg_ignored = true;
    }
    if (argv[3] && strcmp(argv[1], "-s") && strcmp(argv[1], "-n"))
      arg_ignored = true;
    if (arg_ignored)
      cout << "\e[33;1;33mwarning:\e[0m An argument was ignored.\n";
  }
  rng_seed();
  return diff_choose();
}

// Read a single byte from /dev/urandom, convert that to an integer, and seed
// RNG.
void rng_seed() {
  ifstream f("/dev/urandom");
  if (f.fail()) {
    cerr << "\a\e[33;1;31mfatal: Unable to open /dev/urandom\e[0m\n";
    exit(2);
  }
  f.get(rand_byte);
  rand_int = int(rand_byte);
  f.close();
  srand(rand_int);
}

// Create difficulty prompt and set variables based on response
int diff_choose() {
  if (!diff) {
    cout << "Choose a difficulty.\n(1) - Easy (10 attempts)\n(2) - Normal (5 "
            "attempts)\n(3) - Hard (1 attempt)\nMake a selection: ";
    cin >> diff;
  }
  switch (diff) {
  case 1:
    attempts = 10;
    diff_str = "Easy";
    break;
  case 2:
    attempts = 5;
    diff_str = "Normal";
    break;
  case 3:
    attempts = 1;
    diff_str = "Hard";
    break;
  default:
    cerr << "\a\n\e[33;1;31mfatal: Invalid difficulty value.\e[0m\n";
    exit(1);
    break;
  }
  cout << "\nYou selected \e[33;1;37m" << diff_str
       << ".\e[0m You will have \e[33;1;37m" << attempts
       << " attempt(s)\e[0m to get the number correct.\nIs this correct? "
          "(y/n): ";
  cin >> ans;
  if (ans == 'n')
    while (ans != 'y') {
      diff = 0;
      diff_choose();
    }
  return rng_set();
}

// Prepare random values and finalize return value chain
int rng_set() {
  num = rng(1, 100);
  num_range_min = num - rng(1, 10);
  num_range_max = num + rng(1, 10);
  game();
  return 0;
}

// Prompt for user answer and terminate game if user answer is equal to random
// num. Otherwise, loop until user is correct or no attempts remain
void game() {
  if (attempts > 0) {
    cout << "\nNumber is between " << num_range_min << " and " << num_range_max
         << ". (Attempts left: " << attempts << ")\n Answer: ";
    cin >> num_ans;
    if (num_ans == num) {
      attempts--;
      attempts_taken++;
      cout << "\a\e[33;1;37mCorrect!\nAttempts taken: " << attempts_taken
           << "\e[0m\n";
      file_ask();
    } else {
      while (num_ans != num && attempts > 0) {
        attempts--;
        attempts_taken++;
        game();
      }
    }
  } else {
    if (show_num)
      cout << "\a\e[33;1;37m\nYou ran out of attempts!\nThe correct number was "
           << num << ".\e[0m\n";
    else
      cout << "\a\e[33;1;37m\nYou ran out of attempts!\n\e[0m";
  }
}

// Prompt the user and ask if they wish to write contents about their session to
// a file.
void file_ask() {
  cout << "Do you want to write information about your run to a score file? "
          "(y/n): ";
  cin >> ans;
  if (ans == 'y') {
    ofstream f("scores.scf", ios_base::app); // Append, don't overwrite.
    if (f.fail()) {
      cerr << "\a\e[33;1;31mfatal: Unable to write to score file. Do you have "
              "write permissions here?\e[0m\n";
      exit(2);
    }
    if (prompt_for_name) {
      cout << "Please enter the name you would like to use for your save: ";
      cin >> fname;
    } else
      fname = getlogin();
    f << "\t" << fname << "\t\t\t\tAttempts taken: " << attempts_taken
      << "\t\t\t\tAttempts left: " << attempts
      << "\t\t\t\tDifficulty: " << diff_str << '\n';
    f.close();
    cout << "\a\e[33;1;37mInformation written to 'scores.scf'\e[0m\n";
  }
  exit(0);
}

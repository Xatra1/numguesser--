#include <csignal>    // SIGINT, signal()
#include <cstdlib>    // exit(), rand(), srand(), size_t type
#include <filesystem> // filesystem::path
#include <fstream>    // ifstream, ofstream
#include <getopt.h>   // Provides argument parsing
#include <iostream>   // cerr, cin, cout, endl, ios_base
#include <string>     // getline(), stoi(), str type
#include <unistd.h>   // getlogin()

using namespace std;
namespace fs = filesystem;
typedef string str;

int rand_int, num, diff, num_ans, num_range_min, num_range_max, attempts,
    attempts_taken;
bool prompt_for_name, arg_ignored, show_num = true;
char rand_byte, ans;
str diff_str, fname, ver = "numguesser++ v1.4";
const struct option longopts[] = {{"read-file", required_argument, 0, 'f'},
                                  {"difficulty", required_argument, 0, 'd'},
                                  {"help", no_argument, 0, 'h'},
                                  {"usage", no_argument, 0, 'h'},
                                  {"version", no_argument, 0, 'v'}};

uint rng(uint min, uint max);
int diff_choose();
int rng_set();
void rng_seed();
void game();
void file_ask();
void interrupt(int signum);
void usage(int scode);

// Generate a random value between min and max.
uint rng(uint min, uint max) { return (rand() % ((max + 1) - min) + min); }

// Cleanly exit when a SIGINT is raised.
void interrupt(int signum) {
  cout << "Interrupt raised.\n";
  exit(signum);
}

// Print the usage document and exit with status scode
void usage(int scode) {
  cout << R"EOF(Usage: numguesser++ [OPTION...]
    or ng++ [OPTION...]

numguesser++ is a C++ rewrite of numguesser, a random number 
guessing game originally written in C, with some additional 
enhancements.
            
-d, --difficulty 1-3    Chooses the difficulty of the game, 
                        skipping the difficulty
                        select phase. Accepts any value from 
                        1-3 inclusive.

-s                      Prompts for a custom save name after 
                        a victory. If this option is not 
                        passed, the username of the user who 
                        called the program is used instead.
                                    
-f, --read-file FILE    Reads from FILE and exits. FILE must 
                        have the '.scf' extension.
            
-n                      Prevents the program from displaying 
                        the correct number after a loss.
            
-h, --help, --usage     Displays this help document and 
                        exits.
            
-v, --version           Displays the program's version string 
                        and exits.
                                    
Mandatory or optional arguments to long options are also 
mandatory or optional for any corresponding short options.

Exit Codes:
0 - Everything worked as expected.
1 - Invalid difficulty value at selection prompt
2 - Unable to seed RNG
3 - Failed to open score file or score file does not have .scf extension
4 - Invalid difficulty value (-d)
            
Report bugs to https://github.com/Xatra1/numguesser-plus-plus)EOF"
       << endl;
  exit(scode);
}

// Handle any arguments that are passed to the program and set up SIGINT
// handling.
int main(int argc, char *argv[]) {
  str ftxt;
  int index;
  signal(SIGINT, interrupt);
  for (;;) {
    switch (getopt_long(argc, argv, "d:sf:nhv", longopts, &index)) {
    case 'd': {
      str arg = optarg;
      size_t pos;
      try {
        diff = stoi(arg, &pos);
        if (diff < 1 || diff > 3) {
          cout << "\e[33;1;33mwarning:\e[0m Invalid difficulty value (expected "
                  "1-3 inclusive).";
          usage(4);
        }
      } catch (invalid_argument const &ex) {
        cout << "\e[33;1;37mwarning:\e[0m Expected integer for difficulty "
                "argument.";
        usage(4);
      } catch (out_of_range const &ex) {
        cout << "\e[33;1;37mwarning:\e[0m Given integer for difficulty "
                "argument surpasses integer limit.";
        usage(4);
      }
    }
      continue;
    case 's':
      prompt_for_name = true;
      continue;
    case 'f': {
      fs::path extcheck = optarg;
      ifstream f(optarg);
      cout << "Reading score file '" << optarg << "'...\n";
      if (f.fail()) {
        cerr << "\a\e[33;1;31mfatal: Unable to open file " << optarg
             << " for reading.\e[0m\n";
        return 3;
      } else if (extcheck.extension() != ".scf") {
        cerr << "\a\e[33;1;31mfatal: Score file has file extension "
             << extcheck.extension() << " (expected .scf)\e[0m\n";
        return 3;
      }
      while (getline(f, ftxt))
        cout << ftxt << '\n';
      f.close();
      return 0;
      break;
    }
    case 'n':
      show_num = false;
      continue;
    case 'h':
      usage(0);
      break;
    case 'v':
      cout << ver << endl;
      return 0;
      break;
    default:
      usage(1);
      break;
    case -1:
      break;
    }
    break;
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

// Create difficulty prompt and set variables based on response.
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
       << " attempt(s)\e[0m to get the number correct.\n Is this correct? "
          "(y/n): ";
  cin >> ans;
  if (ans == 'n')
    while (ans != 'y') {
      diff = 0;
      diff_choose();
    }
  return rng_set();
}

// Prepare random values and finalize return value chain.
int rng_set() {
  num = rng(1, 100);
  num_range_min = num - rng(1, 10);
  num_range_max = num + rng(1, 10);
  game();
  return 0;
}

// Prompt for user answer and terminate game if user answer is equal to random
// num. Otherwise, loop until user is correct or no attempts remain.
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

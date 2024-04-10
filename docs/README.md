## About
numguesser++ is a C++ rewrite of [numguesser](https://github.com/Xatra1/numguesser), a random number guessing game.
## Building from Source
To compile, open a terminal in the same directory as the makefile and run ``make``.  
This will create an executable in ``src/deb/usr/local/bin/`` named ``numguesser++``. Then you can optionally run ``make build-pkg`` to build and install a Debian package.
## Notes
If you wish for the game to read your score file, pass the file path of the file as an argument to the game.
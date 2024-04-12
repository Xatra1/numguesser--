## Building from Source
To compile, open a terminal in the same directory as the makefile and run ``make``.  
This will create an executable in ``src/deb/usr/local/bin/`` named ``numguesser++``. Then you can optionally run ``make build-pkg`` to build and install a Debian package.
## Notes
If you wish for the game to read your score file, pass the file path of the file as an argument to the game. You can also pass '-s' if you want the game to prompt you for a custom save name instead of using your login name.

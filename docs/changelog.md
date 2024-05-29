## v1.1
- The game now reads from /dev/urandom to seed RNG, rather than using the system time.
- The game now automatically uses your username for your save name. You can still use custom save names by passing '-s' when running the program.
- You can now pass the '-d' argument with a value of 1-3 (inclusive) to bypass difficulty selection.
- You can also pass '-h', '--help', or '--usage' to get a help document, or '-v' for version information.

## v1.2
- Reading from a score file now has it's own arguments, '-f' and '--readfile'
- Score files now use the .scf extension, which is now required for the game to read from the file.
- Fixed the '--usage' arg not being handled at all even when passed.
- '-v' now has a corresponding long option '--version'

## v1.3
- Argument '--readfile' is now '--read-file'
- You can now run 'ng++' to execute the program instead of only 'numguesser++'
- Implemented the '-n' argument from the original version of numguesser, which prevents the correct number from being displayed after a loss.
- Implemented a '--debug' argument that displays debug information about program variables and terminates. The same information is also displayed when terminating the program with Ctrl-C

## v1.4
- The game can now accept multiple arguments at a time.
- Removed the '--debug' argument (as well as the corresponding information)
- Exit codes and their explanations are now included in the help document.
- The game will no longer exit if an invalid parameter is passed to '-d'.
- Added long options for '-n' and '-s'
- Fixed a bug where the program would segfault if an unrecognized long option was passed.
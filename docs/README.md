## Building from Source
### Prerequisites
- g++
- make 
- dpkg*
  
*Optional.
### Compiling
#### Automatic
If you have all required dependencies (including optional) you can execute ``mkng++.sh``. Any argument you pass to the shell script will be passed when the script runs the game. Note that the script assumes the source files are in your home directory.
  
For example, if you wished to compile the game and open the game's help document, you can execute ``mkng++ -h``, ``mkng++.sh --help`` or ``mkng++.sh --usage``.
#### Manual
Open a terminal in the same directory as the makefile and run ``make ng++``. This will create an executable in ``src/deb/usr/local/bin/`` named ``numguesser++``
   
If your system has dpkg installed, you can then run ``make build-pkg`` to build and install a Debian package.
  
If your system does not have dpkg installed, or you do not wish to make a package, you can move the executable to ``/usr/bin`` to allow execution from anywhere.

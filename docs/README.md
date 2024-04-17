# Building from Source
## Prerequisites
- g++
- make 
- dpkg*
  
*Optional.
## Compiling
Open a terminal in the same directory as the makefile and run ``make``. This will create an executable in ``src/deb/usr/local/bin/`` named ``numguesser++``
   
If your system has dpkg installed, you can then run ``make build-pkg`` to build and install a Debian package.
  
If your system does not have dpkg installed, or you do not wish to make a package, you can move the executable to ``/usr/bin`` to allow execution from anywhere.

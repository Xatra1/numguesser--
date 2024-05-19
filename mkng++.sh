#!/bin/bash

# Behavior variables
buildpkg=false
generic=false

# Print the usage document and exit with status code $1
function usage() {
    cat <<-EOF
mkng++ - Helper script for compiling numguesser++
USAGE: mkng++.sh [-b -g]

-b, --build-pkg         Automatically builds and installs
                        a Debian package if dpkg is on your
                        system.

-g, --generic           Installs numguesser++ using the
                        generic 'install' command. Use this
                        as a fallback if -b fails.

-h, --help, --usage     Prints this help document and
                        exits.

If neither -b or -g are specified, both installation methods 
will be attempted.
EOF
    exit $1
}

# Parse arguments passed to the program
function argparse() {
    while [ $# -gt 0 ]; do
        opt=$1
        shift
        case $opt in
        -b | --build-pkg) buildpkg=true ;;
        -g | --generic) generic=true ;;
        -h | --help | --usage) usage 0 ;;
        *)
            if [ "${opt:0:1}" = "-" ]; then
                echo "mkng++: Invalid argument ${opt}"
                usage 1
            fi
            ;;
        esac
    done
}

argparse $*

if [ ! -f ./makefile ]; then
    echo -e '\e[33;1;31mfatal:\e[0m Makefile not found. Are you in the correct directory?'
    exit
fi

if [ ! -f /src/deb/usr/bin/numguesser++ ]; then
    mkdir src/deb/usr 2>/dev/null
    mkdir src/deb/usr/bin 2>/dev/null
fi

make

if [ $buildpkg = true ]; then
    make build-pkg
fi

if [ $generic = true ]; then
    make install
fi

if [ $buildpkg = false -a $generic = false ]; then
    make build-pkg || make install
fi

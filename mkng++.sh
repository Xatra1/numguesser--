#!/bin/bash
read -p "Clear the console before compiling? [y]es, [n]o, [c]ancel: " ans
if [[ "$ans" =~ ^([yY][eE][sS]|[yY])$ ]]; then clear; else if [[ "$ans" =~ ^([cC][aA][nN][cC][eE][lL]|[cC])$ ]]; then exit; fi; fi
if [ ! -f /src/deb/usr/local/bin/numguesser++ ]; then
    mkdir src/deb/usr 2>/dev/null
    mkdir src/deb/usr/local 2>/dev/null
    mkdir src/deb/usr/local/bin 2>/dev/null
fi
make
make build-pkg
echo -e '\e[33;1;37mExecuting ng++ with arguments $1 and $2\e[0m'
read -p "Clear the console before executing? [y]es, [n]o: " ans
if [[ "$ans" =~ ^([yY][eE][sS]|[yY])$ ]]; then clear; else echo; fi
ng++ $1 $2

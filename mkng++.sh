#!/bin/bash
read -p "Clear the console before compiling? (y/n): " ans
if [[ "$ans" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    clear
fi
cd ~/numguesser++
make
make build-pkg
echo -e '\e[33;1;37mExecuting ng++ with arguments $1 and $2\e[0m\n'
read -p "Clear the console before executing? (y/n): " ans
if [[ "$ans" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    clear
fi
ng++ $1 $2

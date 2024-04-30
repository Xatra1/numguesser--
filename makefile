CC=g++
DIR=src/deb/usr/local/bin/numguesser++
ng++: src/numguesser++.cpp src/deb/DEBIAN/control
	$(CC) -o $(DIR) src/numguesser++.cpp
build-pkg: $(DIR)
	if [ -f /usr/bin/numguesser++ ] || [ -f /usr/bin/ng++ ]; then yes | sudo apt-get remove numguesser++; fi
	dpkg-deb --build src/deb/
	sudo dpkg -i src/deb.deb
CC=g++
DIR=src/deb/usr/local/bin/numguesser++
numguesser: src/numguesser++.cpp src/deb/DEBIAN/control
	$(CC) -o $(DIR) src/numguesser++.cpp
build-pkg: $(DIR)
	dpkg-deb --build src/deb/
	sudo dpkg -i src/*.deb
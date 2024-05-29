# Binary directory paths
BINARY_DIR=src/deb/usr/bin/numguesser++
INSTALL_DIR=/usr/bin/numguesser++

# Binary aliases
BINARY_ALIAS=src/deb/usr/bin/ng++
INSTALL_ALIAS=/usr/bin/ng++

# Debian package directory
DEB_DIR=src/deb

# Source files
INPUT=src/numguesser++.cc
CONTROL=src/deb/DEBIAN/control

ng++: $(INPUT) $(CONTROL)
	c++ -o $(BINARY_DIR) $(INPUT)
	c++ -o $(BINARY_ALIAS) $(INPUT)

build-pkg: $(BINARY_DIR)
	dpkg-deb --build $(DEB_DIR)
	sudo apt-get install --reinstall ./$(DEB_DIR).deb
	@rm -v $(DEB_DIR).deb

install: $(BINARY_DIR)
	sudo install $(BINARY_DIR) $(INSTALL_DIR)
	sudo install $(BINARY_ALIAS) $(INSTALL_ALIAS)
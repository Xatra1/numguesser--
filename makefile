BINARY_DIR=src/deb/usr/bin/numguesser++
DEB_ALIAS=src/deb/usr/bin/ng++
INSTALL_DIR=/usr/bin/numguesser++
INSTALL_ALIAS=/usr/bin/ng++
DEB_DIR=src/deb
INPUT=src/numguesser++.cc
CONTROL=src/deb/DEBIAN/control

ng++: $(INPUT) $(CONTROL)
	c++ -o $(BINARY_DIR) $(INPUT)

build-pkg: $(BINARY_DIR)
	sudo ln -sf $(INSTALL_DIR) $(DEB_ALIAS)
	dpkg-deb --build $(DEB_DIR)
	sudo dpkg -i $(DEB_DIR).deb

install: $(BINARY_DIR)
	sudo install $(BINARY_DIR) $(INSTALL_DIR)
	sudo ln -sf $(INSTALL_DIR) $(INSTALL_ALIAS)
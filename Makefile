# Binary directory paths
BINARY_DIR=src/deb/usr/games/numguesser++
INSTALL_DIR=/usr/games/numguesser++

# Binary aliases
BINARY_ALIAS=src/deb/usr/games/ng++
INSTALL_ALIAS=/usr/games/ng++

# Debian package directory
DEB_DIR=src/deb

# Source files
INPUT=src/main.cc
CONTROL=src/deb/DEBIAN/control

ng++: $(INPUT) $(CONTROL)
	mkdir -p src/deb/usr/games
	c++ -o $(BINARY_DIR) $(INPUT)
	c++ -o $(BINARY_ALIAS) $(INPUT)

build-pkg: $(BINARY_DIR)
	@echo -e '\e[1;37mMaking directories...\e[0m'
	mkdir -p src/deb/usr/share/man/man1
	mkdir -p src/deb/usr/share/licenses/numguesser++
	@echo -e '\e[1;37mCompressing manpage...\e[0m'
	gzip -kf src/numguesser++.1
	@echo -e '\e[1;37mCopying files...\e[0m'
	cp src/numguesser++.1.gz $(DEB_DIR)/usr/share/man/man1
	cp LICENSE $(DEB_DIR)/usr/share/licenses/numguesser++
	@echo -e '\e[1;37mBuilding package...\e[0m'
	@dpkg-deb --build $(DEB_DIR) && echo -e '\e[1;37mThe Debian package is now built! You can install it with "sudo apt-get install ./src/deb.deb"\e[0m' || echo -e '\e[1;31mThe package failed to build. Exiting...'

install: $(BINARY_DIR)
	sudo install $(BINARY_DIR) $(INSTALL_DIR)
	sudo install $(BINARY_ALIAS) $(INSTALL_ALIAS)
	gzip -k src/numguesser++.1
	sudo install -Dm644 numguesser++.1.gz /usr/share/man/man1/numguesser++.1
	mkdir /usr/share/licenses/numguesser++
	sudo install -Dm644 LICENSE /usr/share/licenses/numguesser++

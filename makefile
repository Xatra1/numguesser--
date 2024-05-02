CC=g++
DIR=src/deb/usr/local/bin/numguesser++
INSTALL_DIR=/usr/bin/numguesser++
INSTALL_ALIAS_DIR=/usr/bin/ng++

ng++: src/numguesser++.cc src/deb/DEBIAN/control
	$(CC) -o $(DIR) src/numguesser++.cc

build-pkg: $(DIR)
	@echo -e '\e[33;1;37mAutomatically removing package if detected...\e[0m'
	if [ -f $(INSTALL_DIR) ] || [ -f $(INSTALL_ALIAS_DIR) ]; then yes | sudo apt-get remove numguesser++; fi

	@echo -e '\e[33;1;37mBuilding Debian package...\e[0m'
	dpkg-deb --build src/deb/

	@echo -e '\e[33;1;37mInstalling newly built package...\e[0m'
	sudo dpkg -i src/deb.deb
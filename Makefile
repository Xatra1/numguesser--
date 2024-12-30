# Binary directory paths
BINARY_DIR=numguesser++
INPUT=src/main.cc

ng++: $(INPUT)
	c++ -o $(BINARY_DIR) $(INPUT)

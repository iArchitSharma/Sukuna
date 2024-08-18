#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "lexer.h"  
#include "parser.h" 

using namespace std;

void main(int argc, char* argv[]) {
    cout << "Sukuna Compiler" << endl;

    if (argc != 2) {
        cerr << "Error: Compiler needs source file as argument." << endl;
        exit(EXIT_FAILURE);
    }

    // Open the source file.
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Could not open the file " << argv[1] << endl;
        exit(EXIT_FAILURE);
    }

    // Read the entire content of the file into a string.
    string source((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Initialize the lexer and parser.
    Lexer lexer(source);
    Parser parser(lexer);

    // Start the parser.
    parser.parse(); 
    cout << "Parsing completed." << endl;
}


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "lexer.h"
#include "emitter.h"
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Sukuna Compiler" << endl;

    if (argc != 2) {
        cerr << "Error: Compiler needs source file as argument." << endl;
        return EXIT_FAILURE;
    }

    // Open the source file.
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Could not open the file " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    // Read the entire content of the file into a string.
    string source((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Initialize the lexer, emitter, and parser.
    Lexer lexer(source);
    Emitter emitter("out.c");
    Parser parser(lexer, emitter);

    // Start the parser.
    parser.parse(); 
    emitter.writeFile(); 

    cout << "Compiling completed." << endl;

    return EXIT_SUCCESS;
}

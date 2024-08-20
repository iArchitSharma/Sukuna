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

    // Simple test for emitter
    Emitter emitter("test_out.c");
    emitter.headerLine("#include <stdio.h>");
    emitter.emitLine("int main() {");
    emitter.emitLine("    printf(\"Hello, World!\\n\");");
    emitter.emitLine("    return 0;");
    emitter.emitLine("}");
    emitter.writeFile();

    cout << "Compiling completed." << endl;

    return EXIT_SUCCESS;
}

#ifndef EMITTER_H
#define EMITTER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Emitter object keeps track of the generated code and outputs it.

class Emitter {
private:
    string fullPath;
    string header;
    string code;
public:
    Emitter(const string& filePath): fullPath(filePath), header(""), code(""){}

    void emit(const string& newCode){
        code += newCode;
    }

    void emitLine(const string& newCode){
        code += newCode + '\n';
    }

    void headerLine(const std::string& newCode) {
        header += newCode + '\n';
    }

    void writeFile(){
        ofstream outputFile(fullPath);
        if(outputFile.is_open()){
            outputFile << header << code;
            outputFile.close();
        }else{
            cerr << "Error: Could not open file " << fullPath << " for writing." << endl;
        }
    }
};


#endif
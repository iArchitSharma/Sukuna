#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <set>
#include <string>
#include <cstdlib>
#include "lexer.h"
#include "emitter.h"
using namespace std;

// Convert TokenType to string for error messages
string tokenTypeToString(TokenType type) {
    switch(type) {
        case TokenType::PRINT: return "PRINT";
        case TokenType::IF: return "IF";
        // Add more cases for your token types
        default: return "UNKNOWN";
    }
}

// Parser object keeps track of current token and checks if the code matches the grammar
class Parser {
private:
    Lexer lexer;
    Emitter emitter;
    Token curToken;
    Token peekToken;
    set<string> symbols;        // All variables we have declared so far
    set<string> labelsDeclared; // Keep track of all labels declared
    set<string> labelsGotoed;   // All labels goto'ed, so we know if they exist or not

    // Return true if the current token matches
    bool checkToken(TokenType kind) {
        return kind == curToken.kind;
    }

    // Return true if the next token matches
    bool checkPeek(TokenType kind) {
        return kind == peekToken.kind;
    }

    // Try to match current token. If not, error. Advances the current token
    void match(TokenType kind) {
        if(!checkToken(kind)) {
            abort("Expected " + tokenTypeToString(kind) + ", got " + tokenTypeToString(curToken.kind));
        }
        nextToken();
    }

    // Advances the current token
    void nextToken() {
        curToken = peekToken;
        peekToken = lexer.getToken();
    }

    void abort(const string& message) {
        cerr << "Error: " << message << endl;
        exit(EXIT_FAILURE);
    }

    // Return true if the current token is a comparison operator
    bool isComparisonOperator() {
        return checkToken(TokenType::GT) || checkToken(TokenType::GTEQ) || 
               checkToken(TokenType::LT) || checkToken(TokenType::LTEQ) || 
               checkToken(TokenType::EQEQ) || checkToken(TokenType::NOTEQ);
    }

    // Production rules.
    // program ::= {statement}

    void program() {
        emitter.headerLine("#include <stdio.h>");
        emitter.headerLine("int main(void) {");

        //Since some newlines are required in our grammar, need to skip the excess
        while (checkToken(TokenType::NEWLINE)) {
            nextToken();
        }
        // Parse all the statements in the program
        while (!checkToken(TokenType::END_OF_FILE)) {
            statement();
        }

        emitter.emitLine("return 0;");
        emitter.emitLine("}");

        for (const auto& label : labelsGotoed) {
            if (labelsDeclared.find(label) == labelsDeclared.end()) {
                abort("Attempting to GOTO undeclared label: " + label);
            }
        }
    }

    // One of the following statements...
    void statement() {
        if (checkToken(TokenType::PRINT)) {
            nextToken();
            if (checkToken(TokenType::STRING)) {
                emitter.emitLine("printf(\"" + curToken.text + "\\n\");");
                nextToken();
            } else {
                emitter.emit("printf(\"%.2f\\n\", (float)(");
                expression();
                emitter.emitLine("));");
            }
        } else if (checkToken(TokenType::IF)) {
            nextToken();
            emitter.emit("if(");
            comparison();
            match(TokenType::THEN);
            nl();
            emitter.emitLine("){");

            while (!checkToken(TokenType::ENDIF)) {
                statement();
            }
            match(TokenType::ENDIF);
            emitter.emitLine("}");
            //"WHILE" comparison "REPEAT" block "ENDWHILE"
        } else if (checkToken(TokenType::WHILE)) {
            nextToken();
            emitter.emit("while(");
            comparison();
            match(TokenType::REPEAT);
            nl();
            emitter.emitLine("){");

            while (!checkToken(TokenType::ENDWHILE)) {
                statement();
            }
            match(TokenType::ENDWHILE);
            emitter.emitLine("}");
        } else if (checkToken(TokenType::LABEL)) {
            nextToken();

            if (labelsDeclared.find(curToken.text) != labelsDeclared.end()) {
                abort("Label already exists: " + curToken.text);
            }

            labelsDeclared.insert(curToken.text);
            emitter.emitLine(curToken.text + ":");
            match(TokenType::IDENT);
        } else if (checkToken(TokenType::GOTO)) {
            nextToken();
            labelsGotoed.insert(curToken.text);
            emitter.emitLine("goto " + curToken.text + ";");
            match(TokenType::IDENT);
        } else if (checkToken(TokenType::LET)) {
            nextToken();

            if (symbols.find(curToken.text) == symbols.end()) {
                symbols.insert(curToken.text);
                emitter.headerLine("float " + curToken.text + ";");
            }

            emitter.emit(curToken.text + " = ");
            match(TokenType::IDENT);
            match(TokenType::EQ);
            expression();
            emitter.emitLine(";");
        } else if (checkToken(TokenType::INPUT)) {
            nextToken();

            if (symbols.find(curToken.text) == symbols.end()) {
                symbols.insert(curToken.text);
                emitter.headerLine("float " + curToken.text + ";");
            }

            emitter.emitLine("if(0 == scanf(\"%f\", &" + curToken.text + ")) {");
            emitter.emitLine(curToken.text + " = 0;");
            emitter.emit("scanf(\"%");
            emitter.emitLine("*s\");");
            emitter.emitLine("}");
            match(TokenType::IDENT);
        } else {
            abort("Invalid statement at " + curToken.text + " (" + tokenTypeToString(curToken.kind) + ")");
        }

        nl();
    }

    void comparison() {
        expression();

        if (isComparisonOperator()) {
            emitter.emit(curToken.text);
            nextToken();
            expression();
        } else {
            abort("Expected comparison operator at: " + curToken.text);
        }

        while (isComparisonOperator()) {
            emitter.emit(curToken.text);
            nextToken();
            expression();
        }
    }

    void expression() {
        term();

        while (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)) {
            emitter.emit(curToken.text);
            nextToken();
            term();
        }
    }

    void term() {
        unary();

        while (checkToken(TokenType::ASTERISK) || checkToken(TokenType::SLASH)) {
            emitter.emit(curToken.text);
            nextToken();
            unary();
        }
    }

    void unary() {

        if (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)) {
            emitter.emit(curToken.text);
            nextToken();
        }

        primary();
    }

    void primary() {

        if (checkToken(TokenType::NUMBER)) {
            emitter.emit(curToken.text);
            nextToken();
        } else if (checkToken(TokenType::IDENT)) {
            if (symbols.find(curToken.text) == symbols.end()) {
                abort("Referencing variable before assignment: " + curToken.text);
            }

            emitter.emit(curToken.text);
            nextToken();
        } else {
            abort("Unexpected token at " + curToken.text);
        }
    }

    void nl() {
        match(TokenType::NEWLINE);

        while (checkToken(TokenType::NEWLINE)) {
            nextToken();
        }
    }

public:
    Parser(Lexer lexer, Emitter emitter)
        : lexer(lexer),
          emitter(emitter),
          curToken("", TokenType::END_OF_FILE),
          peekToken("", TokenType::END_OF_FILE) {
        nextToken();
        nextToken(); // Call this twice to initialize current and peek
    }

    void parse() {
        program();
    }
};


#endif
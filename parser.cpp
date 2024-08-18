#include <iostream>
#include <set>
#include <string>
#include <cstdlib>
#include "lexer.h"
using namespace std;

//Parser object keeps track of current token and checks if the code matches the grammar
class Parser {
private:
    Lexer lexer;
    Token curToken;
    Token peekToken;
    set<string> symbols;        //All variables we have declared so far
    set<string> labelsDeclared; //Keep track of all labels declared
    set<string> labelsGotoed; //All labels goto'ed, so we know if they exist or not

    // Return true if the current token matches
    bool checkToken(TokenType kind){
        return kind == curToken.kind;
    }

    // Return true if the next token matches
    bool checkPeek(TokenType kind){
        return kind == peekToken.kind;
    }

    //Try to match current token. If not, error. Advances the current token
    void match(TokenType kind){
        if(!checkToken(kind)){
            abort("Expected " + tokenTypeToString(kind) + ", got " + tokenTypeToString(curToken.kind));
        }
        nextToken();
    }

    //Advances the current token
    void nextToken(){
        curToken = peekToken;
        peekToken = lexer.getToken();
    }

    void abort(const string& message){
        cerr << "Error: " << message <<endl;
        exit(EXIT_FAILURE);
    }

    //Return true if the current token is a comparison operator
    bool isComparisonOperator(){
        return checkToken(TokenType::GT) || checkToken(TokenType::GTEQ) || 
               checkToken(TokenType::LT) || checkToken(TokenType::LTEQ) || 
               checkToken(TokenType::EQEQ) || checkToken(TokenType::NOTEQ);
    }

    // Production rules.
    // program ::= {statement}

    void program(){
        cout << "PROGRAM" << endl;

        while (checkToken(TokenType::NEWLINE))
        {
            nextToken();
        }
        // Parse all the statements in the program
        while(!checkToken(TokenType::END_OF_FILE)){
            statement();
        }

        for(const auto& label : labelsGotoed){
            if(labelsDeclared.find(label) == labelsDeclared.end()){
                abort("Attempting to GOTO undeclared label: " + label);
            }
        }
        
    }
    //One of the following statements...
    void statement(){
        //Check the first token to see what kind of statement this is

        //"PRINT" (expression | string)
        if(checkToken(TokenType::PRINT)){
            cout << "STATEMENT-PRINT" << endl;
            nextToken();
            if(checkToken(TokenType::STRING)){
                nextToken();
            }else{
                expression();
            }
        }else if(checkToken(TokenType::IF)){
            cout << "STATEMENT-IF" <<endl;
            nextToken();
            comparison();
            match(TokenType::THEN);
            nl();

            while(!checkToken(TokenType::ENDIF)){
                statement();
            }
            match(TokenType::ENDIF);
        }else if(checkToken(TokenType::WHILE)){
            cout << "STATEMENT-WHILE" << endl;
            nextToken();
            comparison();
            match(TokenType::REPEAT);
            nl();

            while(!checkToken(TokenType::ENDWHILE)){
                statement();
            }
            match(TokenType::ENDWHILE);
        }else if(checkToken(TokenType::LABEL)) {
            cout << "STATEMENT-LABEL" << endl;
            nextToken();

            if (labelsDeclared.find(curToken.text) != labelsDeclared.end()) {
                abort("Label already exists: " + curToken.text);
            }

            labelsDeclared.insert(curToken.text);
            match(TokenType::IDENT);
        } else if (checkToken(TokenType::GOTO)) {
            cout << "STATEMENT-GOTO" << endl;
            nextToken();
            labelsGotoed.insert(curToken.text);
            match(TokenType::IDENT);
        } else if (checkToken(TokenType::LET)) {
            cout << "STATEMENT-LET" << endl;
            nextToken();

            if (symbols.find(curToken.text) == symbols.end()) {
                symbols.insert(curToken.text);
            }

            match(TokenType::IDENT);
            match(TokenType::EQ);
            expression();
        } else if (checkToken(TokenType::INPUT)) {
            cout << "STATEMENT-INPUT" << endl;
            nextToken();

            if (symbols.find(curToken.text) == symbols.end()) {
                symbols.insert(curToken.text);
            }

            match(TokenType::IDENT);
        } else {
            abort("Invalid statement at " + curToken.text + " (" + tokenTypeToString(curToken.kind) + ")");
        }

        nl();
    }
    void comparison() {
        cout << "COMPARISON" << endl;
        expression();

        if (isComparisonOperator()) {
            nextToken();
            expression();
        } else {
            abort("Expected comparison operator at: " + curToken.text);
        }

        while (isComparisonOperator()) {
            nextToken();
            expression();
        }
    }

    void expression() {
        cout << "EXPRESSION" << endl;
        term();

        while (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)) {
            nextToken();
            term();
        }
    }

    void term() {
        cout << "TERM" << endl;
        unary();

        while (checkToken(TokenType::ASTERISK) || checkToken(TokenType::SLASH)) {
            nextToken();
            unary();
        }
    }

    void unary() {
        cout << "UNARY" << endl;

        if (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)) {
            nextToken();
        }

        primary();
    }

    void primary() {
        cout << "PRIMARY (" << curToken.text << ")" << endl;

        if (checkToken(TokenType::NUMBER)) {
            nextToken();
        } else if (checkToken(TokenType::IDENT)) {
            if (symbols.find(curToken.text) == symbols.end()) {
                abort("Referencing variable before assignment: " + curToken.text);
            }

            nextToken();
        } else {
            abort("Unexpected token at " + curToken.text);
        }
    }

    void nl() {
        cout << "NEWLINE" << endl;
        match(TokenType::NEWLINE);

        while (checkToken(TokenType::NEWLINE)) {
            nextToken();
        }
    }

public:
    Parser(Lexer lexer): lexer(lexer) {
        nextToken();
        nextToken();     // Call this twice to initialize current and peek
    }

    void parse() {
        program();
    }
};

int main() {
    string input = "LET x = 10\nPRINT x\n";
    Lexer lexer(input);
    Parser parser(lexer);
    parser.parse();
    return 0;
}
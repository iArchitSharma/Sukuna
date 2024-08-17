#include <iostream>
#include "lexer.h"
using namespace std;

int main()
{
  string input = "LET x = 10\nPRINT x\n";
  Lexer lexer(input);

  Token token = lexer.getToken();
  while (token.kind != TokenType::END_OF_FILE)
  {
    cout << "Token: " << token.text << ", Type: " << static_cast<int>(token.kind) << endl;
    token = lexer.getToken();
  }
  return 0;
}

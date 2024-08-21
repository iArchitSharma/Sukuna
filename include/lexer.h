#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <map>
#include <optional>
using namespace std;

enum class TokenType
{
  END_OF_FILE = -1,
  NEWLINE = 0,
  NUMBER = 1,
  IDENT = 2,
  STRING = 3,
  // Keywords
  LABEL = 101,
  GOTO = 102,
  PRINT = 103,
  INPUT = 104,
  LET = 105,
  IF = 106,
  THEN = 107,
  ENDIF = 108,
  WHILE = 109,
  REPEAT = 110,
  ENDWHILE = 111,
  // Operators
  EQ = 201,
  PLUS = 202,
  MINUS = 203,
  ASTERISK = 204,
  SLASH = 205,
  EQEQ = 206,
  NOTEQ = 207,
  LT = 208,
  LTEQ = 209,
  GT = 210,
  GTEQ = 211
};

// Token contains the original text and the type of token
class Token
{
public:
  string text;
  TokenType kind;
  Token(string tokenText, TokenType tokenKind) : text(tokenText), kind(tokenKind) {}

  static optional<TokenType> checkIfKeyword(const string &tokenText)
  {
    static map<string, TokenType> keywords = {
        {"LABEL", TokenType::LABEL},
        {"GOTO", TokenType::GOTO},
        {"PRINT", TokenType::PRINT},
        {"INPUT", TokenType::INPUT},
        {"LET", TokenType::LET},
        {"IF", TokenType::IF},
        {"THEN", TokenType::THEN},
        {"ENDIF", TokenType::ENDIF},
        {"WHILE", TokenType::WHILE},
        {"REPEAT", TokenType::REPEAT},
        {"ENDWHILE", TokenType::ENDWHILE}};

    auto it = keywords.find(tokenText);
    if (it != keywords.end())
    {
      return it->second;
    }
    return nullopt;
  }
};

class Lexer
{
public:
  Lexer(const string &input) : source(input + '\n'), curChar('\0'), curPos(-1)
  {
    nextChar();
  }

  //  Return the next token
  Token getToken()
  {
    skipWhitespace();
    skipComment();

    Token token("", TokenType::END_OF_FILE);
    if (curChar == '+')
    {
      token = Token(string(1, curChar), TokenType::PLUS);
    }
    else if (curChar == '-')
    {
      token = Token(string(1, curChar), TokenType::MINUS);
    }
    else if (curChar == '*')
    {
      token = Token(string(1, curChar), TokenType::ASTERISK);
    }
    else if (curChar == '/')
    {
      token = Token(string(1, curChar), TokenType::SLASH);
    }
    else if (curChar == '=')
    {
      if (peek() == '=')
      {
        char lastChar = curChar;
        nextChar();
        token = Token(string(1, lastChar) + curChar, TokenType::EQEQ);
      }
      else
      {
        token = Token(string(1, curChar), TokenType::EQ);
      }
    }
    else if (curChar == '>')
    {
      if (peek() == '=')
      {
        char lastChar = curChar;
        nextChar();
        token = Token(string(1, lastChar) + curChar, TokenType::GTEQ);
      }
      else
      {
        token = Token(string(1, curChar), TokenType::GT);
      }
    }
    else if (curChar == '<')
    {
      if (peek() == '=')
      {
        char lastChar = curChar;
        nextChar();
        token = Token(string(1, lastChar) + curChar, TokenType::LTEQ);
      }
      else
      {
        token = Token(string(1, curChar), TokenType::LT);
      }
    }
    else if (curChar == '!')
    {
      if (peek() == '=')
      {
        char lastChar = curChar;
        nextChar();
        token = Token(string(1, lastChar) + curChar, TokenType::NOTEQ);
      }
      else
      {
        abort("Expected !=, got !" + string(1, peek()));
      }
    }
    else if (curChar == '\"')
    {
      nextChar();
      int startPos = curPos;

      while (curChar != '\"')
      {
        if (curChar == '\r' || curChar == '\n' || curChar == '\t' || curChar == '\\' || curChar == '%')
        {
          abort("Illegal character in string.");
        }
        nextChar();
      }

      token = Token(source.substr(startPos, curPos - startPos), TokenType::STRING);
    }
    else if (isdigit(curChar))
    {
      int startPos = curPos;
      while (isdigit(peek()))
      {
        nextChar();
      }
      if (peek() == '.')
      {
        nextChar();

        if (!isdigit(peek()))
        {
          abort("Illegal character in number.");
        }
        while (isdigit(peek()))
        {
          nextChar();
        }
      }

      token = Token(source.substr(startPos, curPos - startPos + 1), TokenType::NUMBER);
    }
    else if (isalpha(curChar))
    {
      int startPos = curPos;
      while (isalnum(peek()))
      {
        nextChar();
      }

      string tokText = source.substr(startPos, curPos - startPos + 1);
      optional<TokenType> keyword = Token::checkIfKeyword(tokText);
      if (keyword)
      {
        token = Token(tokText, *keyword);
      }
      else
      {
        token = Token(tokText, TokenType::IDENT);
      }
    }
    else if (curChar == '\n')
    {
      token = Token(string(1, curChar), TokenType::NEWLINE);
    }
    else if (curChar == '\0')
    {
      token = Token("", TokenType::END_OF_FILE);
    }
    else
    {
      abort("Unknown token: " + string(1, curChar));
    }

    nextChar();
    return token;
  }

private:
  string source;
  char curChar;
  size_t curPos;

  // Process the next character.
  void nextChar()
  {
    curPos++;
    if (curPos >= source.length())
    {
      curChar = '\0';
    }
    else
    {
      curChar = source[curPos];
    }
  }

  // Return the lookahead character
  char peek() const
  {
    if (curPos + 1 >= source.length())
    {
      return '\0';
    }
    return source[curPos + 1];
  }
  // Invalid token found, print error message and exit
  void abort(const string &message) const
  {
    cerr << "Lexing error: " << message << endl;
    exit(EXIT_FAILURE);
  }
  // Skip whitespace except newlines, which we will use to indicate the end of a statement
  void skipWhitespace()
  {
    while (curChar == ' ' || curChar == '\t' || curChar == '\r')
    {
      nextChar();
    }
  }

  void skipComment()
  {
    if (curChar == '#')
    {
      while (curChar != '\n')
      {
        nextChar();
      }
    }
  }
};


#endif // LEXER_H

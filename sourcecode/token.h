#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token {
public:
    Token();
    Token(string argLexeme, string argType, int argRow, int argColumn);
    string lexeme;
    string type;
    string value;
    int row;
    int column;
    int length;
};

#endif

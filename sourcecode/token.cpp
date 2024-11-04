#include "token.h"

using namespace std;

Token::Token(){
    lexeme = "";
    type = "";
    value = "";
    row = 0;
    column = 0;
    length = 0;
}

Token::Token(string argLexeme, string argType, int argRow, int argColumn){
    lexeme = argLexeme;
    type = argType;
    value = argLexeme; // unless... certain types of tokens need to be stored differently
    row = argRow;
    column = argColumn;
    length = argLexeme.size();
}

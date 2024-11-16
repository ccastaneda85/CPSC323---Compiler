#ifndef LEXER2_H
#define LEXER2_H
#include <string>
#include <iostream>

class LexicalAnalyzer {
    private:
        int p1;
        int p2;
        bool specialSymbol(const char &input);
        bool doubleOperator(const char &input);
        bool isKeyword(const std::string &input);

    public:

    LexicalAnalyzer();

};


#endif //LEXER2_H
#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include <string>
#include <vector>
#include <stack>
#include "token.h"

class SyntaxAnalyzer {
private:
    std::vector<Token> tokenStream;
    size_t currentTokenIndex;
    std::stack<std::string> parseStack;

public:
    // Constructor
    SyntaxAnalyzer(std::vector<Token> tokens);
    
    // Main parsing function
    bool parse();

private:
    // Helper functions for stack-based parsing
    void parseProgram();
    void parseStatementList();
    void parseStatement();
    
    // Token management functions
    Token getCurrentToken() const;
    bool hasMoreTokens() const;
    void advance();
    bool match(const std::string& expected);
};

#endif // SYNTAXANALYZER_H
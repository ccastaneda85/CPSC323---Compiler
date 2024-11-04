#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "token.h"

using namespace std;

class LexicalAnalyzer {
private:
    int position;
    vector<Token> tokenStream;
    void generateDefinedTokens();
    unordered_map<string, string> cppTokenMap;

public:
    LexicalAnalyzer(string argcharacterStream);
    bool isKeyword(char argWord);
    void keywordMapper(char argKeyword);
    void characterStreamTo2DTokenVec(string argcharacterStream);
    void wordsVecToTokenStream(vector<vector<string> > argWordsVec);
    bool isWhitespace(char argLexeme);
    bool isTwoCharOperator(string argSubString);
    vector<Token> getTokenStream();
    void printTokenStream();
};

#endif

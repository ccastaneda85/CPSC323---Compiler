#include <vector>
#include <string>
#include <stack>
#include "syntaxanalyzer.h"
#include <iostream>

// Constructor takes the token stream from lexical analyzer
SyntaxAnalyzer::SyntaxAnalyzer(std::vector<Token> tokens) {
    tokenStream = tokens;
    currentTokenIndex = 0;
}

// Get current token
Token SyntaxAnalyzer::getCurrentToken() const {
    if (currentTokenIndex < tokenStream.size()) {
        return tokenStream[currentTokenIndex];
    }
    return Token(); // Return empty token if we're at the end
}

// Move to next token
void SyntaxAnalyzer::advance() {
    if (currentTokenIndex < tokenStream.size()) {
        currentTokenIndex++;
    }
}

// Check if we've reached the end of the token stream
bool SyntaxAnalyzer::hasMoreTokens() const {
    return currentTokenIndex < tokenStream.size();
}

// Parse the program
bool SyntaxAnalyzer::parse() {
    parseStack.push("PROGRAM");
    while (!parseStack.empty()) {
        std::string top = parseStack.top();
        parseStack.pop();

        if (top == "PROGRAM") {
            parseProgram();
        } else if (top == "STATEMENT_LIST") {
            parseStatementList();
        } else if (top == "STATEMENT") {
            parseStatement();
        } else {
            std::cerr << "Unknown grammar rule: " << top << std::endl;
            return false;
        }
    }
    return true;
}

// Example parsing methods - customize these based on your grammar
void SyntaxAnalyzer::parseProgram() {
    // Add your grammar rules here
    // For example:
    // program → statement_list
    parseStack.push("STATEMENT_LIST");
}

void SyntaxAnalyzer::parseStatementList() {
    // Add implementation based on your grammar
    // For example:
    // statement_list → statement statement_list | ε
    if (hasMoreTokens()) {
        parseStack.push("STATEMENT_LIST");
        parseStack.push("STATEMENT");
    }
}

void SyntaxAnalyzer::parseStatement() {
    // Add implementation based on your grammar
    // This is where you'll handle different types of statements
    Token currentToken = getCurrentToken();
    // Add your statement parsing logic here
    advance();
}

bool SyntaxAnalyzer::match(const std::string& expected) {
    if (getCurrentToken().value == expected) {
        advance();
        return true;
    }
    return false;
}
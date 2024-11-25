//lexer.ch
#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<unordered_map>
#include "utilities.h"
#include "token.h"
#include "symboltable.h"

using namespace std;

unordered_map<string, string> tokenMap = {
        {"do", "do"},
        {"if", "if"},
        {"else", "else"},
        {"while", "while"},
        {"break", "break"},
        {"main", "main"},
        {"float", "basic"},
        {"int", "basic"},
        {"char", "basic"},
        {"void", "basic"},
        {"++", "++"},         
        {"--", "--"},         
        {"<=", "<="},        
        {">=", ">="},     
        {"==", "=="},        
        {"&&", "&&"}, 
        {"||", "||"},
        {"!=", "!="},       
        {"(", "("},
        {")", ")"},
        {"[", "["},
        {"]", "]"},
        {"{", "{"},
        {"}", "}"},
        {".", "."},
        {"+", "+"},
        {"-", "-"},
        {"*", "*"},
        {"/", "/"},
        {"%", "%"},
        {"<", "<"},
        {">", ">"},
        {"=", "="},
        {";", ";"},
        {",", ","},
        {"!", "!"},
        {"&", "&"},
        {"|", "|"}
};


bool specialSymbols(const char &ch) {
   return (ch == '+' || ch == '-' || ch == '<' || ch == '>' || ch == '=' || ch == '&' || ch == '|' || ch == '!');
}

bool doubleOperator(string doubleOp) {
    return (doubleOp == "==" || doubleOp == "++" || doubleOp == "--" || 
    doubleOp == "&&" || doubleOp == "||" || doubleOp == "<=" || doubleOp == ">=" || doubleOp == "!=");
}


vector<Token> lexicalAnalyzer(const string& inputString) {
    istringstream inputStream(inputString);
    vector<Token> tokenStream;
    string line;
    int linecount = 1;

    while (getline(inputStream, line)) {
        
        int p1 = 0;
        int p2 = 0;
        Token currToken;
        

        
        while(p1 < line.size()) {
        
            while (p1 < line.size() && isspace(line[p1])) {
                p1++;
            }
           
           if(p1 >= line.size()) {
                break;
           }

            //Identifier DFA
            if(isalpha(line[p1])) { 
                p2 = p1;
                while(p2 < line.size() && isalnum(line[p2])) {  
                    p2++;   
                } //Check to see if identifier is a keyword
                if (tokenMap.find(line.substr(p1, p2 - p1)) != tokenMap.end()) {
                    string tokenType = tokenMap[line.substr(p1, p2 - p1)];
                    currToken.setValues(line.substr(p1, p2 - p1), tokenType, linecount, p1, p2 - p1);
                    tokenStream.push_back(currToken);
                } else {
                    currToken.setValues(line.substr(p1, p2 - p1), "id", linecount, p1, p2 - p1);
                    tokenStream.push_back(currToken);
                }
                p1 = p2;
            }//Number DFA
            else if (isdigit(line[p1])) { 
                
                p2 = p1;
                
                while (p2 < line.size() && isdigit(line[p2])) {
                    p2++;
                } //Checking to see if decimal/real number didnt account for negative numbers because it has not been specified. May need to fix later 
                if (line[p2] == '.' && p2 + 1 < line.size() && isdigit(line[p2 + 1])) {
                    do {
                        p2++;
                    } while(isdigit(line[p2]) && p2 < line.size());
                    
                    currToken.setValues(line.substr(p1, p2 - p1), "real", linecount, p1, p2 - p1);
                    tokenStream.push_back(currToken);
                    
                }
                else {
                    
                    currToken.setValues(line.substr(p1, p2 - p1), "num", linecount, p1, p2 - p1);
                    tokenStream.push_back(currToken);
                }
                p1 = p2;
            }//Comment DFA
            else if (p1 + 1 < line.size() && line[p1] == '/' && line[p1 + 1] == '/') { 
                while (p1 < line.size() && line[p1] != '\n') {
                    p1++;
                }
            }//Double Operator DFA
            else if (p1 + 1 < line.size() && specialSymbols(line[p1])) {
                string characterPair = line.substr(p1, 2);
                if(doubleOperator(characterPair)){
                    string tokenType = tokenMap[characterPair];
                    currToken.setValues(line.substr(p1, 2), tokenType, linecount, p1, 2);
                    tokenStream.push_back(currToken);
                    
                    p1 += 2;
                }
                else{
                    string tokenType = tokenMap[line.substr(p1, 1)];
                    currToken.setValues(line.substr(p1, 1), tokenType, linecount, p1, 1);
                    tokenStream.push_back(currToken);
                    
                    p1++;
                }         
            }//All other Trivial DFA's
            else {
                if (tokenMap.find(line.substr(p1, 1)) != tokenMap.end()) {
                    string tokenType = tokenMap[line.substr(p1, 1)];
                    currToken.setValues(line.substr(p1, 1), tokenType, linecount, p1, 1);
                    tokenStream.push_back(currToken);
                    
                } else {
                    currToken.setValues(line.substr(p1, 1), "Unknown Token", linecount, p1, 1);
                    tokenStream.push_back(currToken);
                    
                }
                p1++;
            }
            
        }
       
        linecount++;
    }

    return tokenStream;
}


#endif //LEXICALANALYZER_H
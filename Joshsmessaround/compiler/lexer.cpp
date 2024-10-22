#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<unordered_map>
#include "utilities.h"

using namespace std;

vector<pair<string, string> > lexicalAnalyzer(const string& inputString);
bool specialSymbols(char &ch);


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


vector<pair<string, string> > lexicalAnalyzer(const string& inputString) {
    vector<pair<string, string> > lexemeTokenStream;
    int p1 = 0;
    int p2 = 0;

    while (p1 < inputString.size()) {
        while (p1 < inputString.size() && isspace(inputString[p1])) {
            p1++;
        }

        //Identifier DFA
        if(isalpha(inputString[p1])) { 
            p2 = p1;
            while(p2 < inputString.size() && isalnum(inputString[p2])) {  
                p2++;   
            }
            if (tokenMap.find(inputString.substr(p1, p2 - p1)) != tokenMap.end()) {
                string token = tokenMap[inputString.substr(p1, p2 - p1)];
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), token));
            } else {
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), "id"));
            }
            p1 = p2;
        }//Number DFA
        else if (isdigit(inputString[p1])) { 
            p2 = p1;
            while (p2 < inputString.size() && isdigit(inputString[p2])) {
                p2++;
            }
            if (inputString[p2] == '.') {
                do {
                    p2++;
                } while(isdigit(inputString[p2]));
                
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), "real"));
            }
            else {
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), "num"));
            }
            p1 = p2;
        }//Comment DFA
        else if (p1 + 1 < inputString.size() && inputString[p1] == '/' && inputString[p1 + 1] == '/') { 
            while (p1 < inputString.size() && inputString[p1] != '\n') {
                p1++;
            }
        }//Double Operator DFA
        else if (p1 + 1 < inputString.size() && specialSymbols(inputString[p1])) {
            string characterPair = inputString.substr(p1, 2);
            if(doubleOperator(characterPair)){
                string token = tokenMap[characterPair];
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, 2), token));
                p1 += 2;
            }
            else{
                string token = tokenMap[inputString.substr(p1, 1)];
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, 1), token));
                p1++;
            }         
        }//All other Trivial DFA's
        else {
            if (tokenMap.find(inputString.substr(p1, 1)) != tokenMap.end()) {
                string token = tokenMap[inputString.substr(p1, 1)];
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, 1), token));
            } else {
                lexemeTokenStream.push_back(make_pair(inputString.substr(p1, 1), "Unknown Token"));
            }
            p1++;
        }
    }

    return lexemeTokenStream;
}

int main(int argc, char const *argv[]) {
    vector<pair<string, string> > lexemeTokenStream;
    string testString = fileReader("testcases/case1.txt");

    lexemeTokenStream = lexicalAnalyzer(testString);

    cout << left << setw(8) << "Lexeme:" << "\t" << left << setw(5) << "Token:" << endl;
    

    for (int i = 0; i < lexemeTokenStream.size(); i++) {
        cout << left << setw(8) << lexemeTokenStream.at(i).first << "\t" << left << setw(5) <<lexemeTokenStream.at(i).second << endl;
    }

    return 0;
}

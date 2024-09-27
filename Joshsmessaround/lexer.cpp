#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<utility>
#include<unordered_map>

using namespace std;

string fileReader(const string& filename);
vector<pair<string, string> > lexicalAnalyzer(const string& inputString);
bool specialSymbols(char &ch);


unordered_map<string, string> tokenMap = {
        {"++", "increment"},         
        {"--", "decrement"},         
        {"<=", "lessThanEq"},        
        {">=", "greaterThanEq"},     
        {"==", "logicEqual"},        
        {"&&", "logicAnd"}, 
        {"||", "logicOr"},       
        {"(", "leftParen"},
        {")", "rightParen"},
        {"[", "leftBracket"},
        {"]", "rightBracket"},
        {"{", "leftBrace"},
        {"}", "rightBrace"},
        {".", "dot"},
        {"+", "plus"},
        {"-", "minus"},
        {"*", "multiply"},
        {"/", "divide"},
        {"%", "modulus"},
        {"<", "lessThan"},
        {">", "greaterThan"},
        {"=", "assignment"},
        {";", "semicolon"},
        {",", "comma"},
        {"!", "logicNot"},
        {"&", "bitAnd"},
        {"|", "bitOr"}
};

string fileReader(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

bool specialSymbols(const char &ch) {
   return (ch == '+' || ch == '-' || ch == '<' || ch == '>' || ch == '=' || ch == '&' || ch == '|');
}

bool doubleOperator(string doubleOp) {
    return (doubleOp == "==" || doubleOp == "++" || doubleOp == "--" || 
    doubleOp == "&&" || doubleOp == "||" || doubleOp == "<=" || doubleOp == ">=");
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
            lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), "Identifier"));
            p1 = p2;
        }//Number DFA
        else if (isdigit(inputString[p1])) { 
            p2 = p1;
            while (p2 < inputString.size() && isdigit(inputString[p2])) {
                p2++;
            }
            lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), "Number"));
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
    string testString = fileReader("front.in");

    lexemeTokenStream = lexicalAnalyzer(testString);

    for (int i = 0; i < lexemeTokenStream.size(); i++) {
        cout << lexemeTokenStream.at(i).first << " -> " << lexemeTokenStream.at(i).second << endl;
    }

    return 0;
}

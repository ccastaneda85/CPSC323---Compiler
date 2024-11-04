#include "lexicalanalyzer.h"

using namespace std;   


// constructor
LexicalAnalyzer::LexicalAnalyzer(string argcharacterStream)
{
    generateDefinedTokens();
    characterStreamTo2DTokenVec(argcharacterStream);
    printTokenStream();

};

void LexicalAnalyzer::generateDefinedTokens()
{
    // quote tokens
    cppTokenMap["("] = "(";
    cppTokenMap[")"] = ")";
    cppTokenMap["["] = "]";
    cppTokenMap["]"] = "]";
    cppTokenMap["{"] = "{";
    cppTokenMap["}"] = "}";
    // operator tokens
    cppTokenMap["."] = ".";
    cppTokenMap["+"] = "+";
    cppTokenMap["-"] = "-";
    cppTokenMap["*"] = "*";
    cppTokenMap["/"] = "/";
    cppTokenMap["%"] = "%";
    cppTokenMap["<"] = "<";
    cppTokenMap[">"] = ">";
    cppTokenMap["="] = "=";
    cppTokenMap[";"] = ";";
    cppTokenMap[","] = ",";
    // comparison tokens
    cppTokenMap["++"] = "++";
    cppTokenMap["--"] = "--";
    cppTokenMap["<="] = "<=";
    cppTokenMap[">="] = ">=";
    cppTokenMap["!="] = "!=";
    cppTokenMap["=="] = "==";
    cppTokenMap["&&"] = "&&";
    cppTokenMap["||"] = "||";
    cppTokenMap["!"] = "!";
    cppTokenMap["&"] = "&";
    cppTokenMap["|"] = "|";
    // keyword tokens
    cppTokenMap["int"] = "basic";
    cppTokenMap["float"] = "basic";
    cppTokenMap["char"] = "basic";
    cppTokenMap["void"] = "basic";
    cppTokenMap["do"] = "do";
    cppTokenMap["if"] = "if";
    cppTokenMap["while"] = "while";
    cppTokenMap["else"] = "else";
    cppTokenMap["main"] = "main";
    cppTokenMap["break"] = "break";
    /* 
    cppTokenMap["return"] = "return";
    cppTokenMap["switch"] = "switch";
    cppTokenMap["case"] = "case";
    cppTokenMap["for"] = "for";
    cppTokenMap["goto"] = "goto";
    cppTokenMap["unsigned"] = "unsigned";
    cppTokenMap["continue"] = "continue";
 */
};

void LexicalAnalyzer::characterStreamTo2DTokenVec(string argcharacterStream)
{
    string word;
    int row = 1;
    // unordered_map<string, string> tokenmap = generateDefinedTokens();
    
    // here we are defining rules as we iterate through the stream of characters.
    //these rules allow us to interpret lexemes (letters/numbers/brackets/etc) 
    // as a word, and then we are just storing all of the words in a vector called words
    // we are iterating through the stream of characters using two cursors,
    // curr1, which always stays on our first lexeme, and 
    // curr2, which moves until it hits the last lexeme of a word
    
    // changed the structure to a 2d vector, account for newline to iterate to the next dimension
    // so that tokens could be displayed on the line they were interpreted.
    // example: "int main(){        vector[0] = { "int","main", "(", ")", "{" }
    //          int i = 0;      --> vector[1] = { "int", "i", "=", "0", ";" }
    //          }"                  vector[2] = { "}" }
    int curr1 = 0;
    int curr2 = 0;
    int coloffset = 0;
    while (curr1 < argcharacterStream.size())
    {
        
	// starts by checking the first letter of the current word, curr1. if curr1 is whitespace, we don't want to count it as part of a word, so we iterate forward until curr1 isn't whitespace.
        while (isWhitespace(argcharacterStream[curr1]))
        {   
            if (argcharacterStream[curr1] == '\n'){
                row++;
                coloffset = curr1+1;
            }

            curr1++;
            curr2 = curr1;
        }
        /*while (row >= tokenStream.size() && curr2 != argcharacterStream.size()) {
        tokenStream.push_back(vector<Token>());  // Add a new row
        }*/
	// checking if the first letter of the current word, curr1 is a letter. if it is, it must be either a keyword or an identifier.
        if (isalpha(argcharacterStream[curr1]))
        {
		// for simplicity sake, we check if the next letter is alphanumeric (alphabetical or numerical) and then keep moving forward to the next letter until it isn't alphanumeric. then we store it in "word" to classify it later, and slide curr1 over to curr2+1 set our curr1 to the next character in the stream, in preparation for starting the while loop over, looking for the next word.
            while (isalnum(argcharacterStream[curr2 + 1]))
            {
                curr2++;
            }
            word = argcharacterStream.substr(curr1, (1 + curr2 - curr1));
            if (cppTokenMap.find(word) == cppTokenMap.end()) {
                tokenStream.push_back(Token(word, "id", row, (curr1-coloffset+1)));
            }
            else {
            tokenStream.push_back(Token(word, cppTokenMap[word], row, (curr1-coloffset+1)));
            }
            curr1 = curr2 + 1;
        }
        else if (isdigit(argcharacterStream[curr1]) || argcharacterStream[curr1] == '.')
        {
            while (isdigit(argcharacterStream[curr2 + 1]) || argcharacterStream[curr2 + 1] == '.')
            {
                curr2++;
            }
            word = argcharacterStream.substr(curr1, (1 + curr2 - curr1));
            if (word.find('.') != string::npos)
            {
                tokenStream.push_back(Token(word, "real", row, curr1-coloffset));
            }
            else
            tokenStream.push_back(Token(word, "number", row, curr1-coloffset));
            curr1 = curr2 + 1;
        }
        // everything else is either going to be a defined token of length 2 (think ==), a defined token of length 1 (think ;), or simply a comment (think // and everything after it as long as its on the same line)
        else
        {
            if (isTwoCharOperator(argcharacterStream.substr(curr1, 2)))
            {
                if (argcharacterStream.substr(curr1, 2) == "//"){
                    while (argcharacterStream[curr2+1] != '\n'){
                        curr2++;
                    }
                    word = argcharacterStream.substr(curr1, 1 + curr2-curr1);
                    tokenStream.push_back(Token(word, "comment", row, curr1-coloffset));
                    row++;
                    curr1 = curr2;
                } else {
                word = argcharacterStream.substr(curr1, 2);
                tokenStream.push_back(Token(word, cppTokenMap[word], row, curr1-coloffset));
                curr1 += 2;
                curr2 = curr1;
                }
            }
            else
            {
                word = argcharacterStream.substr(curr1, 1);
                tokenStream.push_back(Token(word, cppTokenMap[word], row, curr1-coloffset));
                curr1 += 1;
                curr2 = curr1;
            }
        }
    }
}

bool LexicalAnalyzer::isWhitespace(char argLexeme){
    if (argLexeme == ' ' || argLexeme == '\n' || argLexeme == '\t')
        return true;
   
    return false;
}

bool LexicalAnalyzer::isTwoCharOperator(string argSubString){
    if (argSubString == "++" || argSubString == "--" || argSubString == "<=" || argSubString == ">=" || argSubString == "==" || argSubString == "&&" || argSubString == "||" || argSubString == "//" || argSubString == "!=")
        return true;

    return false;
}

vector<Token> LexicalAnalyzer::getTokenStream(){
    return tokenStream;
}

void LexicalAnalyzer::printTokenStream(){
    for (int i = 0; i<tokenStream.size(); i++){
        cout << tokenStream[i].type << " -> " << tokenStream[i].value << "line:col" << tokenStream[i].row << ":" << tokenStream[i].column << endl;
    }
    }

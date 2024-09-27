#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
//#include <"txtToFile.cpp"> ??
//#include <"LexicalAnalyzer.cpp"> ??
using namespace std;
// Lexical Analyzer takes input: lexeme stream, returns output: token stream
class Token
{
    public:
    Token(string argType, string argValue){
        type = argType;
        value = argValue;
    }
    string type;
    string value;
};

/* class TokenStream
{
    private:
    unordered_map<string, string> TokenMap;
    public:
    TokenStream(void){
	
	};
    void addToken(Token argToken);
}; */

class LexicalAnalyzer
{
private:
    int position;
    vector< vector<Token> > tokenStream;
    void generateDefinedTokens();
    unordered_map<string, string> cppTokenMap;

public:
    LexicalAnalyzer(string argLexemeStream);
    bool isKeyword(char argWord);
    void keywordMapper(char argKeyword);
    void lexemeStreamTo2DTokenVec(string argLexemeStream);
    void wordsVecToTokenStream(vector< vector<string> > argWordsVec);
    bool isWhitespace(char argLexeme);
    bool isTwoCharOperator(string argSubString);
    void printTokenStream();
};

string txtToString(string argFile);

int main()
{   // taking a string of code as input:
    // string input = "int main(){ \n myNum7 = getNum(0);\nfor (int i = 0; i <= 7; i++)\nreturn 0;\n}";

    // TAKING TXT FILE AS INPUT INSTEAD OF A STRING:
    string input;
    cout << "Input the test filepath. Example input: testcases/case1.txt" << endl << "Filepath: ";
    cin >> input;
    string lexemeStream = txtToString(input); // Replace "input.txt" with your file name
    LexicalAnalyzer test = LexicalAnalyzer(lexemeStream);
    return 0;
}

void LexicalAnalyzer::generateDefinedTokens()
{
    // quote tokens
    cppTokenMap["("] = "leftParen";
    cppTokenMap[")"] = "rightParen";
    cppTokenMap["["] = "leftBracket";
    cppTokenMap["]"] = "rightBracket";
    cppTokenMap["{"] = "leftBrace";
    cppTokenMap["}"] = "rightBrace";
    // operator tokens
    cppTokenMap["."] = "dot";
    cppTokenMap["+"] = "plus";
    cppTokenMap["-"] = "minus";
    cppTokenMap["*"] = "multiply";
    cppTokenMap["/"] = "divide";
    cppTokenMap["%"] = "modulus";
    cppTokenMap["<"] = "lessThan";
    cppTokenMap[">"] = "greaterThan";
    cppTokenMap["="] = "assignment";
    cppTokenMap[";"] = "semicolon";
    cppTokenMap[","] = "comma";
    // comparison tokens
    cppTokenMap["++"] = "increment";
    cppTokenMap["--"] = "decrement";
    cppTokenMap["<="] = "lessThanEq";
    cppTokenMap[">="] = "greaterThanEq";
    cppTokenMap["=="] = "logicEqual";
    cppTokenMap["&&"] = "logicAnd";
    cppTokenMap["||"] = "logicOr";
    cppTokenMap["!"] = "logicNot";
    cppTokenMap["&"] = "bitAnd";
    cppTokenMap["|"] = "bitOr";

    // keyword tokens
    /*
    cppTokenMap["int"] = "int";
    cppTokenMap["return"] = "return";
    cppTokenMap["if"] = "if";
    cppTokenMap["switch"] = "switch";
    cppTokenMap["float"] = "float";
    cppTokenMap["while"] = "while";
    cppTokenMap["else"] = "else";
    cppTokenMap["case"] = "case";
    cppTokenMap["char"] = "char";
    cppTokenMap["for"] = "for";
    cppTokenMap["goto"] = "goto";
    cppTokenMap["unsigned"] = "unsigned";
    cppTokenMap["main"] = "main";
    cppTokenMap["break"] = "break";
    cppTokenMap["continue"] = "continue";
    cppTokenMap["void"] = "void";
    */
};

LexicalAnalyzer::LexicalAnalyzer(string argLexemeStream)
{
    generateDefinedTokens();
    lexemeStreamTo2DTokenVec(argLexemeStream);
    printTokenStream();

};

void LexicalAnalyzer::lexemeStreamTo2DTokenVec(string argLexemeStream)
{
    string word;
    int row = 0;
    // unordered_map<string, string> tokenmap = generateDefinedTokens();
    
    // here we are defining rules as we iterate through the stream of characters. these rules allow us to interpret lexemes (letters/numbers/brackets/etc) as a word, and then we are just storing all of the words in a vector called words
    // we are iterating through the stream of characters using two cursors, curr1, which always stays on our first lexeme, and curr2, which moves until it hits the last lexeme of a word
    // thinking about changing the structure to a 2d vector, account for newline to iterate to the next dimension so that tokens are displayed on the line they were interpreted.. this could look cool but i dont think its necessary since c++ isnt picky about lines anyway (i think)
    // example: "int main(){        vector[0] = { "int","main", "(", ")", "{" }
    //          int i = 0;      --> vector[1] = { "int", "i", "=", "0", ";" }
    //          }"                  vector[2] = { "}" }
    int curr1 = 0;
    int curr2 = 0;
    while (curr2 < argLexemeStream.size())
    {
        
	// starts by checking the first letter of the current word, curr1. if curr1 is whitespace, we don't want to count it as part of a word, so we iterate forward until curr1 isn't whitespace.
        while (isWhitespace(argLexemeStream[curr1]))
        {   
            if (argLexemeStream[curr1] == '\n')
                row++;

            curr1++;
            curr2 = curr1;
        }
        while (row >= tokenStream.size() && curr2 != argLexemeStream.size()) {
        tokenStream.push_back(vector<Token>());  // Add a new row
        }
	// checking if the first letter of the current word, curr1 is a letter. if it is, it must be either a keyword or an identifier.
        if (isalpha(argLexemeStream[curr1]))
        {
		// for simplicity sake, we check if the next letter is alphanumeric (alphabetical or numerical) and then keep moving forward to the next letter until it isn't alphanumeric. then we store it in "word" to classify it later, and slide curr1 over to curr2+1 set our curr1 to the next character in the stream, in preparation for starting the while loop over, looking for the next word.
            while (isalnum(argLexemeStream[curr2 + 1]))
            {
                curr2++;
            }
            word = argLexemeStream.substr(curr1, (1 + curr2 - curr1));
            tokenStream[row].push_back(Token("identifier",word));
            curr1 = curr2 + 1;
        }
        else if (isnumber(argLexemeStream[curr1]))
        {
            while (isnumber(argLexemeStream[curr2 + 1]))
            {
                curr2++;
            }
            word = argLexemeStream.substr(curr1, (1 + curr2 - curr1));
            tokenStream[row].push_back(Token("number",word));
            curr1 = curr2 + 1;
        }
        // everything else is either going to be a defined token of length 2 (think ==), a defined token of length 1 (think ;), or simply a comment (think // and everything after it as long as its on the same line)
        else
        {
            if (isTwoCharOperator(argLexemeStream.substr(curr1, 2)))
            {
                if (argLexemeStream.substr(curr1, 2) == "//"){
                    while (argLexemeStream[curr2+1] != '\n'){
                        curr2++;
                    }
                    word = argLexemeStream.substr(curr1, 1 + curr2-curr1);
                    tokenStream[row].push_back(Token("comment",word));
                    row++;
                    curr1 = curr2;
                } else {
                word = argLexemeStream.substr(curr1, 2);
                tokenStream[row].push_back(Token(cppTokenMap[word],word));
                curr1 += 2;
                curr2 = curr1;
                }
            }
            else
            {
                word = argLexemeStream.substr(curr1, 1);
                tokenStream[row].push_back(Token(cppTokenMap[word],word));
                curr1 += 1;
                curr2 = curr1;
            }
        }
        /* if (word.length() > 0)
        {
            tokenStream[row].push_back(Token("token",word));
        } */
    }
/*     // this for loop of printing out the words after capturing them is just for testing purposes, so that we can see if the lexemes were read correctly
    // remember to comment out or remove this for loop later
    for (int i = 0; i < tokenStream.size(); i++)
    {
        cout << "\"" << tokenStream[i] << "\"" << endl;
    } */
}

bool LexicalAnalyzer::isWhitespace(char argLexeme){
    if (argLexeme == ' ' || argLexeme == '\n' || argLexeme == '\t')
        return true;
   
    return false;
}

string txtToString(string argFile){

    ifstream inputFile(argFile); // Replace "input.txt" with your file name
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open the file." << endl;
    }

    // Read the file content into the 'input' string
    string line;
    string argStream;
    while (getline(inputFile, line))
    {
        argStream += line + "\n"; // Add the line to input string with a newline
    }

    inputFile.close(); // Close the file after reading
    return argStream;
}

bool LexicalAnalyzer::isTwoCharOperator(string argSubString){
    if (argSubString == "++" || argSubString == "--" || argSubString == "<=" || argSubString == ">=" || argSubString == "==" || argSubString == "&&" || argSubString == "||" || argSubString == "//")
        return true;

    return false;
}
void LexicalAnalyzer::printTokenStream(){
    for (int r = 0; r<tokenStream.size(); r++){
        for (int c = 0; c<tokenStream[r].size(); c++)
        cout << tokenStream[r][c].type << " -> " << tokenStream[r][c].value << endl;
    }
    }

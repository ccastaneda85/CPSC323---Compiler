#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class LexicalAnalyzer
{
private:
    string filename;
    string input;
    int position;
    vector<string> words;
    unordered_map<string, string> generateTokenmap();
public: 
    LexicalAnalyzer(string sourcecode);
    void fileToString();
    bool isKeyword(char arg);
    void inputToWords();
};

unordered_map<string, string> generateTokenmap();
vector<string> inputToWords(string input);

int main()
{
    // string input = "int main(){ \n myNum7 = getNum(0);\nfor (int i = 0; i <= 7; i++)\nreturn 0;\n}";

    LexicalAnalyzer test = LexicalAnalyzer("test.txt");

    return 0;
}

unordered_map<string, string> generateTokenmap()
{
    unordered_map<string, string> map;
    map["("] = "leftParen";
    map[")"] = "rightParen";
    map["["] = "leftBracket";
    map["]"] = "rightBracket";
    map["{"] = "leftBrace";
    map["}"] = "rightBrace";

    map["."] = "dot";
    map["+"] = "plus";
    map["-"] = "minus";
    map["*"] = "multiply";
    map["/"] = "divide";
    map["%"] = "modulus";
    map["<"] = "lessThan";
    map[">"] = "greaterThan";
    map["="] = "assignment";
    map[";"] = "semicolon";
    map[","] = "comma";

    map["++"] = "increment";
    map["--"] = "decrement";
    map["<="] = "lessThanEq";
    map[">="] = "greaterThanEq";
    map["=="] = "logicEqual";
    map["&&"] = "logicAnd";
    map["||"] = "logicOr";
    map["!"] = "logicNot";
    map["&"] = "bitAnd";
    map["|"] = "bitOr";

    return map;
};

LexicalAnalyzer::LexicalAnalyzer(string sourcecode){
    filename = sourcecode;
    fileToString();
    inputToWords();
};

void LexicalAnalyzer::inputToWords()
{
    string word;
    vector<string> argWords;
    // unordered_map<string, string> tokenmap = generateTokenmap();
    int curr1 = 0;
    int curr2 = 0;
    while (curr2 < input.size())
    {
        while (input[curr1] == ' ' || input[curr1] == '\n' || input[curr1] == '\t')
        {
            curr1++;
            curr2 = curr1;
        }
        if (isalpha(input[curr1]))
        {
            while (isalnum(input[curr2 + 1]))
            {
                curr2++;
            }
            word = input.substr(curr1, (1 + curr2 - curr1));
            curr1 = curr2 + 1;
        }
        else if (isnumber(input[curr1]))
        {
            while (isnumber(input[curr2 + 1] || input[curr2 + 1] == '.'))
            {
                curr2++;
            }
            word = input.substr(curr1, (curr2 - curr1));
            curr1 = curr2 + 1;
        }
        else
        {
            if ((input.substr(curr1, 2)) == "++" || (input.substr(curr1, 2)) == "--" || (input.substr(curr1, 2)) ==  "<=" || (input.substr(curr1, 2)) == ">=" || (input.substr(curr1, 2)) == "==" || (input.substr(curr1, 2)) == "&&" || (input.substr(curr1, 2)) == "||")
            {
                word = input.substr(curr1, 2);
                curr1 += 2;
                curr2 = curr1;
            }
            else
            {
                word = input.substr(curr1, 1);
                curr1 += 1;
                curr2 = curr1;
            }
        }
        if (word.length() > 0)
        {
            argWords.push_back(word);
        }
    }

    for (int i = 0; i < argWords.size(); i++)
    {
        cout << "\"" << argWords[i] << "\"" << endl;
    }
    words = argWords;
}

void LexicalAnalyzer::fileToString(){
    //TAKING TXT FILE AS INPUT INSTEAD OF A STRING:
    string arg;
    ifstream inputFile(filename);  // Replace "input.txt" with your file name
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
    }

    // Read the file content into the 'input' string
    string line;
    while (getline(inputFile, line)) {
        arg += line + "\n";  // Add the line to input string with a newline
    }

    inputFile.close();  // Close the file after reading
    input = arg;
}

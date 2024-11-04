#include <iostream>
#include <string>
#include "lexicalanalyzer.h"
#include "syntaxanalyzer.h"

using namespace std;

// function prototype
string txtToString(string argFile);

int main() {
    string input;
    cout << "Input the test filepath. Example input: case6.txt (6-11 are new cases)" << endl << "Filepath: ";
    cin >> input;
    input = "testcases/" + input;
    string characterStream = txtToString(input);
    LexicalAnalyzer test(characterStream);
    //SyntaxAnalyzer syntax(test.getTokenStream());
    return 0;
}

// preprocess the file into a string for the lexical analyzer to use
string txtToString(string argFile){

        ifstream inputFile(argFile); // Open the file
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return ""; // Return an empty string on error
    }

    string line;
    string argStream;

    // Read the file content into the 'argStream' string
    while (getline(inputFile, line)) {
        if (!argStream.empty()) { // If argStream is not empty, add a newline
            argStream += "\n"; // Add a newline before appending the next line
        }
        argStream += line; // Append the current line
    }

    inputFile.close(); // Close the file after reading
    return argStream;
}
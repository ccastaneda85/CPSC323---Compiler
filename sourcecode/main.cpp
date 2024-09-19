#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<utility>

using namespace std;

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

void printWithWhitespaceSymbols(const string& str) {
    for (char ch : str) {
        switch (ch) {
            case ' ':
                cout << "<space>";
                break;
            case '\n':
                cout << "<newline>"; // Keep newline for formatting
                break;
            case '\t':
                cout << "<tab>";
                break;
            default:
                cout << ch;  // Print normal characters as they are
        }
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    //string content = fileReader("testcases/case2.txt");

    // printWithWhitespaceSymbols(content);
    //cout << content << endl;

    vector<pair<string, string>> lexemeTokenPair = {
        {"myInt", "int"}
    };


    for(int i = 0; i < lexemeTokenPair.size(); i++) {
        cout << "Pair" << i + 1 << ": " << lexemeTokenPair[i].first << " ," << lexemeTokenPair[i].second << endl;
    }



    return 0;
}

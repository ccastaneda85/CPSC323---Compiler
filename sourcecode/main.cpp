#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

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
    string content = fileReader("testcases/case2.txt");

    printWithWhitespaceSymbols(content);

    cout << content << endl;



    return 0;
}

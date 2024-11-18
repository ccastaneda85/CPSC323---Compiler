#include <iostream>
#include "utilities.h"
#include "lexicalanalyzer.h"
#include <fstream>
#include <sstream>
#include "parser.h"
using namespace std;

int main(int argc, char const *argv[])
{

    string testString = fileReader("testcases/p2case5.txt");
    vector<Token> TokenStream;
    TokenStream = lexicalAnalyzer(testString);

    // for(auto items: TokenStream) {
    //     cout << items.getType() << " ";
    // }

    parser(TokenStream);

    return 0;
}
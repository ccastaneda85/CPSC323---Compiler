#include <iostream>
#include "utilities.h"
#include "lexicalanalyzer.h"
#include <fstream>
#include <sstream>
#include "parser.h"
#include "concretesyntaxtree.h"
using namespace std;

int main(int argc, char const *argv[])
{

    string testString = fileReader("testcases/case2.txt");
    vector<Token> TokenStream;
    TokenStream = lexicalAnalyzer(testString);
    SyntaxTree* cst = parser(TokenStream);
    cst->print();

    return 0;
}
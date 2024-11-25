#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include "utilities.h"

using namespace std;


struct Production
{
    std::string lhs;
    std::vector<std::string> rhs;
};

std::vector<Production> productions = {
    {"<program>", {"basic", "main", "(", ")", "<block>"}},  // 1
    {"<block>", {"{", "<block_opt>"}},                      // 2
    {"<block_opt>", {"<decls>", "<decls_opt>"}},            // 3
    {"<block_opt>", {"<stmts>", "}"}},                      // 4
    {"<block_opt>", {"}"}},                                 // 5
    {"<decls_opt>", {"<stmts>", "}"}},                      // 6
    {"<decls_opt>", {"}"}},                                 // 7
    {"<decls>", {"<decl>", "<decls’>"}},                    // 8
    {"<decls’>", {"<decl>", "<decls’>"}},                   // 9
    {"<decls’>", {""}},                                     // 10
    {"<decl>", {"<type>", "id", ";"}},                      // 11
    {"<type>", {"basic", "<type’>"}},                       // 12
    {"<type’>", {"[", "num", "]", "<type’>"}},              // 13
    {"<type’>", {""}},                                      // 14
    {"<stmts>", {"<stmt>", "<stmts’>"}},                    // 15
    {"<stmts’>", {"<stmt>", "<stmts’>"}},                   // 16
    {"<stmts’>", {""}},                                     // 17
    {"<stmt>", {"<loc>", "=", "<bool>", ";"}},              // 18
    {"<stmt>", {"if", "(", "<bool>", ")", "<if_opt>"}},     // 19
    {"<stmt>", {"while", "(", "<bool>", ")", "<stmt>"}},    // 20
    {"<stmt>", {"do", "<stmt>", "while", "<bool>", ";"}},   // 21
    {"<stmt>", {"break", ";"}},                             // 22
    {"<stmt>", {"return", "num", ";"}},                     // 23
    {"<stmt>", {"{", "<block_opt>"}},                       // 24
    {"<if_stmt>", {"if", "(", "<bool>", ")", "<if_opt>"}},  // 25
    {"<if_opt>", {"<loc>", "=", "<bool>", ";"}},            // 26
    {"<if_opt>", {"if", "(", "<bool>", ")", "<if_opt>"}},   // 27
    {"<if_opt>", {"while", "(", "<bool>", ")", "<stmt>"}},  // 28
    {"<if_opt>", {"do", "<stmt>", "while", "<bool>", ";"}}, // 29
    {"<if_opt>", {"break", ";"}},                           // 30
    {"<if_opt>", {"return", "num", ";"}},                   // 31
    {"<if_opt>", {"{", "<block_opt>"}},                     // 32
    {"<loc>", {"id", "<loc’>"}},                            // 33
    {"<loc’>", {"[", "<bool>", "]", "<loc’>"}},             // 34
    {"<loc’>", {""}},                                       // 35
    {"<bool>", {"<join>", "<bool’>"}},                      // 36
    {"<bool’>", {"||", "<join>", "<bool’>"}},               // 37
    {"<bool’>", {""}},                                      // 38
    {"<join>", {"<equality>", "<join’>"}},                  // 39
    {"<join’>", {"&&", "<equality>", "<join’>"}},           // 40
    {"<join’>", {""}},                                      // 41
    {"<equality>", {"<rel>", "<equality’>"}},               // 42
    {"<equality’>", {"==", "<rel>", "<equality’>"}},        // 43
    {"<equality’>", {"!=", "<rel>", "<equality’>"}},        // 44
    {"<equality’>", {""}},                                  // 45
    {"<rel>", {"<expr>", "<expr_opt>"}},                    // 46
    {"<expr_opt>", {"<", "<expr>"}},                        // 47
    {"<expr_opt>", {"<=", "<expr>"}},                       // 48
    {"<expr_opt>", {">=", "<expr>"}},                       // 49
    {"<expr_opt>", {">", "<expr>"}},                        // 50
    {"<expr_opt>", {""}},                                   // 51
    {"<expr>", {"<term>", "<expr’>"}},                      // 52
    {"<expr’>", {"+", "<term>", "<expr’>"}},                // 53
    {"<expr’>", {"-", "<term>", "<expr’>"}},                // 54
    {"<expr’>", {""}},                                      // 55
    {"<term>", {"<unary>", "<term’>"}},                     // 56
    {"<term’>", {"*", "<unary>", "<term’>"}},               // 57
    {"<term’>", {"/", "<unary>", "<term’>"}},               // 58
    {"<term’>", {""}},                                      // 59
    {"<unary>", {"!", "<unary>"}},                          // 60
    {"<unary>", {"-", "<unary>"}},                          // 61
    {"<unary>", {"<factor>"}},                              // 62
    {"<factor>", {"(", "<bool>", ")"}},                     // 63
    {"<factor>", {"id", "<loc’>"}},                         // 64
    {"<factor>", {"num"}},                                  // 65
    {"<factor>", {"real"}},                                 // 66
    {"<factor>", {"true"}},                                 // 67
    {"<factor>", {"false"}},                                // 68
};

map<pair<string, string>, int> parsingTable;
void initializeParsingTable()
{
    parsingTable[{"<program>", "basic"}] = 0;
    parsingTable[{"<block>", "{"}] = 1;
    parsingTable[{"<block_opt>", "basic"}] = 2;
    parsingTable[{"<block_opt>", "id"}] = 3;
    parsingTable[{"<block_opt>", "if"}] = 3;
    parsingTable[{"<block_opt>", "while"}] = 3;
    parsingTable[{"<block_opt>", "do"}] = 3;
    parsingTable[{"<block_opt>", "break"}] = 3;
    parsingTable[{"<block_opt>", "return"}] = 3;
    parsingTable[{"<block_opt>", "{"}] = 3;
    parsingTable[{"<block_opt>", "}"}] = 4;
    parsingTable[{"<decls_opt>", "id"}] = 5;
    parsingTable[{"<decls_opt>", "if"}] = 5;
    parsingTable[{"<decls_opt>", "while"}] = 5;
    parsingTable[{"<decls_opt>", "do"}] = 5;
    parsingTable[{"<decls_opt>", "break"}] = 5;
    parsingTable[{"<decls_opt>", "return"}] = 5;
    parsingTable[{"<decls_opt>", "{"}] = 5;
    parsingTable[{"<decls_opt>", "}"}] = 6;
    parsingTable[{"<decls>", "basic"}] = 7;
    parsingTable[{"<decls’>", "basic"}] = 8;
    parsingTable[{"<decls’>", "id"}] = 9;
    parsingTable[{"<decls’>", "if"}] = 9;
    parsingTable[{"<decls’>", "while"}] = 9;
    parsingTable[{"<decls’>", "do"}] = 9;
    parsingTable[{"<decls’>", "break"}] = 9;
    parsingTable[{"<decls’>", "return"}] = 9;
    parsingTable[{"<decls’>", "{"}] = 9;
    parsingTable[{"<decls’>", "}"}] = 9;
    parsingTable[{"<decl>", "basic"}] = 10;
    parsingTable[{"<type>", "basic"}] = 11;
    parsingTable[{"<type’>", "["}] = 12;
    parsingTable[{"<type’>", "id"}] = 13;
    parsingTable[{"<stmts>", "id"}] = 14;
    parsingTable[{"<stmts>", "if"}] = 14;
    parsingTable[{"<stmts>", "while"}] = 14;
    parsingTable[{"<stmts>", "do"}] = 14;
    parsingTable[{"<stmts>", "break"}] = 14;
    parsingTable[{"<stmts>", "return"}] = 14;
    parsingTable[{"<stmts>", "{"}] = 14;
    parsingTable[{"<stmt>", "if"}] = 19;
    parsingTable[{"<stmt>", "while"}] = 20;
    parsingTable[{"<stmt>", "do"}] = 21;
    parsingTable[{"<stmt>", "break"}] = 22;
    parsingTable[{"<stmt>", "return"}] = 23;
    parsingTable[{"<stmt>", "{"}] = 24;
    parsingTable[{"<if_stmt>", "if"}] = 25;
    parsingTable[{"<unary>", "-"}] = 60;
    parsingTable[{"<unary>", "!"}] = 59;
    parsingTable[{"<factor>", "id"}] = 63;
    parsingTable[{"<factor>", "num"}] = 64;
    parsingTable[{"<factor>", "real"}] = 65;
    parsingTable[{"<factor>", "true"}] = 66;
    parsingTable[{"<factor>", "false"}] = 67;
    parsingTable[{"<factor>", "("}] = 62;
}



void parser(vector<Token> &tokenStream)
{
    initializeParsingTable();
    stack<string> parsingStack;
    int p1 = 0;

    parsingStack.push("$");
    parsingStack.push("<program>");

    printStackBottomToTop(parsingStack);
    cout << "p1: " << tokenStream.at(p1).getType() << endl;

    while (!parsingStack.empty())
    {
        string stackTop = parsingStack.top();
        string currentToken = tokenStream.at(p1).getType();

        // Pop epsilon (empty string) rules
        if (stackTop == "")
        {
            parsingStack.pop();
            continue;
        }

        // If the top of the stack matches the current token, consume the token
        if (stackTop == currentToken)
        {
            parsingStack.pop();
            p1++;
            printStackBottomToTop(parsingStack);
            cout << "Matched token: " << currentToken << " at position: " << p1 << endl;
            continue;
        }

        // Check if there is a parsing table entry for the current (stackTop, currentToken) pair
        auto tableEntry = parsingTable.find({stackTop, currentToken});
        if (tableEntry != parsingTable.end())
        {
            int productionIndex = tableEntry->second;
            vector<string> rhs = productions.at(productionIndex).rhs;

            // Pop the non-terminal from the stack
            parsingStack.pop();

            // Push the right-hand side of the production onto the stack (in reverse order)
            for (int i = rhs.size() - 1; i >= 0; --i)
            {
                if (rhs[i] != "") // Ignore epsilon (empty string)
                {
                    parsingStack.push(rhs[i]);
                }
            }

            printStackBottomToTop(parsingStack);
            cout << "Applied production: " << productionIndex << " for (" << stackTop << ", " << currentToken << ")" << endl;
        }
        else
        {
            // If no valid table entry is found, report a syntax error
            cout << "Syntax error at line: " << tokenStream.at(p1).getLineNum()
                 << ", character position: " << tokenStream.at(p1).getFirstCharPos() << endl;
            cout << "Unexpected token: " << currentToken << " when expecting: " << stackTop << endl;
            return; // Exit the function on error
        }
    }

    // Check if the entire input was successfully parsed
    if (parsingStack.empty() && tokenStream.at(p1).getType() == "$")
    {
        cout << "Parsing completed successfully." << endl;
    }
    else
    {
        cout << "Parsing failed. Input was not fully consumed." << endl;
    }
}

#endif // PARSER_H

#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include "utilities.h"

using namespace std;

// struct Production {
//     std::string lhs; // Left-hand side
//     std::vector<std::string> rhs; // Right-hand side symbols
// };

// std::vector<Production> productions = {
//     {"<Program>", {"basic", "main", "(", ")", "<Block>"}},
//     {"<Block>", {"{", "<Block''>"}},
//     {"<Decls>", {"<Decl>", "<Decls'>"}},
//     {"<Decl>", {"<Type>", "id", ";"}},
//     {"<Type>", {"basic", "<Type'>"}},
//     {"<Stmts>", {"<Stmt>", "<Stmts'>"}},
//     {"<Stmt>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>"}},
//     {"<Stmt>", {"<Loc>", "=", "<Bool>", ";"}},
//     {"<Stmt>", {"while", "(", "<Bool>", ")", "<Stmt>"}},
//     {"<Stmt>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";"}},
//     {"<Stmt>", {"return", "num", ";"}},
//     {"<Stmt>", {"break", ";"}},
//     {"<Stmt>", {"{", "<Block''>"}},
//     {"<Loc>", {"id", "<Loc'>"}},
//     {"<Bool>", {"<Join>", "<Bool'>"}},
//     {"<Join>", {"<Equality>", "<Join'>"}},
//     {"<Equality>", {"<Rel>", "<Equality''>"}},
//     {"<Rel>", {"<Expr>", "<Rel'>"}},
//     {"<Expr>", {"<Term>", "<Expr''>"}},
//     {"<Term>", {"<Unary>", "<Term''>"}},
//     {"<Unary>", {"!", "<Unary>"}},
//     {"<Unary>", {"-", "<Unary>"}},
//     {"<Unary>", {"<Factor>"}},
//     {"<Factor>", {"(", "<Bool>", ")"}},
//     {"<Factor>", {"id", "<Loc'>"}},
//     {"<Factor>", {"num"}},
//     {"<Factor>", {"real"}},
//     {"<Factor>", {"true"}},
//     {"<Factor>", {"false"}},
//     {"<Block'>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>", "<Stmts'>", "}"}},
//     {"<Block'>", {"id", "<Loc'>", "=", "<Bool>", ";", "<Stmts'>", "}"}},
//     {"<Block'>", {"while", "(", "<Bool>", ")", "<Stmt>", "<Stmts'>", "}"}},
//     {"<Block'>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";", "<Stmts'>", "}"}},
//     {"<Block'>", {"return", "num", ";", "<Stmts'>", "}"}},
//     {"<Block'>", {"break", ";", "<Stmts'>", "}"}},
//     {"<Block'>", {"{", "<Block''>", "<Stmts'>", "}"}},
//     {"<Block'>", {"}"}},
//     {"<Block''>", {"basic", "<Type'>", "id", ";", "<Decls'>", "<Block'>"}},
//     {"<Block''>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>", "<Stmts'>", "}"}},
//     {"<Block''>", {"id", "<Loc'>", "=", "<Bool>", ";", "<Stmts'>", "}"}},
//     {"<Block''>", {"while", "(", "<Bool>", ")", "<Stmt>", "<Stmts'>", "}"}},
//     {"<Block''>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";", "<Stmts'>", "}"}},
//     {"<Block''>", {"return", "num", ";", "<Stmts'>", "}"}},
//     {"<Block''>", {"break", ";", "<Stmts'>", "}"}},
//     {"<Block''>", {"{", "<Block''>", "<Stmts'>", "}"}},
//     {"<Block''>", {"}"}},
//     {"<Stmts'>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>", "<Stmts'>"}},
//     {"<Stmts'>", {"id", "<Loc'>", "=", "<Bool>", ";", "<Stmts'>"}},
//     {"<Stmts'>", {"while", "(", "<Bool>", ")", "<Stmt>", "<Stmts'>"}},
//     {"<Stmts'>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";", "<Stmts'>"}},
//     {"<Stmts'>", {"return", "num", ";", "<Stmts'>"}},
//     {"<Stmts'>", {"break", ";", "<Stmts'>"}},
//     {"<Stmts'>", {"{", "<Block''>", "<Stmts'>"}},
//     {"<Stmts'>", {""}},
//     {"<Stmt'>", {""}},
//     {"<Stmt'>", {"else", "<Stmt>"}},
//     {"<Equality'>", {"==", "<Rel>"}},
//     {"<Equality'>", {"!=", "<Rel>"}},
//     {"<Rel'>", {"<", "<Expr>"}},
//     {"<Rel'>", {"<=", "<Expr>"}},
//     {"<Rel'>", {">=", "<Expr>"}},
//     {"<Rel'>", {">", "<Expr>"}},
//     {"<Rel'>", {""}},
//     {"<Expr'>", {"+", "<Term>"}},
//     {"<Expr'>", {"-", "<Term>"}},
//     {"<Term'>", {"/", "<Unary>"}},
//     {"<Term'>", {"*", "<Unary>"}},
//     {"<Decls'>", {"<Decl>", "<Decls'>"}},
//     {"<Decls'>", {""}},
//     {"<Type'>", {"[", "num", "]", "<Type'>"}},
//     {"<Type'>", {""}},
//     {"<Loc'>", {"[", "<Bool>", "]", "<Loc'>"}},
//     {"<Loc'>", {""}},
//     {"<Bool'>", {"||", "<Join>", "<Bool'>"}},
//     {"<Bool'>", {""}},
//     {"<Join'>", {"&&", "<Equality>", "<Join'>"}},
//     {"<Join'>", {""}},
//     {"<Equality''>", {"<Equality'>", "<Equality''>"}},
//     {"<Equality''>", {""}},
//     {"<Expr''>", {"<Expr'>", "<Expr''>"}},
//     {"<Expr''>", {""}},
//     {"<Term''>", {"<Term'>", "<Term''>"}},
//     {"<Term''>", {""}}
// };

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

// map<pair<string, string>, int> parsingTable;
// void initializeParsingTable() {
//     parsingTable[{"<Program>", "basic"}] = 0;
//     parsingTable[{"<Block>", "{"}] = 1;
//     parsingTable[{"<Decls>", "basic"}] = 2;
//     parsingTable[{"<Decl>", "basic"}] = 3;
//     parsingTable[{"<Type>", "basic"}] = 4;
//     parsingTable[{"<Stmts>", "{"}] = 5;
//     parsingTable[{"<Stmts>", "id"}] = 5;
//     parsingTable[{"<Stmts>", "if"}] = 5;
//     parsingTable[{"<Stmts>", "while"}] = 5;
//     parsingTable[{"<Stmts>", "do"}] = 5;
//     parsingTable[{"<Stmts>", "return"}] = 5;
//     parsingTable[{"<Stmts>", "break"}] = 5;
//     parsingTable[{"<Stmt>", "{"}] = 12;
//     parsingTable[{"<Stmt>", "id"}] = 7;
//     parsingTable[{"<Stmt>", "if"}] = 6;
//     parsingTable[{"<Stmt>", "while"}] = 8;
//     parsingTable[{"<Stmt>", "do"}] = 9;
//     parsingTable[{"<Stmt>", "return"}] = 10;
//     parsingTable[{"<Stmt>", "break"}] = 11;
//     parsingTable[{"<Loc>", "id"}] = 13;
//     parsingTable[{"<Bool>", "("}] = 14;
//     parsingTable[{"<Bool>", "id"}] = 14;
//     parsingTable[{"<Bool>", "num"}] = 14;
//     parsingTable[{"<Bool>", "!"}] = 14;
//     parsingTable[{"<Bool>", "-"}] = 14;
//     parsingTable[{"<Bool>", "real"}] = 14;
//     parsingTable[{"<Bool>", "TRUE"}] = 14;
//     parsingTable[{"<Bool>", "FALSE"}] = 14;
//     parsingTable[{"<Join>", "("}] = 15;
//     parsingTable[{"<Join>", "id"}] = 15;
//     parsingTable[{"<Join>", "num"}] = 15;
//     parsingTable[{"<Join>", "!"}] = 15;
//     parsingTable[{"<Join>", "-"}] = 15;
//     parsingTable[{"<Join>", "real"}] = 15;
//     parsingTable[{"<Join>", "TRUE"}] = 15;
//     parsingTable[{"<Join>", "FALSE"}] = 15;
//     parsingTable[{"<Equality>", "("}] = 16;
//     parsingTable[{"<Equality>", "id"}] = 16;
//     parsingTable[{"<Equality>", "num"}] = 16;
//     parsingTable[{"<Equality>", "!"}] = 16;
//     parsingTable[{"<Equality>", "-"}] = 16;
//     parsingTable[{"<Equality>", "real"}] = 16;
//     parsingTable[{"<Equality>", "TRUE"}] = 16;
//     parsingTable[{"<Equality>", "FALSE"}] = 16;
//     parsingTable[{"<Rel>", "("}] = 17;
//     parsingTable[{"<Rel>", "id"}] = 17;
//     parsingTable[{"<Rel>", "num"}] = 17;
//     parsingTable[{"<Rel>", "!"}] = 17;
//     parsingTable[{"<Rel>", "-"}] = 17;
//     parsingTable[{"<Rel>", "real"}] = 17;
//     parsingTable[{"<Rel>", "TRUE"}] = 17;
//     parsingTable[{"<Rel>", "FALSE"}] = 17;
//     parsingTable[{"<Expr>", "("}] = 18;
//     parsingTable[{"<Expr>", "id"}] = 18;
//     parsingTable[{"<Expr>", "num"}] = 18;
//     parsingTable[{"<Expr>", "!"}] = 18;
//     parsingTable[{"<Expr>", "-"}] = 18;
//     parsingTable[{"<Expr>", "real"}] = 18;
//     parsingTable[{"<Expr>", "TRUE"}] = 18;
//     parsingTable[{"<Expr>", "FALSE"}] = 18;
//     parsingTable[{"<Term>", "("}] = 19;
//     parsingTable[{"<Term>", "id"}] = 19;
//     parsingTable[{"<Term>", "num"}] = 19;
//     parsingTable[{"<Term>", "!"}] = 19;
//     parsingTable[{"<Term>", "-"}] = 19;
//     parsingTable[{"<Term>", "real"}] = 19;
//     parsingTable[{"<Term>", "TRUE"}] = 19;
//     parsingTable[{"<Term>", "FALSE"}] = 19;
//     parsingTable[{"<Unary>", "("}] = 22;
//     parsingTable[{"<Unary>", "id"}] = 22;
//     parsingTable[{"<Unary>", "num"}] = 22;
//     parsingTable[{"<Unary>", "!"}] = 20;
//     parsingTable[{"<Unary>", "-"}] = 21;
//     parsingTable[{"<Unary>", "real"}] = 22;
//     parsingTable[{"<Unary>", "TRUE"}] = 22;
//     parsingTable[{"<Unary>", "FALSE"}] = 22;
//     parsingTable[{"<Factor>", "("}] = 23;
//     parsingTable[{"<Factor>", "id"}] = 24;
//     parsingTable[{"<Factor>", "num"}] = 25;
//     parsingTable[{"<Factor>", "real"}] = 26;
//     parsingTable[{"<Factor>", "TRUE"}] = 27;
//     parsingTable[{"<Factor>", "FALSE"}] = 28;
//     parsingTable[{"<Block'>", "{"}] = 35;
//     parsingTable[{"<Block'>", "id"}] = 30;
//     parsingTable[{"<Block'>", "if"}] = 29;
//     parsingTable[{"<Block'>", "while"}] = 31;
//     parsingTable[{"<Block'>", "do"}] = 32;
//     parsingTable[{"<Block'>", "return"}] = 33;
//     parsingTable[{"<Block'>", "break"}] = 34;
//     parsingTable[{"<Block'>", "}"}] = 36;
//     parsingTable[{"<Block''>", "basic"}] = 37;
//     parsingTable[{"<Block''>", "{"}] = 44;
//     parsingTable[{"<Block''>", "id"}] = 39;
//     parsingTable[{"<Block''>", "if"}] = 38;
//     parsingTable[{"<Block''>", "while"}] = 40;
//     parsingTable[{"<Block''>", "do"}] = 41;
//     parsingTable[{"<Block''>", "return"}] = 42;
//     parsingTable[{"<Block''>", "break"}] = 43;
//     parsingTable[{"<Block''>", "}"}] = 45;
//     parsingTable[{"<Stmts'>", "{"}] = 52;
//     parsingTable[{"<Stmts'>", "id"}] = 47;
//     parsingTable[{"<Stmts'>", "if"}] = 46;
//     parsingTable[{"<Stmts'>", "while"}] = 48;
//     parsingTable[{"<Stmts'>", "do"}] = 49;
//     parsingTable[{"<Stmts'>", "return"}] = 50;
//     parsingTable[{"<Stmts'>", "break"}] = 51;
//     parsingTable[{"<Stmts'>", "}"}] = 53;
//     parsingTable[{"<Stmt'>", "{"}] = 54;
//     parsingTable[{"<Stmt'>", "id"}] = 54;
//     parsingTable[{"<Stmt'>", "if"}] = 54;
//     parsingTable[{"<Stmt'>", "while"}] = 54;
//     parsingTable[{"<Stmt'>", "do"}] = 54;
//     parsingTable[{"<Stmt'>", "return"}] = 54;
//     parsingTable[{"<Stmt'>", "break"}] = 54;
//     parsingTable[{"<Stmt'>", "}"}] = 54;
//     parsingTable[{"<Stmt'>", "else"}] = 54;
//     parsingTable[{"<Stmt'>", "$"}] = 54;
//     parsingTable[{"<nan>", "else"}] = 55;
//     parsingTable[{"<Equality'>", "=="}] = 56;
//     parsingTable[{"<Equality'>", "!="}] = 57;
//     parsingTable[{"<Rel'>", ")"}] = 62;
//     parsingTable[{"<Rel'>", ";"}] = 62;
//     parsingTable[{"<Rel'>", "=="}] = 62;
//     parsingTable[{"<Rel'>", "!="}] = 62;
//     parsingTable[{"<Rel'>", "<"}] = 58;
//     parsingTable[{"<Rel'>", "<="}] = 59;
//     parsingTable[{"<Rel'>", ">="}] = 60;
//     parsingTable[{"<Rel'>", ">"}] = 61;
//     parsingTable[{"<Rel'>", "]"}] = 62;
//     parsingTable[{"<Rel'>", "||"}] = 62;
//     parsingTable[{"<Rel'>", "&&"}] = 62;
//     parsingTable[{"<Expr'>", "-"}] = 64;
//     parsingTable[{"<Expr'>", "+"}] = 63;
//     parsingTable[{"<Term'>", "/"}] = 65;
//     parsingTable[{"<Term'>", "*"}] = 66;
//     parsingTable[{"<Decls'>", "basic"}] = 67;
//     parsingTable[{"<Decls'>", "{"}] = 68;
//     parsingTable[{"<Decls'>", "id"}] = 68;
//     parsingTable[{"<Decls'>", "if"}] = 68;
//     parsingTable[{"<Decls'>", "while"}] = 68;
//     parsingTable[{"<Decls'>", "do"}] = 68;
//     parsingTable[{"<Decls'>", "return"}] = 68;
//     parsingTable[{"<Decls'>", "break"}] = 68;
//     parsingTable[{"<Decls'>", "}"}] = 68;
//     parsingTable[{"<Type'>", "id"}] = 70;
//     parsingTable[{"<Type'>", "["}] = 69;
//     parsingTable[{"<Loc'>", ")"}] = 72;
//     parsingTable[{"<Loc'>", ";"}] = 72;
//     parsingTable[{"<Loc'>", "="}] = 72;
//     parsingTable[{"<Loc'>", "-"}] = 72;
//     parsingTable[{"<Loc'>", "=="}] = 72;
//     parsingTable[{"<Loc'>", "!="}] = 72;
//     parsingTable[{"<Loc'>", "<"}] = 72;
//     parsingTable[{"<Loc'>", "<="}] = 72;
//     parsingTable[{"<Loc'>", ">="}] = 72;
//     parsingTable[{"<Loc'>", ">"}] = 72;
//     parsingTable[{"<Loc'>", "+"}] = 72;
//     parsingTable[{"<Loc'>", "/"}] = 72;
//     parsingTable[{"<Loc'>", "*"}] = 72;
//     parsingTable[{"<Loc'>", "["}] = 71;
//     parsingTable[{"<Loc'>", "]"}] = 72;
//     parsingTable[{"<Loc'>", "||"}] = 72;
//     parsingTable[{"<Loc'>", "&&"}] = 72;
//     parsingTable[{"<Bool'>", ")"}] = 74;
//     parsingTable[{"<Bool'>", ";"}] = 74;
//     parsingTable[{"<Bool'>", "]"}] = 74;
//     parsingTable[{"<Bool'>", "||"}] = 73;
//     parsingTable[{"<Join'>", ")"}] = 76;
//     parsingTable[{"<Join'>", ";"}] = 76;
//     parsingTable[{"<Join'>", "]"}] = 76;
//     parsingTable[{"<Join'>", "||"}] = 76;
//     parsingTable[{"<Join'>", "&&"}] = 75;
//     parsingTable[{"<Equality''>", ")"}] = 78;
//     parsingTable[{"<Equality''>", ";"}] = 78;
//     parsingTable[{"<Equality''>", "=="}] = 77;
//     parsingTable[{"<Equality''>", "!="}] = 77;
//     parsingTable[{"<Equality''>", "]"}] = 78;
//     parsingTable[{"<Equality''>", "||"}] = 78;
//     parsingTable[{"<Equality''>", "&&"}] = 78;
//     parsingTable[{"<Expr''>", ")"}] = 80;
//     parsingTable[{"<Expr''>", ";"}] = 80;
//     parsingTable[{"<Expr''>", "-"}] = 79;
//     parsingTable[{"<Expr''>", "=="}] = 80;
//     parsingTable[{"<Expr''>", "!="}] = 80;
//     parsingTable[{"<Expr''>", "<"}] = 80;
//     parsingTable[{"<Expr''>", "<="}] = 80;
//     parsingTable[{"<Expr''>", ">="}] = 80;
//     parsingTable[{"<Expr''>", ">"}] = 80;
//     parsingTable[{"<Expr''>", "+"}] = 79;
//     parsingTable[{"<Expr''>", "]"}] = 80;
//     parsingTable[{"<Expr''>", "||"}] = 80;
//     parsingTable[{"<Expr''>", "&&"}] = 80;
//     parsingTable[{"<Term''>", ")"}] = 82;
//     parsingTable[{"<Term''>", ";"}] = 82;
//     parsingTable[{"<Term''>", "-"}] = 82;
//     parsingTable[{"<Term''>", "=="}] = 82;
//     parsingTable[{"<Term''>", "!="}] = 82;
//     parsingTable[{"<Term''>", "<"}] = 82;
//     parsingTable[{"<Term''>", "<="}] = 82;
//     parsingTable[{"<Term''>", ">="}] = 82;
//     parsingTable[{"<Term''>", ">"}] = 82;
//     parsingTable[{"<Term''>", "+"}] = 82;
//     parsingTable[{"<Term''>", "/"}] = 81;
//     parsingTable[{"<Term''>", "*"}] = 81;
//     parsingTable[{"<Term''>", "]"}] = 82;
//     parsingTable[{"<Term''>", "||"}] = 82;
//     parsingTable[{"<Term''>", "&&"}] = 82;
// }

// void parser(vector<Token> &tokenStream)
// {

//     initializeParsingTable();
//     stack<string> parsingStack;
//     int p1 = 0;

//     parsingStack.push("$");
//     printStackBottomToTop(parsingStack);
//     cout << "p1: " << tokenStream.at(p1).getType() << endl;

//     parsingStack.push("<program>");
//     printStackBottomToTop(parsingStack);
//     cout << "p1: " << tokenStream.at(p1).getType() << endl;

//     while (!parsingStack.empty())
//     {

//         if (parsingStack.top() == "")
//         {
//             parsingStack.pop();
//             printStackBottomToTop(parsingStack);
//             cout << "p1: " << tokenStream.at(p1).getType() << endl;
//         }

//         if (parsingStack.top() == tokenStream.at(p1).getType())
//         {
//             p1++;
//             parsingStack.pop();
//             printStackBottomToTop(parsingStack);
//             cout << "p1: " << tokenStream.at(p1).getType() << endl;
//         }
//         else if (parsingTable.find({parsingStack.top(), tokenStream.at(p1).getType()}) != parsingTable.end())
//         {
//             vector<string> rhs = productions.at(parsingTable[{parsingStack.top(), tokenStream.at(p1).getType()}]).rhs;
//             parsingStack.pop();
//             for (int i = rhs.size() - 1; i >= 0; --i)
//             {
//                 parsingStack.push(rhs.at(i));
//             }

//             printStackBottomToTop(parsingStack);
//             cout << "p1: " << tokenStream.at(p1).getType() << endl;
//         }
//         else
//         {
//             cout << "syntax eror at: " << "line : " << tokenStream.at(p1).getLineNum() << " and character position: " << tokenStream.at(p1).getFirstCharPos() << endl;
//             cout << "p1: " << tokenStream.at(p1).getType() << endl;
//             break;
//         }
//     }
// }

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
// basic main ( ) { basic id = num ; id ++ ; id < < num ; id num ; }
/*
[ $ <Program>
[ $ <Block> ) ( main basic
syntax eror at: line : 1 and character position: 4
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Define a structure to hold productions
struct Production {
    string lhs;           // Left-hand side non-terminal
    vector<string> rhs;   // Right-hand side of production (list of symbols)
};

// Parse table
unordered_map<string, unordered_map<string, Production>> parseTable;

// Populate the parse table
void initializeParseTable() {
    // Add entries to the table for <program>
    parseTable["<program>"]["basic"] = {"<program>", {"basic", "main", "(", ")", "<block>"}};

    // Add entries for <block>
    parseTable["<block>"]["{"] = {"<block>", {"{", "<block_opt>"}};

    // Add entries for <block_opt>
    parseTable["<block_opt>"]["basic"] = {"<block_opt>", {"<stmt>", "<block_opt>"}};
    parseTable["<block_opt"]["id"] = {"<block_opt>", {"ε"}};
    parseTable["<block_opt>"]["if"] = {"<block_opt>", {"ε"}};
    parseTable["<block_opt>"]["while"] = {"<block_opt>", {"ε"}};
    parseTable["<block_opt>"]["do"] = {"<block_opt>", {"ε"}};
    parseTable["<block_opt>"]["break"] = {"<block_opt>", {"ε"}};
    parseTable["<block_opt>"]["return"] = {"<block_opt>", {"ε"}};
    parseTable["<block_opt>"]["{"] = {"<block_opt>", {"ε"}};
    parseTable["<block_opt>"]["}"] = {"<block_opt>", {"ε"}};
    
    // Add entries for <decls_opt>
    parseTable["<decls_opt>"]["id"] = {"<decls_opt>", {"ε"}};
    parseTable["<decls_opt>"]["if"] = {"<decls_opt>", {"ε"}};
    parseTable["<decls_opt>"]["while"] = {"<decls_opt>", {"ε"}};
    parseTable["<decls_opt>"]["do"] = {"<decls_opt>", {"ε"}};
    parseTable["<decls_opt>"]["break"] = {"<decls_opt>", {"ε"}};
    parseTable["<decls_opt>"]["return"] = {"<decls_opt>", {"ε"}};
    parseTable["<decls_opt>"]["{"] = {"<decls_opt>", {"ε"}};
    parseTable["<decls_opt>"]["}"] = {"<decls_opt>", {"ε"}};

    // Add entries for <decls>
    parseTable["<decls>"]["basic"] = {"<decls>", {"<decl>", "<decls>"}};

    // Add entries for <decls'>
    parseTable["<decls'>"]["basic"] = {"<decls'>", {"ε"}};

    // Add entries for <decl>
    parseTable["<decl>"]["basic"] = {"<decl>", {"basic", "<id_list>"}};

    // Add entries for <type>
    parseTable["<type>"]["basic"] = {"<type>", {"basic"}};

    // Add entries for <type'>
    parseTable["<type'>"]["["] = {"<type'>", {"[", "num", "]"}};

    // Add entries for <stmts>
    parseTable["<stmts>"]["id"] = {"<stmts>", {"<stmt>", "<stmts>"}};
    parseTable["<stmts>"]["if"] = {"<stmts>", {"<stmt>", "<stmts>"}};
    parseTable["<stmts>"]["while"] = {"<stmts>", {"<stmt>", "<stmts>"}};
    parseTable["<stmts>"]["do"] = {"<stmts>", {"<stmt>", "<stmts>"}};
    parseTable["<stmts>"]["break"] = {"<stmts>", {"<stmt>", "<stmts>"}};
    parseTable["<stmts>"]["return"] = {"<stmts>", {"<stmt>", "<stmts>"}};
    parseTable["<stmts>"]["{"] = {"<stmts>", {"<stmt>", "<stmts>"}};

    // Add entries for <stmts'>
    parseTable["<stmts'>"]["id"] = {"<stmts'>", {"ε"}};
    parseTable["<stmts'>"]["if"] = {"<stmts'>", {"ε"}};
    parseTable["<stmts'>"]["while"] = {"<stmts'>", {"ε"}};
    parseTable["<stmts'>"]["do"] = {"<stmts'>", {"ε"}};
    parseTable["<stmts'>"]["break"] = {"<stmts'>", {"ε"}};
    parseTable["<stmts'>"]["return"] = {"<stmts'>", {"ε"}};
    parseTable["<stmts'>"]["{"] = {"<stmts'>", {"ε"}};

    // Add entries for <stmt>
    parseTable["<stmt>"]["id"] = {"<stmt>", {"<assign>"}};
    parseTable["<stmt>"]["if"] = {"<stmt>", {"if", "(", "<expr>", ")", "<stmt>", "<stmt_opt>"}};
    parseTable["<stmt>"]["while"] = {"<stmt>", {"while", "(", "<expr>", ")", "<stmt>"}};
    parseTable["<stmt>"]["do"] = {"<stmt>", {"do", "<stmt>", "while", "(", "<expr>", ")", ";"}};
    parseTable["<stmt>"]["break"] = {"<stmt>", {"break", ";"}};
    parseTable["<stmt>"]["return"] = {"<stmt>", {"return", "<expr>", ";"}};
    parseTable["<stmt>"]["{"] = {"<stmt>", {"<block>"}};

    // Add entries for <if_stmt>
    parseTable["<if_stmt>"]["if"] = {"<if_stmt>", {"if", "(", "<expr>", ")", "<stmt>", "<stmt_opt>"}};

    // Add entries for <if_opt>
    parseTable["<if_opt>"]["id"] = {"<if_opt>", {"else", "<stmt>"}};
    parseTable["<if_opt>"]["if"] = {"<if_opt>", {"else", "<stmt>"}};
    parseTable["<if_opt>"]["while"] = {"<if_opt>", {"else", "<stmt>"}};
    parseTable["<if_opt>"]["do"] = {"<if_opt>", {"else", "<stmt>"}};
    parseTable["<if_opt>"]["break"] = {"<if_opt>", {"else", "<stmt>"}};
    parseTable["<if_opt>"]["return"] = {"<if_opt>", {"else", "<stmt>"}};
    parseTable["<if_opt>"]["{"] = {"<if_opt>", {"else", "<stmt>"}};

    // Add entries for <loc>
    parseTable["<loc>"]["id"] = {"<loc>", {"id", "<loc_opt>"}};

    // Add entries for <loc'>
    parseTable["<loc'>"]["["] = {"<loc'>", {"[", "<expr>", "]"}};

    // Add entries for <bool>
    parseTable["<bool>"]["!"] = {"<bool>", {"true"}};
    parseTable["<bool>"]["-"] = {"<bool>", {"true"}};
    parseTable["<bool>"]["("] = {"<bool>", {"true"}};
    parseTable["<bool>"]["id"] = {"<bool>", {"true"}};
    parseTable["<bool>"]["num"] = {"<bool>", {"true"}};
    parseTable["<bool>"]["real"] = {"<bool>", {"true"}};
    parseTable["<bool>"]["true"] = {"<bool>", {"true"}};
    parseTable["<bool>"]["false"] = {"<bool>", {"true"}};

    // Add entries for <bool'>
    parseTable["<bool'>"]["||"] = {"<bool'>", {"==", "<expr>"}};

    // Add entries for <join>
    parseTable["<join>"]["!"] = {"<join>", {"<bool>", "<join_opt>"}};
    parseTable["<join>"]["-"] = {"<join>", {"<bool>", "<join_opt>"}};
    parseTable["<join>"]["("] = {"<join>", {"<bool>", "<join_opt>"}};
    parseTable["<join>"]["id"] = {"<join>", {"<bool>", "<join_opt>"}};
    parseTable["<join>"]["num"] = {"<join>", {"<bool>", "<join_opt>"}};
    parseTable["<join>"]["real"] = {"<join>", {"<bool>", "<join_opt>"}};
    parseTable["<join>"]["true"] = {"<join>", {"<bool>", "<join_opt>"}};
    parseTable["<join>"]["false"] = {"<join>", {"<bool>", "<join_opt>"}};

    // Add entries for <join'>
    parseTable["<join'>"]["&&"] = {"<join'>", {"&&", "<bool>", "<join_opt>"}};

    // Add entries for <equality>
    parseTable["<equality>"]["!"] = {"<equality>", {"<join>", "<equality_opt>"}};
    parseTable["<equality>"]["-"] = {"<equality>", {"<join>", "<equality_opt>"}};
    parseTable["<equality>"]["("] = {"<equality>", {"<join>", "<equality_opt>"}};
    parseTable["<equality>"]["id"] = {"<equality>", {"<join>", "<equality_opt>"}};
    parseTable["<equality>"]["num"] = {"<equality>", {"<join>", "<equality_opt>"}};
    parseTable["<equality>"]["real"] = {"<equality>", {"<join>", "<equality_opt>"}};
    parseTable["<equality>"]["true"] = {"<equality>", {"<join>", "<equality_opt>"}};
    parseTable["<equality>"]["false"] = {"<equality>", {"<join>", "<equality_opt>"}};

    // Add entries for <equality'>
    parseTable["<equality'>"]["=="] = {"<equality'>", {"==", "<join>", "<equality_opt>"}};
    parseTable["<equality'>"]["!="] = {"<equality'>", {"!=", "<join>", "<equality_opt>"}};

    // Add entries for <rel>
    parseTable["<rel>"]["!"] = {"<rel>", {"<equality>", "<rel_opt>"}};
    parseTable["<rel>"]["-"] = {"<rel>", {"<equality>", "<rel_opt>"}};
    parseTable["<rel>"]["("] = {"<rel>", {"<equality>", "<rel_opt>"}};
    parseTable["<rel>"]["id"] = {"<rel>", {"<equality>", "<rel_opt>"}};
    parseTable["<rel>"]["num"] = {"<rel>", {"<equality>", "<rel_opt>"}};
    parseTable["<rel>"]["real"] = {"<rel>", {"<equality>", "<rel_opt>"}};
    parseTable["<rel>"]["true"] = {"<rel>", {"<equality>", "<rel_opt>"}};
    parseTable["<rel>"]["false"] = {"<rel>", {"<equality>", "<rel_opt>"}};

    // Add entries for <expr>
    parseTable["<expr>"]["!"] = {"<expr>", {"<rel>", "<expr_opt>"}};
    parseTable["<expr>"]["-"] = {"<expr>", {"<rel>", "<expr_opt>"}};
    parseTable["<expr>"]["("] = {"<expr>", {"<rel>", "<expr_opt>"}};
    parseTable["<expr>"]["id"] = {"<expr>", {"<rel>", "<expr_opt>"}};
    parseTable["<expr>"]["num"] = {"<expr>", {"<rel>", "<expr_opt>"}};
    parseTable["<expr>"]["real"] = {"<expr>", {"<rel>", "<expr_opt>"}};
    parseTable["<expr>"]["true"] = {"<expr>", {"<rel>", "<expr_opt>"}};
    parseTable["<expr>"]["false"] = {"<expr>", {"<rel>", "<expr_opt>"}};

    // Add entries for <expr'>
    parseTable["<expr'>"]["+"] = {"<expr'>", {"=", "<expr>"}};
    parseTable["<expr'>"]["-"] = {"<expr'>", {"=", "<expr>"}};

    // Add entries for <term>
    parseTable["<term>"]["!"] = {"<term>", {"<expr>", "<term_opt>"}};
    parseTable["<term>"]["-"] = {"<term>", {"<expr>", "<term_opt>"}};
    parseTable["<term>"]["("] = {"<term>", {"<expr>", "<term_opt>"}};
    parseTable["<term>"]["id"] = {"<term>", {"<expr>", "<term_opt>"}};
    parseTable["<term>"]["num"] = {"<term>", {"<expr>", "<term_opt>"}};
    parseTable["<term>"]["real"] = {"<term>", {"<expr>", "<term_opt>"}};
    parseTable["<term>"]["true"] = {"<term>", {"<expr>", "<term_opt>"}};
    parseTable["<term>"]["false"] = {"<term>", {"<expr>", "<term_opt>"}};

    // Add entries for <term'>
    parseTable["<term'>"]["*"] = {"<term'>", {"*", "<term>"}};
    parseTable["<term'>"]["/"] = {"<term'>", {"/", "<term>"}};

    // Add entries for <unary>
    parseTable["<unary>"]["!"] = {"<unary>", {"<term>"}};
    parseTable["<unary>"]["-"] = {"<unary>", {"<term>"}};
    parseTable["<unary>"]["("] = {"<unary>", {"<term>"}};
    parseTable["<unary>"]["id"] = {"<unary>", {"<term>"}};
    parseTable["<unary>"]["num"] = {"<unary>", {"<term>"}};
    parseTable["<unary>"]["real"] = {"<unary>", {"<term>"}};
    parseTable["<unary>"]["true"] = {"<unary>", {"<term>"}};
    parseTable["<unary>"]["false"] = {"<unary>", {"<term>"}};

    // Add entries for <factor>
    parseTable["<factor>"]["("] = {"<factor>", {"<unary>"}};
    parseTable["<factor>"]["id"] = {"<factor>", {"<loc>"}};
    parseTable["<factor>"]["num"] = {"<factor>", {"num"}};
    parseTable["<factor>"]["real"] = {"<factor>", {"real"}};
    parseTable["<factor>"]["true"] = {"<factor>", {"true"}};
    parseTable["<factor>"]["false"] = {"<factor>", {"false"}};
}

// Function to retrieve a production from the parse table
Production getProduction(const string& nonTerminal, const string& terminal) {
    return parseTable[nonTerminal][terminal];
}
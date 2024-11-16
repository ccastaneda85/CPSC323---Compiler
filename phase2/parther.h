#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

// Define tokens as string constants for simplicity
enum Token {
    BASIC, MAIN, ID, NUM, REAL, TRUE, FALSE, IF, WHILE, DO, BREAK, RETURN,
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET, ASSIGN, PLUS, MINUS,
    MULT, DIV, LT, LE, GE, GT, AND, OR, EQ, NEQ, NOT, SEMICOLON, END
};

// Mapping from token strings to enum values
std::unordered_map<std::string, Token> tokenMap = {
    {"basic", BASIC}, {"main", MAIN}, {"id", ID}, {"num", NUM}, {"real", REAL}, {"true", TRUE}, {"false", FALSE},
    {"if", IF}, {"while", WHILE}, {"do", DO}, {"break", BREAK}, {"return", RETURN},
    {"(", LPAREN}, {")", RPAREN}, {"{", LBRACE}, {"}", RBRACE}, {"[", LBRACKET}, {"]", RBRACKET},
    {"=", ASSIGN}, {"+", PLUS}, {"-", MINUS}, {"*", MULT}, {"/", DIV},
    {"<", LT}, {"<=", LE}, {">=", GE}, {">", GT}, {"&&", AND}, {"||", OR}, {"==", EQ}, {"!=", NEQ}, {"!", NOT},
    {";", SEMICOLON}, {"$", END}
};

// Define a production rule
struct Production {
    std::string lhs; // Left-hand side
    std::vector<std::string> rhs; // Right-hand side symbols
};

// Parsing table using a map of non-terminal and terminal to production index
std::map<std::string, std::map<Token, int>> parsingTable;

// Function to initialize the parsing table based on the provided rules
void initializeParsingTable() {
    // Fill parsing table based on image provided.
    parsingTable["<program>"][BASIC] = 1;
    parsingTable["<block>"][LBRACE] = 2;
    parsingTable["<block_opt>"][BASIC] = 3;
    parsingTable["<block_opt>"][ID] = 4;
    parsingTable["<block_opt>"][IF] = 4;
    parsingTable["<block_opt>"][WHILE] = 4;
    parsingTable["<block_opt>"][DO] = 4;
    parsingTable["<block_opt>"][BREAK] = 4;
    parsingTable["<block_opt>"][RETURN] = 4;
    parsingTable["<block_opt>"][RBRACE] = 5;
    // Continue filling in entries based on the table image.
}

// List of production rules from the provided grammar
std::vector<Production> productions = {
    {"<program>", {"basic", "main()", "<block>"}},
    {"<block>", {"{", "<block_opt>"}},
    {"<block_opt>", {"<decls>", "<decls_opt>"}},
    {"<block_opt>", {"<stmts>"}},
    {"<block_opt>", {""}},
    {"<decls_opt>", {"<stmts>"}},
    {"<decls_opt>", {""}},
    {"<decls>", {"<decl>", "<decls’>"}},
    {"<decls’>", {"<decl>", "<decls’>"}},
    {"<decls’>", {""}},
    {"<decl>", {"<type>", "id", ";"}},
    {"<type>", {"basic", "<type’>"}},
    {"<type’>", {"[", "num", "]", "<type’>"}},
    {"<type’>", {""}},
    // Continue adding the remaining production rules based on the rules provided
};

// Token stream for testing
std::vector<Token> inputTokens = {BASIC, MAIN, LPAREN, RPAREN, LBRACE, RBRACE, END};

// Parsing function
bool parse(const std::vector<Token>& tokens) {
    std::stack<std::string> parseStack;
    parseStack.push("$");  // End marker
    parseStack.push("<program>");  // Start symbol

    size_t index = 0;
    Token lookahead = tokens[index];

    while (!parseStack.empty()) {
        std::string top = parseStack.top();
        parseStack.pop();

        // Check if the top of the stack is a terminal
        if (tokenMap.count(top) > 0) {
            // Terminal should match the lookahead
            if (tokenMap[top] == lookahead) {
                index++;
                lookahead = (index < tokens.size()) ? tokens[index] : END;
            } else {
                std::cout << "Syntax error: unexpected token" << std::endl;
                return false;
            }
        } else if (parsingTable[top].count(lookahead) > 0) {
            // Apply the production rule from the table
            int productionIndex = parsingTable[top][lookahead];
            Production prod = productions[productionIndex - 1]; // Adjust index for 0-based array

            // Push RHS of the production in reverse order
            for (auto it = prod.rhs.rbegin(); it != prod.rhs.rend(); ++it) {
                if (*it != "") parseStack.push(*it); // Skip ε (empty production)
            }
        } else {
            std::cout << "Syntax error: no matching rule" << std::endl;
            return false;
        }
    }

    return (lookahead == END);
}

int main() {
    initializeParsingTable();

    // Parse the token stream
    if (parse(inputTokens)) {
        std::cout << "Parsing succeeded!" << std::endl;
    } else {
        std::cout << "Parsing failed!" << std::endl;
    }

    return 0;
}

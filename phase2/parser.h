#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include "utilities.h"

using namespace std;


struct Production {
    std::string lhs; // Left-hand side
    std::vector<std::string> rhs; // Right-hand side symbols
};

std::vector<Production> productions = {
    {"<Program>", {"basic", "main", "(", ")", "<Block>"}},
    {"<Block>", {"{", "<Block''>"}},
    {"<Decls>", {"<Decl>", "<Decls'>"}},
    {"<Decl>", {"<Type>", "id", ";"}},
    {"<Type>", {"basic", "<Type'>"}},
    {"<Stmts>", {"<Stmt>", "<Stmts'>"}},
    {"<Stmt>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>"}},
    {"<Stmt>", {"<Loc>", "=", "<Bool>", ";"}},
    {"<Stmt>", {"while", "(", "<Bool>", ")", "<Stmt>"}},
    {"<Stmt>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";"}},
    {"<Stmt>", {"return", "num", ";"}},
    {"<Stmt>", {"break", ";"}},
    {"<Stmt>", {"{", "<Block''>"}},
    {"<Loc>", {"id", "<Loc'>"}},
    {"<Bool>", {"<Join>", "<Bool'>"}},
    {"<Join>", {"<Equality>", "<Join'>"}},
    {"<Equality>", {"<Rel>", "<Equality''>"}},
    {"<Rel>", {"<Expr>", "<Rel'>"}},
    {"<Expr>", {"<Term>", "<Expr''>"}},
    {"<Term>", {"<Unary>", "<Term''>"}},
    {"<Unary>", {"!", "<Unary>"}},
    {"<Unary>", {"-", "<Unary>"}},
    {"<Unary>", {"<Factor>"}},
    {"<Factor>", {"(", "<Bool>", ")"}},
    {"<Factor>", {"id", "<Loc'>"}},
    {"<Factor>", {"num"}},
    {"<Factor>", {"real"}},
    {"<Factor>", {"true"}},
    {"<Factor>", {"false"}},
    {"<Block'>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>", "<Stmts'>", "}"}},
    {"<Block'>", {"id", "<Loc'>", "=", "<Bool>", ";", "<Stmts'>", "}"}},
    {"<Block'>", {"while", "(", "<Bool>", ")", "<Stmt>", "<Stmts'>", "}"}},
    {"<Block'>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";", "<Stmts'>", "}"}},
    {"<Block'>", {"return", "num", ";", "<Stmts'>", "}"}},
    {"<Block'>", {"break", ";", "<Stmts'>", "}"}},
    {"<Block'>", {"{", "<Block''>", "<Stmts'>", "}"}},
    {"<Block'>", {"}"}},
    {"<Block''>", {"basic", "<Type'>", "id", ";", "<Decls'>", "<Block'>"}},
    {"<Block''>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>", "<Stmts'>", "}"}},
    {"<Block''>", {"id", "<Loc'>", "=", "<Bool>", ";", "<Stmts'>", "}"}},
    {"<Block''>", {"while", "(", "<Bool>", ")", "<Stmt>", "<Stmts'>", "}"}},
    {"<Block''>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";", "<Stmts'>", "}"}},
    {"<Block''>", {"return", "num", ";", "<Stmts'>", "}"}},
    {"<Block''>", {"break", ";", "<Stmts'>", "}"}},
    {"<Block''>", {"{", "<Block''>", "<Stmts'>", "}"}},
    {"<Block''>", {"}"}},
    {"<Stmts'>", {"if", "(", "<Bool>", ")", "<Stmt>", "<Stmt'>", "<Stmts'>"}},
    {"<Stmts'>", {"id", "<Loc'>", "=", "<Bool>", ";", "<Stmts'>"}},
    {"<Stmts'>", {"while", "(", "<Bool>", ")", "<Stmt>", "<Stmts'>"}},
    {"<Stmts'>", {"do", "<Stmt>", "while", "(", "<Bool>", ")", ";", "<Stmts'>"}},
    {"<Stmts'>", {"return", "num", ";", "<Stmts'>"}},
    {"<Stmts'>", {"break", ";", "<Stmts'>"}},
    {"<Stmts'>", {"{", "<Block''>", "<Stmts'>"}},
    {"<Stmts'>", {""}},
    {"<Stmt'>", {""}},
    {"<Stmt'>", {"else", "<Stmt>"}},
    {"<Equality'>", {"==", "<Rel>"}},
    {"<Equality'>", {"!=", "<Rel>"}},
    {"<Rel'>", {"<", "<Expr>"}},
    {"<Rel'>", {"<=", "<Expr>"}},
    {"<Rel'>", {">=", "<Expr>"}},
    {"<Rel'>", {">", "<Expr>"}},
    {"<Rel'>", {""}},
    {"<Expr'>", {"+", "<Term>"}},
    {"<Expr'>", {"-", "<Term>"}},
    {"<Term'>", {"/", "<Unary>"}},
    {"<Term'>", {"*", "<Unary>"}},
    {"<Decls'>", {"<Decl>", "<Decls'>"}},
    {"<Decls'>", {""}},
    {"<Type'>", {"[", "num", "]", "<Type'>"}},
    {"<Type'>", {""}},
    {"<Loc'>", {"[", "<Bool>", "]", "<Loc'>"}},
    {"<Loc'>", {""}},
    {"<Bool'>", {"||", "<Join>", "<Bool'>"}},
    {"<Bool'>", {""}},
    {"<Join'>", {"&&", "<Equality>", "<Join'>"}},
    {"<Join'>", {""}},
    {"<Equality''>", {"<Equality'>", "<Equality''>"}},
    {"<Equality''>", {""}},
    {"<Expr''>", {"<Expr'>", "<Expr''>"}},
    {"<Expr''>", {""}},
    {"<Term''>", {"<Term'>", "<Term''>"}},
    {"<Term''>", {""}}
};

map<pair<string, string>, int> parsingTable;
void initializeParsingTable() {
    parsingTable[{"<Program>", "basic"}] = 0;
    parsingTable[{"<Block>", "{"}] = 1;
    parsingTable[{"<Decls>", "basic"}] = 2;
    parsingTable[{"<Decl>", "basic"}] = 3;
    parsingTable[{"<Type>", "basic"}] = 4;
    parsingTable[{"<Stmts>", "{"}] = 5;
    parsingTable[{"<Stmts>", "id"}] = 5;
    parsingTable[{"<Stmts>", "if"}] = 5;
    parsingTable[{"<Stmts>", "while"}] = 5;
    parsingTable[{"<Stmts>", "do"}] = 5;
    parsingTable[{"<Stmts>", "return"}] = 5;
    parsingTable[{"<Stmts>", "break"}] = 5;
    parsingTable[{"<Stmt>", "{"}] = 12;
    parsingTable[{"<Stmt>", "id"}] = 7;
    parsingTable[{"<Stmt>", "if"}] = 6;
    parsingTable[{"<Stmt>", "while"}] = 8;
    parsingTable[{"<Stmt>", "do"}] = 9;
    parsingTable[{"<Stmt>", "return"}] = 10;
    parsingTable[{"<Stmt>", "break"}] = 11;
    parsingTable[{"<Loc>", "id"}] = 13;
    parsingTable[{"<Bool>", "("}] = 14;
    parsingTable[{"<Bool>", "id"}] = 14;
    parsingTable[{"<Bool>", "num"}] = 14;
    parsingTable[{"<Bool>", "!"}] = 14;
    parsingTable[{"<Bool>", "-"}] = 14;
    parsingTable[{"<Bool>", "real"}] = 14;
    parsingTable[{"<Bool>", "TRUE"}] = 14;
    parsingTable[{"<Bool>", "FALSE"}] = 14;
    parsingTable[{"<Join>", "("}] = 15;
    parsingTable[{"<Join>", "id"}] = 15;
    parsingTable[{"<Join>", "num"}] = 15;
    parsingTable[{"<Join>", "!"}] = 15;
    parsingTable[{"<Join>", "-"}] = 15;
    parsingTable[{"<Join>", "real"}] = 15;
    parsingTable[{"<Join>", "TRUE"}] = 15;
    parsingTable[{"<Join>", "FALSE"}] = 15;
    parsingTable[{"<Equality>", "("}] = 16;
    parsingTable[{"<Equality>", "id"}] = 16;
    parsingTable[{"<Equality>", "num"}] = 16;
    parsingTable[{"<Equality>", "!"}] = 16;
    parsingTable[{"<Equality>", "-"}] = 16;
    parsingTable[{"<Equality>", "real"}] = 16;
    parsingTable[{"<Equality>", "TRUE"}] = 16;
    parsingTable[{"<Equality>", "FALSE"}] = 16;
    parsingTable[{"<Rel>", "("}] = 17;
    parsingTable[{"<Rel>", "id"}] = 17;
    parsingTable[{"<Rel>", "num"}] = 17;
    parsingTable[{"<Rel>", "!"}] = 17;
    parsingTable[{"<Rel>", "-"}] = 17;
    parsingTable[{"<Rel>", "real"}] = 17;
    parsingTable[{"<Rel>", "TRUE"}] = 17;
    parsingTable[{"<Rel>", "FALSE"}] = 17;
    parsingTable[{"<Expr>", "("}] = 18;
    parsingTable[{"<Expr>", "id"}] = 18;
    parsingTable[{"<Expr>", "num"}] = 18;
    parsingTable[{"<Expr>", "!"}] = 18;
    parsingTable[{"<Expr>", "-"}] = 18;
    parsingTable[{"<Expr>", "real"}] = 18;
    parsingTable[{"<Expr>", "TRUE"}] = 18;
    parsingTable[{"<Expr>", "FALSE"}] = 18;
    parsingTable[{"<Term>", "("}] = 19;
    parsingTable[{"<Term>", "id"}] = 19;
    parsingTable[{"<Term>", "num"}] = 19;
    parsingTable[{"<Term>", "!"}] = 19;
    parsingTable[{"<Term>", "-"}] = 19;
    parsingTable[{"<Term>", "real"}] = 19;
    parsingTable[{"<Term>", "TRUE"}] = 19;
    parsingTable[{"<Term>", "FALSE"}] = 19;
    parsingTable[{"<Unary>", "("}] = 22;
    parsingTable[{"<Unary>", "id"}] = 22;
    parsingTable[{"<Unary>", "num"}] = 22;
    parsingTable[{"<Unary>", "!"}] = 20;
    parsingTable[{"<Unary>", "-"}] = 21;
    parsingTable[{"<Unary>", "real"}] = 22;
    parsingTable[{"<Unary>", "TRUE"}] = 22;
    parsingTable[{"<Unary>", "FALSE"}] = 22;
    parsingTable[{"<Factor>", "("}] = 23;
    parsingTable[{"<Factor>", "id"}] = 24;
    parsingTable[{"<Factor>", "num"}] = 25;
    parsingTable[{"<Factor>", "real"}] = 26;
    parsingTable[{"<Factor>", "TRUE"}] = 27;
    parsingTable[{"<Factor>", "FALSE"}] = 28;
    parsingTable[{"<Block'>", "{"}] = 35;
    parsingTable[{"<Block'>", "id"}] = 30;
    parsingTable[{"<Block'>", "if"}] = 29;
    parsingTable[{"<Block'>", "while"}] = 31;
    parsingTable[{"<Block'>", "do"}] = 32;
    parsingTable[{"<Block'>", "return"}] = 33;
    parsingTable[{"<Block'>", "break"}] = 34;
    parsingTable[{"<Block'>", "}"}] = 36;
    parsingTable[{"<Block''>", "basic"}] = 37;
    parsingTable[{"<Block''>", "{"}] = 44;
    parsingTable[{"<Block''>", "id"}] = 39;
    parsingTable[{"<Block''>", "if"}] = 38;
    parsingTable[{"<Block''>", "while"}] = 40;
    parsingTable[{"<Block''>", "do"}] = 41;
    parsingTable[{"<Block''>", "return"}] = 42;
    parsingTable[{"<Block''>", "break"}] = 43;
    parsingTable[{"<Block''>", "}"}] = 45;
    parsingTable[{"<Stmts'>", "{"}] = 52;
    parsingTable[{"<Stmts'>", "id"}] = 47;
    parsingTable[{"<Stmts'>", "if"}] = 46;
    parsingTable[{"<Stmts'>", "while"}] = 48;
    parsingTable[{"<Stmts'>", "do"}] = 49;
    parsingTable[{"<Stmts'>", "return"}] = 50;
    parsingTable[{"<Stmts'>", "break"}] = 51;
    parsingTable[{"<Stmts'>", "}"}] = 53;
    parsingTable[{"<Stmt'>", "{"}] = 54;
    parsingTable[{"<Stmt'>", "id"}] = 54;
    parsingTable[{"<Stmt'>", "if"}] = 54;
    parsingTable[{"<Stmt'>", "while"}] = 54;
    parsingTable[{"<Stmt'>", "do"}] = 54;
    parsingTable[{"<Stmt'>", "return"}] = 54;
    parsingTable[{"<Stmt'>", "break"}] = 54;
    parsingTable[{"<Stmt'>", "}"}] = 54;
    parsingTable[{"<Stmt'>", "else"}] = 54;
    parsingTable[{"<Stmt'>", "$"}] = 54;
    parsingTable[{"<nan>", "else"}] = 55;
    parsingTable[{"<Equality'>", "=="}] = 56;
    parsingTable[{"<Equality'>", "!="}] = 57;
    parsingTable[{"<Rel'>", ")"}] = 62;
    parsingTable[{"<Rel'>", ";"}] = 62;
    parsingTable[{"<Rel'>", "=="}] = 62;
    parsingTable[{"<Rel'>", "!="}] = 62;
    parsingTable[{"<Rel'>", "<"}] = 58;
    parsingTable[{"<Rel'>", "<="}] = 59;
    parsingTable[{"<Rel'>", ">="}] = 60;
    parsingTable[{"<Rel'>", ">"}] = 61;
    parsingTable[{"<Rel'>", "]"}] = 62;
    parsingTable[{"<Rel'>", "||"}] = 62;
    parsingTable[{"<Rel'>", "&&"}] = 62;
    parsingTable[{"<Expr'>", "-"}] = 64;
    parsingTable[{"<Expr'>", "+"}] = 63;
    parsingTable[{"<Term'>", "/"}] = 65;
    parsingTable[{"<Term'>", "*"}] = 66;
    parsingTable[{"<Decls'>", "basic"}] = 67;
    parsingTable[{"<Decls'>", "{"}] = 68;
    parsingTable[{"<Decls'>", "id"}] = 68;
    parsingTable[{"<Decls'>", "if"}] = 68;
    parsingTable[{"<Decls'>", "while"}] = 68;
    parsingTable[{"<Decls'>", "do"}] = 68;
    parsingTable[{"<Decls'>", "return"}] = 68;
    parsingTable[{"<Decls'>", "break"}] = 68;
    parsingTable[{"<Decls'>", "}"}] = 68;
    parsingTable[{"<Type'>", "id"}] = 70;
    parsingTable[{"<Type'>", "["}] = 69;
    parsingTable[{"<Loc'>", ")"}] = 72;
    parsingTable[{"<Loc'>", ";"}] = 72;
    parsingTable[{"<Loc'>", "="}] = 72;
    parsingTable[{"<Loc'>", "-"}] = 72;
    parsingTable[{"<Loc'>", "=="}] = 72;
    parsingTable[{"<Loc'>", "!="}] = 72;
    parsingTable[{"<Loc'>", "<"}] = 72;
    parsingTable[{"<Loc'>", "<="}] = 72;
    parsingTable[{"<Loc'>", ">="}] = 72;
    parsingTable[{"<Loc'>", ">"}] = 72;
    parsingTable[{"<Loc'>", "+"}] = 72;
    parsingTable[{"<Loc'>", "/"}] = 72;
    parsingTable[{"<Loc'>", "*"}] = 72;
    parsingTable[{"<Loc'>", "["}] = 71;
    parsingTable[{"<Loc'>", "]"}] = 72;
    parsingTable[{"<Loc'>", "||"}] = 72;
    parsingTable[{"<Loc'>", "&&"}] = 72;
    parsingTable[{"<Bool'>", ")"}] = 74;
    parsingTable[{"<Bool'>", ";"}] = 74;
    parsingTable[{"<Bool'>", "]"}] = 74;
    parsingTable[{"<Bool'>", "||"}] = 73;
    parsingTable[{"<Join'>", ")"}] = 76;
    parsingTable[{"<Join'>", ";"}] = 76;
    parsingTable[{"<Join'>", "]"}] = 76;
    parsingTable[{"<Join'>", "||"}] = 76;
    parsingTable[{"<Join'>", "&&"}] = 75;
    parsingTable[{"<Equality''>", ")"}] = 78;
    parsingTable[{"<Equality''>", ";"}] = 78;
    parsingTable[{"<Equality''>", "=="}] = 77;
    parsingTable[{"<Equality''>", "!="}] = 77;
    parsingTable[{"<Equality''>", "]"}] = 78;
    parsingTable[{"<Equality''>", "||"}] = 78;
    parsingTable[{"<Equality''>", "&&"}] = 78;
    parsingTable[{"<Expr''>", ")"}] = 80;
    parsingTable[{"<Expr''>", ";"}] = 80;
    parsingTable[{"<Expr''>", "-"}] = 79;
    parsingTable[{"<Expr''>", "=="}] = 80;
    parsingTable[{"<Expr''>", "!="}] = 80;
    parsingTable[{"<Expr''>", "<"}] = 80;
    parsingTable[{"<Expr''>", "<="}] = 80;
    parsingTable[{"<Expr''>", ">="}] = 80;
    parsingTable[{"<Expr''>", ">"}] = 80;
    parsingTable[{"<Expr''>", "+"}] = 79;
    parsingTable[{"<Expr''>", "]"}] = 80;
    parsingTable[{"<Expr''>", "||"}] = 80;
    parsingTable[{"<Expr''>", "&&"}] = 80;
    parsingTable[{"<Term''>", ")"}] = 82;
    parsingTable[{"<Term''>", ";"}] = 82;
    parsingTable[{"<Term''>", "-"}] = 82;
    parsingTable[{"<Term''>", "=="}] = 82;
    parsingTable[{"<Term''>", "!="}] = 82;
    parsingTable[{"<Term''>", "<"}] = 82;
    parsingTable[{"<Term''>", "<="}] = 82;
    parsingTable[{"<Term''>", ">="}] = 82;
    parsingTable[{"<Term''>", ">"}] = 82;
    parsingTable[{"<Term''>", "+"}] = 82;
    parsingTable[{"<Term''>", "/"}] = 81;
    parsingTable[{"<Term''>", "*"}] = 81;
    parsingTable[{"<Term''>", "]"}] = 82;
    parsingTable[{"<Term''>", "||"}] = 82;
    parsingTable[{"<Term''>", "&&"}] = 82;
}





void parser(vector<Token> &tokenStream) {
    
    initializeParsingTable();
    stack <string> parsingStack;
    int p1 = 0;
    
    parsingStack.push("$");
        printStackBottomToTop(parsingStack);
        cout << "p1: "<< tokenStream.at(p1).getType() << endl;
    
    parsingStack.push("<Program>");
        printStackBottomToTop(parsingStack);
        cout << "p1: "<< tokenStream.at(p1).getType() << endl;
    
    while(!parsingStack.empty()) {

        
        if(parsingStack.top() == "") {
            parsingStack.pop();
            printStackBottomToTop(parsingStack);
            cout << "p1: "<< tokenStream.at(p1).getType() << endl;
        }
       

       if(parsingStack.top() == tokenStream.at(p1).getType()) {
            p1++;
            parsingStack.pop();
                printStackBottomToTop(parsingStack);
                cout << "p1: "<< tokenStream.at(p1).getType() << endl;
        }
        else if (parsingTable.find({parsingStack.top(), tokenStream.at(p1).getType()}) != parsingTable.end()) {
            vector<string> rhs = productions.at(parsingTable[{parsingStack.top(), tokenStream.at(p1).getType()}]).rhs;
            parsingStack.pop();
            for(int i = rhs.size()-1 ; i >= 0; --i){
                parsingStack.push(rhs.at(i));
                
            }
                
            printStackBottomToTop(parsingStack);
            cout << "p1: "<< tokenStream.at(p1).getType() << endl;
            
        }
        else {
            cout << "syntax eror at: " << "line : " << tokenStream.at(p1).getLineNum() << " and character position: " << tokenStream.at(p1).getFirstCharPos() << endl;
            cout << "p1: "<< tokenStream.at(p1).getType() << endl;
            break;
        }
    }   

}




#endif //PARSER_H
//basic main ( ) { basic id = num ; id ++ ; id < < num ; id num ; }
/*
[ $ <Program> 
[ $ <Block> ) ( main basic 
syntax eror at: line : 1 and character position: 4
*/

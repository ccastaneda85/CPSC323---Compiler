//symboltable.h

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <map>
#include "token.h"

using namespace std;

class SymbolTable {

    private: 
        int key;
        map<int, Token> table;
    
    public:
        SymbolTable() {
            key = 1;
        };
        void addItem(Token& inputToken) {
            table[key++] = inputToken;
        }
        
        void displayItems() const {
            for (const auto& item : table) {
                std::cout << "Key: " << item.first << ", Value: " << item.second.itemToString() << std::endl;
            }
        }
        
        Token get(const int &key) {
            return table[key];
        }
    

};




#endif
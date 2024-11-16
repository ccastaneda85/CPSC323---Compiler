#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

class Token {
    private:
        string lexeme;
        string type;
        int lineNum;
        int firstCharPos;
        int length;
        
   
    public:
        Token() : lexeme(""), type(""), lineNum(0), firstCharPos(0), length(0) {}

        Token(const string &lexeme, const string &type, int lineNum, int firstCharPos, int length) {
            this->lexeme = lexeme;
            this->type = type;
            this->lineNum = lineNum;
            this->firstCharPos = firstCharPos;
            this->length = length;
        }
        
        void setValues(const string &lexeme, const string &type, int lineNum, int firstCharPos, int length) {
            this->lexeme = lexeme;
            this->type = type;
            this->lineNum = lineNum;
            this->firstCharPos = firstCharPos;
            this->length = length;
        }

        string getLexeme() const {
            return lexeme;
        }

        string getType() const {
            return type;
        }

        int getLineNum() const {
            return lineNum;
        }

        int getFirstCharPos() const {
            return firstCharPos;
        }

        int getLength() const {
            return length;
        }

        string itemToString() const {
            return lexeme + " " + type + " " + std::to_string(lineNum) + " " + std::to_string(firstCharPos) + " " + std::to_string(length);
        }

        void printItems() {
            cout << lexeme << " " << type << " " << lineNum << " " << firstCharPos << " " << length << " " << endl; 
        }



};

#endif // TOKEN_H

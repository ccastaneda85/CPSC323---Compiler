#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<utility>

using namespace std;


string fileReader(const string& filename);
vector<pair<string, string> > lexicalAnalyzer(const string& inputString);

int main(int argc, char const *argv[])
{
    
    vector<pair<string, string> > lexemeTokenStream;
    
    //string testString = " int myInt = 0;";
    string testString = fileReader("front.in");
    
    lexemeTokenStream = lexicalAnalyzer(testString);
   
    for(int i = 0; i < lexemeTokenStream.size(); i++) {
        cout << lexemeTokenStream.at(i).first << " -> " << lexemeTokenStream.at(i).second << endl;
    }

    
    return 0;
}



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


vector<pair<string, string> > lexicalAnalyzer(const string& inputString) {
    
    vector<pair<string, string> > lexemeTokenStream;
    
    int p1 = 0;
    int p2 = 0;
    
    while(p1 < inputString.size()) {

        while(isspace(inputString[p1])) {
            
            p1++;
        }
        
        if(isalpha(inputString[p1])) {
            
            p2 = p1;
            
            while(isalnum(inputString[p2])) {
                
                p2++;
                
            }   

            lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), "Identifier"));
            p1 = p2 + 1;

        
        }
        else if(isdigit(inputString[p1])) {
            
            p2 = p1;

            while(isdigit(inputString[p2])) {
                p2++;
            }

            lexemeTokenStream.push_back(make_pair(inputString.substr(p1, p2 - p1), "Number"));
            p1 = p2 + 1;

        }
        else{
            
            lexemeTokenStream.push_back(make_pair(inputString.substr(p1, 1), "other"));
            p1++;
        }
        
    }
        

    return lexemeTokenStream;
}


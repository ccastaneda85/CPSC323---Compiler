//utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

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

#endif //UTILITY_H
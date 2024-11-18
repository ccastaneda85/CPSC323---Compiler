// utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

string fileReader(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void printStackBottomToTop(stack<string> s)
{
    vector<string> temp;

    // Transfer stack contents to a vector
    while (!s.empty())
    {
        temp.push_back(s.top());
        s.pop();
    }

    // Print vector in reverse order to simulate bottom-to-top
    cout << "[ ";
    for (auto it = temp.rbegin(); it != temp.rend(); ++it)
    {
        cout << *it << " ";
    }
    // cout << endl;
}

#endif // UTILITY_H
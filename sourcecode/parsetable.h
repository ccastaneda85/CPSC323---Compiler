#ifndef PARSETABLE_H
#define PARSETABLE_H

#include <map>
#include <string>
#include <vector>

// Define the type for the parse table
using ParseTable = std::map<std::string, std::map<std::string, std::pair<std::string, std::vector<std::string>>>>;

// Declare the parse table
extern ParseTable parseTable;

#endif // PARSETABLE_H
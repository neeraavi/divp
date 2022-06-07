#pragma once
#include <string>
#include <vector>

using linesAsVector = std::vector<std::vector<std::string>>;

linesAsVector readFile(const std::string &filename);
void printLines(const linesAsVector &lines);
void printStringVector(std::vector<std::string> v);

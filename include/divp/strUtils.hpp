#pragma once
#include <regex>
#include <string>

static const auto spaceAtBeginning = std::regex("^\\s+");
static const auto spaceAtEnd = std::regex("\\s+$");
static const auto emptyString = std::string("");

std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);
std::string toLower(std::string &data);

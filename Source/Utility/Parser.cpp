#include "Utility/Parser.hpp"

Parser::Parser(const std::string& path)
: file{ path }, cursor{ 0u }
{
	if(!file.good())
		throw std::runtime_error{ "[PARSER] Could not load file " + path };
}

#include <iostream>
bool Parser::skipToNextLine()
{
    while(true)
	{
		if(file.eof())
			return false;

		std::getline(file, currentLine);

		if(currentLine.empty() || (currentLine[0] == '/' && currentLine[1] == '/'))
			continue;

		break;
	}


	cursor = 0u;
	return true;
}

void Parser::getNextString(std::string& str, bool cvt)
{
	if(skipToNextLine() == false)
		throw std::runtime_error{ "[PARSER] Could not find another string." };

	str = currentLine;

	if(cvt)
	{
		auto pos = 0u, first = pos;
		while((pos = str.find("\\n", first)) != std::string::npos)
		{
			str.replace(pos, 2, "\n");
			first = pos - 2;
		}
	}
}

void Parser::getNextKeyValuePair(std::string& key, std::string& value, const char& separator)
{
	key.clear();

	// Build the key word
	while(currentLine[cursor] != separator)
		key += currentLine[cursor++];

	// Skip the separator
	++cursor;

	value.clear();

	// Build the value word
	while(cursor < currentLine.size())
		value += currentLine[cursor++];
}

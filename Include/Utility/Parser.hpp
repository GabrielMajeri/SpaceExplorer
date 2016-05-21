#pragma once

#include <string>
#include <fstream>

class Parser
{
public:
	Parser(const std::string& path);


	/// Returns true if there are lines left to process
	/// False if EOF is reached
	bool skipToNextLine();

	void getNextString(std::string& str, bool convertEscapedChars = true);

	void getNextKeyValuePair(std::string& key, std::string& value, const char& separator);

private:
	std::ifstream file;

	std::string currentLine;
	uint32_t cursor;
};

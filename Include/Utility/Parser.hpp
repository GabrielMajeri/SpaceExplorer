#pragma once

#include <string>
#include <fstream>

/// General purpose text file parsers. Scans file for different data types.
/// Designed to load config files and game data.
class Parser
{
public:
	/// Constructs a new parser and opens the file at path
	/// Does not read anything
	Parser(const std::string& path);

	/// Returns true if there are lines left to process
	/// False if EOF is reached
	bool skipToNextLine();

	/// Gets the next line that is not a comment, empty or invalid
	void getNextString(std::string& str, bool convertEscapedChars = true);

	/// Gets the next key and value pair separated by the separator
	void getNextKeyValuePair(std::string& key, std::string& value, const char& separator);

	/// Gets the next float value on the current line
	/// Does not move to another line automatically
	float getNextFloat();

	/// Gets the next integer on the current line
	/// Does not move to another line automatically
	int32_t getNextInt();

private:
	/// The file to read
	std::ifstream file;

	/// Buffer for the current line
	std::string currentLine;

	/// Cursor stores the current position in the buffer
	uint32_t cursor;
};

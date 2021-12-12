#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include <LevelEditor/LevelData.h>
#include <string>

struct LevelParser
{
	static LevelData loadFromFile(const std::string& filename);
	static LevelData loadFromString(const std::string& serializedLevel);

	static std::string serialize(const LevelData& data);
	static void saveToFile(const LevelData& data, const std::string& filename);
};

#endif
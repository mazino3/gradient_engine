#include <LevelEditor/LevelParser.h>
#include <json.hpp>

using json = nlohmann::json;


void to_json(json& j, const LevelDataObject& levelObject)
{
	j = json
		{
			{"pos", 
			{
				{"x", levelObject.position.x},
				{"y", levelObject.position.y},
				{"z", levelObject.position.z}
			}},
			{"scale", 
			{
				{"x", levelObject.scale.x},
				{"y", levelObject.scale.y},
				{"z", levelObject.scale.z}
			}}
		};
}

void from_json(const json& j, LevelDataObject& levelObject)
{
	j.at("pos").at("x").get_to(levelObject.position.x);
	j.at("pos").at("y").get_to(levelObject.position.y);
	j.at("pos").at("z").get_to(levelObject.position.z);

	j.at("scale").at("x").get_to(levelObject.scale.x);
	j.at("scale").at("y").get_to(levelObject.scale.y);
	j.at("scale").at("z").get_to(levelObject.scale.z);
}

void to_json(json& j, const LevelData& levelData)
{
	j = json
		{
			{"objects", levelData.objects}
		};
}

void from_json(const json& j, LevelData& levelData)
{
	j.at("objects").get_to(levelData.objects);
}

LevelData LevelParser::loadFromFile(const std::string& filename)
{
	//todo: implement
	LevelData result;
	return result;
}

LevelData LevelParser::loadFromString(const std::string& serializedLevel)
{
	LevelData result = json::parse(serializedLevel.begin(), serializedLevel.end());
	return result;
}

std::string LevelParser::serialize(const LevelData& data)
{
	json result = data;
	return result.dump();
}

void LevelParser::saveToFile(const LevelData& data, const std::string& filename)
{
	//todo: implement
}
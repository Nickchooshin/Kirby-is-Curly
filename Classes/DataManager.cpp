#include "DataManager.h"
#include "cocos2d.h"

#include "json/filereadstream.h""

void DataManager::LoadActionData()
{
	std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("./Data/actions.json");

	char buffer[65536];
	FILE *file = fopen(filePath.c_str(), "r");

	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	actionDocument.ParseStream(is);
	fclose(file);
}

std::string DataManager::GetActionName(int actionNum) const
{
	return actionDocument[actionNum - 1]["Action"].GetString();
}

int DataManager::GetChildHappiness(int actionNum) const
{
	return actionDocument[actionNum - 1]["Child"].GetInt();
}

int DataManager::GetMotherHappiness(int actionNum) const
{
	return actionDocument[actionNum - 1]["Mother"].GetInt();
}

std::string DataManager::GetScriptPath(int actionNum) const
{
	return actionDocument[actionNum - 1]["Script"].GetString();
}
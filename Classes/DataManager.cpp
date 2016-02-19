#include "DataManager.h"
#include "cocos2d.h"

#include "json/filereadstream.h""

const float PENALTY = 0.8f;

void DataManager::Init()
{
	childHappiness = 5.0f;
	motherHappiness = 5.0f;
	time = 10;

	maxHapiness = 10.0f;
}

void DataManager::LoadActionData()
{
	std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("./Data/actions.json");

	char buffer[65536];
	FILE *file = fopen(filePath.c_str(), "r");

	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	actionDocument.ParseStream(is);
	fclose(file);
}

void DataManager::SetRoomNum(int roonNum)
{
	m_roomNum = roonNum;
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

int DataManager::GetMotherPosition() const
{
	return m_motherPosition;
}

int DataManager::GetActionIfType(int actionNum) const
{
	if (actionDocument[actionNum - 1].HasMember("If"))
	{
		if (actionDocument[actionNum - 1]["If"] == "Mother")
			return 1;
		else if (actionDocument[actionNum - 1]["If"] == "Friends")
			return 2;
	}

	return 0;
}

void DataManager::AddChildHapinessValue(int actionNum)
{
	float value = DataManager::getInstance()->GetChildHappiness(actionNum);

	if (prevActionNum == actionNum)
		value *= PENALTY;

	childHappiness += value;

	if (childHappiness < 0.0f)
		childHappiness = 0.0f;
	else if (childHappiness > maxHapiness)
		childHappiness = maxHapiness;
}

void DataManager::AddMotherHapinessValue(int actionNum)
{
	float value = DataManager::getInstance()->GetMotherHappiness(actionNum);

	if (prevActionNum == actionNum)
		value *= PENALTY;

	motherHappiness += value;

	if (motherHappiness < 0.0f)
		motherHappiness = 0.0f;
	else if (motherHappiness > maxHapiness)
		motherHappiness = maxHapiness;
}

void DataManager::RandomMotherPosition()
{
	// 5 ~ 7 pm
	if (time >= 17 && time <= 19)
	{
		m_motherPosition = 5;
	}
	else
	{
		m_motherPosition = rand() % m_roomNum;
	}
}
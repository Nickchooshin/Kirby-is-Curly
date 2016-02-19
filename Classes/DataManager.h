#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include "Singleton.h"

#include "json/document.h"

class DataManager : public Singleton < DataManager >
{
private:
	rapidjson::Document actionDocument;
	int m_motherPosition;
	int m_roomNum;
public:
	int actionNum;
	int childHappiness;
	int motherHappiness;
	int time;

public:
	void LoadActionData();

	void SetRoomNum(int roonNum);

	std::string GetActionName(int actionNum) const;
	int GetChildHappiness(int actionNum) const;
	int GetMotherHappiness(int actionNum) const;
	std::string GetScriptPath(int actionNum) const;
	int GetMotherPosition() const;
	int GetActionIfType(int actionNum) const;

	void RandomMotherPosition();
};

#endif

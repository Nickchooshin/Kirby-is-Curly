#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include "Singleton.h"

#include "json/document.h"

class DataManager : public Singleton < DataManager >
{
private:
	rapidjson::Document actionDocument;

public:
	void LoadActionData();

	std::string GetActionName(int actionNum) const;
	int GetChildHappniess(int actionNum) const;
	int GetMotherHappniess(int actionNum) const;
};

#endif

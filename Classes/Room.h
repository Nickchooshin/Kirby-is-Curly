#ifndef _ROOM_H_
#define _ROOM_H_

#include "cocos2d.h"
#include <vector>
#include "UIPopupWindow.h"

class Room : public cocos2d::Node
{
private:
	std::string m_name;
	std::string m_spritePath;
	int m_num;

	std::vector<int> m_actions;
	UIPopupWindow *m_menuPopup;

public:
	Room(std::string name, std::string spritePath, int num);
	Room(const Room &);
	~Room();

	virtual bool init() override;

	static Room* create(std::string name, std::string spritePath, int num)
	{
		Room *pRet = new(std::nothrow) Room(name, spritePath, num);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}

	void AddAction(int actionNum);
private:
	void ClickRoom(cocos2d::Ref *pSender);
	void ClickMenu(cocos2d::Ref *pSender);
};

#endif
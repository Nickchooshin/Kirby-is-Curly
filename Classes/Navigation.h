#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

#include "cocos2d.h"
#include <vector>

class Navigation : public cocos2d::Node
{
private:
	int m_roomNum;
	int m_currentPosition;
	bool **m_navigation;
	std::vector<int> m_pathStack;

public:
	Navigation();
	Navigation(const Navigation &);
	~Navigation();

	virtual bool init() override;

	void SetCurrentPosition(int currentPosition);
	void FindPath(int destinationPosition);

	int GetCurrentPosition() const;
	int GetNextPosition() const;
	void DeletePrevPosition();

	bool IsEnd() const;

	CREATE_FUNC(Navigation);
private:
	bool DFS(int currentPosition, int destinationPosition, bool *roomCheck);
};

#endif
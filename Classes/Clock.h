#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "cocos2d.h"
#include <vector>

class Clock : public cocos2d::Node
{
private:
	std::vector<cocos2d::Sprite*> m_clock;
	int m_time;

public:
	Clock();
	Clock(const Clock &);
	~Clock();

	virtual bool init() override;

	CREATE_FUNC(Clock);
private:
	void AddedClockSprite(int min, int max, std::string time);

	void UpdateTime(float dt);
};

#endif
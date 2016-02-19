#include "Clock.h"
#include "DataManager.h"

USING_NS_CC;

Clock::Clock()
	: m_clock()
	, m_time(0)
{
}
Clock::~Clock()
{
}

bool Clock::init()
{
	AddedClockSprite(10, 12, "AM");
	AddedClockSprite(1, 8, "PM");

	this->schedule(schedule_selector(Clock::UpdateTime));

	return true;
}

void Clock::AddedClockSprite(int min, int max, std::string time)
{
	for (int i = min; i <= max; i++)
	{
		char filepath[256];
		sprintf(filepath, "./Images/clock/%d%s.png", i, time.c_str());
		Sprite *sprite = Sprite::create(filepath);
		sprite->setVisible(false);
		this->addChild(sprite);

		m_clock.emplace_back(sprite);
	}
}

void Clock::UpdateTime(float dt)
{
	int time = DataManager::getInstance()->time;

	if (m_time != time)
	{
		if(m_time >= 10)
			m_clock[m_time - 10]->setVisible(false);
		m_clock[time - 10]->setVisible(true);

		m_time = time;
	}

	if (time >= 20)
	{
		// Ending Scene
	}
}
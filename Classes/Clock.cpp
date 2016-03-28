#include "Clock.h"
#include "DataManager.h"
#include "TItleScene.h"

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

		float childHapiness = DataManager::getInstance()->childHappiness;
		float motherHapiness = DataManager::getInstance()->motherHappiness;

		if (childHapiness >= 10.0f && motherHapiness >= 10.0f)
		{
			MessageBox("WOW! you complited the happy ending!", "Ending");
		}
		else if (childHapiness >= 5.0f && motherHapiness >= 5.0f)
		{
			MessageBox("WOW! you complited the normal ending!", "Ending");
		}
		//else if (childHapiness >= 1.0f && motherHapiness >= 1.0f)
		else
		{
			MessageBox("WOW! you complited the bad ending!", "Ending");
		}

		Director::getInstance()->replaceScene(TitleScene::createScene());
	}
}
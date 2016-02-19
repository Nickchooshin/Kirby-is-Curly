#include "LogoScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

LogoScene::LogoScene()
	: m_time(0.0f)
	, m_logo(nullptr)
{
}
LogoScene::~LogoScene()
{
}

Scene* LogoScene::createScene()
{
	Scene *scene = LogoScene::create();

	return scene;
}

bool LogoScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_logo = Sprite::create("./Images/Kirby is Curly.jpg");
	m_logo->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	m_logo->setOpacity(0);
	this->addChild(m_logo);

	this->schedule(schedule_selector(LogoScene::FadeIn));

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Sounds/WAV/Take_a_Bath.wav");
	
	return true;
}

void LogoScene::FadeIn(float dt)
{
	if (m_time <= 3.0f)
	{
		float percent = m_time / 3.0f;

		m_logo->setOpacity((int)(percent * 255.0f));
	}
	else
	{
		m_time -= 3.0f;
		m_logo->setOpacity(255);

		this->schedule(schedule_selector(LogoScene::Stay));
		this->unschedule(schedule_selector(LogoScene::FadeIn));
		return;
	}

	m_time += dt;
}

void LogoScene::Stay(float dt)
{
	if(m_time > 1.0f)
	{
		m_time -= 1.0f;

		this->schedule(schedule_selector(LogoScene::FadeOut));
		this->unschedule(schedule_selector(LogoScene::Stay));
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
		return;
	}

	m_time += dt;
}

void LogoScene::FadeOut(float dt)
{
	if (m_time <= 3.0f)
	{
		float percent = m_time / 3.0f;

		m_logo->setOpacity(255 - (int)(percent * 255.0f));
	}
	else
	{
		m_time -= 3.0f;
		m_logo->setOpacity(0);

		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
		Director::getInstance()->replaceScene(TitleScene::createScene());
		return;
	}

	m_time += dt;
}
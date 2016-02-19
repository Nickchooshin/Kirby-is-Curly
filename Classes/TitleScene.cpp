#include "TitleScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

TitleScene::TitleScene()
	: commandCount(0)
{
}
TitleScene::~TitleScene()
{
}

Scene* TitleScene::createScene()
{
	Scene *scene = TitleScene::create();

	return scene;
}

bool TitleScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Background
	Sprite *background = Sprite::create("./Images/house_back.png");
	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(background);

	Sprite *background2 = Sprite::create("./Images/house_front.png");
	background2->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(background2);

	// Buttons
	ui::Button *startButton = ui::Button::create("./Images/dummy_start.png");
	startButton->setPosition(Vec2(visibleSize.width / 2.0f, 240.0f));
	startButton->addClickEventListener(CC_CALLBACK_1(TitleScene::clickEvent, this));
	startButton->setTag(0);
	this->addChild(startButton);

	ui::Button *loadButton = ui::Button::create("./Images/dummy_click.png");
	loadButton->setPosition(Vec2(visibleSize.width / 2.0f, 160.0f));
	loadButton->addClickEventListener(CC_CALLBACK_1(TitleScene::clickEvent, this));
	loadButton->setTag(1);
	this->addChild(loadButton);

	if (!UserDefault::getInstance()->getBoolForKey("save"))
		loadButton->setEnabled(false);

	ui::Button *exitButton = ui::Button::create("./Images/dummy_exit.png");
	exitButton->setPosition(Vec2(visibleSize.width / 2.0f, 80.0f));
	exitButton->addClickEventListener(CC_CALLBACK_1(TitleScene::clickEvent, this));
	exitButton->setTag(2);
	this->addChild(exitButton);

	// Keyboard
	EventListenerKeyboard *eventListenerKeyboard = EventListenerKeyboard::create();
	eventListenerKeyboard->onKeyPressed = CC_CALLBACK_2(TitleScene::KeyDown, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListenerKeyboard, this);

	return true;
}

void TitleScene::clickEvent(Ref *pSender)
{
	ui::Button *button = (ui::Button*)pSender;
	int tag = button->getTag();

	switch (tag)
	{
	case 0:
		DataManager::getInstance()->Init();

		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->replaceScene(CCTransitionFade::create(3.0f, GameScene::createScene()));
		break;

	case 1:
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();

		Director::getInstance()->replaceScene(CCTransitionFade::create(3.0f, GameScene::createScene()));
		break;

	case 2:
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	}
}

void TitleScene::KeyDown(EventKeyboard::KeyCode keycode, cocos2d::Event* args)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (commandCount > 1)
			commandCount = 1;
		else
			commandCount += 1;
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (commandCount >= 2 && commandCount <= 3)
			commandCount += 1;
		else
			commandCount = 0;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (commandCount == 4 || commandCount == 6)
			commandCount += 1;
		else
			commandCount = 0;
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (commandCount == 5 || commandCount == 7)
			commandCount += 1;
		else
			commandCount = 0;
		break;

	case EventKeyboard::KeyCode::KEY_B:
		if (commandCount == 8)
			commandCount += 1;
		else
			commandCount = 0;
		break;

	case EventKeyboard::KeyCode::KEY_A:
		if (commandCount == 9)
			commandCount += 1;
		else
			commandCount = 0;
		break;
	}
	
	if (commandCount == 10)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Sounds/WAV/Eat_Snack.wav");
		commandCount = 0;
	}
}
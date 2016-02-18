#include "TitleScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "DataManager.h"

USING_NS_CC;

TitleScene::TitleScene()
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

	//Sprite *background = Sprite::create("./Images/dummy_title.png");
	Sprite *background = Sprite::create("./Images/dummy_color.png");
	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	//background->setColor(Color3B(125, 125, 125));
	this->addChild(background);

	ui::Button *startButton = ui::Button::create("./Images/dummy_start.png");
	startButton->setPosition(Vec2(visibleSize.width / 2.0f, 240.0f));
	startButton->addClickEventListener(CC_CALLBACK_1(TitleScene::clickEvent, this));
	startButton->setTag(0);
	this->addChild(startButton);

	ui::Button *loadButton = ui::Button::create("./Images/dummy_load.png");
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

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("abc.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	//CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.ogg");
	return true;
}

void TitleScene::clickEvent(Ref *pSender)
{
	ui::Button *button = (ui::Button*)pSender;
	int tag = button->getTag();

	switch (tag)
	{
	case 0:
		//UserDefault::getInstance()->setBoolForKey("save", false);
		//UserDefault::getInstance()->setIntegerForKey("child_happiness", 5);
		//UserDefault::getInstance()->setIntegerForKey("mother_happiness", 5);
		DataManager::getInstance()->childHappiness = 5;
		DataManager::getInstance()->motherHappiness = 5;

		Director::getInstance()->replaceScene(CCTransitionFade::create(3.0f, GameScene::createScene()));
		break;

	case 1:
		Director::getInstance()->replaceScene(CCTransitionFade::create(3.0f, GameScene::createScene()));
		break;

	case 2:
		break;
	}
}
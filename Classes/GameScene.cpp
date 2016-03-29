#include "GameScene.h"
#include "Dialog.h"
#include "Room.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"
#include "Clock.h"
#include "Navigation.h"

#include "json/document.h"
#include "json/filereadstream.h"

USING_NS_CC;

GameScene::GameScene()
	: m_childHappinessBar(nullptr)
	, m_motherHappinessBar(nullptr)
	, m_hourHand(nullptr)
	, m_roomPositions()
	, m_mother(nullptr)
	, m_child(nullptr)
{
}
GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	Scene *scene = Scene::create();

	Layer *layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Background
	Sprite *background = Sprite::create("./Images/house_back.png");
	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(background);

	Sprite *background2 = Sprite::create("./Images/house_front.png");
	background2->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(background2);

	// Child HappinessBar
	m_childHappinessBar = ui::LoadingBar::create("./Images/Gauge_Bar.png");
	m_childHappinessBar->setPosition(Vec2(1200.0f, visibleSize.height - 100));
	m_childHappinessBar->setColor(Color3B(125, 255, 125));
	this->addChild(m_childHappinessBar);

	Sprite *childHappinessBarFrame = Sprite::create("./Images/Gauge_Bar_Frame.png");
	childHappinessBarFrame->setPosition(m_childHappinessBar->getContentSize().width / 2.0f, m_childHappinessBar->getContentSize().height / 2.0f);
	m_childHappinessBar->addChild(childHappinessBarFrame);

	Sprite *childHappinessIcon = Sprite::create("./Images/Icon_Child.png");
	childHappinessIcon->setPosition(m_childHappinessBar->getPosition().x - (m_childHappinessBar->getContentSize().width / 2.0f) - childHappinessIcon->getContentSize().width / 2.0f, m_childHappinessBar->getPosition().y);
	this->addChild(childHappinessIcon);

	// Mother HappinessBar
	m_motherHappinessBar = ui::LoadingBar::create("./Images/Gauge_Bar.png");
	m_motherHappinessBar->setPosition(Vec2(1200.0f, visibleSize.height - 50));
	m_motherHappinessBar->setColor(Color3B(125, 255, 125));
	this->addChild(m_motherHappinessBar);

	Sprite *motherHappinessBarFrame = Sprite::create("./Images/Gauge_Bar_Frame.png");
	motherHappinessBarFrame->setPosition(m_motherHappinessBar->getContentSize().width / 2.0f, m_motherHappinessBar->getContentSize().height / 2.0f);
	m_motherHappinessBar->addChild(motherHappinessBarFrame);

	Sprite *motherHappinessIcon = Sprite::create("./Images/Icon_Mother.png");
	motherHappinessIcon->setPosition(m_motherHappinessBar->getPosition().x - (m_motherHappinessBar->getContentSize().width / 2.0f) - motherHappinessIcon->getContentSize().width / 2.0f, m_motherHappinessBar->getPosition().y);
	this->addChild(motherHappinessIcon);

	// Clock
	Clock *clock = Clock::create();
	clock->setPosition(100.0f, visibleSize.height - 100.0f);
	this->addChild(clock);

	// Room
	RoomsLoad();

	// Mother Position
	srand(time(0));
	DataManager::getInstance()->SetRoomNum(m_roomPositions.size());
	DataManager::getInstance()->RandomMotherPosition();

	// Mother
	m_mother = Sprite::create("./Images/dummy_mother.png");
	this->addChild(m_mother);

	Animation *motherAnimation = Animation::create();
	motherAnimation->setDelayPerUnit(0.25f);
	motherAnimation->addSpriteFrameWithFile("./Images/Squirrelgame/Squirrelmom/squirrelmom01.png");
	motherAnimation->addSpriteFrameWithFile("./Images/Squirrelgame/Squirrelmom/squirrelmom02.png");
	motherAnimation->addSpriteFrameWithFile("./Images/Squirrelgame/Squirrelmom/squirrelmom03.png");
	motherAnimation->addSpriteFrameWithFile("./Images/Squirrelgame/Squirrelmom/squirrelmom04.png");

	Animate *motherAnimate = Animate::create(motherAnimation);
	RepeatForever *motherRepeat = RepeatForever::create(motherAnimate);

	m_mother->setScale(0.5f);
	//m_mother->setAnchorPoint(Vec2(0.5f, 0.144750254841998f));
	m_mother->runAction(motherRepeat);

	// Child
	m_child = Sprite::create("./Images/dummy_child.png");
	this->addChild(m_child);

	Action *childAnimation = CreateChildAnimationAction(0);

	m_child->setScale(0.5f);
	//m_child->setAnchorPoint(Vec2(0.5f, 0.1187607573149742f));
	m_child->runAction(childAnimation);
	m_child->setPosition(m_roomPositions[0]);

	// Child Navigation;
	m_childNavigation = Navigation::create();
	m_childNavigation->SetCurrentPosition(0);
	this->addChild(m_childNavigation, 0, "navigation");

	// Schedule
	this->schedule(schedule_selector(GameScene::UpdateHappiness));
	this->schedule(schedule_selector(GameScene::UpdateMotherPosition));

	// Audio
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Sounds/Music/Kirby is Kurly Tune.mp3", true);

	// Custom Event Listener
	EventListenerCustom *listenerChildMoving = EventListenerCustom::create("child_moving", CC_CALLBACK_1(GameScene::SetDestinationPosition, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerChildMoving, this);

	return true;
}

void GameScene::SetDestinationPosition(cocos2d::EventCustom *eventCustom)
{
	int destination = *(int*)eventCustom->getUserData();

	m_childNavigation->FindPath(destination);

	this->unschedule(schedule_selector(GameScene::ChildMoving));
	this->schedule(schedule_selector(GameScene::ChildMoving));
}

void GameScene::ChildMoving(float dt)
{
	if (!m_childNavigation->IsEnd())
	{
		int roomNum = m_childNavigation->GetNextPosition();
		Vec2 destination = m_roomPositions[roomNum];
		Vec2 direction = destination - m_child->getPosition();
		float distance = direction.length();
		float time = distance / 200.0f;

		MoveTo *moveAction = MoveTo::create(time, destination);
		moveAction->setTag(1);
		m_child->stopActionByTag(1);
		m_child->runAction(moveAction);

		int animationType = GetChildAnimationType(direction);
		Action *animationAction = CreateChildAnimationAction(animationType);
		m_child->stopActionByTag(0);
		m_child->runAction(animationAction);

		m_childNavigation->SetCurrentPosition(roomNum);
		m_childNavigation->DeletePrevPosition();

		this->schedule(schedule_selector(GameScene::ChildMoving), time);
	}
	else
	{
		Action *animationAction = CreateChildAnimationAction(0);
		m_child->stopActionByTag(0);
		m_child->runAction(animationAction);

		std::string eventName = "menu_popup-" + std::to_string(m_childNavigation->GetCurrentPosition());
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(eventName, nullptr);

		this->unschedule(schedule_selector(GameScene::ChildMoving));
	}
}

void GameScene::RoomsLoad()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	DataManager::getInstance()->LoadActionData();
	
	std::string filePath = FileUtils::getInstance()->fullPathForFilename("./Data/rooms.json");

	char buffer[65536];
	FILE *file = fopen(filePath.c_str(), "r");

	rapidjson::Document document;
	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	document.ParseStream(is);
	fclose(file);

	const int size = document.Size();

	for (int i = 0; i < size; i++)
	{
		rapidjson::Value &roomValue = document[i];
		rapidjson::Value &actionValue = roomValue["Actions"];

		std::string name = roomValue["Room"].GetString();
		std::string sprite = roomValue["Sprite"].GetString();
		float positionX = roomValue["PositionX"].GetDouble();
		float positionY = visibleSize.height - roomValue["PositionY"].GetDouble();

		Room *room = Room::create(name, sprite, i);
		room->setPosition(positionX, positionY);
		for (int j = 0; j < actionValue.Size(); j++)
			room->AddAction(actionValue[j].GetInt());
		this->addChild(room);

		m_roomPositions.emplace_back(Vec2(positionX, positionY));
	}
}

void GameScene::UpdateHappiness(float dt)
{
	float maxHapiness = DataManager::getInstance()->maxHapiness;
	float childHappiness = DataManager::getInstance()->childHappiness;
	float motherHappiness = DataManager::getInstance()->motherHappiness;

	m_childHappinessBar->setPercent((childHappiness / maxHapiness) * 100.0f);
	m_motherHappinessBar->setPercent((motherHappiness / maxHapiness) * 100.0f);
}

void GameScene::UpdateMotherPosition(float dt)
{
	int motherPosition = DataManager::getInstance()->GetMotherPosition();

	m_mother->setPosition(m_roomPositions[motherPosition]);
}

int GameScene::GetChildAnimationType(cocos2d::Vec2 direction)
{
	float forceX = abs(direction.x);
	float forceY = abs(direction.y);

	if (forceX >= forceY)
	{
		if (direction.x >= 0.0f)
			return 2;
		else
			return 1;
	}
	else
	{
		if (direction.y >= 0.0f)
			return 3;
		else
			return 0;
	}
}

Action* GameScene::CreateChildAnimationAction(int type)
{
	Animation *childAnimation = Animation::create();
	childAnimation->setDelayPerUnit(0.25f);

	for (int i = 0; i < 4; i++)
	{
		char filename[256];

		switch (type)
		{
		case 0:
			sprintf(filename, "./Images/Squirrelgame/Squirrelkidfront/squirrelkidfront%02d.png", (i + 1));
			break;

		case 1:
			sprintf(filename, "./Images/Squirrelgame/SquirrelKid Left Movement/squirrelkidleft%02d.png", (i + 1));
			break;

		case 2:
			sprintf(filename, "./Images/Squirrelgame/SquirrelKid Right Movement/squirrelkidright%02d.png", (i + 1));
			break;

		case 3:
			sprintf(filename, "./Images/Squirrelgame/squirrelkid back.png", (i + 1));
			break;
		}

		childAnimation->addSpriteFrameWithFile(filename);
	}

	Animate *childAnimate = Animate::create(childAnimation);
	RepeatForever *childRepeat = RepeatForever::create(childAnimate);
	childRepeat->setTag(0);

	return childRepeat;
}
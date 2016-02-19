#include "GameScene.h"
#include "Dialog.h"
#include "Room.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"
#include "Clock.h"

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
	Sprite *childHappinessBarFrame = Sprite::create("./Images/dummy_gauge_frame.png");
	childHappinessBarFrame->setPosition(1200.0f, visibleSize.height - 100);
	this->addChild(childHappinessBarFrame);

	m_childHappinessBar = ui::LoadingBar::create("./Images/dummy_gauge.png");
	m_childHappinessBar->setPosition(childHappinessBarFrame->getPosition());
	m_childHappinessBar->setColor(Color3B(125, 255, 125));
	this->addChild(m_childHappinessBar);

	Sprite *childHappinessIcon = Sprite::create("./Images/dummy_icon_c.png");
	childHappinessIcon->setPosition(childHappinessBarFrame->getPosition().x - (childHappinessBarFrame->getContentSize().width / 2.0f) - childHappinessIcon->getContentSize().width / 2.0f, childHappinessBarFrame->getPosition().y);
	this->addChild(childHappinessIcon);

	// Mother HappinessBar
	Sprite *motherHappinessBarFrame = Sprite::create("./Images/dummy_gauge_frame.png");
	motherHappinessBarFrame->setPosition(1200.0f, visibleSize.height - 50);
	this->addChild(motherHappinessBarFrame);

	m_motherHappinessBar = ui::LoadingBar::create("./Images/dummy_gauge.png");
	m_motherHappinessBar->setPosition(motherHappinessBarFrame->getPosition());
	m_motherHappinessBar->setColor(Color3B(125, 255, 125));
	this->addChild(m_motherHappinessBar);

	Sprite *motherHappinessIcon = Sprite::create("./Images/dummy_icon_m.png");
	motherHappinessIcon->setPosition(motherHappinessBarFrame->getPosition().x - (motherHappinessBarFrame->getContentSize().width / 2.0f) - motherHappinessIcon->getContentSize().width / 2.0f, motherHappinessBarFrame->getPosition().y);
	this->addChild(motherHappinessIcon);

	// Clock
	Clock *clock = Clock::create();
	clock->setPosition(100.0f, visibleSize.height - 100.0f);
	this->addChild(clock);

	// Mother
	m_mother = Sprite::create("./Images/dummy_mother.png");
	this->addChild(m_mother);

	Animation *motherAnimation = Animation::create();
	motherAnimation->setDelayPerUnit(0.1f);
	motherAnimation->addSpriteFrameWithFile("./Images/dummy_mother.png");
	motherAnimation->addSpriteFrameWithFile("./Images/dummy_mother2.png");

	Animate *motherAnimate = Animate::create(motherAnimation);
	RepeatForever *motherRepeat = RepeatForever::create(motherAnimate);

	m_mother->runAction(motherRepeat);

	// Child
	m_child = Sprite::create("./Images/dummy_child.png");
	//this->addChild(m_child);

	Animation *childAnimation = Animation::create();
	childAnimation->setDelayPerUnit(0.1f);
	childAnimation->addSpriteFrameWithFile("./Images/dummy_child.png");
	childAnimation->addSpriteFrameWithFile("./Images/dummy_child2.png");

	Animate *childAnimate = Animate::create(childAnimation);
	RepeatForever *childRepeat = RepeatForever::create(childAnimate);

	m_child->runAction(childRepeat);

	// Room
	RoomsLoad();

	// Mother Position
	srand(time(0));
	DataManager::getInstance()->SetRoomNum(m_roomPositions.size());
	DataManager::getInstance()->RandomMotherPosition();

	// Child Position
	this->addChild(m_child);

	// Schedule
	this->schedule(schedule_selector(GameScene::UpdateHappiness));
	this->schedule(schedule_selector(GameScene::UpdateMotherAndChildPosition));

	// Audio
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Sounds/Music/Kirby is Kurly Tune.mp3", true);

	return true;
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

void GameScene::UpdateMotherAndChildPosition(float dt)
{
	// Mother
	int motherPosition = DataManager::getInstance()->GetMotherPosition();

	m_mother->setPosition(m_roomPositions[motherPosition]);

	// Child
	int childPosition = DataManager::getInstance()->GetChildPosition();

	m_child->setPosition(m_roomPositions[childPosition]);
}
#include "GameScene.h"
#include "Dialog.h"
#include "Room.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"

#include "json/document.h"
#include "json/filereadstream.h"

USING_NS_CC;

GameScene::GameScene()
	: m_childHappinessBar(nullptr)
	, m_motherHappinessBar(nullptr)
	, m_hourHand(nullptr)
	, m_roomPositions()
	, m_mother(nullptr)
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
	childHappinessBarFrame->setPosition(1000.0f, visibleSize.height - 250);
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
	motherHappinessBarFrame->setPosition(1000.0f, visibleSize.height - 200);
	this->addChild(motherHappinessBarFrame);

	m_motherHappinessBar = ui::LoadingBar::create("./Images/dummy_gauge.png");
	m_motherHappinessBar->setPosition(motherHappinessBarFrame->getPosition());
	m_motherHappinessBar->setColor(Color3B(125, 255, 125));
	this->addChild(m_motherHappinessBar);

	Sprite *motherHappinessIcon = Sprite::create("./Images/dummy_icon_m.png");
	motherHappinessIcon->setPosition(motherHappinessBarFrame->getPosition().x - (motherHappinessBarFrame->getContentSize().width / 2.0f) - motherHappinessIcon->getContentSize().width / 2.0f, motherHappinessBarFrame->getPosition().y);
	this->addChild(motherHappinessIcon);

	// Clock
	Sprite *clock = Sprite::create("./Images/dummy_clock.png");
	clock->setPosition(200.0f, visibleSize.height - 200.0f);
	this->addChild(clock);

	Sprite *minuteHand = Sprite::create("./Images/dummy_clock_minute_hand.png");
	minuteHand->setPosition(clock->getPosition());
	this->addChild(minuteHand);

	m_hourHand = Sprite::create("./Images/dummy_clock_hour_hand.png");
	m_hourHand->setPosition(clock->getPosition());
	this->addChild(m_hourHand);

	// Room
	RoomsLoad();

	// Mother
	m_mother = Sprite::create("./Images/dummy_mother.png");
	this->addChild(m_mother);

	srand(time(0));
	DataManager::getInstance()->SetRoomNum(m_roomPositions.size());
	DataManager::getInstance()->RandomMotherPosition();

	// Schedule
	this->schedule(schedule_selector(GameScene::UpdateHappiness));
	this->schedule(schedule_selector(GameScene::UpdateTime));
	this->schedule(schedule_selector(GameScene::UpdateMotherPosition));

	// Audio
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Sounds/Music/Kirby is Kurly Tune.mp3", true);

	return true;
}

void GameScene::RoomsLoad()
{
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
		float positionY = roomValue["PositionY"].GetDouble();

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

void GameScene::UpdateTime(float dt)
{
	int time = DataManager::getInstance()->time;

	m_hourHand->setRotation((time % 12) * 30.0f);

	if (time >= 20)
	{
		// Ending Scene
	}
}

void GameScene::UpdateMotherPosition(float dt)
{
	int motherPosition = DataManager::getInstance()->GetMotherPosition();

	m_mother->setPosition(m_roomPositions[motherPosition]);
}
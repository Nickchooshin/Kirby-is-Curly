#include "GameScene.h"
#include "Dialog.h"
#include "Room.h"
#include "DataManager.h"

#include "json/document.h"
#include "json/filereadstream.h"

USING_NS_CC;

GameScene::GameScene()
	: m_childHappinessBar(nullptr)
	, m_motherHappinessBar(nullptr)
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

	Sprite *background = Sprite::create("./Images/temp.jpg");
	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(background);

	Sprite *childHappinessBarFrame = Sprite::create("./Images/dummy_gauge_frame.png");
	childHappinessBarFrame->setPosition(1000.0f, visibleSize.height - 250);
	this->addChild(childHappinessBarFrame);

	m_childHappinessBar = ui::LoadingBar::create("./Images/dummy_gauge.png");
	m_childHappinessBar->setPosition(childHappinessBarFrame->getPosition());
	m_childHappinessBar->setColor(Color3B(125, 255, 125));
	this->addChild(m_childHappinessBar);

	Sprite *motherHappinessBarFrame = Sprite::create("./Images/dummy_gauge_frame.png");
	motherHappinessBarFrame->setPosition(1000.0f, visibleSize.height - 200);
	this->addChild(motherHappinessBarFrame);

	m_motherHappinessBar = ui::LoadingBar::create("./Images/dummy_gauge.png");
	m_motherHappinessBar->setPosition(motherHappinessBarFrame->getPosition());
	m_motherHappinessBar->setColor(Color3B(125, 255, 125));
	this->addChild(m_motherHappinessBar);

	RoomsLoad();

	this->schedule(schedule_selector(GameScene::UpdateHappiness));

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

		Room *room = Room::create(name, sprite);
		room->setPosition(positionX, positionY);
		for (int j = 0; j < actionValue.Size(); j++)
			room->AddAction(actionValue[j].GetInt());
		this->addChild(room);
		
	}
}

void GameScene::UpdateHappiness(float dt)
{
	int childHappiness = DataManager::getInstance()->childHappiness;
	int motherHappiness = DataManager::getInstance()->motherHappiness;

	m_childHappinessBar->setPercent((childHappiness / 15.0f) * 100.0f);
	m_motherHappinessBar->setPercent((motherHappiness / 15.0f) * 100.0f);
}
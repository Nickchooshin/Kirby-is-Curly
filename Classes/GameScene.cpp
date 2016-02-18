#include "GameScene.h"
#include "Dialog.h"
#include "Room.h"
#include "DataManager.h"

#include "json/document.h"
#include "json/filereadstream.h"

USING_NS_CC;

GameScene::GameScene()
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

	Dialog *dialog = Dialog::create();
	dialog->LoadScript("./Data/test_script.json");
	//this->addChild(dialog);

	RoomsLoad();

	return true;
}

void GameScene::RoomsLoad()
{
	DataManager::getInstance()->LoadActionData();
	
	std::string filePath = FileUtils::getInstance()->fullPathForFilename("./Data/rooms_.json");

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
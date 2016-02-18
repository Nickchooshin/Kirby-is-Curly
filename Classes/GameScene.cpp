#include "GameScene.h"
#include "Dialog.h"

USING_NS_CC;

GameScene::GameScene()
{
}
GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	Scene *scene = GameScene::create();

	return scene;
}

bool GameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Dialog *dialog = Dialog::create();
	dialog->LoadScript("./Data/test_script.json");
	this->addChild(dialog);

	return true;
}

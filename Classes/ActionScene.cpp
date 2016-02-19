#include "ActionScene.h"
#include "Dialog.h"
#include "DataManager.h"

USING_NS_CC;

ActionScene::ActionScene()
	: m_dialog(nullptr)
{
}
ActionScene::~ActionScene()
{
}

Scene* ActionScene::createScene()
{
	Scene *scene = ActionScene::create();

	return scene;
}

bool ActionScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int actionNum = DataManager::getInstance()->actionNum;

	m_dialog = Dialog::create();
	m_dialog->LoadScript(DataManager::getInstance()->GetScriptPath(actionNum));
	this->addChild(m_dialog);

	this->schedule(schedule_selector(ActionScene::dialogEndCheck));

	return true;
}

void ActionScene::dialogEndCheck(float dt)
{
	if (m_dialog->IsEnd())
	{
		int actionNum = DataManager::getInstance()->actionNum;
		DataManager::getInstance()->childHappiness += DataManager::getInstance()->GetChildHappiness(actionNum);
		DataManager::getInstance()->motherHappiness += DataManager::getInstance()->GetMotherHappiness(actionNum);
		DataManager::getInstance()->time += 1;
		DataManager::getInstance()->RandomMotherPosition();

		Director::getInstance()->popScene();
	}
}
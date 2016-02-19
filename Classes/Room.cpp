#include "Room.h"
#include "ui/CocosGUI.h"
#include "DataManager.h"
#include "ActionScene.h"

#include "json/document.h"
#include "json/filereadstream.h"

USING_NS_CC;

Room::Room(std::string name, std::string spritePath, int num)
	: m_name(name)
	, m_spritePath(spritePath)
	, m_num(num)
	, m_actions()
{
}
Room::~Room()
{
}

bool Room::init()
{
	ui::Button *button = ui::Button::create(m_spritePath);
	button->addClickEventListener(CC_CALLBACK_1(Room::ClickRoom, this));
	button->setTitleText(m_name);
	this->addChild(button);

	return true;
}

void Room::AddAction(int actionNum)
{
	m_actions.emplace_back(actionNum);
}

void Room::ClickRoom(Ref *pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_menuPopup = UIPopupWindow::create(nullptr, nullptr);
	m_menuPopup->setCallBackFunc(CC_CALLBACK_1(Room::ClickMenu, this));

	int i;
	for (i = 0; i < m_actions.size(); i++)
	{
		int action = m_actions[i];

		ui::Button *button = ui::Button::create("./Images/dummy_button.png");
		button->setPosition(Vec2(visibleSize.width / 2.0f, (visibleSize.height / 2.0f) + button->getContentSize().height - (button->getContentSize().height * i)));
		button->setTag(action);
		button->addClickEventListener(CC_CALLBACK_1(Room::ClickMenu, this));
		m_menuPopup->addChild(button);

		if (DataManager::getInstance()->GetActionIfType(action) == 1)
		{
			int motherPosition = DataManager::getInstance()->GetMotherPosition();

			if (motherPosition != m_num)
				button->setEnabled(false);
		}
		else if (DataManager::getInstance()->GetActionIfType(action) == 2)
		{
			int time = DataManager::getInstance()->time;

			if (time < 13 || time > 16)
				button->setEnabled(false);
		}

		Label *label = Label::create(DataManager::getInstance()->GetActionName(action), "fonts/arial.ttf", 20.0f, button->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label->setColor(Color3B(0, 0, 0));
		label->setPosition(label->getContentSize().width / 2.0f, label->getContentSize().height / 2.0f);
		button->addChild(label);
	}

	ui::Button *button = ui::Button::create("./Images/dummy_button.png");
	button->setPosition(Vec2(visibleSize.width / 2.0f, (visibleSize.height / 2.0f) + button->getContentSize().height - (button->getContentSize().height * i)));
	button->setTag(0);
	button->addClickEventListener(CC_CALLBACK_1(Room::ClickMenu, this));
	m_menuPopup->addChild(button);

	Label *label = Label::create("Back", "fonts/arial.ttf", 20.0f, button->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(label->getContentSize().width / 2.0f, label->getContentSize().height / 2.0f);
	button->addChild(label);

	DataManager::getInstance()->SetChildPosition(m_num);

	m_menuPopup->showPopup((Layer*)this->getParent());
}

void Room::ClickMenu(Ref *pSender)
{
	ui::Button *button = (ui::Button*)pSender;
	int tag = button->getTag();

	switch (tag)
	{
	case 0:
		break;

	default:
		DataManager::getInstance()->actionNum = tag;
		Director::getInstance()->pushScene(ActionScene::createScene());
		break;
	}

	m_menuPopup->closePopup();
}
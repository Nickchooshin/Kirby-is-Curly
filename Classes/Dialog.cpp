#include "Dialog.h"
#include "ui/CocosGUI.h"
#include "json/document.h"
#include "json/filereadstream.h"

USING_NS_CC;

Dialog::Dialog()
	: m_document()
	, m_index(0)
	, m_maxIndex(0)
	, m_label(nullptr)
{
}
Dialog::~Dialog()
{
}

bool Dialog::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	ui::Scale9Sprite *frame = ui::Scale9Sprite::create("./Images/dummy_frame.png");
	frame->setContentSize(Size(visibleSize.width, 100.0f));
	frame->setPosition(Vec2(visibleSize.width / 2.0f, frame->getContentSize().height / 2.0f));
	this->addChild(frame);

	m_label = Label::create("", "fonts/arial.ttf", 30.0f, frame->getContentSize());
	m_label->setColor(Color3B(0, 0, 0));
	m_label->setPosition(frame->getPosition());
	this->addChild(m_label);

	EventListenerMouse *eventListenerMouse = EventListenerMouse::create();
	eventListenerMouse->onMouseDown = CC_CALLBACK_1(Dialog::DialogClick, this);
	frame->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListenerMouse, this);

	return true;
}

bool Dialog::LoadScript(std::string filePath)
{
	filePath = FileUtils::getInstance()->fullPathForFilename(filePath);

	char buffer[65536];
	FILE *file = fopen(filePath.c_str(), "r");
	if (!file)
		return false;

	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	m_document.ParseStream(is);
	fclose(file);

	m_index = 0;
	m_maxIndex = m_document.Size();

	m_label->setString(m_document[m_index]["dialog"].GetString());

	return true;
}

bool Dialog::IsEnd() const
{
	return m_index == m_maxIndex;
}

void Dialog::Next()
{
	if (m_index < m_maxIndex - 1)
	{
		++m_index;

		m_label->setString(m_document[m_index]["dialog"].GetString());
	}
}

void Dialog::Prev()
{
	if (m_index > 0)
	{
		--m_index;

		m_label->setString(m_document[m_index]["dialog"].GetString());
	}
}

void Dialog::DialogClick(cocos2d::Ref *pSender)
{
	EventMouse *event = (EventMouse*)pSender;
	int mouseButton = event->getMouseButton();

	switch (mouseButton)
	{
	case 0:
		Next();
		break;

	case 1:
		Prev();
		break;
	}
}
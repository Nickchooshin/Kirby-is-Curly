#include "Dialog.h"
#include "ui/CocosGUI.h"
#include "json/document.h"
#include "json/reader.h"
#include "json/filereadstream.h"
/*
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/prettywriter.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "../rapidjson/include/rapidjson/filewritestream.h"
*/

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

	m_label = Label::create("dsdsfsfsf", "fonts/arial.ttf", 30.0f, frame->getContentSize());
	m_label->setColor(Color3B(0, 0, 0));
	m_label->setPosition(frame->getPosition());
	this->addChild(m_label);

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

	Next();

	return true;
}

void Dialog::Next()
{
	if (m_index < m_maxIndex)
	{
		m_label->setString(m_document[m_index]["dialog"].GetString());

		++m_index;
	}
}

bool Dialog::IsEnd() const
{
	return m_index == m_maxIndex;
}
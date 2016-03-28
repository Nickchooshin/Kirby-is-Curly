#include "Navigation.h"

#include "json/document.h"
#include "json/filereadstream.h""

Navigation::Navigation()
	: m_roomNum(0)
	, m_currentPosition(0)
	, m_navigation(nullptr)
	, m_pathStack()
{
}
Navigation::~Navigation()
{
	if (m_navigation != nullptr)
	{
		for (int i = 0; i < m_roomNum; i++)
			delete[] m_navigation[i];

		delete[] m_navigation;
	}
}

bool Navigation::init()
{
	std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("./Data/room_navigation.json");

	char buffer[65536];
	FILE *file = fopen(filePath.c_str(), "r");

	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	rapidjson::Document document;

	document.ParseStream(is);
	fclose(file);

	m_roomNum = document.Capacity();
	m_navigation = new bool*[m_roomNum];

	for (int i = 0; i < m_roomNum; i++)
	{
		m_navigation[i] = new bool[m_roomNum];

		for (int j = 0; j < m_roomNum; j++)
			m_navigation[i][j] = (bool)document[i]["Navigation"][j].GetInt();
	}

	return true;
}

void Navigation::SetCurrentPosition(int currentPosition)
{
	m_currentPosition = currentPosition;
}

void Navigation::FindPath(int destinationPosition)
{
	m_pathStack.clear();

	bool *roomCheck = new bool[m_roomNum];
	for (int i = 0; i < m_roomNum; i++)
		roomCheck[i] = false;

	DFS(m_currentPosition, destinationPosition, roomCheck);
	m_pathStack.push_back(m_currentPosition);

	delete[] roomCheck;
}

int Navigation::GetCurrentPosition() const
{
	return m_currentPosition;
}

int Navigation::GetNextPosition() const
{
	return m_pathStack.back();
}

void Navigation::DeletePrevPosition()
{
	m_pathStack.pop_back();
}

bool Navigation::IsEnd() const
{
	return m_pathStack.empty();
}

bool Navigation::DFS(int currentPosition, int destinationPosition, bool *roomCheck)
{
	roomCheck[currentPosition] = true;

	if (currentPosition == destinationPosition)
		return true;

	for (int i = 0; i < m_roomNum; i++)
	{
		if (i != currentPosition &&
			m_navigation[currentPosition][i] &&
			!roomCheck[i] &&
			DFS(i, destinationPosition, roomCheck))
		{
			m_pathStack.push_back(i);
			return true;
		}
	}

	return false;
}
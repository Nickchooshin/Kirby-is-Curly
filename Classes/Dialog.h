#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "cocos2d.h"
#include "json/document.h"

class Dialog : public cocos2d::Node
{
private:
	rapidjson::Document m_document;
	int m_index;
	int m_maxIndex;
	bool m_isEnd;

	cocos2d::Label *m_label;

public:
	Dialog();
	Dialog(const Dialog &);
	~Dialog();

	virtual bool init() override;

	CREATE_FUNC(Dialog);

	bool LoadScript(std::string filePath);

	bool IsEnd() const;
private:
	void Next();

	void DialogClick(cocos2d::Ref *pSender);
};

#endif
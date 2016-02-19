#ifndef _TITLE_SCENE_H_
#define _TILTE_SCENE_H_

#include "cocos2d.h"

class TitleScene : public cocos2d::Scene
{
private:
	int commandCount;

public:
	TitleScene();
	TitleScene(const TitleScene &);
	~TitleScene();

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(TitleScene);
private:
	void TitleScene::clickEvent(Ref *pSender);

	void KeyDown(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* args);
	void KeyUp(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* args);
};

#endif

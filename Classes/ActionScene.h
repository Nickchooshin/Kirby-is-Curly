#ifndef _ACTION_SCENE_H_
#define _ACTION_SCENE_H_

#include "cocos2d.h"

class Dialog;

class ActionScene : public cocos2d::Scene
{
private:
	Dialog *m_dialog;

public:
	ActionScene();
	ActionScene(const ActionScene &);
	~ActionScene();

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(ActionScene);
private:
	void dialogEndCheck(float dt);
};

#endif
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer
{
private:
	cocos2d::ui::LoadingBar *m_childHappinessBar;
	cocos2d::ui::LoadingBar *m_motherHappinessBar;

public:
	GameScene();
	GameScene(const GameScene &);
	~GameScene();

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(GameScene);
private:
	void RoomsLoad();
	void UpdateHappiness(float dt);
};

#endif

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

class GameScene : public cocos2d::Layer
{
private:
	cocos2d::ui::LoadingBar *m_childHappinessBar;
	cocos2d::ui::LoadingBar *m_motherHappinessBar;
	cocos2d::Sprite *m_hourHand;
	std::vector<cocos2d::Vec2> m_roomPositions;
	cocos2d::Sprite *m_mother;

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
	void UpdateTime(float dt);
	void UpdateMotherPosition(float dt);
};

#endif

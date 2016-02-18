#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene();
	GameScene(const GameScene &);
	~GameScene();

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(GameScene);
};

#endif

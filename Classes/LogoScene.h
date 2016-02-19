#ifndef _LOGO_SCENE_H_
#define _LOGO_SCENE_H_

#include "cocos2d.h"

class LogoScene : public cocos2d::Scene
{
private:
	float m_time;
	cocos2d::Sprite *m_logo;

public:
	LogoScene();
	LogoScene(const LogoScene &);
	~LogoScene();

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(LogoScene);

	void FadeIn(float dt);
	void Stay(float dt);
	void FadeOut(float dt);
};

#endif
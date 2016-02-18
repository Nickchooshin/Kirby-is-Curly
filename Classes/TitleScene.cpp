#include "TitleScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
}

Scene* TitleScene::createScene()
{
	Scene *scene = TitleScene::create();

	return scene;
}

bool TitleScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//Sprite *background = Sprite::create("./Images/dummy_title.png");
	Sprite *background = Sprite::create("./Images/dummy_color.png");
	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	//background->setColor(Color3B(125, 125, 125));
	this->addChild(background);

	ui::Button *clickButton = ui::Button::create("./Images/dummy_click.png");
	clickButton->setPosition(Vec2(visibleSize.width / 2.0f, 80.0f));
	clickButton->addClickEventListener(CC_CALLBACK_1(TitleScene::clickEvent, this));
	this->addChild(clickButton);

	return true;
}

void TitleScene::clickEvent(Ref *pSender)
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(3.0f, GameScene::createScene()));
}
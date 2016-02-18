#ifndef UIPopupWindow_h
#define UIPopupWindow_h

#include "ui/cocosgui.h"
#include "UI_PopupWindowBase.h"

using namespace cocos2d::ui;

class UIPopupWindow : public UI_PopupWindowBase
{
public:
	static UIPopupWindow * create(Sprite  *sprBackgroundBoard, Sprite  *sprBackgroundImg);	//�⺻������ ��׶��� �̹�����  ���濡 ������ �̹����� �����Ѵ�.
	virtual bool onInit();

	virtual void addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag);	//�˾�â�� ��ư�� �߰��Ѵ�.

	virtual void onBtnClickCallbackFnc(Ref *pSender, ui::Widget::TouchEventType   touchType);	//�߰��Ǵ� ��ư�鿡 ���� �ݹ��Լ� ����

	virtual bool onTouchBegan(Touch* touch, Event* event){ return true; };
	virtual void onTouchMoved(Touch* touch, Event* event){};
	virtual void onTouchEnded(Touch* touch, Event* event){};
	virtual void onTouchCancelled(Touch* touch, Event* event){};
	//CREATE_FUNC(UIPopupWindow);    //�⺻ create()�Լ� ����

public:
	virtual void setFontSize_Title(int size);	//Ÿ��Ʋ ��Ʈ ����� �����Ѵ�.
	virtual void setColor_Title(const Color3B& color);	//Ÿ��Ʋ ��Ʈ ���� ����
	virtual void setPosition_Title(const Point& position);
	virtual void setFontName_Title(const std::string& name);

	virtual void setFontSize_Msg(int size);	//�޽����� ��Ʈ ����� �����Ѵ�.
	virtual void setColor_Msg(const Color3B& color);	//�޽��� ��Ʈ ���� ����
	virtual void setPosition_Msg(const Point& position);
	virtual void setFontName_Msg(const std::string& name);

	virtual void setTitleString(const std::string& text);
	virtual void setMessageString(const std::string& text);

	virtual void setBackgroundImagePosition(const Point& position);	//��׶��� �̹����� ���� ��ġ ����

	virtual void setBackgroundBorard(Sprite  *sprBg);//�˾� �Ʒ��� �����̳� �� �̷���? �Ͽ��� �� �عٴ�

protected:
	virtual void setBackgroundImage(Sprite  *sprBg);	//���� ������ �ڽ�

	virtual void setTextInit();	//����� ���� UI�ʱ�ȭ

protected:
	Sprite *m_sprBg;	//��׶��� �̹���
	Text *m_txtTitle;	//Ÿ��Ʋ
	Text *m_txt;	//����

	long m_nZorderCnt;
};

#endif
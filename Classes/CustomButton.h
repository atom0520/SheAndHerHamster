#ifndef CUSTOM_BTN_H
#define CUSTOM_BTN_H
#include "cocos2d.h"
USING_NS_CC;

class Hero;
class CustomButton : public Sprite
{
public:
	CustomButton();
	~CustomButton();
	CREATE_FUNC(CustomButton);
	virtual bool init();
	static CustomButton* create(const char * normal_btn_filename, \
		const char * pressed_btn_filename, \
		const char * disabled_btn_filename);

	virtual	bool onTouchBegan(Touch* touch, Event *unused_event);
	virtual void onTouchMoved(Touch* touch, Event *unused_event);
	virtual	void onTouchEnded(Touch* touch, Event *unused_event);
	
	void setEnabled(bool isEnabled);
	bool isEnabled();
    bool _pressed;
	EventListenerTouchOneByOne* _listenerTouch;
	SpriteFrame * _btnSpriteFrames[3];

protected:

};

#endif
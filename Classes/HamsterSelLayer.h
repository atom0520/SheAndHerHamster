#ifndef HAMSTER_SEL_LAYER_H
#define HAMSTER_SEL_LAYER_H

#include "GameEffect.h"
#include "cocos2d.h"
using namespace cocos2d;

class HamsterSelLayer :public Layer
{
public:
	HamsterSelLayer();
	~HamsterSelLayer();
	CREATE_FUNC(HamsterSelLayer);
	virtual bool init();
	void update(float dt);
	void onEnter();
	//void onEnter();
	void onExit();
	void menuCallBack(Ref *pSender);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	bool onTouchBegan(Touch * touch, Event *event);
	void onTouchMoved(Touch * touch, Event *event);
#endif

	Sprite * _fg1;
	Sprite * _fg2;
	Sprite * _bg;
	Sprite * _hamsterHeads[8];
	GameEffect * _selectRect;

	Sprite * _selectedHamsterNameSprite;

	GameEffect * _DD;
	GameEffect *_hamster;
	int _selectIndex;

	bool _isSelectFixed;

	int _replaceSceneWait;

	MenuItemImage * _okBtn;
protected:

	static long old_clock_count;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	EventListenerTouchOneByOne * _listenerTouch;
#endif
};

#endif

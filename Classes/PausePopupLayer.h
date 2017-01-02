#ifndef PAUSE_POPUP_LAYER_H
#define PAUSE_POPUP_LAYER_H

#include "cocos2d.h"
USING_NS_CC;

class PausePopupLayer :public Layer
{
public:
	PausePopupLayer();
	~PausePopupLayer();
	virtual bool init();
	CREATE_FUNC(PausePopupLayer);
	void setSwallowTouchListener();
	//void setKeyboardListener();
	void onExit();
	int _oldGameState;
protected:
	
	void menuCallback(Ref *pSender);

	EventListenerTouchOneByOne * _touchListener;
};

#endif
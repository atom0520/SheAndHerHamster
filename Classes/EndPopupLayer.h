#ifndef END_POPUP_LAYER_H
#define END_POPUP_LAYER_H

#include "cocos2d.h"
USING_NS_CC;

class EndPopupLayer :public Layer
{
public:
	EndPopupLayer();
	~EndPopupLayer();
	virtual bool init();
	CREATE_FUNC(EndPopupLayer);
	static EndPopupLayer * create(int type);
	void setSwallowTouchListener();
	void onExit();

	enum class Type{
		END_RANKING_WIN,
		END_RANKING_LOSE,
		END_CAUGHT,
		END_SURVIVED,
	};
protected:
	int _type;
	void menuCallback(Ref *pSender);
	EventListenerTouchOneByOne * _listener;
};

#endif
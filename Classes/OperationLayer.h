#ifndef OPERATION_LAYER_H
#define OPERATION_LAYER_H
#include "cocos2d.h"
using namespace cocos2d;

#define TOUCH_MOVE_DIRECTION_LEFT 2
#define TOUCH_MOVE_DIRECTION_RIGHT 4
#define TOUCH_MOVE_TRIGGER_DISTANCE 44

class OperationLayer :public Layer
{
public:
	OperationLayer();
	~OperationLayer();
	CREATE_FUNC(OperationLayer);
	virtual bool init();
	virtual	bool onTouchBegan(Touch* touch, Event *unused_event);
	virtual void onTouchMoved(Touch* touch, Event *unused_event);
	virtual	void onTouchEnded(Touch* touch, Event *unused_event);
	void resetTouchMove();

	EventListenerTouchOneByOne* _listenerTouch;

	int _touchMoveTrigger;

private:
	void uiMenuCallback(Ref* pSender);

	Point _touchBeginPoint;
	Point _touchEndPoint;
	
};

#endif
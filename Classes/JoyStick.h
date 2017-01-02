#ifndef JOY_STICK_H
#define JOY_STICK_H
#include "cocos2d.h"
USING_NS_CC; 

#define JOYSTICK_MOVE_DIRECTION_LEFT 2
#define JOYSTICK_MOVE_DIRECTION_RIGHT 4
#define JOYSTICK_MOVE_TRIGGER_DISTANCE 20 

class Hero;
class JoyStick : public Sprite
{
public:
	JoyStick();
	~JoyStick();
	virtual bool init();
	virtual	bool onTouchBegan(Touch* touch, Event *unused_event);
	virtual void onTouchMoved(Touch* touch, Event *unused_event);
	virtual	void onTouchEnded(Touch* touch, Event *unused_event);
	
	void setJoyStickPosition(Vec2 point);
	void setJoyStickScale(float scale);
	CREATE_FUNC(JoyStick);
	
	//Vec2 _offDirection;
	
	EventListenerTouchOneByOne* _listenerTouch;
	//Sprite *_joyStick;
	Sprite *_joyStickBg;

	void resetMove();

	Point _moveBeginPoint;
	Point _moveEndPoint;
	int _moveTrigger;

	Point _center;
protected:
	//void showJoyStick();
	//void hideJoyStick();
	//void updateJoyStick(Touch* touch);
	//int _joyStickr;
	int _joyStickR;

	

	
 
};

#endif
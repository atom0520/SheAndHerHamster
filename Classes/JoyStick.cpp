#include "JoyStick.h"

JoyStick::JoyStick()
{
}

JoyStick::~JoyStick()
{
}

bool JoyStick::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Sprite::init() );
		_joyStickBg = Sprite::create("operation_layer/joy_stick_bg.png");//±³¾°
		//_joyStick = Sprite::create("operation_layer/joy_stick.png");//Ò¡¸Ë
		this->addChild(_joyStickBg, 0);
		//this->addChild(_joyStick, 1);
		//this->hideJoyStick();
		//this->showJoyStick();
		_joyStickBg->setScale(1.5);
		_joyStickR = _joyStickBg->getContentSize().width*_joyStickBg->getScale() / 2;
		//_joyStickr= _joyStick->getContentSize().width/2;

		//_offDirection = Point::ZERO;
		//_offDistance = 0;

		_listenerTouch = EventListenerTouchOneByOne::create();
		_listenerTouch->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
		_listenerTouch->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
		_listenerTouch->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerTouch, this);
		_moveBeginPoint = Point::ZERO;
		_moveEndPoint = Point::ZERO;
		_moveTrigger = 0;

		ret = true;
	} while(0);

	return ret;
}

//void JoyStick::showJoyStick()
//{
//	_joyStick->setVisible(true); 
//	_joyStickBg->setVisible(true);
//}

//void JoyStick::hideJoyStick()
//{
//	_joyStick->setVisible(false);
//	_joyStickBg->setVisible(true);
//}

//void JoyStick::resetJoyStick()
//{
//	_joyStick->setPosition(_start);
//	hideJoyStick();
//	_offDirection = Vec2::ZERO;
//	_offDistance = 0;
//}
void JoyStick::resetMove(){
	_moveBeginPoint;
	_moveEndPoint;
	_moveTrigger=0;
}

//void JoyStick::updateJoyStick(Touch* touch)
//{
//	Point hit = touch->getLocation();
//	float distance = _start.getDistance(hit);
//	auto direction = (hit - _start).getNormalized();
//	_offDirection = direction;
//	_offDistance = distance;
//    
//	if(distance < _joyStickr/2)
//	{
//		_joyStick->setPosition(_start + (direction  * distance));
//	}else if(distance >_joyStickr) {
//		_joyStick->setPosition(_start + (direction  * _joyStickr));
//	}else {
//		_joyStick->setPosition(_start + (direction  * _joyStickr / 2));
//	}
//
//}


bool JoyStick::onTouchBegan(Touch* touch, Event *unused_event)
{
	if(_joyStickBg->getBoundingBox().containsPoint(touch->getLocation()))
	{
		_moveBeginPoint = touch->getLocation();
		//this->showJoyStick();
		//updateJoyStick(touch);

		return true;
	}
}

void JoyStick::onTouchMoved(Touch* touch, Event *unused_event)
{
	/*if (_joyStickBg->getBoundingBox().containsPoint(touch->getLocation()))
	{
		if (_joyStick->isVisible())
		{
			updateJoyStick(touch);
			return;
		}
	}*/
	//else if (_joyStickBg->getBoundingBox().containsPoint(touch->getLocation())==false\
	//	&& _joyStickBg->getBoundingBox().containsPoint(touch->getPreviousLocation())==true)
	//{
	//	resetJoyStick();
	//}
}

void JoyStick::onTouchEnded(Touch* touch, Event *unused_event)
{
	/*if (_joyStickBg->getBoundingBox().containsPoint(touch->getLocation())==true\
		&& _joyStickBg->getBoundingBox().containsPoint(touch->getPreviousLocation()) == true)
	{
		resetJoyStick();
	}	*/
	if (_joyStickBg->getBoundingBox().containsPoint(touch->getLocation()) \
		&& _joyStickBg->getBoundingBox().containsPoint(touch->getPreviousLocation()) == true)
	{
		_moveEndPoint = touch->getLocation();
		if (_moveEndPoint.x - _moveBeginPoint.x < -JOYSTICK_MOVE_TRIGGER_DISTANCE){
			_moveTrigger = JOYSTICK_MOVE_DIRECTION_LEFT;
		}
		else{
			if (_moveEndPoint.x - _moveBeginPoint.x > JOYSTICK_MOVE_TRIGGER_DISTANCE){
				_moveTrigger = JOYSTICK_MOVE_DIRECTION_RIGHT;
			}
		}
	}
}

void JoyStick::setJoyStickPosition(Vec2 point)
{
	_center = point;
	_joyStickBg->setPosition(point);
}

void JoyStick::setJoyStickScale(float scale)
{
	_joyStickBg->setScale(scale);
	//_joyStick->setScale(scale);
}
#include "CustomButton.h"

CustomButton::CustomButton(){

}

CustomButton::~CustomButton(){

}

bool CustomButton::init(){
	if (!Sprite::init()){
		return false;
	}
    
    _pressed =false;
	_listenerTouch = EventListenerTouchOneByOne::create();
	_listenerTouch->onTouchBegan = CC_CALLBACK_2(CustomButton::onTouchBegan, this);
	_listenerTouch->onTouchMoved = CC_CALLBACK_2(CustomButton::onTouchMoved, this);
	_listenerTouch->onTouchEnded = CC_CALLBACK_2(CustomButton::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerTouch, this);


	return true;
}

CustomButton * CustomButton::create(const char * normal_btn_filename, const char * pressed_btn_filename, const char * disabled_btn_filename){
	auto customBtn = CustomButton::create();
	if (customBtn == nullptr){
		return nullptr;
	}

	customBtn->_btnSpriteFrames[0] = Sprite::create(normal_btn_filename)->getSpriteFrame();
	customBtn->_btnSpriteFrames[0]->retain();
	customBtn->_btnSpriteFrames[1] = Sprite::create(pressed_btn_filename)->getSpriteFrame();
	customBtn->_btnSpriteFrames[1]->retain();
	customBtn->_btnSpriteFrames[2] = Sprite::create(disabled_btn_filename)->getSpriteFrame();
	customBtn->_btnSpriteFrames[2]->retain();

	customBtn->setSpriteFrame(customBtn->_btnSpriteFrames[0]);
	return customBtn;
}

bool CustomButton::onTouchBegan(Touch* touch, Event *unused_event)
{
        if (this->getBoundingBox().containsPoint(touch->getLocation()))
        {
            _pressed=true;
			
				setSpriteFrame(_btnSpriteFrames[1]);
			
            
            return true;
        }
}

void CustomButton::onTouchMoved(Touch* touch, Event *unused_event)
{
		if (this->getBoundingBox().containsPoint(touch->getLocation())==false\
			&&this->getBoundingBox().containsPoint(touch->getPreviousLocation()) == true)
		{
			
			_pressed=false;
			
				setSpriteFrame(_btnSpriteFrames[0]);
			
 
		}
}

void CustomButton::onTouchEnded(Touch* touch, Event *unused_event)
{
        if (this->getBoundingBox().containsPoint(touch->getLocation())==true\
            &&this->getBoundingBox().containsPoint(touch->getPreviousLocation()) == true)
        {
            _pressed=false;

			
				setSpriteFrame(_btnSpriteFrames[0]);
			
            
        }
}

void CustomButton::setEnabled(bool isEnabled){
	
	if (isEnabled == true){
		_listenerTouch->setEnabled(true);
		setSpriteFrame(_btnSpriteFrames[0]);
	}
	else{
		_listenerTouch->setEnabled(false);
		setSpriteFrame(_btnSpriteFrames[2]);
		_pressed = false;
	}
}

bool CustomButton::isEnabled(){

	return _listenerTouch->isEnabled();
}

#include "OperationLayer.h"
#include "OperationManager.h"
#include "InputManager.h"
#include "QuestionManager.h"
#include "Joystick.h"
#include "CustomButton.h"
#include "PausePopupLayer.h"
#include "GameManager.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

OperationLayer::OperationLayer(){

}

OperationLayer::~OperationLayer(){

}

bool OperationLayer::init(){
	if (!Layer::init()){
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();


	auto speedUpBtn = CustomButton::create("operation_layer/speed_up_btn_01.png", \
		"operation_layer/speed_up_btn_02.png", \
		"operation_layer/speed_up_btn_03.png");

	speedUpBtn->setScale(1.2);
	speedUpBtn->setAnchorPoint(Point(0.5, 0.5));
	speedUpBtn->setPosition(Point(speedUpBtn->getContentSize().width*speedUpBtn->getScale()/2 + 8,\
		speedUpBtn->getContentSize().height*speedUpBtn->getScale()/2 + 8));
	OperationManager::getInstance()->_speedUpBtn = speedUpBtn;

	this->addChild(speedUpBtn, 2);

	MenuItemImage * pauseMenuItem = MenuItemImage::create(
		"operation_layer/pause_btn_01.png",
		"operation_layer/pause_btn_02.png",
		"operation_layer/pause_btn_03.png",
		CC_CALLBACK_1(OperationLayer::uiMenuCallback, this));
	
	pauseMenuItem->setScale(1);
	pauseMenuItem->setAnchorPoint(Point(0.5, 0.5));
	pauseMenuItem->setPosition(Point(speedUpBtn->getPositionX(),\
		speedUpBtn->getPositionY() + speedUpBtn->getContentSize().height*speedUpBtn->getScale() / 2 + pauseMenuItem->getContentSize().height*pauseMenuItem->getScale() / 2 + 8));
	pauseMenuItem->setTag(0);

	OperationManager::getInstance()->_pauseBtn = pauseMenuItem;
	
	MenuItemImage * zBtn = MenuItemImage::create(
		"operation_layer/z_btn_01.png",
		"operation_layer/z_btn_02.png",
		"operation_layer/z_btn_03.png",
		CC_CALLBACK_1(OperationLayer::uiMenuCallback, this));
	zBtn->setScale(1);
	zBtn->setAnchorPoint(Point(0.5, 0.5));
	zBtn->setPosition(Point(winSize.width - (zBtn->getContentSize().width + 8)*2 - zBtn->getContentSize().width / 2 - 8, speedUpBtn->getPositionY()));
	zBtn->setTag(1);
	zBtn->setEnabled(false);

	OperationManager::getInstance()->_zBtn = zBtn;

	MenuItemImage * xBtn = MenuItemImage::create(
		"operation_layer/x_btn_01.png",
		"operation_layer/x_btn_02.png",
		"operation_layer/x_btn_03.png",
		CC_CALLBACK_1(OperationLayer::uiMenuCallback, this));
	xBtn->setScale(1);
	xBtn->setAnchorPoint(Point(0.5, 0.5));
	xBtn->setPosition(Point(winSize.width - (xBtn->getContentSize().width+8)-xBtn->getContentSize().width / 2 - 8, speedUpBtn->getPositionY()));
	xBtn->setTag(2);
	xBtn->setEnabled(false);

	OperationManager::getInstance()->_xBtn = xBtn;

	MenuItemImage * cBtn = MenuItemImage::create(
		"operation_layer/c_btn_01.png",
		"operation_layer/c_btn_02.png",
		"operation_layer/c_btn_03.png",
		CC_CALLBACK_1(OperationLayer::uiMenuCallback, this));
	cBtn->setScale(1);
	cBtn->setAnchorPoint(Point(0.5, 0.5));
	cBtn->setPosition(Point(winSize.width - cBtn->getContentSize().width / 2 - 8, speedUpBtn->getPositionY()));
	cBtn->setTag(3);
	cBtn->setEnabled(false);

	OperationManager::getInstance()->_cBtn = cBtn;

	auto uiMenu = Menu::create(pauseMenuItem,zBtn,xBtn,cBtn,NULL);
	uiMenu->setPosition(Point(0,0));
	
	this->addChild(uiMenu, 1);

	_listenerTouch = EventListenerTouchOneByOne::create();
	_listenerTouch->onTouchBegan = CC_CALLBACK_2(OperationLayer::onTouchBegan, this);
	_listenerTouch->onTouchMoved = CC_CALLBACK_2(OperationLayer::onTouchMoved, this);
	_listenerTouch->onTouchEnded = CC_CALLBACK_2(OperationLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerTouch, this);

	resetTouchMove();

	return true;
}


bool OperationLayer::onTouchBegan(Touch* touch, Event *unused_event)
{
	if (GameManager::getInstance()->_gameState != (int)GameManager::GameState::IN_THE_GAME){
		return false;
	}

	if (_touchMoveTrigger != 0){
		return false;
	}
	_touchBeginPoint = touch->getLocation();
	return true;
}

void OperationLayer::onTouchMoved(Touch* touch, Event *unused_event)
{

}

void OperationLayer::onTouchEnded(Touch* touch, Event *unused_event)
{
	if (GameManager::getInstance()->_gameState != (int)GameManager::GameState::IN_THE_GAME){
		return;
	}
	if (_touchMoveTrigger != 0){
		return;
	}
	_touchEndPoint = touch->getLocation();
	if (_touchEndPoint.x - _touchBeginPoint.x < -TOUCH_MOVE_TRIGGER_DISTANCE){
		_touchMoveTrigger = TOUCH_MOVE_DIRECTION_LEFT;
		
	}
	else{
		if (_touchEndPoint.x - _touchBeginPoint.x > TOUCH_MOVE_TRIGGER_DISTANCE){
			_touchMoveTrigger = TOUCH_MOVE_DIRECTION_RIGHT;
			
		}
	}
}

void OperationLayer::resetTouchMove(){
	_touchBeginPoint = Point::ZERO;
	_touchEndPoint = Point::ZERO;
	_touchMoveTrigger = 0;
}

void OperationLayer::uiMenuCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	switch (((MenuItemImage*)pSender)->getTag()){
	case 0:{
	    
		auto pausePopupLayer =  PausePopupLayer::create();
		pausePopupLayer->setName("pause_pop_up_layer");
		this->getParent()->addChild(pausePopupLayer, 20);
		break;
	}
	case 1:
	case 2:
	case 3:
		QuestionManager::getInstance()->optionsCallback(pSender);
		break;
	}

}

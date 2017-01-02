#include "PausePopupLayer.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "CharacterManager.h"
#include "MapManager.h"
#include "GameEffectManager.h"
#include "HUDManager.h"
#include "OperationManager.h"
#include "QuestionManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

PausePopupLayer::PausePopupLayer(){

}

PausePopupLayer::~PausePopupLayer(){
	
}

void PausePopupLayer::onExit(){
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
}

bool PausePopupLayer::init(){
	if (!Layer::init()){
		return false;
	}


	if (GameManager::getInstance()->_gameState != (int)GameManager::GameState::PAUSE){
		_oldGameState = GameManager::getInstance()->_gameState;
		GameManager::getInstance()->_gameState = (int)GameManager::GameState::PAUSE;
	}

	setSwallowTouchListener();
	//setKeyboardListener();

	auto pauseBg = Sprite::create("pause_popup_layer/pause_bg.png");

	pauseBg->setAnchorPoint(Point(0, 0));

	this->addChild(pauseBg, 1);

	auto winSize = Director::getInstance()->getWinSize();
	
	auto popupMenu = Menu::create();

	auto continueMenuItem = MenuItemImage::create("pause_popup_layer/continue_0.png", \
		"pause_popup_layer/continue_1.png", \
		CC_CALLBACK_1(PausePopupLayer::menuCallback,this));

	continueMenuItem->setAnchorPoint(Point(0.5, 0.5));
	continueMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2  + 64));
	continueMenuItem->setTag(0);
	popupMenu->addChild(continueMenuItem, 2);
	
	auto restartMenuItem = MenuItemImage::create("pause_popup_layer/restart_0.png", \
		"pause_popup_layer/restart_1.png", \
		CC_CALLBACK_1(PausePopupLayer::menuCallback, this));

	restartMenuItem->setAnchorPoint(Point(0.5, 0.5));
	restartMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2 ));
	restartMenuItem->setTag(1);
	popupMenu->addChild(restartMenuItem, 2);

	auto returnMenuItem = MenuItemImage::create("pause_popup_layer/return_0.png", \
		"pause_popup_layer/return_1.png", \
		CC_CALLBACK_1(PausePopupLayer::menuCallback, this));

	returnMenuItem->setAnchorPoint(Point(0.5, 0.5));
	returnMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2 - 64));
	returnMenuItem->setTag(2);
	popupMenu->addChild(returnMenuItem, 2);

	this->addChild(popupMenu, 2);
	popupMenu->setPosition(Point(0, 0));
	/*MessageBox("pause popup layer init", "test");*/
	return true;
}

void PausePopupLayer::menuCallback(Ref *pSender){
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	switch (((MenuItemImage*)pSender)->getTag()){
	case 0:{
			   GameManager::getInstance()->_gameState = _oldGameState;
			   this->removeFromParentAndCleanup(true);
	}
		break;
	case 1:{
			   int orginalSelHamsterId = GameManager::getInstance()->_playerSelHamsterId;
			   int originalSelGameMode = GameManager::getInstance()->_gameMode;
			   GameManager::getInstance()->destroyInstance();
			   CharacterManager::getInstance()->destroyInstance();
			   MapManager::getInstance()->destroyInstance();
			   GameEffectManager::getInstance()->destroyInstance();
			   HUDManager::getInstance()->destroyInstance();
			   OperationManager::getInstance()->destroyInstance();
			   QuestionManager::getInstance()->destroyInstance();

			   GameManager::getInstance()->_playerSelHamsterId = orginalSelHamsterId;
			   GameManager::getInstance()->_gameMode = originalSelGameMode;

			   auto newScene = GameScene::createScene();
			   auto sceneTransition = TransitionFadeDown::create(0.5, newScene);
			   Director::getInstance()->replaceScene(sceneTransition);
			  // this->removeFromParentAndCleanup(true);
			 
	}
		break;
	case 2:{
			   GameManager::getInstance()->destroyInstance();
			   CharacterManager::getInstance()->destroyInstance();
			   MapManager::getInstance()->destroyInstance();
			   GameEffectManager::getInstance()->destroyInstance();
			   HUDManager::getInstance()->destroyInstance();
			   OperationManager::getInstance()->destroyInstance();
			   QuestionManager::getInstance()->destroyInstance();
			  
			   auto newScene = TitleScene::createScene();
			   auto transition = TransitionFadeDown::create(0.5, newScene);
			   Director::getInstance()->replaceScene(transition);

			 //  this->removeFromParentAndCleanup(true);
			   
		
	}
		break;
	}
}

void PausePopupLayer::setSwallowTouchListener()
{
	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		return true;
	};
	_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

//void PausePopupLayer::setKeyboardListener()
//{
//	_keyboardListener = EventListenerKeyboard::create();
//	
//	_keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event)
//	{
//		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_CTRL){
//			
//			GameManager::getInstance()->_gameState = _oldGameState;
//			this->removeFromParentAndCleanup(true);
//		}
//		
//	};
//	
//	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
//}

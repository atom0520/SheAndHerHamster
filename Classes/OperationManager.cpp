#include "OperationManager.h"
#include "CharacterManager.h"
#include "InputManager.h"
#include "PausePopupLayer.h"
#include "GameManager.h"
#include "QuestionManager.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

//ÉùÃ÷¾²Ì¬±äÁ¿
OperationManager * OperationManager::_instance = nullptr;

OperationManager * OperationManager::getInstance(){
	if (_instance == nullptr){
		_instance = new OperationManager();
		_instance->init();
	}
	return _instance;
}

void OperationManager::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

bool OperationManager::init(){
	_operationLayer = nullptr;
	//_joyStick = nullptr;
	_speedUpBtn = nullptr;
	_pauseBtn = nullptr;
	return true;
}

void OperationManager::update(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_LEFT_CTRL] == (int)InputManager::KeyState::JUST_PRESSED){
		if (GameManager::getInstance()->_gameState == (int)GameManager::GameState::GET_READY\
			|| GameManager::getInstance()->_gameState == (int)GameManager::GameState::IN_THE_GAME){
			//_joyStick->resetJoyStick();
			auto pausePopupLayer = PausePopupLayer::create();
			pausePopupLayer->setName("pause_pop_up_layer");
			_operationLayer->getParent()->addChild(pausePopupLayer, 20);
		}
		else if (GameManager::getInstance()->_gameState == (int)GameManager::GameState::PAUSE){

			auto pausePopupLayer = (PausePopupLayer*)_operationLayer->getParent()->getChildByName("pause_pop_up_layer");
			GameManager::getInstance()->_gameState = pausePopupLayer->_oldGameState;
			pausePopupLayer->removeFromParentAndCleanup(true);

		}
	}
#endif
    /*if(_speedUpBtn != nullptr){
        if(((Hamster *)CharacterManager::getInstance()->_player)->_energy < HAMSTER_RUN_CONSUMED_ENERGY){
            if(_speedUpBtn->_disabled==false){
                _speedUpBtn->_disabled=true;
            }
        }
        else{
            if(_speedUpBtn->_disabled==true){
                _speedUpBtn->_disabled=false;
            }
        }
        _speedUpBtn->updateFrame();
    }*/
    
}

void OperationManager::optionBtnCallBack(Ref *pSender){
	MenuItemImage * optionBtn = (MenuItemImage *)pSender;

	if (optionBtn->getTag() == QuestionManager::getInstance()->_currentKeyOptionTag){

		((Hamster *)CharacterManager::getInstance()->_player)->_energy += QuestionManager::getInstance()->_currentQuestionReward;
		QuestionManager::getInstance()->clearQuestion();
		QuestionManager::getInstance()->_needResetQuestion = true;
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");

	}
	else{

		((Hamster *)CharacterManager::getInstance()->_player)->_energy -= QuestionManager::getInstance()->_currentQuestionErrorPunishment;

		_zBtn->setEnabled(false);
		_xBtn->setEnabled(false);
		_cBtn->setEnabled(false);

		QuestionManager::getInstance()->_cdAfterError = CD_TIME_AFTER_ERROR;
		QuestionManager::getInstance()->highlightKeyOption();
		SimpleAudioEngine::getInstance()->playEffect("sound/error.wav");

	}
}
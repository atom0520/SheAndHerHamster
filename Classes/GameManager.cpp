#include "GameManager.h"
#include "OperationManager.h"
#include "GameManager.h"
#include "CharacterManager.h"
#include "MapManager.h"
#include "HUDManager.h"
#include "QuestionManager.h"
#include "GameEffectManager.h"
#include "GlobalEffect.h"
#include "EndPopupLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "InputManager.h"
#endif

//ÉùÃ÷¾²Ì¬±äÁ¿
GameManager * GameManager::_instance = nullptr;

GameManager * GameManager::getInstance(){
	if (_instance == nullptr){
		_instance = new GameManager();
		_instance->init();
	}
	return _instance;
}

void GameManager::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

bool GameManager::init(){
	_gameState = (int)GameState::PAUSE;
	_gameMode = (int)GameMode::RANKING_MODE;
	_finishNum = 0;
	_playerSelHamsterId = 1;
	_roundNum = 0;
	_caughtNum = 0;
	_getReadyPhaseCounter=0;
	_endPhaseCounter=0;
    _guidePhase=0;
	_playerMoveCompleteInGuide=false;
    _playerRunCompleteInGuide=false;
	return true;
}


void GameManager::update(){
	switch (GameManager::getInstance()->_gameState){
	case (int)GameManager::GameState::PAUSE:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		InputManager::getInstance()->update();
#endif
		OperationManager::getInstance()->update();
		MapManager::getInstance()->update();
		break;

	case (int)GameManager::GameState::GET_READY:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		InputManager::getInstance()->update();
#endif
		CharacterManager::getInstance()->update();
		MapManager::getInstance()->update();
		GameEffectManager::getInstance()->update();
		HUDManager::getInstance()->update();
		OperationManager::getInstance()->update();
		
		switch (_gameMode){
		case (int)GameMode::GUIDE_MODE:{
			switch (_guidePhase){
			case 0:{
				if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
					GameEffect * guideWords = GlobalEffect::create(73, \
						GAME_EFFECT_DIRECTION_DOWN, \
						Director::getInstance()->getWinSize().width / 2, \
						HEAD_NOTICE_EFFECT_POS_Y);

					guideWords->setScale(0.8);
					if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
						if (guideWords != nullptr){
							GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
							GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
						}
					}

				}

				if (GameManager::getInstance()->_getReadyPhaseCounter != -1){
					GameManager::getInstance()->_getReadyPhaseCounter++;
				}
			}break;
			case 1:{
				if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
					GameEffect * guideWords = GlobalEffect::create(74, \
						GAME_EFFECT_DIRECTION_DOWN, \
						Director::getInstance()->getWinSize().width / 2, \
						HEAD_NOTICE_EFFECT_POS_Y);
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
					GameEffect * guideWords = GlobalEffect::create(90, \
						GAME_EFFECT_DIRECTION_DOWN, \
						Director::getInstance()->getWinSize().width / 2, \
						HEAD_NOTICE_EFFECT_POS_Y);
#endif
					guideWords->setScale(0.8);
					if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
						if (guideWords != nullptr){
							GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
							GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
						}
					}

					//GameManager::getInstance()->_getReadyPhaseCounter = -1;
				}

				if (GameManager::getInstance()->_getReadyPhaseCounter != -1){
					GameManager::getInstance()->_getReadyPhaseCounter++;
				}


			}break;
			case 2:{
				if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
					GameEffect * guideWords = GlobalEffect::create(75, \
						GAME_EFFECT_DIRECTION_DOWN, \
						Director::getInstance()->getWinSize().width / 2, \
						HEAD_NOTICE_EFFECT_POS_Y);
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
					GameEffect * guideWords = GlobalEffect::create(76, \
						GAME_EFFECT_DIRECTION_DOWN, \
						Director::getInstance()->getWinSize().width / 2, \
						HEAD_NOTICE_EFFECT_POS_Y);
#endif
					guideWords->setScale(0.8);
					if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
						if (guideWords != nullptr){
							GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
							GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
						}
					}

					//GameManager::getInstance()->_getReadyPhaseCounter = -1;
				}

				if (GameManager::getInstance()->_getReadyPhaseCounter <10000){
					GameManager::getInstance()->_getReadyPhaseCounter++;
				}
			}break;
			case 3:{
					   if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
						   GameEffect * guideWords = GlobalEffect::create(77, \
							   GAME_EFFECT_DIRECTION_DOWN, \
							   Director::getInstance()->getWinSize().width / 2, \
							   HEAD_NOTICE_EFFECT_POS_Y);

						   guideWords->setScale(0.8);
						   if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
							   if (guideWords != nullptr){
								   GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
								   GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
							   }
						   }

						   //GameManager::getInstance()->_getReadyPhaseCounter = -1;
					   }

					   if (GameManager::getInstance()->_getReadyPhaseCounter <10000){
						   GameManager::getInstance()->_getReadyPhaseCounter++;
					   }
			}break;
			case 4:{
					   if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)					   
						   GameEffect * guideWords = GlobalEffect::create(78, \
							   GAME_EFFECT_DIRECTION_DOWN, \
							   Director::getInstance()->getWinSize().width / 2, \
							   HEAD_NOTICE_EFFECT_POS_Y);
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
						   GameEffect * guideWords = GlobalEffect::create(79, \
							   GAME_EFFECT_DIRECTION_DOWN, \
							   Director::getInstance()->getWinSize().width / 2, \
							   HEAD_NOTICE_EFFECT_POS_Y);
#endif
						   guideWords->setScale(0.8);
						   if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
							   if (guideWords != nullptr){
								   GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
								   GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
							   }
						   }

					   }else if (GameManager::getInstance()->_getReadyPhaseCounter > 32){
						   QuestionManager::getInstance()->update();
					   }

					   if (GameManager::getInstance()->_getReadyPhaseCounter <10000){
						   GameManager::getInstance()->_getReadyPhaseCounter++;
					   }
			}break;
			case 5:{
					   if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
						   GameEffect * guideWords = GlobalEffect::create(80, \
							   GAME_EFFECT_DIRECTION_DOWN, \
							   Director::getInstance()->getWinSize().width / 2, \
							   HEAD_NOTICE_EFFECT_POS_Y+80);

						   guideWords->setScale(0.8);
						   if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
							   if (guideWords != nullptr){
								   GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
								   GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
							   }
						   }


						   
					   }
					   else if (GameManager::getInstance()->_getReadyPhaseCounter > 32){
						   if (QuestionManager::getInstance()->_cdAfterError == 0){
							   QuestionManager::getInstance()->update();
						   }
						  
					   }

					   if (GameManager::getInstance()->_getReadyPhaseCounter <10000){
						   GameManager::getInstance()->_getReadyPhaseCounter++;
					   }
			}break;
			case 6:{
					   if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)						
							   GameEffect * guideWords = GlobalEffect::create(81, \
								   GAME_EFFECT_DIRECTION_DOWN, \
								   Director::getInstance()->getWinSize().width / 2, \
								   HEAD_NOTICE_EFFECT_POS_Y+80);
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
							   GameEffect * guideWords = GlobalEffect::create(82, \
								   GAME_EFFECT_DIRECTION_DOWN, \
								   Director::getInstance()->getWinSize().width / 2, \
								   HEAD_NOTICE_EFFECT_POS_Y+80);
#endif

						   guideWords->setScale(0.8);
						   if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
							   if (guideWords != nullptr){
								   GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
								   GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
							   }
						   }

					   }

					   if (GameManager::getInstance()->_getReadyPhaseCounter <10000){
						   GameManager::getInstance()->_getReadyPhaseCounter++;
					   }
			}
			case 7:{
					   
					   if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
						  
						   GameEffect * guideWords = GlobalEffect::create(83, \
							   GAME_EFFECT_DIRECTION_DOWN, \
							   Director::getInstance()->getWinSize().width / 2, \
							   HEAD_NOTICE_EFFECT_POS_Y + 80);

						   guideWords->setScale(0.8);
						   if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
							   if (guideWords != nullptr){
								   GameEffectManager::getInstance()->_glEffectLayer->addChild(guideWords, 1);
								   GameEffectManager::getInstance()->_gameEffects.push_back(guideWords);
							   }
						   }

					   }

					   if (GameManager::getInstance()->_getReadyPhaseCounter <10000){
						   GameManager::getInstance()->_getReadyPhaseCounter++;
					   }
			}break;
			}
			
		}break;
		case (int)GameMode::RANKING_MODE:{
			if (GameManager::getInstance()->_getReadyPhaseCounter == 32){
				GameEffect * countDownEffect = GlobalEffect::create(1, \
					GAME_EFFECT_DIRECTION_DOWN, \
					Director::getInstance()->getWinSize().width / 2, \
					HEAD_NOTICE_EFFECT_POS_Y);

				if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
					if (countDownEffect != nullptr){
						GameEffectManager::getInstance()->_glEffectLayer->addChild(countDownEffect, 1);
						GameEffectManager::getInstance()->_gameEffects.push_back(countDownEffect);
					}
				}

				//GameManager::getInstance()->_getReadyPhaseCounter = -1;
			}
			
			if (GameManager::getInstance()->_getReadyPhaseCounter != -1){
				GameManager::getInstance()->_getReadyPhaseCounter++;
			}
			
		}break;
		case (int)GameMode::ELIMINATION_MODE:{
			if (GameManager::getInstance()->_getReadyPhaseCounter == 16){
				
				
			}
			else if (GameManager::getInstance()->_getReadyPhaseCounter == 32){

				GameEffect * roundNumEffect = GlobalEffect::create(31, \
					GAME_EFFECT_DIRECTION_DOWN, \
					Director::getInstance()->getWinSize().width / 2, \
					HEAD_NOTICE_EFFECT_POS_Y);

				if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
					if (roundNumEffect != nullptr){
						GameEffectManager::getInstance()->_glEffectLayer->addChild(roundNumEffect, 1);
						GameEffectManager::getInstance()->_gameEffects.push_back(roundNumEffect);
					}
				}

				/*GameManager::getInstance()->_getReadyPhaseCounter = -1;*/
			}
			
			if (GameManager::getInstance()->_getReadyPhaseCounter != -1){
				GameManager::getInstance()->_getReadyPhaseCounter++;
			}										 

		}break;
		case (int)GameMode::SURVIVAL_MODE:{
			
			if (GameManager::getInstance()->_getReadyPhaseCounter == 16){
				
			}else if (GameManager::getInstance()->_getReadyPhaseCounter == 32){

				GameEffect * catsWarningEffect = GlobalEffect::create(39, \
					GAME_EFFECT_DIRECTION_DOWN, \
					Director::getInstance()->getWinSize().width / 2, \
					HEAD_NOTICE_EFFECT_POS_Y);

				if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
					if (catsWarningEffect != nullptr){
						GameEffectManager::getInstance()->_glEffectLayer->addChild(catsWarningEffect, 1);
						GameEffectManager::getInstance()->_gameEffects.push_back(catsWarningEffect);
					}
				}

			}
			
			if (GameManager::getInstance()->_getReadyPhaseCounter != -1){
				GameManager::getInstance()->_getReadyPhaseCounter++;
			}

		}break;
		}
	
		break;

	case  (int)GameManager::GameState::IN_THE_GAME:
		switch (_gameMode){
		case (int)GameMode::GUIDE_MODE:{
			switch (_guidePhase){
			case 1:{
			
			if (_playerMoveCompleteInGuide == true){
				_guidePhaseFinish = true;
				_playerMoveCompleteInGuide = false;
			}

			if (CharacterManager::getInstance()->_player->getPositionY() <= MapManager::getInstance()->_recurrenceLineInGuidePosY){
				for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_hamsters.begin(); it != CharacterManager::getInstance()->_hamsters.end();){
					if ((*it) != nullptr){
						(*it)->setPositionY((*it)->getPositionY()+MapManager::getInstance()->_recurrenceDistanceInGuide);
					}
					it++;
				}
				for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_masters.begin(); it != CharacterManager::getInstance()->_masters.end();){
					if ((*it) != nullptr){
						(*it)->setPositionY((*it)->getPositionY() + MapManager::getInstance()->_recurrenceDistanceInGuide);
					}
					it++;
				}
			}

			}break;
			case 2:{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			   if (OperationManager::getInstance()->_speedUpBtn->_pressed == true \
//				   || InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_SPACE] >= (int)InputManager::KeyState::JUST_PRESSED)
//			   {
//					_guidePhaseFinish = true;
//				}
//#else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//				if (OperationManager::getInstance()->_speedUpBtn->_pressed == true){
//					_guidePhaseFinish = true;
//
//				}
//#endif
				if (_playerRunCompleteInGuide == true){
					_guidePhaseFinish = true;
					_playerRunCompleteInGuide = false;
				}

				if (CharacterManager::getInstance()->_player->getPositionY() <= MapManager::getInstance()->_recurrenceLineInGuidePosY){
					for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_hamsters.begin(); it != CharacterManager::getInstance()->_hamsters.end();){
						if ((*it) != nullptr){
							(*it)->setPositionY((*it)->getPositionY() + MapManager::getInstance()->_recurrenceDistanceInGuide);
						}
						it++;
					}
					for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_masters.begin(); it != CharacterManager::getInstance()->_masters.end();){
						if ((*it) != nullptr){
							(*it)->setPositionY((*it)->getPositionY() + MapManager::getInstance()->_recurrenceDistanceInGuide);
						}
						it++;
					}
				}

			}break;
			case 3:{

			}break;
			case 4:{
			
			}break;
			}
			
		}break;

		case (int)GameMode::ELIMINATION_MODE:{
			switch (_roundNum){
			case 0:{
				if (_finishNum == 6){
					finishEliminationRound(_roundNum);
				}
			}break;
			case 1:{
				if (_finishNum == 4){
					finishEliminationRound(_roundNum);
				}
			}break;
			case 2:{
				if (_finishNum == 2){
					finishEliminationRound(_roundNum);
				}
			}break;
			case 3:{
				if (_finishNum == 1){
					finishEliminationRound(_roundNum);
				}
			}break;
			}
		}break;
		case (int)GameMode::SURVIVAL_MODE:{
			if (_caughtNum == 7\
				&& ((Hamster *)CharacterManager::getInstance()->_player)->_caught == false){
				CharacterManager::getInstance()->_player->_state = (int)Hamster::State::WIN;
				
				((Hamster *)CharacterManager::getInstance()->_player)->_ranking = 1;
				GameManager::getInstance()->finishRace();
			}
				/*if (_caughtNum + _finishNum >= 8){
				}*/
		}
		}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		InputManager::getInstance()->update();
#endif
		CharacterManager::getInstance()->update();
		MapManager::getInstance()->update();
		GameEffectManager::getInstance()->update();
		HUDManager::getInstance()->update();
		QuestionManager::getInstance()->update();
		OperationManager::getInstance()->update();


		break;
	case  (int)GameManager::GameState::END:{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		InputManager::getInstance()->update();
#endif
		CharacterManager::getInstance()->update();
		MapManager::getInstance()->update();
		HUDManager::getInstance()->update();
		GameEffectManager::getInstance()->update();

		if (GameManager::getInstance()->_endPhaseCounter == 8){
			if (((Hamster *)CharacterManager::getInstance()->_player)->_finish==true){
				SimpleAudioEngine::getInstance()->playEffect("sound/cheer.wav");
			}
		}
		else if (GameManager::getInstance()->_endPhaseCounter == 64){
			switch (_gameMode){
			case (int)GameMode::GUIDE_MODE:{				
				auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_RANKING_WIN);
				_gameLayer->getParent()->addChild(endLayer, 10);
			}break;
			case (int)GameMode::RANKING_MODE:{
				if (((Hamster*)CharacterManager::getInstance()->_player)->_ranking <= 3){
					auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_RANKING_WIN);
					_gameLayer->getParent()->addChild(endLayer, 10);
				}
				else{
					auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_RANKING_LOSE);
					_gameLayer->getParent()->addChild(endLayer, 10);
				}

			}break;
			case (int)GameMode::ELIMINATION_MODE:{
				if (((Hamster*)CharacterManager::getInstance()->_player)->_ranking == 1){
					auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_RANKING_WIN);
					_gameLayer->getParent()->addChild(endLayer, 10);
				}
				else{
					auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_RANKING_LOSE);
					_gameLayer->getParent()->addChild(endLayer, 10);
				}
			}break;
			case (int)GameMode::SURVIVAL_MODE:
			{
				if (((Hamster*)CharacterManager::getInstance()->_player)->_caught == true){
					auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_CAUGHT);
					_gameLayer->getParent()->addChild(endLayer, 10);
				}
				else if (((Hamster*)CharacterManager::getInstance()->_player)->_caught == false \
					&& GameManager::getInstance()->_caughtNum == 7){
					auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_SURVIVED);
					_gameLayer->getParent()->addChild(endLayer, 10);
				}
				else{

					if (((Hamster*)CharacterManager::getInstance()->_player)->_ranking <= 3){
						auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_RANKING_WIN);
						_gameLayer->getParent()->addChild(endLayer, 10);
					}
					else{
						auto endLayer = EndPopupLayer::create((int)EndPopupLayer::Type::END_RANKING_LOSE);
						_gameLayer->getParent()->addChild(endLayer, 10);
					}
				}

			}break;
			}
		}

		if (GameManager::getInstance()->_endPhaseCounter != -1){
			GameManager::getInstance()->_endPhaseCounter++;
		}
		
	}break;

	default:
		break;
	}
}

void GameManager::startGame(){
	_gameState = (int)GameState::IN_THE_GAME;

	switch (_gameMode){
	case (int)GameMode::RANKING_MODE:{

	}break;
	case (int)GameMode::ELIMINATION_MODE:{
		if (CharacterManager::getInstance()->_player != nullptr){
			if (CharacterManager::getInstance()->_player->_state != (int)Hamster::State::LOSE \
				&& ((Hamster *)CharacterManager::getInstance()->_player)->_finish == true){
				CharacterManager::getInstance()->_player->_state = (int)Hamster::State::STOP;
				
				((Hamster *)CharacterManager::getInstance()->_player)->_finish = false;
			}
		}

		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_opponentHamsters.begin(); it != CharacterManager::getInstance()->_opponentHamsters.end();){
			if ((*it) != nullptr){
				if ((*it)->_state != (int)Hamster::State::LOSE \
					&& ((Hamster *)*it)->_finish == true){
					(*it)->_state = (int)Hamster::State::STOP;
					((Hamster *)*it)->_finish = false;
				}
			}
			it++;
		}
	}break;
	case (int)GameMode::SURVIVAL_MODE:{

	}break;
	}
	
	//OperationManager::getInstance()->_joyStick->_listenerTouch->setEnabled(true);
	QuestionManager::getInstance()->initFoldedQuestionPanel();
	QuestionManager::getInstance()->_needResetQuestion = true;
	
}

//void GameManager::reStartGame(){
//	_gameState = (int)GameState::IN_THE_GAME;
//
//	if (CharacterManager::getInstance()->_player != nullptr){
//		if (CharacterManager::getInstance()->_player->_state != (int)Hamster::State::LOSE \
//			&& ((Hamster *)CharacterManager::getInstance()->_player)->_finish ==true){
//			CharacterManager::getInstance()->_player->_state = (int)Hamster::State::STOP;
//			((Hamster *)CharacterManager::getInstance()->_player)->_finish = false;
//		}		
//	}
//
//	for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_opponentHamsters.begin(); it != CharacterManager::getInstance()->_opponentHamsters.end();){
//		if ((*it) != nullptr){
//			if ((*it)->_state != (int)Hamster::State::LOSE \
//				&& ((Hamster *)CharacterManager::getInstance()->_player)->_finish == true){
//				(*it)->_state = (int)Hamster::State::STOP;
//				((Hamster *)*it)->_finish = false;
//			}			
//		}
//		it++;
//	}
//
//	OperationManager::getInstance()->_joyStick->_eventListener->setEnabled(true);
//	QuestionManager::getInstance()->initFoldedQuestionPanel();
//
//}

void GameManager::winGame(){
	_gameState = (int)GameState::END;
	MessageBox("win", "win");

	GameEffect * winEffect = GlobalEffect::create(2, \
		GAME_EFFECT_DIRECTION_DOWN, \
		Director::getInstance()->getWinSize().width / 2, \
		Director::getInstance()->getWinSize().height - 100);

	if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
		if (winEffect != nullptr){
			GameEffectManager::getInstance()->_glEffectLayer->addChild(winEffect, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(winEffect);
		}
	}

	//OperationManager::getInstance()->_joyStick->_listenerTouch->setEnabled(false);
	QuestionManager::getInstance()->removeQuestionPanel();

}

void GameManager::finishRace(){
	//OperationManager::getInstance()->_joyStick->_listenerTouch->setEnabled(false);
	//OperationManager::getInstance()->_joyStick->resetJoyStick();
	QuestionManager::getInstance()->removeQuestionPanel();
	_gameState = (int)GameState::END;
	_endPhaseCounter = 0;
}

void GameManager::finishEliminationRound(int roundNum){
	/*OperationManager::getInstance()->_joyStick->_eventListener->setEnabled(false);
	OperationManager::getInstance()->_joyStick->resetJoyStick();*/
	QuestionManager::getInstance()->removeQuestionPanel();

	if (roundNum == 3){
		if (CharacterManager::getInstance()->_player != nullptr){
			if (((Hamster *)CharacterManager::getInstance()->_player)->_finish == true){
				CharacterManager::getInstance()->_player->_state = (int)Hamster::State::WIN;
				GameManager::getInstance()->finishRace();
			}
			else{
				CharacterManager::getInstance()->_player->_state = (int)Hamster::State::LOSE;

				((Sprite *)HUDManager::getInstance()->_hudLayer->getChildByTag(CharacterManager::getInstance()->_player->_id))->setSpriteFrame(\
					Sprite::create(String::createWithFormat(\
					"character/hamster/%d/head/hamster_head_discolored.png", \
					CharacterManager::getInstance()->_player->_id)->getCString())->getSpriteFrame());
				
				switch (CharacterManager::getInstance()->_player->_id){
				case 1:
				case 2:
				case 7:
				case 8:{
						   SimpleAudioEngine::getInstance()->playEffect("sound/caught_f.wav");
				}break;
				case 3:
				case 4:
				case 5:
				case 6:{
						   SimpleAudioEngine::getInstance()->playEffect("sound/caught_m.wav");
				}break;
				}

				GameManager::getInstance()->finishRace();
			}
		}

		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_opponentHamsters.begin(); it != CharacterManager::getInstance()->_opponentHamsters.end();){
			if ((*it) != nullptr && (*it)->_state != (int)Hamster::State::LOSE){
				if (((Hamster *)*it)->_finish == true){
					(*it)->_state = (int)Hamster::State::WIN;
				}
				else{
					if (((Hamster *)*it)->_ranking < _finishNum + 1){
						((Hamster *)*it)->_ranking = _finishNum + 1;
					}
					(*it)->_state = (int)Hamster::State::LOSE;
					((Sprite *)HUDManager::getInstance()->_hudLayer->getChildByTag((*it)->_id))->setSpriteFrame(\
						Sprite::create(String::createWithFormat(\
						"character/hamster/%d/head/hamster_head_discolored.png", \
						((Hamster *)*it)->_id)->getCString())->getSpriteFrame());
				}
			}
			it++;
		}

		return;
	}

	if (CharacterManager::getInstance()->_player != nullptr){
		if (((Hamster *)CharacterManager::getInstance()->_player)->_finish == true){
			//MessageBox("win", "test");
			CharacterManager::getInstance()->_player->_state = (int)Hamster::State::WIN;
		}
		else{
			
			if (((Hamster *)CharacterManager::getInstance()->_player)->_ranking < _finishNum + 1){
				((Hamster *)CharacterManager::getInstance()->_player)->_ranking = _finishNum + 1;
			}
			CharacterManager::getInstance()->_player->_state = (int)Hamster::State::LOSE;

			((Sprite *)HUDManager::getInstance()->_hudLayer->getChildByTag(CharacterManager::getInstance()->_player->_id))->setSpriteFrame(\
				Sprite::create(String::createWithFormat(\
				"character/hamster/%d/head/hamster_head_discolored.png", \
				CharacterManager::getInstance()->_player->_id)->getCString())->getSpriteFrame());

			switch (CharacterManager::getInstance()->_player->_id){
			case 1:
			case 2:
			case 7:
			case 8:{
					   SimpleAudioEngine::getInstance()->playEffect("sound/caught_f.wav");
			}break;
			case 3:
			case 4:
			case 5:
			case 6:{
					   SimpleAudioEngine::getInstance()->playEffect("sound/caught_m.wav");
			}break;
			}

			GameManager::getInstance()->finishRace();
		}
	}

	for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_opponentHamsters.begin(); it != CharacterManager::getInstance()->_opponentHamsters.end();){
		if ((*it) != nullptr && (*it)->_state != (int)Hamster::State::LOSE){
			if (((Hamster *)*it)->_finish == true){
				//MessageBox("win", "test");
				(*it)->_state = (int)Hamster::State::WIN;
			}
			else{
				if (((Hamster *)*it)->_ranking < _finishNum + 1){
					((Hamster *)*it)->_ranking = _finishNum + 1;
				}
				(*it)->_state = (int)Hamster::State::LOSE;
				((Sprite *)HUDManager::getInstance()->_hudLayer->getChildByTag((*it)->_id) )->setSpriteFrame(\
					Sprite::create(String::createWithFormat(\
					"character/hamster/%d/head/hamster_head_discolored.png", \
					((Hamster *)*it)->_id)->getCString())->getSpriteFrame());
			}
		}
		it++;
	}

	if (CharacterManager::getInstance()->_player->_state != (int)Hamster::State::LOSE){
		GameEffect * topNumNoticeEffect = GlobalEffect::create(36 + roundNum, \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			Director::getInstance()->getWinSize().height - 224);

		if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
			if (topNumNoticeEffect != nullptr){
				GameEffectManager::getInstance()->_glEffectLayer->addChild(topNumNoticeEffect, 1);
				GameEffectManager::getInstance()->_gameEffects.push_back(topNumNoticeEffect);
			}
		}
		_roundNum += 1;
		_finishNum = 0;
	}

}
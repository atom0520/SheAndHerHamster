#include "GameEffectManager.h"
#include "OperationManager.h"
#include "HUDManager.h"
#include "QuestionManager.h"
#include "CharacterManager.h"
#include "GlobalEffect.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "Global.h"

using namespace CocosDenshion;

//ÉùÃ÷¾²Ì¬±äÁ¿
GameEffectManager * GameEffectManager::_instance = nullptr;

GameEffectManager * GameEffectManager::getInstance(){
	if (_instance == nullptr){
		_instance = new GameEffectManager();
		_instance->init();
	}
	return _instance;
}

bool GameEffectManager::init(){
	_glEffectLayer = nullptr;
	return true;
}

void GameEffectManager::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

void GameEffectManager::update(){

	for (auto it = _gameEffects.begin(); it != _gameEffects.end();){
		if ((*it) != nullptr){			
			switch ((*it)->_id){
			case 1:{
				if ((*it)->_needRemoved == false){
					(*it)->update();
					it++;
				}
				else{
					GameManager::getInstance()->startGame();
					(*it)->removeFromParentAndCleanup(true);
					//CC_SAFE_RELEASE(*it);
					(*it) = nullptr;
					it = _gameEffects.erase(it);
				}
			}break; 
			
			case 31:
			case 32:
			case 33:
			case 34:
			case 40:{
					if ((*it)->_needRemoved == false){
						(*it)->update();
						it++;
					}
					else{
						GameEffect * countDownEffect = GlobalEffect::create(1, \
							GAME_EFFECT_DIRECTION_DOWN, \
							Director::getInstance()->getWinSize().width / 2, \
							HEAD_NOTICE_EFFECT_POS_Y);

						if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
							if (countDownEffect != nullptr){
								GameEffectManager::getInstance()->_glEffectLayer->addChild(countDownEffect, 1);
								GameEffectManager::getInstance()->_needAddedEffects.push_back(countDownEffect);
							}
						}
						(*it)->removeFromParentAndCleanup(true);
						//CC_SAFE_RELEASE(*it);
						(*it) = nullptr;
						it = _gameEffects.erase(it);
					}
				
			}break;
			case 36:
			case 37:
			case 38:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							it++;
						}
						else{
							GameEffect * roundNumEffect = GlobalEffect::create((*it)->_id-4, \
								GAME_EFFECT_DIRECTION_DOWN, \
								Director::getInstance()->getWinSize().width / 2, \
								HEAD_NOTICE_EFFECT_POS_Y);

							if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
								if (roundNumEffect != nullptr){
									GameEffectManager::getInstance()->_glEffectLayer->addChild(roundNumEffect, 1);
									GameEffectManager::getInstance()->_needAddedEffects.push_back(roundNumEffect);

								}
							}
							(*it)->removeFromParentAndCleanup(true);
							//CC_SAFE_RELEASE(*it);
							(*it) = nullptr;
							it = _gameEffects.erase(it);
						}
						
			}break;
			case 39:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							it++;
						}
						else{
							GameEffect * roundNumEffect = GlobalEffect::create(40, \
								GAME_EFFECT_DIRECTION_DOWN, \
								Director::getInstance()->getWinSize().width / 2, \
								HEAD_NOTICE_EFFECT_POS_Y);

							if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
								if (roundNumEffect != nullptr){
									GameEffectManager::getInstance()->_glEffectLayer->addChild(roundNumEffect, 1);
									GameEffectManager::getInstance()->_needAddedEffects.push_back(roundNumEffect);
								}
							}
							(*it)->removeFromParentAndCleanup(true);
							//CC_SAFE_RELEASE(*it);
							(*it) = nullptr;
							it = _gameEffects.erase(it);
						}
						
			}break;
			case 73:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							
							it++;

						}
						else{
							
							GameManager::getInstance()->_getReadyPhaseCounter = 0;
							GameManager::getInstance()->_guidePhase += 1;

							(*it)->removeFromParentAndCleanup(true);
							//CC_SAFE_RELEASE(*it);
							(*it) = nullptr;
							it = _gameEffects.erase(it);

						}
			}break;
			case 74:
			case 90:{
						if ((*it)->_needRemoved == false){
							(*it)->update();

							if (((GameEffect *)*it)->_currentAnimationIndex == 0 \
								&& ((GameEffect *)*it)->_animationCounter == 48)	{

								/*GameEffect * selectRect = GlobalEffect::create(29, \
									GAME_EFFECT_DIRECTION_DOWN, \
									0, \
									0);
								selectRect->setScale(2.5);*/

								/*if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (selectRect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(selectRect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(selectRect);
									}
								}*/

								GameEffect * guideCursor = GlobalEffect::create(84, \
									GAME_EFFECT_DIRECTION_DOWN, \
									Director::getInstance()->getWinSize().width/2, \
									Director::getInstance()->getWinSize().height/2);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (guideCursor != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(guideCursor, 2);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(guideCursor);
									}
								}


								GameManager::getInstance()->_gameState = (int)GameManager::GameState::IN_THE_GAME;
								GameManager::getInstance()->_playerMoveCompleteInGuide = false;
							}							

							it++;
						}
						else{
							
							if (GameManager::getInstance()->_guidePhaseFinish == true)
							{								
								GameEffect * goodEffect = GlobalEffect::create(85, \
									GAME_EFFECT_DIRECTION_DOWN, \
									Director::getInstance()->getWinSize().width / 2, \
									HEAD_NOTICE_EFFECT_POS_Y);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (goodEffect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(goodEffect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(goodEffect);
									}
								}

								(*it)->removeFromParentAndCleanup(true);
								//CC_SAFE_RELEASE(*it);
								(*it) = nullptr;
								it = _gameEffects.erase(it);						
		
							}
							else{
								it++;
							}
							
						}

			}break;
			case 75:
			case 76:{
						if ((*it)->_needRemoved == false){
							(*it)->update();

							if (((GameEffect *)*it)->_currentAnimationIndex == 0 \
								&& ((GameEffect *)*it)->_animationCounter == 48){

								GameEffect * selectRect = GlobalEffect::create(29, \
									GAME_EFFECT_DIRECTION_DOWN, \
									OperationManager::getInstance()->_speedUpBtn->getPositionX(), \
									OperationManager::getInstance()->_speedUpBtn->getPositionY());
								selectRect->setScale(1.8f);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (selectRect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(selectRect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(selectRect);
									}
								}

								GameEffect * guideCursor = GlobalEffect::create(86, \
									GAME_EFFECT_DIRECTION_DOWN, \
									OperationManager::getInstance()->_speedUpBtn->getPositionX(), \
									OperationManager::getInstance()->_speedUpBtn->getPositionY());

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (guideCursor != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(guideCursor, 2);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(guideCursor);
									}
								}

								if (((Hamster*)CharacterManager::getInstance()->_player)->_energy < HAMSTER_RUN_CONSUMED_ENERGY){
									((Hamster*)CharacterManager::getInstance()->_player)->_energy += HAMSTER_RUN_CONSUMED_ENERGY;
								}
								GameManager::getInstance()->_playerRunCompleteInGuide = false;
								GameManager::getInstance()->_gameState = (int)GameManager::GameState::IN_THE_GAME;
								if (OperationManager::getInstance()->_speedUpBtn->isEnabled() == false){
									OperationManager::getInstance()->_speedUpBtn->setEnabled(true);
								}							
							
							}

							it++;
						}
						else{

							if (GameManager::getInstance()->_guidePhaseFinish == true)
							{
								GameEffect * goodEffect = GlobalEffect::create(85, \
									GAME_EFFECT_DIRECTION_DOWN, \
									Director::getInstance()->getWinSize().width / 2, \
									HEAD_NOTICE_EFFECT_POS_Y);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (goodEffect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(goodEffect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(goodEffect);
									}
								}

								(*it)->removeFromParentAndCleanup(true);
								//CC_SAFE_RELEASE(*it);
								(*it) = nullptr;
								it = _gameEffects.erase(it);

							}
							else{
								it++;
							}

						}

			}break;
			case 77:{
						if ((*it)->_needRemoved == false){
							(*it)->update();

							if (((GameEffect *)*it)->_currentAnimationIndex == 1 \
								&& ((GameEffect *)*it)->_animationCounter == 4){

								GameEffect * selectRect = GlobalEffect::create(29, \
									GAME_EFFECT_DIRECTION_DOWN, \
									HUDManager::getInstance()->_energyProgress->getPositionX(), \
									HUDManager::getInstance()->_energyProgress->getPositionY());
								selectRect->setScale(2.5);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (selectRect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(selectRect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(selectRect);
									}
								}
							}
							it++;
						}
						else{							
							static int changePhaseDelay = 0;
							if (changePhaseDelay > 8){
								GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
								GameManager::getInstance()->_guidePhaseFinish = false;

								GameManager::getInstance()->_getReadyPhaseCounter = 0;
								GameManager::getInstance()->_guidePhase += 1;

								(*it)->removeFromParentAndCleanup(true);

								(*it) = nullptr;
								it = _gameEffects.erase(it);
							}
							else{
								if (changePhaseDelay == 0){
									GameManager::getInstance()->_guidePhaseFinish = true;
								}
								changePhaseDelay++;
								it++;
							}							
						}
			}break;
			
			case 78:
			case 79:
			{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							
							if (((GameEffect *)*it)->_currentAnimationIndex == 0 \
								&& ((GameEffect *)*it)->_animationCounter == 80){
								
								(*it)->setPositionY(HEAD_NOTICE_EFFECT_POS_Y + 80);
								QuestionManager::getInstance()->initFoldedQuestionPanel();
								QuestionManager::getInstance()->_needResetQuestion = true;
							}if (((GameEffect *)*it)->_currentAnimationIndex == 1 \
								&& ((GameEffect *)*it)->_animationCounter == 0){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
								(*it)->setPositionY(HEAD_NOTICE_EFFECT_POS_Y + 48);
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
								(*it)->setPositionY(HEAD_NOTICE_EFFECT_POS_Y + 80);
#endif
							}
														
							it++;
						}
						else{
							
							static bool hasCreatedHintRect = false;
							if (QuestionManager::getInstance()->_state == (int)QuestionManager::State::NOTHING_ON_DISPLAY\
								&& hasCreatedHintRect == false){
								QuestionManager::getInstance()->_needResetQuestion = true;

							}else if (QuestionManager::getInstance()->_state == (int)QuestionManager::State::QUESTION_ON_DISPLAY\
								&& hasCreatedHintRect == false){
									
									/*GameEffect * hintRect = GlobalEffect::create(88, \
										GAME_EFFECT_DIRECTION_DOWN, \
										QuestionManager::getInstance()->_questionPanelBg->getPositionX() - QuestionManager::getInstance()->_questionPanelBg->getAnchorPointInPoints().x + QuestionManager::getInstance()->_optionXBtn->getPositionX(), \
										QuestionManager::getInstance()->_questionPanelBg->getPositionY() - QuestionManager::getInstance()->_questionPanelBg->getAnchorPointInPoints().y + QuestionManager::getInstance()->_optionXBtn->getPositionY());*/
								    
								    int keyOptionBtnPosX = 0;

									if (OperationManager::getInstance()->_zBtn->getTag() == QuestionManager::getInstance()->_currentKeyOptionTag){
										keyOptionBtnPosX = OperationManager::getInstance()->_zBtn->getPositionX();
									}
									else if (OperationManager::getInstance()->_xBtn->getTag() == QuestionManager::getInstance()->_currentKeyOptionTag){
										keyOptionBtnPosX = OperationManager::getInstance()->_xBtn->getPositionX();
									}
									else if (OperationManager::getInstance()->_cBtn->getTag() == QuestionManager::getInstance()->_currentKeyOptionTag){
										keyOptionBtnPosX = OperationManager::getInstance()->_cBtn->getPositionX();
									}
								
									GameEffect * hintRect = GlobalEffect::create(29, \
										GAME_EFFECT_DIRECTION_DOWN, \
										keyOptionBtnPosX, \
										OperationManager::getInstance()->_zBtn->getPositionY());
									hintRect->setScale(1.5);

									if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
										if (hintRect != nullptr){
											GameEffectManager::getInstance()->_glEffectLayer->addChild(hintRect, 1);
											GameEffectManager::getInstance()->_needAddedEffects.push_back(hintRect);
										}
										hasCreatedHintRect = true;
									}

									GameEffect * guideCursor = GlobalEffect::create(87, \
										GAME_EFFECT_DIRECTION_DOWN, \
										keyOptionBtnPosX, \
										OperationManager::getInstance()->_zBtn->getPositionY());

									if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
										if (guideCursor != nullptr){
											GameEffectManager::getInstance()->_glEffectLayer->addChild(guideCursor, 2);
											GameEffectManager::getInstance()->_needAddedEffects.push_back(guideCursor);
										}
									}	
							}
							else if (hasCreatedHintRect == true)
							{
							
								if (QuestionManager::getInstance()->_needResetQuestion == true){
									
									GameManager::getInstance()->_guidePhaseFinish = true;
									QuestionManager::getInstance()->clearQuestion();
									QuestionManager::getInstance()->_needResetQuestion = false;
								}
							}							
							
							if (GameManager::getInstance()->_guidePhaseFinish == true)
							{
								
								GameEffect * goodEffect = GlobalEffect::create(85, \
									GAME_EFFECT_DIRECTION_DOWN, \
									Director::getInstance()->getWinSize().width / 2, \
									HEAD_NOTICE_EFFECT_POS_Y+80);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (goodEffect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(goodEffect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(goodEffect);
									}
								}

								(*it)->removeFromParentAndCleanup(true);
								//CC_SAFE_RELEASE(*it);
								(*it) = nullptr;
								it = _gameEffects.erase(it);

							}
							else{
								it++;
							}
							//it++;
						}

			}break;
			case 80:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							if (((GameEffect *)*it)->_currentAnimationIndex == 0 \
								&& ((GameEffect *)*it)->_animationCounter == 64){
								GameEffect * selectRect = GlobalEffect::create(29, \
									GAME_EFFECT_DIRECTION_DOWN, \
									HUDManager::getInstance()->_energyProgress->getPositionX(), \
									HUDManager::getInstance()->_energyProgress->getPositionY());
								selectRect->setScale(2.5);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (selectRect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(selectRect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(selectRect);
									}
								}
							}
							else if (((GameEffect *)*it)->_currentAnimationIndex == 1 \
								&& ((GameEffect *)*it)->_animationCounter == 8){
								QuestionManager::getInstance()->_needResetQuestion = true;
							}else if (((GameEffect *)*it)->_currentAnimationIndex == 1 \
								&& ((GameEffect *)*it)->_animationCounter == 64){

								if (QuestionManager::getInstance()->_optionZBtn->getTag() != QuestionManager::getInstance()->_currentKeyOptionTag){
									QuestionManager::getInstance()->optionsCallback(QuestionManager::getInstance()->_optionZBtn);
								}
								else if (QuestionManager::getInstance()->_optionXBtn->getTag() != QuestionManager::getInstance()->_currentKeyOptionTag){
									QuestionManager::getInstance()->optionsCallback(QuestionManager::getInstance()->_optionXBtn);
								}
								else if (QuestionManager::getInstance()->_optionCBtn->getTag() != QuestionManager::getInstance()->_currentKeyOptionTag){
									QuestionManager::getInstance()->optionsCallback(QuestionManager::getInstance()->_optionCBtn);
								}
								
								
							}
							else if (((GameEffect *)*it)->_currentAnimationIndex == 2\
								&& ((GameEffect *)*it)->_animationCounter == 80){
								
								QuestionManager::getInstance()->_cdAfterError = 0;
							}
							it++;
						}
						else{
							static int changePhaseDelay = 0;
							if (changePhaseDelay > 8){
								GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
								GameManager::getInstance()->_guidePhaseFinish = false;

								GameManager::getInstance()->_getReadyPhaseCounter = 0;
								GameManager::getInstance()->_guidePhase += 1;

								(*it)->removeFromParentAndCleanup(true);

								(*it) = nullptr;
								it = _gameEffects.erase(it);
							}
							else{
								if (changePhaseDelay == 0){
									GameManager::getInstance()->_guidePhaseFinish = true;
									QuestionManager::getInstance()->clearQuestion();
									QuestionManager::getInstance()->_needResetQuestion = false;
								}
								changePhaseDelay++;
								it++;
							}
						}
			}break;
			case 81:
			case 82:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							if (((GameEffect *)*it)->_currentAnimationIndex == 0 \
								&& ((GameEffect *)*it)->_animationCounter == 16){
								GameEffect * selectRect = GlobalEffect::create(29, \
									GAME_EFFECT_DIRECTION_DOWN, \
									OperationManager::getInstance()->_pauseBtn->getPositionX(), \
									OperationManager::getInstance()->_pauseBtn->getPositionY());
								selectRect->setScale(1.8f);

								if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
									if (selectRect != nullptr){
										GameEffectManager::getInstance()->_glEffectLayer->addChild(selectRect, 1);
										GameEffectManager::getInstance()->_needAddedEffects.push_back(selectRect);
									}
								}
							}
							
							
							it++;
						}
						else{
							static int changePhaseDelay = 0;
							if (changePhaseDelay > 8){
								GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
								GameManager::getInstance()->_guidePhaseFinish = false;

								GameManager::getInstance()->_getReadyPhaseCounter = 0;
								GameManager::getInstance()->_guidePhase += 1;

								(*it)->removeFromParentAndCleanup(true);

								(*it) = nullptr;
								it = _gameEffects.erase(it);
							}
							else{
								if (changePhaseDelay == 0){
									GameManager::getInstance()->_guidePhaseFinish = true;
									QuestionManager::getInstance()->clearQuestion();
									QuestionManager::getInstance()->_needResetQuestion = false;
								}
								changePhaseDelay++;
								it++;
							}
						}
			}break;
			case 83:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							if (((GameEffect *)*it)->_currentAnimationIndex == 2 \
								&& ((GameEffect *)*it)->_animationCounter == 32){
								SimpleAudioEngine::getInstance()->playEffect(READY_GO_EFFECT_FILE_PATH);
							}
							it++;
						}
						else{
							GameManager::getInstance()->_guidePhaseFinish = false;
							GameManager::getInstance()->_getReadyPhaseCounter = 0;
							GameManager::getInstance()->_guidePhase += 1;
							GameManager::getInstance()->_gameState = (int)GameManager::GameState::IN_THE_GAME;
							//OperationManager::getInstance()->_joyStick->_listenerTouch->setEnabled(true);
							OperationManager::getInstance()->_speedUpBtn->setEnabled(true);
							QuestionManager::getInstance()->_needResetQuestion = true;

							GameEffect * guideArrowDown = GlobalEffect::create(89, \
								GAME_EFFECT_DIRECTION_DOWN, \
								Director::getInstance()->getWinSize().width / 2, \
								48);

							if (GameEffectManager::getInstance()->_glEffectLayer != nullptr){
								if (guideArrowDown != nullptr){
									GameEffectManager::getInstance()->_glEffectLayer->addChild(guideArrowDown, 1);
									GameEffectManager::getInstance()->_needAddedEffects.push_back(guideArrowDown);
								}
							}

							(*it)->removeFromParentAndCleanup(true);
							(*it) = nullptr;
							it = _gameEffects.erase(it);
							
						}
			}break;
			case 85:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							it++;
						}
						else{
							switch (GameManager::getInstance()->_guidePhase){
							case 1:{
										GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;

										GameManager::getInstance()->_guidePhaseFinish = false;
										GameManager::getInstance()->_getReadyPhaseCounter = 0;
										GameManager::getInstance()->_guidePhase += 1;									  
							}break;
							case 2:{
										OperationManager::getInstance()->_speedUpBtn->setEnabled(false);
										GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
										GameManager::getInstance()->_guidePhaseFinish = false;
										GameManager::getInstance()->_getReadyPhaseCounter = 0;
										GameManager::getInstance()->_guidePhase += 1;
							}break;

							case 4:{
									  
									   GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;

									   GameManager::getInstance()->_guidePhaseFinish = false;
									   GameManager::getInstance()->_getReadyPhaseCounter = 0;
									   GameManager::getInstance()->_guidePhase += 1;
							}break;

							}
							(*it)->removeFromParentAndCleanup(true);
							//CC_SAFE_RELEASE(*it);
							(*it) = nullptr;
							it = _gameEffects.erase(it);
						}
			
			}break;
			case 29:
			case 84:
			case 86:
			case 87:
			case 88:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::GUIDE_MODE){
								if (GameManager::getInstance()->_guidePhaseFinish == true){

									(*it)->removeFromParentAndCleanup(true);
									//CC_SAFE_RELEASE(*it);
									(*it) = nullptr;
									it = _gameEffects.erase(it);
								}
								else{
									it++;
								}
							}
						}
						else{
							(*it)->removeFromParentAndCleanup(true);
							//CC_SAFE_RELEASE(*it);
							(*it) = nullptr;
							it = _gameEffects.erase(it);
						}

			}break;
			case 89:{						
				(*it)->update();
				if (GameManager::getInstance()->_gameState == (int)GameManager::GameState::END){
					(*it)->removeFromParentAndCleanup(true);
					
					(*it) = nullptr;
					it = _gameEffects.erase(it);
				}else{				
					it++;
				}
			}break;
			default:{
						if ((*it)->_needRemoved == false){
							(*it)->update();
							it++;
						}
						else{
							(*it)->removeFromParentAndCleanup(true);
							//CC_SAFE_RELEASE(*it);
							(*it) = nullptr;
							it = _gameEffects.erase(it);
						}

			}break;
			}			

		}
		
	}
	
	for (auto it = _needAddedEffects.begin(); it != _needAddedEffects.end();){
		if ((*it) !=nullptr ){
			GameEffectManager::getInstance()->_gameEffects.push_back((*it));
			it = _needAddedEffects.erase(it);
		}
	}
}

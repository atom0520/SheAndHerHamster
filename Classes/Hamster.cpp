#include "Hamster.h"

#include "DataManager.h"
#include "InputManager.h"
#include "OperationManager.h"
#include "MapManager.h"
#include "GameManager.h"
#include "QuestionManager.h"
#include "HUDManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Hamster::Hamster(){

}

Hamster::~Hamster(){
	unloadAllAnimations();
	unloadAllFrames();
}

bool Hamster::init(){
	if (!Character::init()){
		return false;
	}
	_type = (int)Type::HAMSTER;

	_state = (int)State::STOP;
	_master = nullptr;

	_moveSpeed = HAMSTER_WALK_MOVE_SPEED;
	_energy = 100;
	_maxEnergy = 200;

	_runTrigger = false;
	_runTriggerEnergy = HAMSTER_RUN_CONSUMED_ENERGY;

	_intellegence = 25;
	_reactivity = 25;
	_reactionTime = 0;

	_ranking = 1;
	_finish =false;
	_caught = false;
	return true;
}

Hamster*  Hamster::create(int id, int controlType, int x, int y){
	Hamster * hamster = Hamster::create();
	if (hamster == nullptr){
		return nullptr;
	}
	hamster->_id = id;
	hamster->_controlType = controlType;
	hamster->setPosition(Point(x, y));
	hamster->_destPosition = Point(x, y);

	hamster->loadAllFrames();
	hamster->loadAllAnimations();
	hamster->updateFrame();

	return hamster;
}

void  Hamster::loadFramesFromDataFile(const char *framesDataKey){
	ValueMap framesData = DataManager::getInstance()->_staticData\
		.at("character").asValueMap()\
		.at("hamster").asValueMap()\
		//.at(String::createWithFormat("%02d", _elfId)->getCString()).asValueMap()
		.at(Value(_id).asString().c_str()).asValueMap()\
		.at("frames").asValueMap()\
		.at(framesDataKey).asValueMap();

	std::string spriteFrameNamePrefix = framesData.at("spriteframe_name_prefix").asString();
	int frameNum = framesData.at("frame_num").asInt();

	int frameIndexStart = this->_frames.size();
	_animationsFrameIndexStart[std::string(framesDataKey)] = frameIndexStart;

	float frameAnchorPointX = framesData.at("frame_anchor_point_x").asFloat();
	float frameAnchorPointY = framesData.at("frame_anchor_point_y").asFloat();

	for (int index = 0; index < frameNum; index++)
	{
        auto spriteFrameName =String::createWithFormat("%s_%02d.png", spriteFrameNamePrefix.c_str(), index+1);
		
        this->_frames[frameIndexStart + index]=Sprite::createWithSpriteFrameName(spriteFrameName->getCString())->getSpriteFrame();
		this->_frames[frameIndexStart + index]->retain();
	
		_framesAnchorPoint[frameIndexStart + index] = Point(frameAnchorPointX, frameAnchorPointY);
	}

}

void  Hamster::loadAllFrames(){
	loadFramesFromDataFile("stop_down");
	loadFramesFromDataFile("stop_left");
	loadFramesFromDataFile("stop_right");
	loadFramesFromDataFile("stop_up");
	loadFramesFromDataFile("walk_down");
	loadFramesFromDataFile("walk_left");
	loadFramesFromDataFile("walk_right");
	loadFramesFromDataFile("walk_up");
	loadFramesFromDataFile("run_down");
	loadFramesFromDataFile("run_left");
	loadFramesFromDataFile("run_right");
	loadFramesFromDataFile("run_up");
	loadFramesFromDataFile("cheer_down");
	loadFramesFromDataFile("cry_down");
}

void Hamster::loadAnimationFromDataFile(const char* animationDataKey){
	ValueMap framesData = DataManager::getInstance()->_staticData\
		.at("character").asValueMap()\
		.at("hamster").asValueMap()\
		.at(Value(_id).asString().c_str()).asValueMap()\
		.at("animations").asValueMap()\
		.at(animationDataKey).asValueMap();


	int animationId = _animationsId.size();

	_animationsId[std::string(animationDataKey)] = animationId;

	int animationFrameNum = framesData.at("animation_frame_num").asInt();

	bool isAnimationLooping = framesData.at("loop").asBool();

	//判断framesData中是否存有"animation_frame_index_start"的信息
	bool doesDataIncludeFrameIndexStart = false;
	for (auto it = framesData.begin(); it != framesData.end(); it++){
		if (it->first == std::string("animation_frame_index_start")){
			doesDataIncludeFrameIndexStart = true;
		}
	}
	int animationFrameIndexStart;
	if (doesDataIncludeFrameIndexStart){
		animationFrameIndexStart = _animationsFrameIndexStart[std::string(framesData.at("animation_frame_index_start").asString())];
	}
	else{
		animationFrameIndexStart = _animationsFrameIndexStart[std::string(animationDataKey)];
	}

	ValueMap animationFrameSequence = framesData.at("animation_frame_sequence").asValueMap();
	ValueMap animationDurationSequence = framesData.at("animation_duration_sequence").asValueMap();

	_animationFrameSequences[animationId] = new int[animationFrameNum + 1];
	_animationDurationSequences[animationId] = new int[animationFrameNum];

	for (int animationFrameIndex = 0; animationFrameIndex < animationFrameNum; animationFrameIndex++){
		_animationFrameSequences[animationId][animationFrameIndex] = animationFrameSequence[Value(animationFrameIndex).asString().c_str()].asInt() + animationFrameIndexStart;
		_animationDurationSequences[animationId][animationFrameIndex] = animationDurationSequence[Value(animationFrameIndex).asString().c_str()].asInt();
	}

	if (isAnimationLooping){
		_animationFrameSequences[animationId][animationFrameNum] = -1;//循环动画序列结尾标志
	}
	else{
		_animationFrameSequences[animationId][animationFrameNum] = -2;//非循环动画序列结尾标志
	}
}

void  Hamster::loadAllAnimations(){
	loadAnimationFromDataFile("stop_down");
	loadAnimationFromDataFile("stop_left");
	loadAnimationFromDataFile("stop_right");
	loadAnimationFromDataFile("stop_up");
	loadAnimationFromDataFile("walk_down");
	loadAnimationFromDataFile("walk_left");
	loadAnimationFromDataFile("walk_right");
	loadAnimationFromDataFile("walk_up");
	loadAnimationFromDataFile("run_down");
	loadAnimationFromDataFile("run_left");
	loadAnimationFromDataFile("run_right");
	loadAnimationFromDataFile("run_up");
	loadAnimationFromDataFile("cheer_down");
	loadAnimationFromDataFile("cry_down");
}

void Hamster::update(){
	this->setZOrder(MapManager::getInstance()->_mapHeight - this->getPositionY());
	/*OperationManager::getInstance()->_testLabel1->setString(String::createWithFormat("player_x is:%d,\nplayer_y is:%d", (int)this->getPositionX(), (int)this->getPositionY())->getCString());*/
	
	if (_energy < 0){
		_energy = 0;
	}
	else if (_energy>_maxEnergy){
		_energy = _maxEnergy;
	}

	switch (GameManager::getInstance()->_gameMode)
	{
		case (int)GameManager::GameMode::GUIDE_MODE:{
			if (GameManager::getInstance()->_guidePhase == 1){
				if (!isMoving() \
					&& GameManager::getInstance()->_gameState == (int)GameManager::GameState::IN_THE_GAME \
					&& _state != (int)State::WIN\
					&& _state != (int)State::LOSE\
					&& _state != (int)State::PAUSE\
					&& _finish != true){
					if (_moveTrigger != 0){
						GameManager::getInstance()->_playerMoveCompleteInGuide = true;
					}
				}
			}
			else if (GameManager::getInstance()->_guidePhase == 2){
				if (!isMoving() \
					&& GameManager::getInstance()->_gameState == (int)GameManager::GameState::IN_THE_GAME \
					&& _state != (int)State::WIN\
					&& _state != (int)State::LOSE\
					&& _state != (int)State::PAUSE\
					&& _finish != true){
					if (_runTrigger == true){
						GameManager::getInstance()->_playerRunCompleteInGuide = true;
					}
				}
			}
			else if (GameManager::getInstance()->_guidePhase >= 8){
				if (_finish == false){
					if (getPositionY() <= MapManager::getInstance()->_finishLinePosY){
						_finish = true;
						if (this->_controlType == (int)ControlType::PLAYER){
							_ranking = GameManager::getInstance()->_finishNum + 1;
							GameManager::getInstance()->_finishNum += 1;

							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
								_destPosition.y -= 32;
							}

						}
						else if (this->_controlType == (int)ControlType::COMPUTER){
							
							_ranking = GameManager::getInstance()->_finishNum + 1;

							GameManager::getInstance()->_finishNum += 1;
							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
								_destPosition.y -= 32;
							}
						}
					}
				}
				else if (_finish == true){
					if (_state != (int)State::WIN\
						&& _state != (int)State::LOSE\
						&& _state != (int)State::PAUSE)
					{
						if (isMoving() == false){
							
							_state = (int)State::WIN;
							if (this->_controlType == (int)ControlType::PLAYER){
								GameManager::getInstance()->finishRace();
							}
						}
					}
				}
			}
			
		}break;
		case (int)GameManager::GameMode::RANKING_MODE:{
			/*if (_state != (int)State::WIN\
				&& _state != (int)State::LOSE\
				&& _state != (int)State::PAUSE)
			{*/
			if (_finish == false){
				if (getPositionY() <= MapManager::getInstance()->_finishLinePosY){
					_finish = true;
					if (this->_controlType == (int)ControlType::PLAYER){
						/*_state = (int)State::WIN;*/

						HUDManager::getInstance()->displayFinishHamster(_id);

						_ranking = GameManager::getInstance()->_finishNum + 1;
						GameManager::getInstance()->_finishNum += 1;

						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
							_destPosition.y -= 32;
						}
						
					}
					else if (this->_controlType == (int)ControlType::COMPUTER){
						/*_state = (int)State::WIN;*/
						HUDManager::getInstance()->displayFinishHamster(this->_id);
						_ranking = GameManager::getInstance()->_finishNum + 1;

						GameManager::getInstance()->_finishNum += 1;
						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
							_destPosition.y -= 32;
						}
					}
				}
			}
			else if (_finish == true){
				if (_state != (int)State::WIN\
					&& _state != (int)State::LOSE\
					&& _state != (int)State::PAUSE)
				{
					if (isMoving() == false){
						/*if (_ranking <= 3){
							_state = (int)State::WIN;
						}
						else{
							_state = (int)State::LOSE;
						}*/
						_state = (int)State::WIN;
						if (this->_controlType == (int)ControlType::PLAYER){
							GameManager::getInstance()->finishRace();
						}
					}
				}
			}
				
			//}
		}break;
		case (int)GameManager::GameMode::ELIMINATION_MODE:{
			switch (GameManager::getInstance()->_roundNum){
				case 0:{
					if (_finish == false\
						&& GameManager::getInstance()->_finishNum < 6){
						if (getPositionY() <= MapManager::getInstance()->_eliminationLinePosY[0]){
							_finish = true;
							if (this->_controlType == (int)ControlType::PLAYER){

								//HUDManager::getInstance()->displayFinishHamster(_id);

								//_ranking = GameManager::getInstance()->_finishNum + 1;
								GameManager::getInstance()->_finishNum += 1;


								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
								//GameManager::getInstance()->finishRankingRace();
							}
							else if (this->_controlType == (int)ControlType::COMPUTER){
								
								//HUDManager::getInstance()->displayFinishHamster(this->_id);
							   // _ranking = GameManager::getInstance()->_finishNum + 1;

								GameManager::getInstance()->_finishNum += 1;


								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
							}
						}
					}
					else if (_finish == true){
						if (_state != (int)State::WIN\
							&& _state != (int)State::LOSE\
							&& _state != (int)State::PAUSE)
						{
							if (isMoving() == false){
								_state = (int)State::WIN;
							}
						}
					}		
				}break;
				case 1:{
					if (_finish == false\
						&& GameManager::getInstance()->_finishNum < 4){
						if (getPositionY() <= MapManager::getInstance()->_eliminationLinePosY[1]){
							_finish = true;
							if (this->_controlType == (int)ControlType::PLAYER){

								//HUDManager::getInstance()->displayFinishHamster(_id);
								_ranking = GameManager::getInstance()->_finishNum + 1;
								GameManager::getInstance()->_finishNum += 1;


								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
							}
							else if (this->_controlType == (int)ControlType::COMPUTER){

								//HUDManager::getInstance()->displayFinishHamster(this->_id);
								_ranking = GameManager::getInstance()->_finishNum + 1;
								GameManager::getInstance()->_finishNum += 1;
								
								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
							}
						}
					}
					else if (_finish == true){
						if (_state != (int)State::WIN\
							&& _state != (int)State::LOSE\
							&& _state != (int)State::PAUSE)
						{
							if (isMoving() == false){
								_state = (int)State::WIN;
							}
						}
					}
				}break;
				case 2:{
					if (_finish == false\
						&& GameManager::getInstance()->_finishNum < 2){
						if (getPositionY() <= MapManager::getInstance()->_eliminationLinePosY[2]){
							_finish = true;
							if (this->_controlType == (int)ControlType::PLAYER){

								//HUDManager::getInstance()->displayFinishHamster(_id);
								_ranking = GameManager::getInstance()->_finishNum + 1;
								GameManager::getInstance()->_finishNum += 1;


								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
							}
							else if (this->_controlType == (int)ControlType::COMPUTER){

								//HUDManager::getInstance()->displayFinishHamster(this->_id);
								_ranking = GameManager::getInstance()->_finishNum + 1;
								GameManager::getInstance()->_finishNum += 1;

								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
							}
						}
					}
					else if (_finish == true){
						if (_state != (int)State::WIN\
							&& _state != (int)State::LOSE\
							&& _state != (int)State::PAUSE)
						{
							if (isMoving() == false){
								_state = (int)State::WIN;
							}
						}
					}
				}break;
				case 3:{
					if (_finish == false\
						&& GameManager::getInstance()->_finishNum < 1){
						if (getPositionY() <= MapManager::getInstance()->_finishLinePosY){
							_finish = true;
							if (this->_controlType == (int)ControlType::PLAYER){

								//HUDManager::getInstance()->displayFinishHamster(_id);
								_ranking = GameManager::getInstance()->_finishNum + 1;
								GameManager::getInstance()->_finishNum += 1;


								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
							}
							else if (this->_controlType == (int)ControlType::COMPUTER){

								//HUDManager::getInstance()->displayFinishHamster(this->_id);
								_ranking = GameManager::getInstance()->_finishNum + 1;
								GameManager::getInstance()->_finishNum += 1;

								if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
									_destPosition.y -= 32;
								}
							}
						}
					}
					else if (_finish == true){
						if (_state != (int)State::WIN\
							&& _state != (int)State::LOSE\
							&& _state != (int)State::PAUSE)
						{
							if (isMoving() == false){
								_state = (int)State::WIN;
							}
						}
					}
				}break;
			}
		
		}break;
		case (int)GameManager::GameMode::SURVIVAL_MODE:{
			if (_finish == false && _caught==false\
				&& _state != (int)State::WIN\
				&& _state != (int)State::LOSE\
				&& _state != (int)State::PAUSE){
				if (getPositionY() <= MapManager::getInstance()->_finishLinePosY){
					_finish = true;
					if (this->_controlType == (int)ControlType::PLAYER){
						/*_state = (int)State::WIN;*/

						//HUDManager::getInstance()->displayFinishHamster(_id);

						_ranking = GameManager::getInstance()->_finishNum + 1;
						GameManager::getInstance()->_finishNum += 1;

						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
							_destPosition.y -= 32;
						}

					}
					else if (this->_controlType == (int)ControlType::COMPUTER){
						/*_state = (int)State::WIN;*/
						//HUDManager::getInstance()->displayFinishHamster(this->_id);
						_ranking = GameManager::getInstance()->_finishNum + 1;

						GameManager::getInstance()->_finishNum += 1;
						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
							_destPosition.y -= 32;
						}
					}
				}
			}
			else if (_finish == true){
				if (_state != (int)State::WIN\
					&& _state != (int)State::LOSE\
					&& _state != (int)State::PAUSE)
				{
					if (isMoving() == false){
						/*if (_ranking <= 3){
						_state = (int)State::WIN;
						}
						else{
						_state = (int)State::LOSE;
						}*/
						_state = (int)State::WIN;
						if (this->_controlType == (int)ControlType::PLAYER){
							GameManager::getInstance()->finishRace();
						}
					}
				}
			}
			else if (_caught == true){
				if (_state != (int)State::WIN\
					&& _state != (int)State::LOSE\
					&& _state != (int)State::PAUSE)
				{
					_state = (int)State::LOSE;
					switch (_id){
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
					
					GameManager::getInstance()->_caughtNum += 1;
					if (this->_controlType == (int)ControlType::PLAYER){
						GameManager::getInstance()->finishRace();
					}
				}				
			}
		}break;
	}

	if (GameManager::getInstance()->_gameState == (int)GameManager::GameState::IN_THE_GAME \
		&& _state != (int)State::WIN\
		&& _state != (int)State::LOSE\
		&& _state != (int)State::PAUSE\
		&& _finish != true){

		if (_controlType == (int)ControlType::PLAYER){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			if (InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_LEFT_ARROW] == (int)InputManager::KeyState::JUST_PRESSED\
				|| OperationManager::getInstance()->_operationLayer->_touchMoveTrigger == TOUCH_MOVE_DIRECTION_LEFT)
#else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if (OperationManager::getInstance()->_operationLayer->_touchMoveTrigger == TOUCH_MOVE_DIRECTION_LEFT)
#endif			
			{
				_moveTrigger = CHARACTER_DIRECTION_LEFT;
				OperationManager::getInstance()->_operationLayer->resetTouchMove();
			}
			else 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			if(InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_RIGHT_ARROW] == (int)InputManager::KeyState::JUST_PRESSED\
				|| OperationManager::getInstance()->_operationLayer->_touchMoveTrigger == TOUCH_MOVE_DIRECTION_RIGHT)
#else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if(OperationManager::getInstance()->_operationLayer->_touchMoveTrigger == TOUCH_MOVE_DIRECTION_RIGHT)
#endif					
			{
				_moveTrigger = CHARACTER_DIRECTION_RIGHT;
				OperationManager::getInstance()->_operationLayer->resetTouchMove();
			}
			else{

			}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			if ((InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_SPACE] >= (int)InputManager::KeyState::JUST_PRESSED\
				|| OperationManager::getInstance()->_speedUpBtn->_pressed == true)\
				&& _energy >= HAMSTER_RUN_CONSUMED_ENERGY)
#else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if (OperationManager::getInstance()->_speedUpBtn->_pressed == true\
				&& _energy >= HAMSTER_RUN_CONSUMED_ENERGY)
#endif
			{
				_runTrigger = true;
			}
			/*else{
				_runTrigger = false;
			}*/
		}
		else if (_controlType == (int)ControlType::COMPUTER){
			updateAI();
		}
	}


	//判断是否可以接受左右移动角色的输入信号
	if (!isMoving() \
		&& GameManager::getInstance()->_gameState == (int)GameManager::GameState::IN_THE_GAME \
		&& _state != (int)State::WIN\
		&& _state != (int)State::LOSE\
		&& _state != (int)State::PAUSE\
		&& _finish != true)
	{
		switch (_moveTrigger){
		case CHARACTER_DIRECTION_LEFT:
			

			if (_runTrigger == true\
				&& _energy >= HAMSTER_RUN_CONSUMED_ENERGY)
			{
				

				if (moveLeft() == true){
					_energy -= HAMSTER_RUN_CONSUMED_ENERGY;
					_state = (int)State::RUN;
					_moveSpeed = HAMSTER_RUN_MOVE_SPEED;
				}
			}
			else{
				if (moveLeft() == true){
					_state = (int)State::WALK;
					_moveSpeed = HAMSTER_WALK_MOVE_SPEED;
				}
			}
			
			break;
		case CHARACTER_DIRECTION_RIGHT:
			

			if (_runTrigger == true\
				&& _energy >= HAMSTER_RUN_CONSUMED_ENERGY)
			{
				
				if (moveRight() == true){
					_energy -= HAMSTER_RUN_CONSUMED_ENERGY;
					_state = (int)State::RUN;
					_moveSpeed = HAMSTER_RUN_MOVE_SPEED;
				}
			}
			else{
				if (moveRight() == true){
					_state = (int)State::WALK;
					_moveSpeed = HAMSTER_WALK_MOVE_SPEED;
				}
			}
			
			break;
		default:
			if (_runTrigger == true\
				&& _energy >= HAMSTER_RUN_CONSUMED_ENERGY)
			{
				

				if (moveDown() == true){
					_energy -= HAMSTER_RUN_CONSUMED_ENERGY;
					_state = (int)State::RUN;
					_moveSpeed = HAMSTER_RUN_MOVE_SPEED;
				}
			}
			else{
				if (moveDown() == true){
					_state = (int)State::WALK;
					_moveSpeed = HAMSTER_WALK_MOVE_SPEED;
				}
			}
			break;

		}
		_moveTrigger = 0;
		_runTrigger = 0;
	}

	if (isMoving())
	{
		updateMove();
	
	}
	//若本帧不作任何移动
	else
	{
		if (_state == (int)State::WALK\
			|| _state == (int)State::RUN)
		{
			_state=(int)State::STOP;
		}
	}

	updateFrame();
}

void Hamster::updateFrame(){

	String * animationIdKeyStrPrefix = nullptr;
	switch (_state){
	case (int)State::STOP:
		animationIdKeyStrPrefix = String::create("stop_");
		break;
	case (int)State::WALK:
		animationIdKeyStrPrefix = String::create("walk_");
		break;
	case (int)State::RUN:
		animationIdKeyStrPrefix = String::create("run_");
		break;
	case (int)State::WIN:
		animationIdKeyStrPrefix = String::create("cheer_");
		_direction = CHARACTER_DIRECTION_DOWN;
		break;
	case (int)State::LOSE:
		animationIdKeyStrPrefix = String::create("cry_");
		_direction = CHARACTER_DIRECTION_DOWN;
		break;
	case (int)State::PAUSE:
		animationIdKeyStrPrefix = String::create("stop_");
		_direction = CHARACTER_DIRECTION_DOWN;
		break;
	}

	String * animationIdKeyStrSuffix = nullptr;
	switch (_direction){
	case CHARACTER_DIRECTION_DOWN:
		animationIdKeyStrSuffix = String::create("down");
		break;
	case CHARACTER_DIRECTION_LEFT:
		animationIdKeyStrSuffix = String::create("left");
		break;
	case CHARACTER_DIRECTION_RIGHT:
		animationIdKeyStrSuffix = String::create("right");
		break;
	case CHARACTER_DIRECTION_UP:
		animationIdKeyStrSuffix = String::create("up");
		break;
	}

	String * animationIdKeyStr = String::createWithFormat("%s%s", animationIdKeyStrPrefix->getCString(), animationIdKeyStrSuffix->getCString());
	
	if (_currentAnimationId != _animationsId[std::string(animationIdKeyStr->getCString())])
	{
		setCurrentFrame(_animationsId[std::string(animationIdKeyStr->getCString())], 0);
	}
	else
	{
		if (_animationDurationSequences[_currentAnimationId][_currentAnimationIndex] == -1){
			//此帧乃永久帧
		}
		else if (++_animationCounter >= _animationDurationSequences[_currentAnimationId][_currentAnimationIndex])
		{
			//重置角色行走动画换帧计时器
			_animationCounter = 0;

			//到达循环动画序列结尾
			if (_animationFrameSequences[_currentAnimationId][_currentAnimationIndex + 1] == -1)
			{
				_currentAnimationIndex = 0;
			}
			//到达非循环动画序列结尾
			else if (_animationFrameSequences[_currentAnimationId][_currentAnimationIndex + 1] == -2)
			{
				switch (_state)
				{
				case (int)State::WIN:
					_state = (int)State::PAUSE;
					break;
				}

			}
			//进入动画序列下一帧
			else{
				_currentAnimationIndex++;
			}

		}

		_currentFrameIndex = _animationFrameSequences[_currentAnimationId][_currentAnimationIndex];
		setAnchorPoint(Point(_framesAnchorPoint[_currentFrameIndex]));
		_currentFrame = _frames[_currentFrameIndex];

		if (_currentFrame != nullptr)
			setSpriteFrame(_currentFrame);
	}

}

void Hamster::updateAI(){
	if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::GUIDE_MODE \
		&& GameManager::getInstance()->_guidePhase != 1 && GameManager::getInstance()->_guidePhase != 8){
		return;
	}

	//if (!isMoving()){
	if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
			
	}
	else if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){
		_moveTrigger = CHARACTER_DIRECTION_LEFT;
	}
	else if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT))
	{
		_moveTrigger = CHARACTER_DIRECTION_RIGHT;
	}
	//}

	if (_energy >= _runTriggerEnergy){
		_runTrigger = true;
	}
	if (_energy < HAMSTER_RUN_CONSUMED_ENERGY){

		_runTrigger = false;
		_runTriggerEnergy = (1 + rand() % 10)*HAMSTER_RUN_CONSUMED_ENERGY;
	}

	
	if (100+rand()%100 < _reactionTime + _reactivity){
		_reactionTime = 0;
		if (rand() % 100 < (50 + _intellegence)){
			_energy += QuestionManager::getInstance()->_currentQuestionReward;
		}
		else{
			_energy -= QuestionManager::getInstance()->_currentQuestionErrorPunishment;
		}
	}
	else{
		_reactionTime++;
	}
	
	
	
}
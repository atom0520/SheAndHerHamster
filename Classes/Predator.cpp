#include "Predator.h"
#include "DataManager.h"
#include "CharacterManager.h"
#include "GameManager.h"
#include "MapManager.h"

Predator::Predator(){

}

Predator::~Predator(){
	unloadAllAnimations();
	unloadAllFrames();
}

bool Predator::init(){
	if (!Character::init()){
		return false;
	}

	_state = (int)State::STOP;
	_type = (int)Type::PREDATOR;
	_vision = 3;

	return true;
}

Predator*  Predator::create(int id, int x, int y){
	Predator * hamster = Predator::create();
	if (hamster == nullptr){
		return nullptr;
	}
	hamster->_id = id;
	hamster->setPosition(Point(x, y));
	hamster->_destPosition = Point(x, y);

	hamster->loadAllFrames();
	hamster->loadAllAnimations();
	hamster->updateFrame();

	return hamster;
}

void  Predator::loadFramesFromDataFile(const char *framesDataKey){
	ValueMap framesData = DataManager::getInstance()->_staticData\
		.at("character").asValueMap()\
		.at("predator").asValueMap()\
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

void  Predator::loadAllFrames(){
	loadFramesFromDataFile("stop_down");
	loadFramesFromDataFile("stop_left");
	loadFramesFromDataFile("stop_right");
	loadFramesFromDataFile("stop_up");
	loadFramesFromDataFile("walk_down");
	loadFramesFromDataFile("walk_left");
	loadFramesFromDataFile("walk_right");
	loadFramesFromDataFile("walk_up");
}

void Predator::loadAnimationFromDataFile(const char* animationDataKey){
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

void  Predator::loadAllAnimations(){
	loadAnimationFromDataFile("stop_down");
	loadAnimationFromDataFile("stop_left");
	loadAnimationFromDataFile("stop_right");
	loadAnimationFromDataFile("stop_up");
	loadAnimationFromDataFile("walk_down");
	loadAnimationFromDataFile("walk_left");
	loadAnimationFromDataFile("walk_right");
	loadAnimationFromDataFile("walk_up");
}

void Predator::update(){
	this->setZOrder(MapManager::getInstance()->_mapHeight - this->getPositionY());

	updateAI();

	if (!isMoving() \
		&& GameManager::getInstance()->_gameState == (int)GameManager::GameState::IN_THE_GAME)
	{

		switch (_moveTrigger){
		case CHARACTER_DIRECTION_DOWN:
			if (moveDown() == true){
				_state = (int)State::WALK;
				_moveSpeed = PREDATOR_WALK_MOVE_SPEED;
			}	
			break;
		case CHARACTER_DIRECTION_LEFT:
			if (moveLeft() == true){
				_state = (int)State::WALK;
				_moveSpeed = PREDATOR_WALK_MOVE_SPEED;
			}
			break;
		case CHARACTER_DIRECTION_RIGHT:			
			if (moveRight() == true){
				_state = (int)State::WALK;
				_moveSpeed = PREDATOR_WALK_MOVE_SPEED;
			}			
			break;
		case CHARACTER_DIRECTION_UP:
			if (moveUp() == true){
				_state = (int)State::WALK;
				_moveSpeed = PREDATOR_WALK_MOVE_SPEED;
			}
			break;
		default:
			break;
		}
	}

	if (isMoving())
	{
		updateMove();

	}
	//若本帧不作任何移动
	else
	{
		if (_state == (int)State::WALK)
		{
			_state = (int)State::STOP;
		}
	}

	updateFrame();
}

void Predator::updateFrame(){

	String * animationIdKeyStrPrefix = nullptr;
	switch (_state){
	case (int)State::STOP:
		animationIdKeyStrPrefix = String::create("stop_");
		break;
	case (int)State::WALK:
		animationIdKeyStrPrefix = String::create("walk_");
		break;
	case (int)State::PAUSE:
		animationIdKeyStrPrefix = String::create("stop_");
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

void Predator::updateAI(){
	if (!isMoving()){
		_moveTrigger = 0;

		if (((Hamster *)CharacterManager::getInstance()->_player)->_caught == true \
			||GameManager::getInstance()->_caughtNum >=7){
			return;
		}
		Hamster * nearestSurvivedHamster = nullptr;
		int nearestDistanceSq=0;
		for (int i = 0 ;i < CharacterManager::getInstance()->_hamsters.size(); i++){
			if (CharacterManager::getInstance()->_hamsters.at(i) != nullptr\
				&& ((Hamster *)CharacterManager::getInstance()->_hamsters.at(i))->_caught == false\
				&&  CharacterManager::getInstance()->_hamsters.at(i)->_state != (int)Hamster::State::LOSE){
				int offTileX = (int)CharacterManager::getInstance()->_hamsters.at(i)->getPositionX() - (int)this->getPositionX();
				int offTileY = (int)CharacterManager::getInstance()->_hamsters.at(i)->getPositionY() - (int)this->getPositionY();
				if (nearestSurvivedHamster == nullptr){
					nearestSurvivedHamster = (Hamster *)CharacterManager::getInstance()->_hamsters.at(i);
					nearestDistanceSq = offTileX*offTileX + offTileY*offTileY;

				}
				else{
					if (offTileX*offTileX + offTileY*offTileY<nearestDistanceSq){
						nearestSurvivedHamster = (Hamster *)CharacterManager::getInstance()->_hamsters.at(i);
						nearestDistanceSq = offTileX*offTileX + offTileY*offTileY;
					}
					
					/*if (((Hamster *)CharacterManager::getInstance()->_hamsters.at(i))->_ranking \
	                    >nearestSurvivedHamster->_ranking){
						nearestSurvivedHamster = (Hamster *)CharacterManager::getInstance()->_hamsters.at(i);
					}*/
				}
			}
		}
		
		if (nearestSurvivedHamster != nullptr){
			if (nearestSurvivedHamster->_caught == false\
				&&  nearestSurvivedHamster->_state != (int)Hamster::State::LOSE)
			{
				int offTileX = (int)nearestSurvivedHamster->getPositionX() / 32 - (int)this->getPositionX() / 32;
				int offTileY = (int)nearestSurvivedHamster->getPositionY() / 32 - (int)this->getPositionY() / 32;

				if (offTileY > 0){
					if (offTileY <= _vision){
						if (offTileX<0){
							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){
								_moveTrigger = CHARACTER_DIRECTION_LEFT;
							}
						}
						else if (offTileX > 0){
							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT))
							{
								_moveTrigger = CHARACTER_DIRECTION_RIGHT;
							}
						}
						else if (offTileX == 0){
							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_UP))
							{
								_moveTrigger = CHARACTER_DIRECTION_UP;
							}
							else{
								turnUp();
								if (abs(nearestSurvivedHamster->getPositionY() - this->getPositionY()) <= 32){
									//MessageBox("Caught a hamster!", "test");
									nearestSurvivedHamster->_caught = true;
								}
							}
						}
					}
					else{
						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_UP))
						{
							_moveTrigger = CHARACTER_DIRECTION_UP;
						}
						else if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){
							_moveTrigger = CHARACTER_DIRECTION_LEFT;
						}
						else if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT)){
							_moveTrigger = CHARACTER_DIRECTION_RIGHT;
						}
					}

				}
				else if (offTileY < 0){
					if (-offTileY <= _vision){
						if (offTileX<0){
							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){
								_moveTrigger = CHARACTER_DIRECTION_LEFT;
							}
						}
						else if (offTileX > 0){
							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT))
							{
								_moveTrigger = CHARACTER_DIRECTION_RIGHT;
							}
						}
						else if (offTileX == 0){
							if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN))
							{
								_moveTrigger = CHARACTER_DIRECTION_DOWN;
							}
							else{
								turnDown();
								if (abs(nearestSurvivedHamster->getPositionY() - this->getPositionY()) <= 32){
									//MessageBox("Caught a hamster!", "test");
									nearestSurvivedHamster->_caught = true;
								}
							}
						}
					}
					else{
						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN))
						{
							_moveTrigger = CHARACTER_DIRECTION_DOWN;
						}
						else if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){
							_moveTrigger = CHARACTER_DIRECTION_LEFT;
						}
						else if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT)){
							_moveTrigger = CHARACTER_DIRECTION_RIGHT;
						}
					}
				}
				else if (offTileY == 0){
					if (offTileX<0){
						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){
							_moveTrigger = CHARACTER_DIRECTION_LEFT;
						}
						else{
							turnLeft();
							if (abs(nearestSurvivedHamster->getPositionX() - this->getPositionX()) <= 32){
								
								nearestSurvivedHamster->_caught = true;
							}
						}
					}
					else if (offTileX > 0){
						if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT))
						{
							_moveTrigger = CHARACTER_DIRECTION_RIGHT;
						}
						else{
							turnRight();
							if (abs(nearestSurvivedHamster->getPositionX() - this->getPositionX()) <= 32){

								nearestSurvivedHamster->_caught = true;
							}
						}
					}
					else if (offTileX == 0){
						//impossible
					}
				}
			}
		}
		
	}
}
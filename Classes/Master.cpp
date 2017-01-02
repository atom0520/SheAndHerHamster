#include "Master.h"
#include "DataManager.h"
#include "Hamster.h"
#include "MapManager.h"

Master::Master(){

}

Master::~Master(){
	unloadAllAnimations();
	unloadAllFrames();
}

bool Master::init(){
	if (!Character::init()){
		return false;
	}	
	_type = (int)Type::MASTER;

	_state = (int)State::STOP;
	_direction = CHARACTER_DIRECTION_DOWN;
	
	_hamster = nullptr;
	_reactionTime = 0;
	return true;
}

Master * Master::create(int id, Hamster * hamster, int x, int y){
	Master * master = Master::create();
	if (master == nullptr){
		return nullptr;
	}
	master->_id = id;
	master->_hamster = hamster;
	master->setPosition(Point(x, y));
	master->_destPosition = Point(x, y);

	master->loadAllFrames();
	master->loadAllAnimations();
	master->updateFrame();

	return master;
}

void Master::loadFramesFromDataFile(const char *framesDataKey)
{
	ValueMap framesData = DataManager::getInstance()->_staticData\
		.at("character").asValueMap()\
		.at("master").asValueMap()\
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

void Master::loadAllFrames()
{
	loadFramesFromDataFile("stop_down");
	loadFramesFromDataFile("stop_left");
	loadFramesFromDataFile("stop_right");
	loadFramesFromDataFile("stop_up");
	loadFramesFromDataFile("walk_down");
	loadFramesFromDataFile("walk_left");
	loadFramesFromDataFile("walk_right");
	loadFramesFromDataFile("walk_up");
}

void Master::loadAnimationFromDataFile(const char* animationDataKey)
{
	ValueMap framesData = DataManager::getInstance()->_staticData\
		.at("character").asValueMap()\
		.at("master").asValueMap()\
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

void Master::loadAllAnimations()
{
	loadAnimationFromDataFile("stop_down");
	loadAnimationFromDataFile("stop_left");
	loadAnimationFromDataFile("stop_right");
	loadAnimationFromDataFile("stop_up");
	loadAnimationFromDataFile("walk_down");
	loadAnimationFromDataFile("walk_left");
	loadAnimationFromDataFile("walk_right");
	loadAnimationFromDataFile("walk_up");
}

void Master::update()
{
	this->setZOrder(MapManager::getInstance()->_mapHeight - this->getPositionY());
	updateAI();
	//判断是否可以接受左右移动角色的输入信号
	if (!isMoving())
	{		
		if (_moveTrigger==CHARACTER_DIRECTION_DOWN){
			_moveTrigger = 0;
			_state = (int)State::WALK;
			this->_moveSpeed = _hamster->_moveSpeed;
			moveDown();
				
		}
		else if (_moveTrigger == CHARACTER_DIRECTION_LEFT){
			_moveTrigger = 0;
			_state = (int)State::WALK;
			this->_moveSpeed = _hamster->_moveSpeed;
			moveLeft();
		}
		else if (_moveTrigger == CHARACTER_DIRECTION_RIGHT){
			_moveTrigger = 0;
			_state = (int)State::WALK;
			this->_moveSpeed = _hamster->_moveSpeed;
			moveRight();
		}
		else if (_moveTrigger == CHARACTER_DIRECTION_UP){
			_moveTrigger = 0;
			_state = (int)State::WALK;
			this->_moveSpeed = _hamster->_moveSpeed;
			moveUp();
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

//bool Master::canMove(int posX, int  posY, int direction){
//	bool canMove = true;
//	if (Character::canMove(posX, posY, direction) == false){
//		canMove = false;
//		return canMove;
//	}
//
//	int newDestTileX, newDestTileY;
//	switch (direction){
//	case CHARACTER_DIRECTION_DOWN:
//		newDestTileX = posX / 32;
//		newDestTileY = posY / 32 - 1;
//		break;
//	case CHARACTER_DIRECTION_LEFT:
//		newDestTileX = posX / 32 - 1;
//		newDestTileY = posY / 32;
//		break;
//	case CHARACTER_DIRECTION_RIGHT:
//		newDestTileX = posX / 32 + 1;
//		newDestTileY = posY / 32;
//		break;
//	case CHARACTER_DIRECTION_UP:
//		newDestTileX = posX / 32;
//		newDestTileY = posY / 32 + 1;
//		break;
//	}
//
//	if ()
//}

void Master::updateFrame()
{
	String * animationIdKeyStrPrefix = nullptr;
	switch (_state){
	case (int)State::STOP:
		animationIdKeyStrPrefix = String::create("stop_");
		break;
	case (int)State::WALK:
		animationIdKeyStrPrefix = String::create("walk_");
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

void Master::updateAI()
{
	int offTileX = (int)_hamster->getPositionX() / 32 - (int)this->getPositionX() / 32;
	int offTileY = (int)_hamster->getPositionY() / 32 - (int)this->getPositionY() / 32;
	if (!isMoving()){
		if (_hamster != nullptr){
			
						
			if (abs(offTileY) > 0){
				if (offTileY < 0){
					//turnDown();

					if (_reactionTime >= MASTER_REACTION_TIME){
						_moveTrigger = CHARACTER_DIRECTION_DOWN;
					}
					else{
						_reactionTime ++;
					}
				
				}
				else if (offTileY > 0){
					//turnUp();
					if (_reactionTime >= MASTER_REACTION_TIME){
						_moveTrigger = CHARACTER_DIRECTION_UP;
					}
					else{
						_reactionTime++;
					}
				}
				/*else if (offTileY == -1 && abs(offTileX) != 0){

					if (_reactionTime >= MASTER_REACTION_TIME){
						_moveTrigger = CHARACTER_DIRECTION_DOWN;
					}
					else{
						_reactionTime++;
					}
				}
				else if (offTileY == 1 && abs(offTileX) != 0){
					if (_reactionTime >= MASTER_REACTION_TIME){
						_moveTrigger = CHARACTER_DIRECTION_UP;
					}
					else{
						_reactionTime++;
					}
				}				
				else if (abs(offTileY) == 1 && abs(offTileX) == 0){
					_moveTrigger = 0;
					_reactionTime = 0;
				}*/
			}
			else //if(abs(offTileX)>0)
			{
				if (offTileX < 0 && canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT))
				{
						_moveTrigger = CHARACTER_DIRECTION_LEFT;
					
				}
				else if (offTileX > 0 && canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT))
				{
						_moveTrigger = CHARACTER_DIRECTION_RIGHT;
					
				}
				else{
					_moveTrigger = 0;
					_reactionTime = 0;
				}
				
				/*if (offTileX > 0){
					turnRight();

					if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT)){
						if (_reactionTime >= MASTER_REACTION_TIME){
							_moveTrigger = CHARACTER_DIRECTION_RIGHT;
						}
						else{
							_reactionTime++;
						}
						
					}
					else{
						_moveTrigger = 0;
						_reactionTime = 0;
					}
				}
				else if (offTileX < 0){
					turnLeft();

					if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){
						if (_reactionTime >= MASTER_REACTION_TIME){
							_moveTrigger = CHARACTER_DIRECTION_LEFT;
						}
						else{
							_reactionTime++;
						}
					}
					else{
						_moveTrigger = 0;
						_reactionTime = 0;
					}
				}			*/
			}		
		}		
	}
	if (abs(offTileY) > 0){
		if (offTileY < 0){
			turnDown();
		}
		else if (offTileY > 0){
			turnUp();
		}
	}
	else if (abs(offTileX) > 0){
		if (offTileX < 0){
			turnLeft();
		}
		else if (offTileX > 0){
			turnRight();
		}
	}

}
#include "Character.h"
#include "MapManager.h"
#include "CharacterManager.h"
#include "Master.h"

Character::Character(){

}

Character::~Character(){
	unloadAllAnimations();
	unloadAllFrames();
}

bool Character::init(){
	if (!Sprite::init()){
		return false;
	}
	_id = 0;
	_state = 0;
	_type = (int)Type::HAMSTER;
	_direction = CHARACTER_DIRECTION_DOWN;

	_currentAnimationId = 0;
	_currentAnimationIndex = 0;
	_animationCounter = 0;

	_currentFrameIndex = 0;
	_currentFrame = nullptr;

	_moveSpeed = 4;
	_destPosition = Point(0, 0);

	_moveTrigger = 0;
	return true;
}

Character * Character::create(int x, int y){
	Character * gameObject = Character::create();
	if (!gameObject){
		return nullptr;
	}
	gameObject->setPosition(Point(x, y));
	gameObject->_destPosition = Point(x, y);

	return gameObject;

}


void Character::turnDown(){
	if (_direction != CHARACTER_DIRECTION_DOWN){
		_direction = CHARACTER_DIRECTION_DOWN;
	}
}

void Character::turnLeft(){

	if (_direction != CHARACTER_DIRECTION_LEFT){
		
		_direction = CHARACTER_DIRECTION_LEFT;
	}
}

void Character::turnRight(){
	if (_direction != CHARACTER_DIRECTION_RIGHT){
		_direction = CHARACTER_DIRECTION_RIGHT;
	}
}

void Character::turnUp(){
	if (_direction != CHARACTER_DIRECTION_UP){
		_direction = CHARACTER_DIRECTION_UP;
	}
}

bool Character::moveDown(bool isDirFixed){
	if (!isDirFixed)
	{
		turnDown();
	}


	if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_DOWN)){
		_destPosition.y -= 32;
		return true;
	}
	else{
		/*switch (_type){
		case (int)Type::HAMSTER:
			return false;
			break;
		case (int)Type::MASTER:
			_destPosition.y -= 32;
			do{
				if (moveDown() == true){
					break;
				}
			} while (1);
			break;
		}*/
		return false;
	}
}

bool Character::moveLeft(bool isDirFixed){
	
	if (!isDirFixed)
	{
		
		turnLeft();
	}


	if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_LEFT)){

		_destPosition.x -= 32;
		return true;
	}
	else{
		return false;
	}

}

bool Character::moveRight(bool isDirFixed){
	if (!isDirFixed)
	{
		turnRight();
	}


   	if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_RIGHT)){

		_destPosition.x += 32;
		return true;
	}
	else{
		return false;
	}
}

bool Character::moveUp(bool isDirFixed){
	if (!isDirFixed)
	{
		turnUp();
	}

	if (canMove(_destPosition.x, _destPosition.y, CHARACTER_DIRECTION_UP)){

		_destPosition.y += 32;
		return true;
	}
	else{
		/*switch (_type){
		case (int)Type::HAMSTER:
			return false;
			break;
		case (int)Type::MASTER:
			_destPosition.y += 32;
			do{
				if (moveUp() == true){
					break;
				}
			} while (1);
			break;
		}*/
		return false;
	}
}


bool Character::canMove(int posX, int posY, int direction)
{
	int newDestTileX, newDestTileY;
	bool canMove = true;

	switch (direction){
	case CHARACTER_DIRECTION_DOWN:
		newDestTileX = (int)posX / 32;
		newDestTileY = (int)posY / 32 - 1;
		break;
	case CHARACTER_DIRECTION_LEFT:
		newDestTileX = (int)posX / 32 - 1;
		newDestTileY = (int)posY / 32;
		break;
	case CHARACTER_DIRECTION_RIGHT:
		newDestTileX = (int)posX / 32 + 1;
		newDestTileY = (int)posY / 32;
		break;
	case CHARACTER_DIRECTION_UP:
		newDestTileX = (int)posX / 32;
		newDestTileY = (int)posY / 32 + 1;
		break;
	}

	switch (_type){
	case (int)Type::HAMSTER:
		if (newDestTileX < HAMSTER_TRACK_MIN_TILE_X || newDestTileX>HAMSTER_TRACK_MAX_TILE_X){
			canMove = false;
			return canMove;
		}
		if (newDestTileY < 0 || newDestTileY>(int)MapManager::getInstance()->_mapHeight / 32 - 1){
			canMove = false;
			return canMove;
		}

		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_hamsters.begin(); it != CharacterManager::getInstance()->_hamsters.end();){
			if ((*it) != nullptr){
				if (this != (*it)){
					int charDestTileX = (*it)->_destPosition.x / 32;
					int charDestTileY = (*it)->_destPosition.y / 32;
					if (newDestTileX == charDestTileX && newDestTileY == charDestTileY){
						canMove = false;	
						
					}
				}
			}
			if (canMove == false){
				return false;
			}
			it++;
		}

		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_predators.begin();\
			it != CharacterManager::getInstance()->_predators.end();){
			if ((*it) != nullptr){
				int charDestTileX = (*it)->_destPosition.x / 32;
				int charDestTileY = (*it)->_destPosition.y / 32;
				if (newDestTileX == charDestTileX && newDestTileY == charDestTileY){
					canMove = false;

				}
			}
			if (canMove == false){
				return false;
			}
			it++;
		}

		break;
	case (int)Type::MASTER:
		//MessageBox(Value(_destPosition.x / 32).asString().c_str(), "1");

		if ((int)_destPosition.x / 32 <= MASTER_LEFT_TRACK_TILE_X){
		
			if (newDestTileX > MASTER_LEFT_TRACK_TILE_X){
				
				canMove = false;
				return canMove;
			}
		}
		else if ((int)_destPosition.x / 32 >= MASTER_RIGHT_TRACK_TILE_X){
			if (newDestTileX < MASTER_RIGHT_TRACK_TILE_X){
				canMove = false;
				return canMove;
			}
		}
		
		if (newDestTileY < 0 || newDestTileY>MapManager::getInstance()->_mapHeight / 32 - 1){
			canMove = false;
			return canMove;
		}
	
		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_masters.begin(); it != CharacterManager::getInstance()->_masters.end();){
			if ((*it) != nullptr){
				if (this != (*it)){
					int charDestTileX = (*it)->_destPosition.x / 32;
					int charDestTileY = (*it)->_destPosition.y / 32;
					if (newDestTileX == charDestTileX && newDestTileY == charDestTileY){
						switch (_direction){
						case CHARACTER_DIRECTION_DOWN:
							if (((Master*)this)->_hamster->getPositionY() >= \
								((Master*)(*it))->_hamster->getPositionY()){
								canMove = false;
							}
							break;
						case CHARACTER_DIRECTION_LEFT:

						case CHARACTER_DIRECTION_RIGHT:
							canMove = false;
							break;
						case CHARACTER_DIRECTION_UP:
							if (((Master*)this)->_hamster->getPositionY() <= \
								((Master*)(*it))->_hamster->getPositionY()){
								canMove = false;
							}
							break;
						}

					}
				}
			}
			if (canMove == false){
				return false;
			}
			it++;
		}

		break;
	case (int)Type::PREDATOR:
		if (newDestTileX < HAMSTER_TRACK_MIN_TILE_X || newDestTileX>HAMSTER_TRACK_MAX_TILE_X){
			canMove = false;
			return canMove;
		}
		if (newDestTileY < 0 || newDestTileY>(int)MapManager::getInstance()->_mapHeight / 32 - 1){
			canMove = false;
			return canMove;
		}

		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_hamsters.begin(); it != CharacterManager::getInstance()->_hamsters.end();){
			if ((*it) != nullptr){
					int charDestTileX = (*it)->_destPosition.x / 32;
					int charDestTileY = (*it)->_destPosition.y / 32;
					if (newDestTileX == charDestTileX && newDestTileY == charDestTileY){
						canMove = false;

					}
			}
			if (canMove == false){
				return false;
			}
			it++;
		}

		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_predators.begin(); \
			it != CharacterManager::getInstance()->_predators.end();){
			if ((*it) != nullptr && (*it) != this){
				int charDestTileX = (*it)->_destPosition.x / 32;
				int charDestTileY = (*it)->_destPosition.y / 32;
				if (newDestTileX == charDestTileX && newDestTileY == charDestTileY){
					canMove = false;

				}
			}
			if (canMove == false){
				return false;
			}
			it++;
		}

		break;
	default:
		if (newDestTileX < 0 || newDestTileX>MapManager::getInstance()->_mapWidth / 32 - 1){
			canMove = false;
			return canMove;
		}
		if (newDestTileY < 0 || newDestTileY>MapManager::getInstance()->_mapHeight / 32 - 1){
			canMove = false;
			return canMove;
		}
		break;
	}

	



	return canMove;

}

void Character::turnToward(Character* aim){
	int offX = aim->getPositionX() - this->getPositionX();
	int offY = aim->getPositionY() - this->getPositionY();
	if (abs(offY) >= abs(offX)){
		if (offY < 0){
			turnDown();
		}
		else if (offY > 0){
			turnUp();
		}
	}
	else{
		if (offX < 0){
			turnLeft();
		}
		else if (offX > 0){
			turnRight();
		}
	}
}

void Character::turnAwayFrom(Character* aim){

}

void Character::moveToward(Character* aim, bool isDirFixed){
	//int aimPosX = aim->getPositionX();
	//MessageBox(Value(aimPosX).asString().c_str(), "test");
	int offX = aim->getPositionX() - this->getPositionX();
	int offY = aim->getPositionY() - this->getPositionY();
	if (abs(offY) >= abs(offX)){
		if (offY < 0){
			moveDown(isDirFixed);
		}
		else if (offY > 0){
			moveUp(isDirFixed);
		}
	}
	else{
		if (offX < 0){
			moveLeft(isDirFixed);
		}
		else if (offX > 0){
			moveRight(isDirFixed);
		}
	}
}

void Character::moveAwayFrom(Character* aim, bool isDirFixed){

}

void Character::loadFramesFromDataFile(const char *framesDataKey){

};

void Character::loadAllFrames(){
	MessageBox("loadAllAnimationFrames", "test!");
}

void Character::unloadAllFrames(){
	for (int frameIndex = 0; frameIndex < this->_frames.size(); frameIndex++)
	{
		if (this->_frames[frameIndex] != nullptr)
		{
			if (this->_frames[frameIndex]->getReferenceCount()>0)
				this->_frames[frameIndex]->release();
			this->_frames[frameIndex] = nullptr;
		}
	}
	/*for (std::map<int, SpriteFrame*>::iterator it = _frames.begin(); it != _frames.end();){
	if (it->second != nullptr){
	if (it->second->getReferenceCount()>0){
	it->second->release();
	it->second=nullptr;
	_frames.erase(it++);
	}
	}
	else{
	it++;
	}
	}*/
}

void Character::loadAnimationFromDataFile(const char* animationDataKey){

}

void Character::loadAllAnimations(){

}

void Character::unloadAllAnimations(){
	for (int animationIndex = 0; animationIndex < this->_animationFrameSequences.size(); animationIndex++)
	{
		if (this->_animationFrameSequences[animationIndex] != nullptr)
		{
			//free(this->_animationFrameSequences[animationIndex]);
			//用new开辟的空间应该用delete释放
			//delete不但能释放对象的空间，还会在释放前先自动调用对象的析构函数
			delete[] this->_animationFrameSequences[animationIndex];
			//释放后还要将原指针置为nullptr，以免遗留野指针（野指针将无法通过if(  !=nullptr)来判断是否开辟了空间）
			this->_animationFrameSequences[animationIndex] = nullptr;

		}
	}
	//for (std::map<int, int*>::iterator it = _animationFrameSequences.begin(); it != _animationFrameSequences.end();){
	//	if (it->second != nullptr){
	//		delete[] it->second;
	//	    it->second = nullptr;
	//		_animationFrameSequences.erase(it++);
	//	}
	//	else{
	//		it++;
	//	}
	//}
}

bool Character::setCurrentAnimationId(int animationId){
	if (this->_animationFrameSequences[animationId] != nullptr){
		this->_currentAnimationId = animationId;
		this->_currentAnimationIndex = 0;
		this->_animationCounter = 0;
		return true;
	}
	else{
		return false;
	}
}

bool Character::setCurrentFrame(int animationId, int animationIndex){
	int frameIndex = this->_animationFrameSequences[animationId][animationIndex];
	if (this->_frames[frameIndex] != nullptr){
		this->_currentFrameIndex = frameIndex;
		this->_currentFrame = this->_frames[frameIndex];
		this->_currentAnimationId = animationId;
		this->_currentAnimationIndex = animationIndex;
		this->_animationCounter = 0;

		setSpriteFrame(this->_currentFrame);
		
		setAnchorPoint(Point(_framesAnchorPoint[_currentFrameIndex]));
		/*if (hpbar_visible){
		hpbar->setPosition(sprite->getAnchorPointInPoints().x + HPBAR_OFFSET_X,
		sprite->getAnchorPointInPoints().y + HPBAR_OFFSET_Y);
		}*/

		return true;
	}
	else{
		return false;
	}
}

void Character::update(){

}

void Character::updateFrame(){

}

void Character::updateMove(){
	int oldPositionX = getPositionX();
	if (_destPosition.x > oldPositionX + _moveSpeed){
		setPositionX(oldPositionX + _moveSpeed);
	}
	else if (_destPosition.x < oldPositionX - _moveSpeed){
		setPositionX(oldPositionX - _moveSpeed);
	}
	else{
		setPositionX(_destPosition.x);
	}

	int oldPositionY = getPositionY();
	if (_destPosition.y > oldPositionY + _moveSpeed){
		setPositionY(oldPositionY + _moveSpeed);
	}
	else if (_destPosition.y < oldPositionY - _moveSpeed){
		setPositionY(oldPositionY - _moveSpeed);
	}
	else{
		setPositionY(_destPosition.y);
	}

}

bool Character::isMoving(){

	return (getPositionX() != _destPosition.x || getPositionY() != _destPosition.y);
}

void Character::updateAI(){

}

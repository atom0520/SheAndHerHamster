#include "GameEffect.h"
#include "DataManager.h"

GameEffect::GameEffect(){

}

GameEffect::~GameEffect(){
	unloadFrames();
	unloadAnimation();
}

bool GameEffect::init(){
	if (!Sprite::init()){
		return false;
	}
	_id = 0;
	_direction = GAME_EFFECT_DIRECTION_LEFT;

	_animationFrameSequence = nullptr;
	_animationDurationSequence = nullptr;

	_currentAnimationIndex = 0;
	_animationCounter = 0;

	_currentFrameIndex = 0;
	_currentFrame = nullptr;

	_needRemoved = false;
	_target = nullptr;
	return true;
}

void GameEffect::update(){
	
}

void GameEffect::updateFrame(){

}

void  GameEffect::loadFramesFromDataFile(){
	
}

void  GameEffect::loadFrames(){
	loadFramesFromDataFile();
}

void GameEffect::unloadFrames(){
	for (int frameIndex = 0; frameIndex < this->_frames.size(); frameIndex++)
	{
		if (this->_frames[frameIndex] != nullptr)
		{
			if (this->_frames[frameIndex]->getReferenceCount()>0){
				this->_frames[frameIndex]->release();
				this->_frames[frameIndex] = nullptr;
			}
		}
	}
	//for (std::map<int, SpriteFrame*>::iterator it = _frames.begin(); it != _frames.end();){
	//	if (it->second != nullptr){
	//		if (it->second->getReferenceCount()>0){
	//			it->second->release();
	//			it->second = nullptr;
	//			_frames.erase(it++);
	//		}			
	//	}
	//	else{
	//		it++;
	//	}
	//}
}

void  GameEffect::loadAnimationFromDataFile(){
}

void  GameEffect::loadAnimation(){
	loadAnimationFromDataFile();
}

void  GameEffect::unloadAnimation(){

	if (this->_animationFrameSequence != nullptr)
	{
		//free(this->_animationFrameSequences[animationIndex]);
		//用new开辟的空间应该用delete释放
		//delete不但能释放对象的空间，还会在释放前先自动调用对象的析构函数
		delete[] this->_animationFrameSequence;
		//释放后还要将原指针置为nullptr，以免遗留野指针（野指针将无法通过if(  !=nullptr)来判断是否开辟了空间）
		this->_animationFrameSequence = nullptr;
	}
}

bool GameEffect::setCurrentFrame(int animationIndex){
	int frameIndex = this->_animationFrameSequence[animationIndex];
	if (this->_frames[frameIndex] != nullptr){
		this->_currentFrameIndex = frameIndex;
		this->_currentFrame = this->_frames[frameIndex];
		this->_currentAnimationIndex = animationIndex;
		this->_animationCounter = 0;

		setSpriteFrame(this->_currentFrame);
		setAnchorPoint(Point(_framesAnchorPoint));

		return true;
	}
	else{
		return false;
	}
}
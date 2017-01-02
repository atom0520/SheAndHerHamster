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
		//��new���ٵĿռ�Ӧ����delete�ͷ�
		//delete�������ͷŶ���Ŀռ䣬�������ͷ�ǰ���Զ����ö������������
		delete[] this->_animationFrameSequence;
		//�ͷź�Ҫ��ԭָ����Ϊnullptr����������Ұָ�루Ұָ�뽫�޷�ͨ��if(  !=nullptr)���ж��Ƿ񿪱��˿ռ䣩
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
#include"GlobalEffect.h"
#include "DataManager.h"
#include "GameManager.h"
#include "GameEffectManager.h"
#include "CharacterManager.h"
#include "OperationManager.h"
#include "SimpleAudioEngine.h"
#include "Global.h"
using namespace CocosDenshion;

GlobalEffect::GlobalEffect(){

}

GlobalEffect::~GlobalEffect(){
	unloadFrames();
	unloadAnimation();
}

bool GlobalEffect::init(){
	if (!GameEffect::init()){
		return false;
	}
	_needRemoved = false;


	return true;
}

GlobalEffect* GlobalEffect::create(int id, int direction, int x, int  y){
	GlobalEffect * globalEffect = GlobalEffect::create();
	if (globalEffect == nullptr){
		return nullptr;
	}
	globalEffect->_id = id;

	globalEffect->_direction = direction;
	globalEffect->setPosition(Point(x, y));

	globalEffect->loadFrames();
	globalEffect->loadAnimation();
	globalEffect->updateFrame();

	

	return globalEffect;
}

void GlobalEffect::update(){
	if (_needRemoved){
		return;
	}

	

	updateFrame();
}

void GlobalEffect::updateFrame(){
	

	switch (_id){
	case 1:{
		if (_animationCounter == 0){
			switch (_currentAnimationIndex){
			case 0:
			case 1:
			case 2:{
						SimpleAudioEngine::getInstance()->playEffect(COUNTER_EFFECT_FILE_PATH);
			}break;
			case 3:{
						SimpleAudioEngine::getInstance()->playEffect(READY_GO_EFFECT_FILE_PATH);
			}break;
			}
		}
	}break;
	
	case 31:
	case 32:
	case 33:
	case 34:{
		if (_animationCounter == 0){
			switch (_currentAnimationIndex){
			case 0:{
						SimpleAudioEngine::getInstance()->playEffect(HORN_EFFECT_FILE_PATH);
						
			}break;
			}
		}
	}break;

	case 36:
	case 37:
	case 38:{
		if (_animationCounter == 0){
			switch (_currentAnimationIndex){
			case 0:{
						if (CharacterManager::getInstance()->_player != nullptr){
							switch (CharacterManager::getInstance()->_player->_id){
							case 1:
							case 2:
							case 7:
							case 8:{
									   switch (_id){
									   case 36:{
										   SimpleAudioEngine::getInstance()->playEffect(GOOD_FEMALE_EFFECT_FILE_PATH);
									   }break;
									   case 37:
									   {
											SimpleAudioEngine::getInstance()->playEffect(COOL_FEMALE_EFFECT_FILE_PATH);
									   }break;
									   case 38:
									   {
										    SimpleAudioEngine::getInstance()->playEffect(PERFECT_FEMALE_EFFECT_FILE_PATH);
									   }break;
									   }
										
							}break;
							case 3:
							case 4:
							case 5:
							case 6:{
									switch (_id){
									case 36:{
												SimpleAudioEngine::getInstance()->playEffect(GOOD_MALE_EFFECT_FILE_PATH);
									}break;
									case 37:
									{
												SimpleAudioEngine::getInstance()->playEffect(COOL_MALE_EFFECT_FILE_PATH);
									}break;
									case 38:
									{
												SimpleAudioEngine::getInstance()->playEffect(PERFECT_MALE_EFFECT_FILE_PATH);
									}break;
									}
							}break;
							}
						}

			}break;
			}
		}
	}break;
	case 84:{
		if (_currentAnimationIndex == 1){
			this->setPositionX(this->getPositionX() + 2);
		}
	}break;
	case 85:{
				if (_currentAnimationIndex == 0 && _animationCounter == 6){
					SimpleAudioEngine::getInstance()->playEffect(GOOD_FEMALE_EFFECT_FILE_PATH);
				}
				
	}break;
	}

	if (this->getAnchorPoint() != _framesAnchorPoint){
		this->setAnchorPoint(_framesAnchorPoint);
	}

	if (_animationDurationSequence[_currentAnimationIndex] == -1){
		//此帧乃永久帧
	}
	else if (++_animationCounter >= _animationDurationSequence[_currentAnimationIndex])
	{
		_animationCounter = 0;	

		//到达循环动画序列结尾
		if (_animationFrameSequence[_currentAnimationIndex + 1] == -1)
		{
			_currentAnimationIndex = 0;
			switch (_id){
			case 84:{
				this->setPositionX(Director::getInstance()->getWinSize().width/2);
			}break;
			}
		}
		//到达非循环动画序列结尾
		else if (_animationFrameSequence[_currentAnimationIndex + 1] == -2)
		{
			_needRemoved = true;
		}
		//进入动画序列下一帧
		else{
			_currentAnimationIndex++;
		}
	}

	_currentFrameIndex = _animationFrameSequence[_currentAnimationIndex];
	_currentFrame = _frames[_currentFrameIndex];

	if (_currentFrame != nullptr)
		setSpriteFrame(_currentFrame);
}

void  GlobalEffect::loadFramesFromDataFile(){
	ValueMap framesData = DataManager::getInstance()->_staticData\
		.at("game_effect").asValueMap()\
		.at("global_effect").asValueMap()\
		.at(Value(_id).asString().c_str()).asValueMap()\
		.at("frames").asValueMap();

	std::string spriteFrameNamePrefix = framesData.at("spriteframe_name_prefix").asString();
	int frameNum = framesData.at("frame_num").asInt();

	float frameAnchorPointX = framesData.at("frame_anchor_point_x").asFloat();
	float frameAnchorPointY = framesData.at("frame_anchor_point_y").asFloat();

	_framesAnchorPoint = Point(frameAnchorPointX, frameAnchorPointY);

	for (int index = 0; index < frameNum; index++)
	{
        auto spriteFrameName =String::createWithFormat("%s_%02d.png", spriteFrameNamePrefix.c_str(), index+1);
        
        this->_frames[index] = Sprite::createWithSpriteFrameName(spriteFrameName->getCString())->getSpriteFrame();
        
		this->_frames[index]->retain();
		/*this->_frames[index] = SpriteFrame::create(filename->getCString(), Rect(srcX, srcY, width, height));*/

	}
}

void  GlobalEffect::loadFrames(){
	loadFramesFromDataFile();
}

void  GlobalEffect::loadAnimationFromDataFile(){
	ValueMap framesData = DataManager::getInstance()->_staticData\
		.at("game_effect").asValueMap()\
		.at("global_effect").asValueMap()\
		.at(Value(_id).asString().c_str()).asValueMap()\
		.at("animation").asValueMap();

	int animationFrameNum = framesData.at("animation_frame_num").asInt();

	bool isAnimationLooping = framesData.at("loop").asBool();

	ValueMap animationFrameSequence = framesData.at("animation_frame_sequence").asValueMap();
	ValueMap animationDurationSequence = framesData.at("animation_duration_sequence").asValueMap();

	_animationFrameSequence = new int[animationFrameNum + 1];
	_animationDurationSequence = new int[animationFrameNum];

	for (int animationFrameIndex = 0; animationFrameIndex < animationFrameNum; animationFrameIndex++){
		_animationFrameSequence[animationFrameIndex] = animationFrameSequence[Value(animationFrameIndex).asString().c_str()].asInt();
		_animationDurationSequence[animationFrameIndex] = animationDurationSequence[Value(animationFrameIndex).asString().c_str()].asInt();
	}

	if (isAnimationLooping){
		_animationFrameSequence[animationFrameNum] = -1;//循环动画序列结尾标志
	}
	else{
		_animationFrameSequence[animationFrameNum] = -2;//非循环动画序列结尾标志
	}
}

void  GlobalEffect::loadAnimation(){
	loadAnimationFromDataFile();
}
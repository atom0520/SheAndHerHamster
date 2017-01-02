#ifndef GAME_EFFECT_H
#define GAME_EFFECT_H

#define GAME_EFFECT_DIRECTION_DOWN  1
#define GAME_EFFECT_DIRECTION_LEFT  2
#define GAME_EFFECT_DIRECTION_RIGHT 4
#define GAME_EFFECT_DIRECTION_UP  8

#include "Character.h"
#include "cocos2d.h"
USING_NS_CC;

class GameEffect : public Sprite
{
	
public:
	GameEffect();
	~GameEffect();
	CREATE_FUNC(GameEffect);
	virtual bool init();

	friend class GameEffectManager;

	virtual void update();
	virtual void updateFrame();

	virtual void loadFramesFromDataFile();
	virtual void loadFrames();
	virtual void unloadFrames();

	virtual void loadAnimationFromDataFile();
	virtual void loadAnimation();
	virtual void unloadAnimation();

	virtual bool setCurrentFrame(int animationIndex);
	bool _needRemoved;
	int _id;
protected:
	
	std::map<int, SpriteFrame *> _frames;
	Point _framesAnchorPoint;

	int _direction;
	

	int * _animationFrameSequence;
	int * _animationDurationSequence;
	int _currentAnimationIndex;
	int _animationCounter;

	int _currentFrameIndex;
	SpriteFrame * _currentFrame;

	Character * _target;
};

#endif
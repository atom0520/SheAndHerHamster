#ifndef GLOBAL_EFFECT_H
#define GLOBAL_EFFECT_H

#include"cocos2d.h"

using namespace cocos2d;
#include "GameEffect.h"

class GlobalEffect : public GameEffect
{
public:
	GlobalEffect();
	~GlobalEffect();
	CREATE_FUNC(GlobalEffect);
	virtual bool init();
	static GlobalEffect * create(int id, int direction, int x, int  y);
	
	virtual void update();
	virtual void updateFrame();

	virtual void loadFramesFromDataFile();
	virtual void loadFrames();
	virtual void loadAnimationFromDataFile();
	virtual void loadAnimation();
	
protected:

};

#endif
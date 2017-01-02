#ifndef PREDATOR_H
#define PREDATOR_H

#define PREDATOR_WALK_MOVE_SPEED 6

#include "Character.h"
#include "cocos2d.h"
using namespace cocos2d;

class Predator :public Character{
public:
	Predator();
	~Predator();
	CREATE_FUNC(Predator);
	virtual bool init();
	static Predator * create(int id, int x, int y);

	virtual void loadFramesFromDataFile(const char *framesDataKey);
	virtual void loadAllFrames();

	virtual void loadAnimationFromDataFile(const char* animationDataKey);
	virtual void loadAllAnimations();

	virtual void update();
	virtual void updateFrame();
	virtual void updateAI();

	enum class State{
		STOP,
		WALK,
		PAUSE,
	};

protected:
	int _vision;
};

#endif

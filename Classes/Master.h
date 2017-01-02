#ifndef MASTER_H
#define MASTER_H

#define MASTER_REACTION_TIME 16
#define MASTER_LEFT_TRACK_TILE_X  7
#define MASTER_RIGHT_TRACK_TILE_X 12

#include "Character.h"
#include "cocos2d.h"
using namespace cocos2d;

class Hamster;
class Master : public Character
{
public:
	Master();
	~Master();
	CREATE_FUNC(Master);
	virtual bool init();
    static Master * create(int id, Hamster * hamster, int x, int y);

	virtual void loadFramesFromDataFile(const char *framesDataKey);
	virtual void loadAllFrames();

	virtual void loadAnimationFromDataFile(const char* animationDataKey);
	virtual void loadAllAnimations();
	virtual void update();
	virtual void updateFrame();
	virtual void updateAI();
	//virtual bool canMove(int posX, int  posY, int direction);

	enum class State{
		STOP,
		WALK,
	};
	Hamster * _hamster;
protected:
	
	
	int _reactionTime;
};

#endif

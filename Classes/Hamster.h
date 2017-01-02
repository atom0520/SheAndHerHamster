#ifndef HAMSTER_H
#define HAMSTER_H

#define HAMSTER_RUN_CONSUMED_ENERGY 5
#define HAMSTER_RUN_MOVE_SPEED 8
#define HAMSTER_WALK_MOVE_SPEED 4
#define HAMSTER_TRACK_MIN_TILE_X  8
#define HAMSTER_TRACK_MAX_TILE_X  11

#include "Character.h"
#include "cocos2d.h"
using namespace cocos2d;

class Master;
class Hamster :public Character{
public:
	Hamster();
	~Hamster();
	CREATE_FUNC(Hamster);
	virtual bool init();
	static Hamster * create(int id, int controlType, int x, int y);

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
		RUN,
		WIN,
		LOSE,
		PAUSE,
	};

	enum class ControlType{
		PLAYER,
		COMPUTER,
	};

	Master * _master;

	int _energy;
	int _maxEnergy;
	int _ranking;
	bool _finish;
	bool _caught;
	bool _runTrigger;

protected:
	
	int _controlType;
	
	int _runTriggerEnergy;
	int _intellegence;
	int _reactivity;
	int _reactionTime;
	
};

#endif

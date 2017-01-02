#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "cocos2d.h"
USING_NS_CC;

class GameLayer :public Layer
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	
	void onEnter();
	void onExit();
	
	void update(float dt);

	void addPlayer();
	void addOpponentHamsters();
	void addMasters();
	void addPredators();
private:

	static long old_clock_count;

};

#endif
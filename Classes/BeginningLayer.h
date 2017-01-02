#ifndef BEGINNING_LAYER_H
#define BEGINNING_LAYER_H

#include "cocos2d.h"

USING_NS_CC;

class BeginningLayer : public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BeginningLayer);
	virtual bool init();

	void onEnter();
	void onExit();
	void update(float dt);
	int _counter;
};

#endif // GAME_SCENE_H
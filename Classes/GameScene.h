#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
};

#endif // GAME_SCENE_H

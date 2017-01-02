#ifndef HAMSTER_SEL_SCENE_H
#define HAMSTER_SEL_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class HamsterSelScene : public Scene
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
};

#endif // HAMSTER_SEL_SCENE_H
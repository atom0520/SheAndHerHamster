#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public Scene
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
};

#endif // TITLE_SCENE_H
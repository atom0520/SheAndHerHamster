#ifndef MAP_LAYER_H
#define MAP_LAYER_H

#include "cocos2d.h"
using namespace cocos2d;

class MapLayer :public Layer
{
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	virtual bool init();
	void update(float dt);

private:

};

#endif
#ifndef HUD_LAYER_H
#define HUD_LAYER_H
#include "cocos2d.h"
using namespace cocos2d;

class HUDLayer :public Layer
{
public:
	HUDLayer();
	~HUDLayer();
	CREATE_FUNC(HUDLayer);
	virtual bool init();

	void update(float dt);

protected:
	
};

#endif
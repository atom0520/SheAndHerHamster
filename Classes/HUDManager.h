#ifndef HUD_MANAGER_H
#define HUD_MANAGER_H

#include "Progress.h"
#include "cocos2d.h"
USING_NS_CC;

//游戏“抬头显示”信息管理类
class HUDManager : public Ref{
public:
	static HUDManager * getInstance();
	static void destroyInstance();
	virtual bool init();
	virtual void update();
	virtual void displayFinishHamster(int hamsterId);
	virtual void displayHamsterHeads();
	virtual void updateHamsterHeads();

	Layer * _hudLayer;
	Progress * _energyProgress;
	Sprite * _rankingNumSprite;
	SpriteFrame * _rankingNumSpriteFrames[8];
	Sprite * _rankingNote;
	Sprite *_displayedHamsterNote;
	std::vector<Sprite *> _displayedHamsterSprites;

protected:
	static HUDManager * _instance;
};

#endif
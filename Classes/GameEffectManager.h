#ifndef GAME_EFFECT_MANAGER_H
#define GAME_EFFECT_MANAGER_H

#define HEAD_NOTICE_EFFECT_POS_Y  (Director::getInstance()->getWinSize().height - 160)


#include "GameEffect.h"
#include "cocos2d.h"
USING_NS_CC;

//游戏特效类的管理类
class GameEffectManager : public Ref{
public:
	static GameEffectManager * getInstance();
	static void destroyInstance();
	virtual bool init();
	virtual void update();

	std::vector<GameEffect*> _gameEffects;
	std::vector<GameEffect*> _needAddedEffects;
	Layer * _glEffectLayer;

protected:
	static GameEffectManager * _instance;
};

#endif
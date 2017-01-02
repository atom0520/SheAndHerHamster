#ifndef MODE_SEL_LAYER_H
#define MODE_SEL_LAYER_H

#include "GameEffect.h"
#include "cocos2d.h"
using namespace cocos2d;

class ModeSelLayer :public Layer
{
public:
	ModeSelLayer();
	~ModeSelLayer();
	CREATE_FUNC(ModeSelLayer);
	virtual bool init();
	void update(float dt);

	void onEnter();
	void onExit();
	void menuCallBack(Ref* pSender);
	
	//GameEffect * _selectRect;

	//GameEffect * _DD;

	int _selectIndex;
	
	bool _isSelectFixed;

	int _replaceSceneWait;

protected:

	static long old_clock_count;

	Sprite *_fg;
	Sprite * _bg;
	Sprite * _modeNotes[4];
	MenuItemImage * _toLeftBtn;
	MenuItemImage * _toRightBtn;

	MenuItemImage * _okBtn;
	//MenuItemImage * _instructionBtn;
	int _modeShowCounter;
	

	std::vector<GameEffect*> _modeShowEffects[4];
	std::vector<GameEffect*> _audienceEffects;
};

#endif

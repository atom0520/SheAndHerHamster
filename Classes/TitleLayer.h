#ifndef TITLE_LAYER_H
#define TITLE_LAYER_H

#include "cocos2d.h"
using namespace cocos2d;

class TitleLayer :public Layer
{
public:
	TitleLayer();
	~TitleLayer();
	CREATE_FUNC(TitleLayer);
	virtual bool init();
	void onEnter();

	void menuCallback(Ref*pSender);
protected:

};

#endif
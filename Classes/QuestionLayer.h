#ifndef QUESTION_LAYER_H
#define QUESTION_LAYER_H

#include "cocos2d.h"
using namespace cocos2d;

class QuestionLayer :public Layer
{
public:
	QuestionLayer();
	~QuestionLayer();
	CREATE_FUNC(QuestionLayer);
	virtual bool init();
	void update(float dt);

	
	
private:

};

#endif
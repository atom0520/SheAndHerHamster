#ifndef PROGRESS_H
#define PROGRESS_H

#include "cocos2d.h"
USING_NS_CC;

class Progress : public Node
{
public:
	Progress();
	~Progress();

	virtual bool init();
	CREATE_FUNC(Progress);
	static Progress * create(ProgressTimerType type,const char * bgFilename, const char * fillFilename);

	void setFill(ProgressTimer * timer){ this->_fill = timer; };
	void setPercentage(float percentage){ _fill->setPercentage(percentage); };
	float getPercentage(){ return _fill->getPercentage(); };

	
	Sprite * _bg;
protected:
	ProgressTimer * _fill;

};

#endif
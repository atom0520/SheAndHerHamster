#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

class TimeManager : public Ref{
public:
	static TimeManager * getInstance();
	static void destroyInstance();

	virtual bool init();
	long getCurrentTimeInMillisecond();
protected:
	static TimeManager * _instance;
};

#endif
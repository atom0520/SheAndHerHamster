#include "TimeManager.h"

//ÉùÃ÷¾²Ì¬±äÁ¿
TimeManager * TimeManager::_instance = nullptr;

TimeManager * TimeManager::getInstance(){
	if (_instance == nullptr){
		_instance = new TimeManager();
		_instance->init();
	}
	return _instance;
}

void TimeManager::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

bool  TimeManager::init(){
	
	return true;
}

long TimeManager::getCurrentTimeInMillisecond(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec/1000;
}
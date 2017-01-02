#include "Progress.h"

Progress::Progress(){

}

Progress::~Progress(){

}

bool Progress::init()
{
	_fill = nullptr;
	_bg = nullptr;
	return true;
}

Progress * Progress::create(ProgressTimerType type,const char * bgFilename, const char * fillFilename)
{
	Progress * progress =Progress::create();
	if (progress == nullptr){
		return nullptr;
	}
	
	progress->_bg = Sprite::create(bgFilename);
	progress->addChild(progress->_bg, 1);
	progress->_bg->setPosition(progress->getContentSize() / 2);

	progress->_fill = ProgressTimer::create(Sprite::create(fillFilename));
	progress->addChild(progress->_fill, 2);
	progress->_fill->setPosition(progress->getContentSize() / 2);

	//设置渐变条类型
	progress->_fill->setType(type);
	
	//设置起点
	if (type == ProgressTimerType::RADIAL){
		progress->_fill->setMidpoint(Point(0.5, 0.5));
		progress->_fill->setReverseProgress(true);
	}

	//设置初始百分比
	progress->_fill->setPercentage(0);

	return progress;
	
}
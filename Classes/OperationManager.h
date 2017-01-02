#ifndef OPERATION_MANAGER_H
#define OPERATION_MANAGER_H

//#include "JoyStick.h"
#include "CustomButton.h"
#include "cocos2d.h"
#include "OperationLayer.h"
USING_NS_CC;

class OperationManager : public Ref{
public:

	static OperationManager * getInstance();
	static void destroyInstance();
	virtual bool init();

	virtual void update();
	void optionBtnCallBack(Ref *pSender);

	OperationLayer * _operationLayer;
	//JoyStick * _joyStick;
	CustomButton * _speedUpBtn;
	MenuItemImage * _pauseBtn;
	MenuItemImage * _zBtn;
	MenuItemImage * _xBtn;
	MenuItemImage * _cBtn;

protected:
	static OperationManager * _instance;
};

#endif
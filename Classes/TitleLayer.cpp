#include "TitleLayer.h"
#include "ModeSelScene.h"
#include "HamsterSelScene.h"

#include "GameManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

TitleLayer::TitleLayer()
{

}

TitleLayer::~TitleLayer()
{

}

bool TitleLayer::init()
{
	if (!Layer::init()){
		return false;		
	}

	Sprite * bg = Sprite::create("title/title_bg.png");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	this->addChild(bg, 1);

	Menu * titleMenu = Menu::create();

	MenuItemImage * startMenuItem = MenuItemImage::create("title/start_0.png", \
		"title/start_1.png", \
		CC_CALLBACK_1(TitleLayer::menuCallback, this));
	titleMenu->addChild(startMenuItem,1);
	startMenuItem->setScale(0.6);
	startMenuItem->setAnchorPoint(Point(0, 0));
	startMenuItem->setPosition(Point(200, 200));
	startMenuItem->setTag(0);

	MenuItemImage * exitMenuItem = MenuItemImage::create("title/exit_0.png", \
		"title/exit_1.png", \
		CC_CALLBACK_1(TitleLayer::menuCallback, this));
	titleMenu->addChild(exitMenuItem, 1);
	exitMenuItem->setScale(0.6);
	exitMenuItem->setAnchorPoint(Point(0, 0));
	exitMenuItem->setPosition(Point(startMenuItem->getPositionX(), startMenuItem->getPositionY()-50));
	exitMenuItem->setTag(1);

	this->addChild(titleMenu, 1);
	titleMenu->setPosition(Point(0, 0));

	return true;
}

void  TitleLayer::onEnter(){
	Layer::onEnter();

	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/title.wav", true);
	}
	else{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/title.wav", true);
	}
}

void TitleLayer::menuCallback(Ref*pSender){
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");

	switch (((MenuItemImage*)pSender)->getTag()){
	case 0:{

		auto newScene = ModeSelScene::createScene();

		//auto transition = TransitionFadeDown::create(0.5, newScene);
		auto transition = TransitionFade::create(0.5, newScene);
        //auto transition = TransitionPageTurn::create(0.5, newScene,true);
		CCLOG("replaceScene(ModeSelScene::createScene())");
        
		Director::getInstance()->replaceScene(transition);
	}	
		break;
	case 1:{
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
					   MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
					   return;
		#endif			
					   Director::getInstance()->end();

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
					   exit(0);
		#endif
	}
		break;
	}
}

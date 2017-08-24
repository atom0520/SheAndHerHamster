#include "EndPopupLayer.h"
#include "GlobalEffect.h"
#include "GameEffectManager.h"
#include "GameManager.h"
#include "CharacterManager.h"
#include "MapManager.h"
#include "HUDManager.h"
#include "OperationManager.h"
#include "QuestionManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "Global.h"

using namespace CocosDenshion;

EndPopupLayer::EndPopupLayer(){

}

EndPopupLayer::~EndPopupLayer(){

}


bool EndPopupLayer::init(){
	if (!Layer::init()){
		return false;
	}
	setSwallowTouchListener();

	auto winSize = Director::getInstance()->getWinSize();

	auto endBg = Sprite::create("end_popup_layer/end_bg.png");

	endBg->setAnchorPoint(Point(0, 0));

	this->addChild(endBg , 1);

	auto popupMenu = Menu::create();

	auto restartMenuItem = MenuItemImage::create("pause_popup_layer/restart_0.png", \
		"pause_popup_layer/restart_1.png", \
		CC_CALLBACK_1(EndPopupLayer::menuCallback, this));

	restartMenuItem->setAnchorPoint(Point(0.5, 0.5));
	restartMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2 -80));
	restartMenuItem->setTag(1);
	popupMenu->addChild(restartMenuItem, 2);

	auto returnMenuItem = MenuItemImage::create("pause_popup_layer/return_0.png", \
		"pause_popup_layer/return_1.png", \
		CC_CALLBACK_1(EndPopupLayer::menuCallback, this));

	returnMenuItem->setAnchorPoint(Point(0.5, 0.5));
	returnMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2 - 144));
	returnMenuItem->setTag(2);
	popupMenu->addChild(returnMenuItem, 2);

	this->addChild(popupMenu, 2);
	popupMenu->setPosition(Point(0, 0));

	return true;
}

void EndPopupLayer::menuCallback(Ref *pSender){
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");

	switch (((MenuItemImage*)pSender)->getTag()){
	case 1:{
			   int originalSelHamsterId = GameManager::getInstance()->_playerSelHamsterId;
			   int originalSelGameMode = GameManager::getInstance()->_gameMode;
			   GameManager::getInstance()->destroyInstance();
			   CharacterManager::getInstance()->destroyInstance();
			   MapManager::getInstance()->destroyInstance();
			   GameEffectManager::getInstance()->destroyInstance();
			   HUDManager::getInstance()->destroyInstance();
			   OperationManager::getInstance()->destroyInstance();
			   QuestionManager::getInstance()->destroyInstance();

			   GameManager::getInstance()->_playerSelHamsterId = originalSelHamsterId;
			   GameManager::getInstance()->_gameMode = originalSelGameMode;

			   auto newScene = GameScene::createScene();

			   auto sceneTransition = TransitionFadeDown::create(0.5, newScene);
			   Director::getInstance()->replaceScene(sceneTransition);
			   // this->removeFromParentAndCleanup(true);

	}
		break;
	case 2:{
			   GameManager::getInstance()->destroyInstance();
			   CharacterManager::getInstance()->destroyInstance();
			   MapManager::getInstance()->destroyInstance();
			   GameEffectManager::getInstance()->destroyInstance();
			   HUDManager::getInstance()->destroyInstance();
			   OperationManager::getInstance()->destroyInstance();
			   QuestionManager::getInstance()->destroyInstance();

			   auto newScene = TitleScene::createScene();
			   auto transition = TransitionFadeDown::create(0.5, newScene);
			   Director::getInstance()->replaceScene(transition);

			   //  this->removeFromParentAndCleanup(true);


	}
		break;
	}
}

EndPopupLayer * EndPopupLayer::create(int type){
	auto popupLayer = EndPopupLayer::create();
	if (popupLayer == nullptr){
		return nullptr;
	}
	popupLayer->_type = type;

	auto winSize = Director::getInstance()->getWinSize();

	
	switch (type){
	case (int)Type::END_RANKING_WIN:{
		auto endRankingNote = Sprite::create("end_popup_layer/end_ranking_note.png");
		popupLayer->addChild(endRankingNote, 1);
		endRankingNote->setAnchorPoint(Point(0.5, 0.5));
		endRankingNote->setPosition(Point(winSize.width / 2, winSize.height - 192 - 48));

		auto rankingNumSprite = Sprite::create(String::createWithFormat("end_popup_layer/%d.png", ((Hamster*)CharacterManager::getInstance()->_player)->_ranking)->getCString());
		popupLayer->addChild(rankingNumSprite, 1);
		rankingNumSprite->setAnchorPoint(Point(0.5, 0.5));
		rankingNumSprite->setPosition(Point(winSize.width / 2 + 50, endRankingNote->getPositionY()));

		GameEffect * winEffect = GlobalEffect::create(2, \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			Director::getInstance()->getWinSize().height - 192);

		if (winEffect != nullptr){
			popupLayer->addChild(winEffect, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(winEffect);
		}

		GameEffect * cheerHamster = GlobalEffect::create(4 + 2 * (CharacterManager::getInstance()->_player->_id - 1), \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			winEffect->getPositionY() - 128);

		if (cheerHamster != nullptr){
			popupLayer->addChild(cheerHamster, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(cheerHamster);
		}


		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect(WIN_EFFECT_FILE_PATH);
		}
		else{
			SimpleAudioEngine::getInstance()->playEffect(WIN_EFFECT_FILE_PATH);
		}
	}break;
	case (int)Type::END_RANKING_LOSE:{
		auto endRankingNote = Sprite::create("end_popup_layer/end_ranking_note.png");
		popupLayer->addChild(endRankingNote, 1);
		endRankingNote->setAnchorPoint(Point(0.5, 0.5));
		endRankingNote->setPosition(Point(winSize.width / 2, winSize.height - 192 - 48));

		auto rankingNumSprite = Sprite::create(String::createWithFormat("end_popup_layer/%d.png", ((Hamster*)CharacterManager::getInstance()->_player)->_ranking)->getCString());
		popupLayer->addChild(rankingNumSprite, 1);
		rankingNumSprite->setAnchorPoint(Point(0.5, 0.5));
		rankingNumSprite->setPosition(Point(winSize.width / 2 + 50, endRankingNote->getPositionY()));

		GameEffect * loseEffect = GlobalEffect::create(3, \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			Director::getInstance()->getWinSize().height - 192);

		if (loseEffect != nullptr){
			popupLayer->addChild(loseEffect, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(loseEffect);
		}

		GameEffect * cryingHamster = GlobalEffect::create(5 + 2 * (CharacterManager::getInstance()->_player->_id - 1), \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			loseEffect->getPositionY() - 128);

		if (cryingHamster != nullptr){
			popupLayer->addChild(cryingHamster, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(cryingHamster);
		}

		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect(LOSE_EFFECT_FILE_PATH);
		}
		else{
			SimpleAudioEngine::getInstance()->playEffect(LOSE_EFFECT_FILE_PATH);
		}
	}break;
	case (int)Type::END_CAUGHT:{
		auto endRankingNote = Sprite::create("end_popup_layer/end_caught_note.png");
		popupLayer->addChild(endRankingNote, 1);
		endRankingNote->setAnchorPoint(Point(0.5, 0.5));
		endRankingNote->setPosition(Point(winSize.width / 2, winSize.height - 192 - 48));

		/*auto rankingNumSprite = Sprite::create(String::createWithFormat("end_popup_layer/%d.png", ((Hamster*)CharacterManager::getInstance()->_player)->_ranking)->getCString());
		popupLayer->addChild(rankingNumSprite, 1);
		rankingNumSprite->setAnchorPoint(Point(0.5, 0.5));
		rankingNumSprite->setPosition(Point(winSize.width / 2 + 50, endRankingNote->getPositionY()));*/

		GameEffect * loseEffect = GlobalEffect::create(3, \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			Director::getInstance()->getWinSize().height - 192);

		if (loseEffect != nullptr){
			popupLayer->addChild(loseEffect, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(loseEffect);
		}

		GameEffect * cryingHamster = GlobalEffect::create(5 + 2 * (CharacterManager::getInstance()->_player->_id - 1), \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			loseEffect->getPositionY() - 128);

		if (cryingHamster != nullptr){
			popupLayer->addChild(cryingHamster, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(cryingHamster);
		}

		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect(LOSE_EFFECT_FILE_PATH);
		}
		else{
			SimpleAudioEngine::getInstance()->playEffect(LOSE_EFFECT_FILE_PATH);
		}
	}break;
	case (int)Type::END_SURVIVED:{
		auto endRankingNote = Sprite::create("end_popup_layer/end_survived_note.png");
		popupLayer->addChild(endRankingNote, 1);
		endRankingNote->setAnchorPoint(Point(0.5, 0.5));
		endRankingNote->setPosition(Point(winSize.width / 2, winSize.height - 192 - 48));

		GameEffect * winEffect = GlobalEffect::create(2, \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			Director::getInstance()->getWinSize().height - 192);

		if (winEffect != nullptr){
			popupLayer->addChild(winEffect, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(winEffect);
		}

		GameEffect * cheerHamster = GlobalEffect::create(4 + 2 * (CharacterManager::getInstance()->_player->_id - 1), \
			GAME_EFFECT_DIRECTION_DOWN, \
			Director::getInstance()->getWinSize().width / 2, \
			winEffect->getPositionY() - 128);

		if (cheerHamster != nullptr){
			popupLayer->addChild(cheerHamster, 1);
			GameEffectManager::getInstance()->_gameEffects.push_back(cheerHamster);
		}


		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect(WIN_EFFECT_FILE_PATH);
		}
		else{
			SimpleAudioEngine::getInstance()->playEffect(WIN_EFFECT_FILE_PATH);
		}
	}break;
	}
	
	return popupLayer;
}

void EndPopupLayer::onExit(){
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listener);
}

void EndPopupLayer::setSwallowTouchListener()
{
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		return true;
	};
	_listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}
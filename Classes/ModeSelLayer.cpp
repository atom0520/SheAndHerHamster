#include "ModeSelLayer.h"
#include "HamsterSelScene.h"
#include "GameScene.h"
#include "GlobalEffect.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "SimpleAudioEngine.h"
#include "Global.h"

using namespace CocosDenshion;

long ModeSelLayer::old_clock_count = 0;

ModeSelLayer::ModeSelLayer()
{

}

ModeSelLayer::~ModeSelLayer()
{
	for (std::vector<GameEffect*>::iterator it = _modeShowEffects[_selectIndex].begin(); it != _modeShowEffects[_selectIndex].end();){
		if ((*it) != nullptr){
			CC_SAFE_RELEASE_NULL(*it);
		}
		it++;
	}

	for (int i = 0; i < 3; ){
		if (_modeNotes[i] != nullptr){
			CC_SAFE_RELEASE_NULL(_modeNotes[i]);
		}
		i++;
	}
}

bool ModeSelLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	_selectIndex = 0;
	_isSelectFixed = false;
	_modeShowCounter = 0;

	auto winSize = Director::getInstance()->getWinSize();
	

	_fg = Sprite::create("mode_sel_layer/fg.png");
	_fg->setAnchorPoint(Point(0.5, 0));
	_fg->setPosition(Point(winSize.width/2, -32));
	this->addChild(_fg, 3);

	_bg = Sprite::create("mode_sel_layer/bg.png");
	_bg->setScale(1);
	_bg->setAnchorPoint(Point(0.5, 1));
	_bg->setPosition(Point(winSize.width / 2-160, winSize.height+144));
	
	this->addChild(_bg, 2);

	{
		_modeNotes[0] = Sprite::create("mode_sel_layer/mode_guide_note.png");
		_modeNotes[1] = Sprite::create("mode_sel_layer/mode_ranking_note.png");
		_modeNotes[2] = Sprite::create("mode_sel_layer/mode_elimination_note.png");
		_modeNotes[3] = Sprite::create("mode_sel_layer/mode_survival_note.png");
		for (int i = 0; i < 4; i++){
			_modeNotes[i]->retain();
			_modeNotes[i]->setPosition(winSize.width / 2, winSize.height - 96);
		}		

		this->addChild(_modeNotes[_selectIndex], 4);
	}

	
	auto btnMenu = Menu::create();

	_toLeftBtn = MenuItemImage::create("mode_sel_layer/toleft_btn_01.png", \
		"mode_sel_layer/toleft_btn_02.png", \
		"mode_sel_layer/toleft_btn_03.png", \
		CC_CALLBACK_1(ModeSelLayer::menuCallBack, this));
	_toLeftBtn->setTag(0);
	_toLeftBtn->setScale(0.8);
	_toLeftBtn->setPosition(winSize.width / 2 - _modeNotes[_selectIndex]->getContentSize().width / 2 - _toLeftBtn->getContentSize().width*0.8 / 2 - 16, \
		_modeNotes[_selectIndex]->getPositionY());
	btnMenu->addChild(_toLeftBtn, 2);

	_toLeftBtn->setEnabled(false);

	_toRightBtn = MenuItemImage::create("mode_sel_layer/toright_btn_01.png", \
		"mode_sel_layer/toright_btn_02.png", \
		"mode_sel_layer/toright_btn_03.png", \
		CC_CALLBACK_1(ModeSelLayer::menuCallBack, this));
	_toRightBtn->setTag(1);
	_toRightBtn->setScale(0.8);
	_toRightBtn->setPosition(winSize.width / 2 + _modeNotes[_selectIndex]->getContentSize().width / 2 + _toLeftBtn->getContentSize().width*0.8 / 2 + 16, \
		_modeNotes[_selectIndex]->getPositionY());
	btnMenu->addChild(_toRightBtn, 2);

	_okBtn = MenuItemImage::create("mode_sel_layer/ok_btn_01.png", \
		"mode_sel_layer/ok_btn_02.png", \
		"mode_sel_layer/ok_btn_03.png", \
		CC_CALLBACK_1(ModeSelLayer::menuCallBack, this));
	_okBtn->setTag(2);
	_okBtn->setScale(0.5);
	//_okBtn->setPosition(winSize.width / 2 - _okBtn->getContentSize().width*0.5/2 -4, 
	_okBtn->setPosition(winSize.width / 2,\
		_modeNotes[_selectIndex]->getPositionY() - _modeNotes[_selectIndex]->getContentSize().height / 2 - _okBtn->getContentSize().height*0.5 / 2 - 16);
	btnMenu->addChild(_okBtn, 2);

	/*_instructionBtn = MenuItemImage::create("mode_sel_layer/instruction_btn_01.png", \
		"mode_sel_layer/instruction_btn_02.png", \
		"mode_sel_layer/instruction_btn_03.png", \
		CC_CALLBACK_1(ModeSelLayer::menuCallBack, this));
	_instructionBtn->setScale(0.5);
	_instructionBtn->setPosition(winSize.width / 2 + _okBtn->getContentSize().width*0.5 / 2 +4, \
		_okBtn->getPositionY());
	_instructionBtn->setTag(3);
	btnMenu->addChild(_instructionBtn, 2);*/

	btnMenu->setPosition(0, 0);
	this->addChild(btnMenu,4);
	
	{
		GameEffect * stopRightHamster2 = GlobalEffect::create(69, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 7 * 32 - 16);
		stopRightHamster2->retain();
		stopRightHamster2->setTag(0);
		_modeShowEffects[0].push_back(stopRightHamster2);

		GameEffect * walkingRightHamster2 = GlobalEffect::create(22, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 7 * 32 - 16);
		walkingRightHamster2->retain();
		walkingRightHamster2->setTag(1);
		_modeShowEffects[0].push_back(walkingRightHamster2);

		GameEffect * stopLeftHamster2 = GlobalEffect::create(70, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 7 * 32 - 16);
		stopLeftHamster2->retain();
		stopLeftHamster2->setTag(2);
		_modeShowEffects[0].push_back(stopLeftHamster2);

		GameEffect * walkingLeftHamster2 = GlobalEffect::create(71, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 7 * 32 - 16);
		walkingLeftHamster2->retain();
		walkingLeftHamster2->setTag(3);
		_modeShowEffects[0].push_back(walkingLeftHamster2);
		
		GameEffect * guideCursor = GlobalEffect::create(72, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 7 * 32 - 16);
		guideCursor->retain();
		guideCursor->setTag(4);
		_modeShowEffects[0].push_back(guideCursor);
	}

	for (std::vector<GameEffect*>::iterator it = _modeShowEffects[0].begin(); it != _modeShowEffects[0].end();){
		
		if ((*it) != nullptr){
			   _fg->addChild(*it, 6);
			switch (((GameEffect *)*it)->getTag()){
			case 1:
			case 2:
			case 3:{
					   (*it)->setVisible(false);
			}break;
			
			}
			
		}
		it++;
	}

	{
		GameEffect * runningHamster1 = GlobalEffect::create(41, GAME_EFFECT_DIRECTION_DOWN, 6 * 32 - 16, 7 * 32 - 16);
		runningHamster1->retain();
		_modeShowEffects[1].push_back(runningHamster1);
		GameEffect * runningHamster2 = GlobalEffect::create(42, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 8 * 32 - 16);
		runningHamster2->retain();
		_modeShowEffects[1].push_back(runningHamster2);
		GameEffect * runningHamster3 = GlobalEffect::create(43, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 6 * 32 - 16);
		runningHamster3->retain();
		_modeShowEffects[1].push_back(runningHamster3);

	}

	{
		GameEffect * winningHamster1 = GlobalEffect::create(4, GAME_EFFECT_DIRECTION_DOWN, 8 * 32 - 16, 7 * 32 - 16);
		winningHamster1->retain();
		_modeShowEffects[2].push_back(winningHamster1);
		GameEffect * losingHamster2 = GlobalEffect::create(7, GAME_EFFECT_DIRECTION_DOWN, 6 * 32 - 16, 7 * 32 - 16);
		losingHamster2->retain();
		_modeShowEffects[2].push_back(losingHamster2);
	}

	{
		GameEffect * runningHamster1 = GlobalEffect::create(41, GAME_EFFECT_DIRECTION_DOWN, 6 * 32 - 16, 7 * 32 - 16);
		runningHamster1->retain();
		_modeShowEffects[3].push_back(runningHamster1);
		GameEffect * walkingPredator1 = GlobalEffect::create(44, GAME_EFFECT_DIRECTION_DOWN, 5 * 32 - 16, 7 * 32 - 16);
		walkingPredator1->retain();
		_modeShowEffects[3].push_back(walkingPredator1);
	}

	{
		for (int i = 1; i <= 8; i++){
			int posX, posY;
			if (i <= 2){
				posX = 6 * 32 - 16 - 32*(i-1);
				posY = 4 * 32 - 16;
			}
			else if (i <= 6){
				posX = 5 * 32 - 16 + 32 * (i - 3);
				posY = 3 * 32 - 16;
			}
			else if(i>=7){
				posX = 8 * 32 - 16 - 32 * (i - 7);
				posY = 4 * 32 - 16;
			}
			GameEffect * audience = GlobalEffect::create(45+(i-1), GAME_EFFECT_DIRECTION_DOWN, posX, posY);
			_fg->addChild(audience, 6+4-(posY+16)/32);
			_audienceEffects.push_back(audience);
		}

	}

	Sprite * blackWhiteLine = Sprite::create("mode_sel_layer/blackwhite_line_vertical.png");
	blackWhiteLine->setPosition(8 * 32 - 16, 7 * 32 - 16);
	_fg->addChild(blackWhiteLine, 5);
    
	return true;
}


void ModeSelLayer::onEnter(){
	Layer::onEnter();
	CCLOG("onEnter");

	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->playBackgroundMusic(MODE_SEL_SCENE_BGM_FILE_PATH, true);
	}
	else{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(MODE_SEL_SCENE_BGM_FILE_PATH, true);
	}

	this->schedule(schedule_selector(ModeSelLayer::update),0.03);
}
void ModeSelLayer::onExit(){
	Layer::onExit();
}

void ModeSelLayer::update(float dt){
	//while (TimeManager::getInstance()->getCurrentTimeInMillisecond() - old_clock_count < 30);
	//old_clock_count = TimeManager::getInstance()->getCurrentTimeInMillisecond();

	if (_isSelectFixed == false){
		switch (_selectIndex){
		case 0:{
				  
			if (_modeShowCounter >= 0 && _modeShowCounter <= 17){
			   _modeShowEffects[_selectIndex].at(4)->update();

			}
			else if (_modeShowCounter == 18){
				if (_modeShowEffects[_selectIndex].at(4)->_needRemoved == true){
					_modeShowEffects[_selectIndex].at(4)->setVisible(false);

					_modeShowEffects[_selectIndex].at(0)->setVisible(false);
					_modeShowEffects[_selectIndex].at(1)->setPositionX(_modeShowEffects[_selectIndex].at(3)->getPositionX());
					_modeShowEffects[_selectIndex].at(1)->setCurrentFrame(0);
					_modeShowEffects[_selectIndex].at(1)->setVisible(true);
				}
			}
			else if (_modeShowCounter >= 19 && _modeShowCounter <= 26){
				_modeShowEffects[_selectIndex].at(1)->setPositionX(_modeShowEffects[_selectIndex].at(1)->getPositionX() + 4);
				_modeShowEffects[_selectIndex].at(1)->update();
			}
			else if (_modeShowCounter == 27){

				_modeShowEffects[_selectIndex].at(1)->setVisible(false);
				_modeShowEffects[_selectIndex].at(0)->setPositionX(_modeShowEffects[_selectIndex].at(1)->getPositionX());
				_modeShowEffects[_selectIndex].at(0)->setVisible(true);

				_modeShowEffects[_selectIndex].at(4)->setPositionX(_modeShowEffects[_selectIndex].at(1)->getPositionX()+32);
				_modeShowEffects[_selectIndex].at(4)->setCurrentFrame(0);
				_modeShowEffects[_selectIndex].at(4)->_needRemoved = false;

				_modeShowEffects[_selectIndex].at(4)->setVisible(true);

			}
			else if (_modeShowCounter >= 28 && _modeShowCounter <= 45){
				_modeShowEffects[_selectIndex].at(4)->update();
			}
			else if (_modeShowCounter == 46){
				if (_modeShowEffects[_selectIndex].at(4)->_needRemoved == true){

					_modeShowEffects[_selectIndex].at(4)->setVisible(false);

					_modeShowEffects[_selectIndex].at(0)->setVisible(false);

					_modeShowEffects[_selectIndex].at(1)->setCurrentFrame(0);
					_modeShowEffects[_selectIndex].at(1)->setVisible(true);
				}
			}
			else if (_modeShowCounter >= 47 && _modeShowCounter <= 54){

				_modeShowEffects[_selectIndex].at(1)->setPositionX(_modeShowEffects[_selectIndex].at(1)->getPositionX() + 4);
				_modeShowEffects[_selectIndex].at(1)->update();
			}
			else if (_modeShowCounter == 55){

				_modeShowEffects[_selectIndex].at(1)->setVisible(false);
				_modeShowEffects[_selectIndex].at(0)->setPositionX(_modeShowEffects[_selectIndex].at(1)->getPositionX());
				_modeShowEffects[_selectIndex].at(0)->setVisible(true);

				_modeShowEffects[_selectIndex].at(4)->setPositionX(_modeShowEffects[_selectIndex].at(1)->getPositionX() - 32);
				_modeShowEffects[_selectIndex].at(4)->setCurrentFrame(0);
				_modeShowEffects[_selectIndex].at(4)->_needRemoved = false;
				_modeShowEffects[_selectIndex].at(4)->setVisible(true);

			}
			else if (_modeShowCounter >= 56 && _modeShowCounter <= 73){
				_modeShowEffects[_selectIndex].at(4)->update();
				if (_modeShowCounter == 63){

					_modeShowEffects[_selectIndex].at(0)->setVisible(false);
					_modeShowEffects[_selectIndex].at(2)->setPositionX(_modeShowEffects[_selectIndex].at(0)->getPositionX());

					_modeShowEffects[_selectIndex].at(2)->setVisible(true);

				}
			}
			else if (_modeShowCounter == 74){
				if (_modeShowEffects[_selectIndex].at(4)->_needRemoved == true){

					_modeShowEffects[_selectIndex].at(4)->setVisible(false);

					_modeShowEffects[_selectIndex].at(2)->setVisible(false);
					_modeShowEffects[_selectIndex].at(3)->setPositionX(_modeShowEffects[_selectIndex].at(2)->getPositionX());
					_modeShowEffects[_selectIndex].at(3)->setCurrentFrame(0);
					_modeShowEffects[_selectIndex].at(3)->setVisible(true);
				}
			}
			else if (_modeShowCounter >= 75 && _modeShowCounter <= 82){

				_modeShowEffects[_selectIndex].at(3)->setPositionX(_modeShowEffects[_selectIndex].at(3)->getPositionX() - 4);
				_modeShowEffects[_selectIndex].at(3)->update();
			}
			else if (_modeShowCounter == 83){

				_modeShowEffects[_selectIndex].at(3)->setVisible(false);
				_modeShowEffects[_selectIndex].at(2)->setPositionX(_modeShowEffects[_selectIndex].at(3)->getPositionX());
				_modeShowEffects[_selectIndex].at(2)->setVisible(true);

				_modeShowEffects[_selectIndex].at(4)->setPositionX(_modeShowEffects[_selectIndex].at(2)->getPositionX() - 32);
				_modeShowEffects[_selectIndex].at(4)->setCurrentFrame(0);
				_modeShowEffects[_selectIndex].at(4)->_needRemoved = false;
				_modeShowEffects[_selectIndex].at(4)->setVisible(true);

			}
			else if (_modeShowCounter >= 84 && _modeShowCounter <= 101){
				_modeShowEffects[_selectIndex].at(4)->update();
			}
			else if (_modeShowCounter == 102){
				if (_modeShowEffects[_selectIndex].at(4)->_needRemoved == true){

					_modeShowEffects[_selectIndex].at(4)->setVisible(false);

					_modeShowEffects[_selectIndex].at(2)->setVisible(false);
					_modeShowEffects[_selectIndex].at(3)->setCurrentFrame(0);
					_modeShowEffects[_selectIndex].at(3)->setVisible(true);

				}
			}
			else if (_modeShowCounter >= 103 && _modeShowCounter <= 110){
				_modeShowEffects[_selectIndex].at(3)->setPositionX(_modeShowEffects[_selectIndex].at(3)->getPositionX() - 4);
				_modeShowEffects[_selectIndex].at(3)->update();
			}
			else if (_modeShowCounter == 111){

				_modeShowEffects[_selectIndex].at(3)->setVisible(false);
				_modeShowEffects[_selectIndex].at(2)->setPositionX(_modeShowEffects[_selectIndex].at(3)->getPositionX());
				_modeShowEffects[_selectIndex].at(2)->setVisible(true);

				_modeShowEffects[_selectIndex].at(4)->setPositionX(_modeShowEffects[_selectIndex].at(2)->getPositionX() + 32);
				_modeShowEffects[_selectIndex].at(4)->setCurrentFrame(0);
				_modeShowEffects[_selectIndex].at(4)->_needRemoved = false;
				_modeShowEffects[_selectIndex].at(4)->setVisible(true);

			}
			else if (_modeShowCounter >= 112 && _modeShowCounter <= 129){
				_modeShowEffects[_selectIndex].at(4)->update();
				if (_modeShowCounter == 120){
					_modeShowEffects[_selectIndex].at(2)->setVisible(false);
					_modeShowEffects[_selectIndex].at(0)->setPositionX(_modeShowEffects[_selectIndex].at(3)->getPositionX());
					_modeShowEffects[_selectIndex].at(0)->setVisible(true);
				}
			}
			else if (_modeShowCounter ==130){
				_modeShowEffects[_selectIndex].at(4)->setVisible(false);

				_modeShowEffects[_selectIndex].at(0)->setVisible(false);
				_modeShowEffects[_selectIndex].at(1)->setPositionX(_modeShowEffects[_selectIndex].at(3)->getPositionX());
				_modeShowEffects[_selectIndex].at(1)->setCurrentFrame(0);
				_modeShowEffects[_selectIndex].at(1)->setVisible(true);
				_modeShowCounter = 18;
			}

			_modeShowCounter += 1;
		}break;
		case 1:
		case 2:
		case 3:{
			for (std::vector<GameEffect*>::iterator it = _modeShowEffects[_selectIndex].begin(); it != _modeShowEffects[_selectIndex].end();){
				if ((*it) != nullptr){
					(*it)->update();
				}
				it++;
			}
		}break;
		}
	}
	
	
}

void ModeSelLayer::menuCallBack(Ref* pSender){
	switch (((MenuItemImage*)pSender)->getTag()){
	case 0:{
		if (_selectIndex >= 1){
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
			_modeNotes[_selectIndex]->removeFromParentAndCleanup(false);
			for (std::vector<GameEffect*>::iterator it = _modeShowEffects[_selectIndex].begin(); it != _modeShowEffects[_selectIndex].end();){
				if ((*it) != nullptr){
					(*it)->removeFromParentAndCleanup(false);
				}
				it++;
			}
			_selectIndex--;
			this->addChild(_modeNotes[_selectIndex],4);

			for (std::vector<GameEffect*>::iterator it = _modeShowEffects[_selectIndex].begin(); it != _modeShowEffects[_selectIndex].end();){
				if ((*it) != nullptr){
					_fg->addChild(*it, 6);
				}
				it++;
			}

			switch (_selectIndex){
			case 0:{
				 _toLeftBtn->setEnabled(false);

			}break;
			case 1:
			case 2:
			{
				_toLeftBtn->setEnabled(true);
				_toRightBtn->setEnabled(true);
			}break;
			case 3:{
				 _toRightBtn->setEnabled(false);
			}break;
			}
		}
		
	}break;
	case 1:{
		if (_selectIndex <= 2){
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
			_modeNotes[_selectIndex]->removeFromParentAndCleanup(false);
			for (std::vector<GameEffect*>::iterator it = _modeShowEffects[_selectIndex].begin(); it != _modeShowEffects[_selectIndex].end();){
				if ((*it) != nullptr){
					(*it)->removeFromParentAndCleanup(false);
				}
				it++;
			}
			_selectIndex++;

			this->addChild(_modeNotes[_selectIndex],4);
			
			for (std::vector<GameEffect*>::iterator it = _modeShowEffects[_selectIndex].begin(); it != _modeShowEffects[_selectIndex].end();){
				if ((*it) != nullptr){
					_fg->addChild(*it, 6);
				}
				it++;
			}
			
			switch (_selectIndex){
			case 0:{
					   _toLeftBtn->setEnabled(false);

			}break;
			case 1:
			case 2:
			{
					   _toLeftBtn->setEnabled(true);
					   _toRightBtn->setEnabled(true);
			}break;
			case 3:{
					   _toRightBtn->setEnabled(false);
			}break;
			}			
		}
	}break;
	case 2:{
			SimpleAudioEngine::getInstance()->playEffect(SELECT_FIXED_EFFECT_FILE_PATH);
			_isSelectFixed = true;
			_toLeftBtn->setEnabled(false);
			_toRightBtn->setEnabled(false);
			_okBtn->setEnabled(false);
			//_instructionBtn->setEnabled(false);

			GameManager::getInstance()->_gameMode = (int)GameManager::GameMode::GUIDE_MODE+_selectIndex;

			this->unschedule(schedule_selector(ModeSelLayer::update));

			if (_selectIndex == 0){
				auto newScene = GameScene::createScene();
				//auto transition = TransitionFadeDown::create(0.5, newScene);
				auto transition = TransitionFade::create(0.5, newScene);
				Director::getInstance()->replaceScene(transition);
			}
			else{
				auto newScene = HamsterSelScene::createScene();
				//auto transition = TransitionFadeDown::create(0.5, newScene);
				auto transition = TransitionFade::create(0.5, newScene);
				Director::getInstance()->replaceScene(transition);
			}
			
	}break;
	case 3:{

	}break;
	}
}

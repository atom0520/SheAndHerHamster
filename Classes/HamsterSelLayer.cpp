#include "HamsterSelLayer.h"
#include "GlobalEffect.h"
#include "GameScene.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "InputManager.h"
#endif

long HamsterSelLayer::old_clock_count = 0;

HamsterSelLayer::HamsterSelLayer()
{

}

HamsterSelLayer::~HamsterSelLayer()
{

}

bool HamsterSelLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	_fg1 = Sprite::create("hamster_sel_layer/fg.png");
	_fg1->setAnchorPoint(Point(0, 0));
	_fg1->setPosition(Point(0, 0));
	this->addChild(_fg1, 2);
	_fg2 = Sprite::create("hamster_sel_layer/fg.png");
	_fg2->setAnchorPoint(Point(0, 0));
	_fg2->setPosition(Point(_fg1->getPositionX()+_fg1->getContentSize().width, 0));
	this->addChild(_fg2, 2);
	
	_bg = Sprite::create("hamster_sel_layer/bg.png");
	_bg->setAnchorPoint(Point(0, 0));
	_bg->setPosition(Point(-256, 0));
	this->addChild(_bg, 1);

	auto selectNoteSprite = Sprite::create("hamster_sel_layer/select_note.png");
	selectNoteSprite->setAnchorPoint(Point(0.5, 0));
	selectNoteSprite->setPosition(Point(winSize.width / 2, winSize.height - 72 - selectNoteSprite->getContentSize().height));
	this->addChild(selectNoteSprite, 3);
	

	for (int i = 0; i < 8;i++){
		_hamsterHeads[i] = Sprite::create(String::createWithFormat("character/hamster/%d/head/hamster_head.png", i+1)->getCString());
		_hamsterHeads[i]->setScale(1.2);
		_hamsterHeads[i]->setAnchorPoint(Point(0.5, 0.5));
		_hamsterHeads[i]->setPosition(Point(winSize.width / 2 + 16 / 2 - 2 * (_hamsterHeads[i]->getContentSize().width + 16) + (i % 4)* (_hamsterHeads[i]->getContentSize().width + 16) +  _hamsterHeads[i]->getContentSize().width/2, \
			416 + i / 4 * (_hamsterHeads[i]->getContentSize().height + 16)));
		
		this->addChild(_hamsterHeads[i], 2);
	}	
	
	_isSelectFixed = false;
	_selectIndex = 0;
	_selectRect = GlobalEffect::create(29, \
		GAME_EFFECT_DIRECTION_DOWN, \
		_hamsterHeads[_selectIndex]->getPositionX(), \
		_hamsterHeads[_selectIndex]->getPositionY());
	_selectRect->setScale(1.3);
	_selectRect->setAnchorPoint(_hamsterHeads[0]->getAnchorPoint());
	this->addChild(_selectRect, 3);

	
	//_selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());

	_selectedHamsterNameSprite = Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString());
	_selectedHamsterNameSprite->setPosition(Point(winSize.width / 2, winSize.height / 2 + 8));
	this->addChild(_selectedHamsterNameSprite, 4);

	auto menu = Menu::create();
	_okBtn = MenuItemImage::create("hamster_sel_layer/ok_btn_01.png", \
		"hamster_sel_layer/ok_btn_02.png", \
		"hamster_sel_layer/ok_btn_03.png", \
		CC_CALLBACK_1(HamsterSelLayer::menuCallBack, this));
	_okBtn->setScale(0.5);
	_okBtn->setTag(0);
	_okBtn->setAnchorPoint(Point(0.5, 0.5));
	//_okBtn->setPosition(winSize.width/2, winSize.height/2);
	_okBtn->setPosition(_selectedHamsterNameSprite->getPositionX(), \
		_selectedHamsterNameSprite->getPositionY() - _selectedHamsterNameSprite->getContentSize().height/ 2 - _okBtn->getContentSize().height*0.5 / 2 - 4);
	menu->addChild(_okBtn, 3);
	menu->setPosition(0, 0);
	this->addChild(menu, 3);

	_DD = GlobalEffect::create(20, \
		GAME_EFFECT_DIRECTION_DOWN, \
		Director::getInstance()->getWinSize().width / 2 - 64 -16, \
		4*32+16);

	this->addChild(_DD, 3);

	_hamster = GlobalEffect::create(21+_selectIndex, \
		GAME_EFFECT_DIRECTION_DOWN, \
		Director::getInstance()->getWinSize().width / 2+16, \
		2 * 32 + 16);

	this->addChild(_hamster, 3);
	/*if (winEffect != nullptr){
		popupLayer->addChild(winEffect, 1);
		GameEffectManager::getInstance()->_gameEffects.push_back(winEffect);
	}*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	_listenerTouch = EventListenerTouchOneByOne::create();
	_listenerTouch->onTouchBegan = CC_CALLBACK_2(HamsterSelLayer::onTouchBegan, this);
	_listenerTouch->onTouchMoved = CC_CALLBACK_2(HamsterSelLayer::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listenerTouch, this);
#endif
    

    
	return true;
}

void HamsterSelLayer::onEnter()
{
	Layer::onEnter();

	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/hamster_sel_scene.wav", true);
	}
	else{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/hamster_sel_scene.wav", true);
	}
	this->schedule(schedule_selector(HamsterSelLayer::update), 0.03);
}

void HamsterSelLayer::onExit(){
	Layer::onExit();
}

void HamsterSelLayer::update(float dt){

	/*while (TimeManager::getInstance()->getCurrentTimeInMillisecond() - old_clock_count < 30);
	old_clock_count = TimeManager::getInstance()->getCurrentTimeInMillisecond();*/

	  if (_isSelectFixed == false){
		  _fg1->setPositionX(_fg1->getPositionX() - 1);
		  _fg2->setPositionX(_fg2->getPositionX() - 1);
		  if (_fg1->getPositionX() < -_fg1->getContentSize().width){
			  _fg1->setPositionX(_fg2->getPositionX() + _fg2->getContentSize().width);
		  }
		  if (_fg2->getPositionX() < -_fg2->getContentSize().width){
			  _fg2->setPositionX(_fg1->getPositionX() + _fg1->getContentSize().width);
		  }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		  InputManager::getInstance()->update();

		  static int delay = 0;
		  if (delay>5){
			  if (InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_LEFT_MOUSE_BUTTON] >= (int)InputManager::KeyState::JUST_PRESSED){
				
				  for (int i = 0; i<8; i++)
				  {
					 
					  if (_hamsterHeads[i]->getBoundingBox().containsPoint(InputManager::getInstance()->_mousePosition)){
						  
						  if (_selectIndex != i){
							  SimpleAudioEngine::getInstance()->playEffect("sound/cursor.wav");
							  _selectIndex = i;
							  _selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());
							  _selectedHamsterNameSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString())->getSpriteFrame());

							  if (_hamster != nullptr){
								  if (_hamster->getReferenceCount() > 0){
									  _hamster->removeFromParent();
									  _hamster = nullptr;
								  }
							  }
							  _hamster = GlobalEffect::create(21 + _selectIndex, \
								  GAME_EFFECT_DIRECTION_DOWN, \
								  Director::getInstance()->getWinSize().width / 2 + 16, \
								  2 * 32 + 16);
							  this->addChild(_hamster, 3);
							  break;
						  }

					  }
				  }
			  }			  

			  if (InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_SPACE] >= (int)InputManager::KeyState::JUST_PRESSED){
				  
				  menuCallBack(_okBtn);

			  }

			  if (_isSelectFixed == false && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_LEFT_ARROW] >= (int)InputManager::KeyState::JUST_PRESSED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_RIGHT_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_DOWN_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_UP_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED){
				  
				  if (_selectIndex % 4>0){
					  delay = 0;
					  _selectIndex--;
					  SimpleAudioEngine::getInstance()->playEffect("sound/cursor.wav");
					  _selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());
					  _selectedHamsterNameSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString())->getSpriteFrame());
					  
					  if (_hamster != nullptr){
						  if (_hamster->getReferenceCount() > 0){
							  _hamster->removeFromParent();
							  _hamster = nullptr;
						  }
					  }
					  _hamster = GlobalEffect::create(21 + _selectIndex, \
						  GAME_EFFECT_DIRECTION_DOWN, \
						  Director::getInstance()->getWinSize().width / 2 + 16, \
						  2 * 32 + 16);
					  this->addChild(_hamster, 3);

				  }
			  }
			  else if (_isSelectFixed == false && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_RIGHT_ARROW] >= (int)InputManager::KeyState::JUST_PRESSED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_LEFT_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_DOWN_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_UP_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED){
				  if (_selectIndex % 4<3){
					  delay = 0;

					  _selectIndex++;
					  SimpleAudioEngine::getInstance()->playEffect("sound/cursor.wav");
					  _selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());
					  _selectedHamsterNameSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString())->getSpriteFrame());
				  
					  if (_hamster != nullptr){
						  if (_hamster->getReferenceCount() > 0){
							  _hamster->removeFromParent();
							  _hamster = nullptr;
						  }
					  }
					  _hamster = GlobalEffect::create(21 + _selectIndex, \
						  GAME_EFFECT_DIRECTION_DOWN, \
						  Director::getInstance()->getWinSize().width / 2 + 16, \
						  2 * 32 + 16);
					  this->addChild(_hamster, 3);
				  }
			  }
			  else if (_isSelectFixed == false && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_DOWN_ARROW] >= (int)InputManager::KeyState::JUST_PRESSED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_UP_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_LEFT_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_RIGHT_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED){
				  if (_selectIndex / 4 == 1){
					  delay = 0;
					  _selectIndex -= 4;
					  SimpleAudioEngine::getInstance()->playEffect("sound/cursor.wav");
					  _selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());
					  _selectedHamsterNameSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString())->getSpriteFrame());
				  
					  if (_hamster != nullptr){
						  if (_hamster->getReferenceCount() > 0){
							  _hamster->removeFromParent();
							  _hamster = nullptr;
						  }
					  }
					  _hamster = GlobalEffect::create(21 + _selectIndex, \
						  GAME_EFFECT_DIRECTION_DOWN, \
						  Director::getInstance()->getWinSize().width / 2 + 16, \
						  2 * 32 + 16);
					  this->addChild(_hamster, 3);
				  }
			  }
			  else if (_isSelectFixed == false && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_UP_ARROW] >= (int)InputManager::KeyState::JUST_PRESSED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_DOWN_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_LEFT_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED\
				  && InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_RIGHT_ARROW] <= (int)InputManager::KeyState::JUST_RELEASED){
				  if (_selectIndex / 4 == 0){
					  delay = 0;
					  _selectIndex += 4;
					  SimpleAudioEngine::getInstance()->playEffect("sound/cursor.wav");
					  _selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());
					  _selectedHamsterNameSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString())->getSpriteFrame());
				  
					  if (_hamster != nullptr){
						  if (_hamster->getReferenceCount() > 0){
							  _hamster->removeFromParent();
							  _hamster = nullptr;
						  }
					  }
					  _hamster = GlobalEffect::create(21 + _selectIndex, \
						  GAME_EFFECT_DIRECTION_DOWN, \
						  Director::getInstance()->getWinSize().width / 2 + 16, \
						  2 * 32 + 16);
					  this->addChild(_hamster, 3);
				  }
			  }


		  }
		  else{
			  delay++;
		  }
#endif
		  _DD->update();
		  _selectRect->update();
	  }
	  
	  _hamster->update();	
	
	  if (_isSelectFixed == true){
		  if (_hamster->_needRemoved == true\
			  && _hamster->_id>=53\
			  && _hamster->_id<=60){
			  if (_hamster != nullptr){
				  if (_hamster->getReferenceCount() > 0){
					  _hamster->removeFromParent();
					  _hamster = nullptr;
				  }
			  }
			 
			  _hamster = GlobalEffect::create(61 + _selectIndex, \
				  GAME_EFFECT_DIRECTION_DOWN, \
				  Director::getInstance()->getWinSize().width / 2 + 16, \
				  2 * 32 + 16);
			  this->addChild(_hamster, 3);
		  }
		  if (_replaceSceneWait == 48){
			  this->unschedule(schedule_selector(HamsterSelLayer::update));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)		
			  InputManager::getInstance()->destroyInstance();
#endif
			  GameManager::getInstance()->_playerSelHamsterId = _selectIndex+1;
			  auto newScene = GameScene::createScene();
			  //auto transition = TransitionFadeDown::create(0.5, newScene);
			  auto transition = TransitionFade::create(0.5, newScene);
              //auto transition = TransitionFadeDown::create(0, newScene);
			  Director::getInstance()->replaceScene(transition);			  
			  
		  }
		  
          _replaceSceneWait++;
		  
	  }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
bool HamsterSelLayer::onTouchBegan(Touch * touch, Event *event)
{
	
	for (int i = 0; i<8; i++)
	{
		if (_hamsterHeads[i]->getBoundingBox().containsPoint(touch->getLocation())){
			if (_selectIndex != i){
				SimpleAudioEngine::getInstance()->playEffect("sound/cursor.wav");
				_selectIndex = i;
				_selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());
				_selectedHamsterNameSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString())->getSpriteFrame());

				if (_hamster != nullptr){
					if (_hamster->getReferenceCount() > 0){
						_hamster->removeFromParent();
						_hamster = nullptr;
					}
				}
				_hamster = GlobalEffect::create(21 + _selectIndex, \
					GAME_EFFECT_DIRECTION_DOWN, \
					Director::getInstance()->getWinSize().width / 2 + 16, \
					2 * 32 + 16);
				this->addChild(_hamster, 3);
				
			}
            return true;
            //break;
		}
	}
}

void HamsterSelLayer::onTouchMoved(Touch * touch, Event *event)
{
	for (int i = 0; i<8; i++)
	{
		if (_hamsterHeads[i]->getBoundingBox().containsPoint(touch->getLocation())){
			if (_selectIndex != i){
				SimpleAudioEngine::getInstance()->playEffect("sound/cursor.wav");
				_selectIndex = i;
				_selectRect->setPosition(_hamsterHeads[_selectIndex]->getPosition());
				_selectedHamsterNameSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hamster_sel_layer/name_%02d.png", _selectIndex + 1)->getCString())->getSpriteFrame());

				if (_hamster != nullptr){
					if (_hamster->getReferenceCount() > 0){
						_hamster->removeFromParent();
						_hamster = nullptr;
					}
				}
				_hamster = GlobalEffect::create(21 + _selectIndex, \
					GAME_EFFECT_DIRECTION_DOWN, \
					Director::getInstance()->getWinSize().width / 2 + 16, \
					2 * 32 + 16);
				this->addChild(_hamster, 3);
				break;
			}

		}
	}
}
#endif

void HamsterSelLayer::menuCallBack(Ref *pSender){
	switch (((Node *)pSender)->getTag()){
	case 0:{
			   _isSelectFixed = true;
			   _replaceSceneWait = 0;

			   _okBtn->setEnabled(false);

			   SimpleAudioEngine::getInstance()->playEffect("sound/select_fixed.wav");

			   if (_hamster != nullptr){
				   if (_hamster->getReferenceCount() > 0){
					   _hamster->removeFromParent();
					   _hamster = nullptr;
				   }
			   }
			   _hamster = GlobalEffect::create(53 + _selectIndex, \
				   GAME_EFFECT_DIRECTION_DOWN, \
				   Director::getInstance()->getWinSize().width / 2 + 16, \
				   2 * 32 + 16);
			   this->addChild(_hamster, 3);


			   if (_DD != nullptr){
				   if (_DD->getReferenceCount() > 0){
					   _DD->removeFromParent();
					   _DD = nullptr;
				   }
			   }

			   _DD = GlobalEffect::create(30, \
				   GAME_EFFECT_DIRECTION_DOWN, \
				   Director::getInstance()->getWinSize().width / 2 - 64 - 16, \
				   4 * 32 + 16);
			   this->addChild(_DD, 3);

	}break;
	case 1:{

	}break;
	}
}

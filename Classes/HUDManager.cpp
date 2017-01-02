#include "HUDManager.h"
#include "CharacterManager.h"
#include "GameManager.h"

//ÉùÃ÷¾²Ì¬±äÁ¿
HUDManager * HUDManager::_instance = nullptr;

HUDManager * HUDManager::getInstance(){
	if (_instance == nullptr){
		_instance = new HUDManager();
		_instance->init();
	}
	return _instance;
}

void HUDManager::destroyInstance(){
	if (!_instance){
		return;
	}

	for (int i = 0; i < 8; i++){
		if (_instance->_rankingNumSpriteFrames[i] != nullptr){
			if (_instance->_rankingNumSpriteFrames[i]->getReferenceCount()>0){
				_instance->_rankingNumSpriteFrames[i]->release();
			}
			_instance->_rankingNumSpriteFrames[i] = nullptr;
		}
	}

	delete _instance;
	_instance = nullptr;
}

bool  HUDManager::init(){
	_hudLayer=nullptr;
	_energyProgress = nullptr;
	_rankingNumSprite = nullptr;
	_rankingNote = nullptr;
	_displayedHamsterNote = nullptr;

	for (int i = 0; i < 8; i++){
        _rankingNumSpriteFrames[i] = Sprite::createWithSpriteFrameName(String::createWithFormat("ranking_num_%d.png",i+1)->getCString())->getSpriteFrame();
		_rankingNumSpriteFrames[i]->retain();
	}

	return true;
}

void HUDManager::update(){
	//MessageBox(Value((float)((Hamster *)CharacterManager::getInstance()->_player)->_energy\
	//	/ (float)((Hamster *)CharacterManager::getInstance()->_player)->_maxEnergy).asString().c_str(), "test");
	if (_energyProgress->getPercentage() > (int)(100 * (float)((Hamster *)CharacterManager::getInstance()->_player)->_energy\
		                                       / (float)((Hamster *)CharacterManager::getInstance()->_player)->_maxEnergy) )
	{
		_energyProgress->setPercentage(_energyProgress->getPercentage()-1);
	}
	else if (_energyProgress->getPercentage() < (int)(100 * (float)((Hamster *)CharacterManager::getInstance()->_player)->_energy\
		                                            / (float)((Hamster *)CharacterManager::getInstance()->_player)->_maxEnergy) )
	{
		_energyProgress->setPercentage(_energyProgress->getPercentage()+1);
	}
	
	//if (_rankingNumSprite != nullptr){
	//	if (_rankingNumSprite->getReferenceCount() > 0){
	//		//auto oldTexture = _rankingNumSprite->getTexture();
	//		_rankingNumSprite->removeFromParent();	
	//		//Director::getInstance()->getTextureCache()->removeTexture(oldTexture);
	//		_rankingNumSprite = nullptr;
	//	}
	//}	
	//
	_rankingNumSprite->setSpriteFrame(_rankingNumSpriteFrames[((Hamster *)CharacterManager::getInstance()->_player)->_ranking-1]);
	//_rankingNumSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hud/ranking/%d.png", ((Hamster*)CharacterManager::getInstance()->_player)->_ranking)->getCString())->getSpriteFrame());
	//_rankingNumSprite = Sprite::create(String::createWithFormat("hud/ranking/%d.png", ((Hamster*)CharacterManager::getInstance()->_player)->_ranking)->getCString());
	//_rankingNumSprite->setSpriteFrame(Sprite::create(String::createWithFormat("hud/ranking/%d.png", ((Hamster*)CharacterManager::getInstance()->_player)->_ranking)->getCString())->getSpriteFrame());
	//_rankingNumSprite = Sprite::create(String::createWithFormat("hud/ranking/%d.png", ((Hamster*)CharacterManager::getInstance()->_player)->_ranking)->getCString());
	/*if (_rankingNumSprite != nullptr){
		_rankingNumSprite->setAnchorPoint(Point(0, 0));
		_rankingNumSprite->setPosition(Point(_rankingNote->getPositionX() + _rankingNote->getContentSize().width*_rankingNote->getScale(), \
			_rankingNote->getPositionY()));
		_hudLayer->addChild(_rankingNumSprite, 1);
	}*/
	
	

	switch (GameManager::getInstance()->_gameMode){
	case (int)GameManager::GameMode::RANKING_MODE:{
	}break;
	case (int)GameManager::GameMode::ELIMINATION_MODE:
	case (int)GameManager::GameMode::SURVIVAL_MODE:{
		updateHamsterHeads();
	}break;
	}	
	
}

void  HUDManager::displayFinishHamster(int hamsterId){
	auto winSize = Director::getInstance()->getWinSize();
	auto hamsterSprite = Sprite::create(String::createWithFormat("character/hamster/%d/head/hamster_head.png", hamsterId)->getCString());
	hamsterSprite->setScale(0.8);
	_hudLayer->addChild(hamsterSprite, 1);
	
	hamsterSprite->setAnchorPoint(Point(0, 0));
	hamsterSprite->setPosition(Point(12 + _displayedHamsterSprites.size()*(hamsterSprite->getContentSize().width*0.8+4),\
		_displayedHamsterNote->getPositionY() - hamsterSprite->getContentSize().height*0.8-4));
	_displayedHamsterSprites.push_back(hamsterSprite);	
}

void  HUDManager::displayHamsterHeads(){
	int displayedOrder = 1;
	for (int rankingIndex = 1; rankingIndex <= 8; rankingIndex++){

		if (CharacterManager::getInstance()->_player != nullptr){
			if (((Hamster *)CharacterManager::getInstance()->_player)->_ranking == rankingIndex\
				&& ((Hamster *)CharacterManager::getInstance()->_player)->_state != (int)Hamster::State::LOSE){
				
				auto hamsterSprite = Sprite::create(String::createWithFormat(\
					"character/hamster/%d/head/hamster_head.png",\
					((Hamster *)CharacterManager::getInstance()->_player)->_id)->getCString());
				hamsterSprite->setScale(0.8);
				_hudLayer->addChild(hamsterSprite, 1);

				hamsterSprite->setAnchorPoint(Point(0, 0));
				hamsterSprite->setPosition(Point(12 + (displayedOrder-1)*(hamsterSprite->getContentSize().width*0.8 + 4), \
					_displayedHamsterNote->getPositionY() - hamsterSprite->getContentSize().height*0.8 - 4));
				hamsterSprite->setTag(((Hamster *)CharacterManager::getInstance()->_player)->_id);
				
				_displayedHamsterSprites.push_back(hamsterSprite);
				
				displayedOrder++;
			}
		}

		for (std::vector<Character *>::iterator it = CharacterManager::getInstance()->_opponentHamsters.begin();\
			it != CharacterManager::getInstance()->_opponentHamsters.end();){
			if ((*it) != nullptr){
				if (((Hamster *)*it)->_ranking == rankingIndex\
					&& ((Hamster *)*it)->_state != (int)Hamster::State::LOSE){
					//MessageBox(Value(((Hamster *)*it)->_id).asString().c_str(), "test");
					auto hamsterSprite = Sprite::create(String::createWithFormat(\
						"character/hamster/%d/head/hamster_head.png", \
						((Hamster *)*it)->_id)->getCString());
					hamsterSprite->setScale(0.8);
					_hudLayer->addChild(hamsterSprite, 1);

					hamsterSprite->setAnchorPoint(Point(0, 0));

					hamsterSprite->setPosition(Point(12 + (displayedOrder - 1)*(hamsterSprite->getContentSize().width*0.8 + 4), \
						_displayedHamsterNote->getPositionY() - hamsterSprite->getContentSize().height*0.8 - 4));
					
					hamsterSprite->setTag(((Hamster *)*it)->_id);
					
					_displayedHamsterSprites.push_back(hamsterSprite);
					
					displayedOrder++;
				}
			}
			it++;
		}

	}


}
void  HUDManager::updateHamsterHeads(){
	int displayedOrder = 1;
	for (int rankingIndex = 1; rankingIndex <= 8; rankingIndex++){
		
		/*if (CharacterManager::getInstance()->_player != nullptr){
			
			if (((Hamster *)CharacterManager::getInstance()->_player)->_ranking == rankingIndex){
				auto hamsterSprite = _hudLayer->getChildByTag(((Hamster *)CharacterManager::getInstance()->_player)->_id);
				if (hamsterSprite != nullptr){

					hamsterSprite->setPosition(Point(12 + (displayedOrder - 1)*((hamsterSprite)->getContentSize().width*0.8 + 4), \
						_finishHamsterNote->getPositionY() - (hamsterSprite)->getContentSize().height*0.8 - 4));
					displayedOrder++;
				}
			}
		}*/

		for (std::vector<Character *>::iterator hamsterIt = CharacterManager::getInstance()->_hamsters.begin(); \
			hamsterIt != CharacterManager::getInstance()->_hamsters.end();){
			if ((*hamsterIt) != nullptr){
				if (((Hamster *)*hamsterIt)->_ranking == rankingIndex){
					auto hamsterSprite = _hudLayer->getChildByTag(((Hamster *)*hamsterIt)->_id);
					if ((*hamsterIt)->_state == (int)Hamster::State::LOSE){
						hamsterSprite->setColor(Color3B(192, 192, 192));
						
					}
					if (hamsterSprite != nullptr){
						hamsterSprite->setPosition(Point(12 + (displayedOrder - 1)*((hamsterSprite)->getContentSize().width*0.8 + 4), \
							_displayedHamsterNote->getPositionY() - (hamsterSprite)->getContentSize().height*0.8 - 4));
						displayedOrder++;
					}					
				}
			}
			hamsterIt++;
		}
	}
}
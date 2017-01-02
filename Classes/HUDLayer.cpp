#include "HUDLayer.h"
#include "Progress.h"
#include "HUDManager.h"
#include "CharacterManager.h"
#include "DataManager.h"
#include "GameManager.h"

HUDLayer::HUDLayer(){

}

HUDLayer::~HUDLayer(){

}

bool HUDLayer::init(){
	if (!Layer::init()){
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	
	Progress * energyProgress = Progress::create(ProgressTimerType::RADIAL, "hud/energy_progress/energy_progress_bg.png", "hud/energy_progress/energy_progress_fill.png");
	
	energyProgress->setPercentage(100 * (float)((Hamster *)CharacterManager::getInstance()->_player)->_energy\
		                        / (float)((Hamster *)CharacterManager::getInstance()->_player)->_maxEnergy);
	
	this->addChild(energyProgress, 2);
	
	energyProgress->setPosition(Point(60, 300));
	HUDManager::getInstance()->_energyProgress = energyProgress;

	Sprite * hamsterHead = Sprite::create(String::createWithFormat("character/hamster/%d/figure/hamster_figure.png", CharacterManager::getInstance()->_player->_id)->getCString());
	this->addChild(hamsterHead, 1);
	hamsterHead->setPosition(energyProgress->getPosition());

	
	auto rankingNote = Sprite::create("hud/ranking/ranking_note.png");
	rankingNote->setScale(0.8);
	HUDManager::getInstance()->_rankingNote = rankingNote;

	this->addChild(rankingNote, 1);
	rankingNote->setAnchorPoint(Point(0, 0));
	rankingNote->setPosition(Point(energyProgress->getPositionX() - energyProgress->_bg->getContentSize().width / 2 - 8, \
		energyProgress->getPositionY() - energyProgress->_bg->getContentSize().height / 2 - 32));

	
	Sprite * rankingNumSprite = Sprite::create();	
	this->addChild(rankingNumSprite, 1);
	rankingNumSprite->setAnchorPoint(Point(0, 0));
	rankingNumSprite->setPosition(Point(rankingNote->getPositionX() + rankingNote->getContentSize().width*rankingNote->getScale(), \
		rankingNote->getPositionY()));

	HUDManager::getInstance()->_rankingNumSprite = rankingNumSprite;
	HUDManager::getInstance()->_rankingNumSprite->setSpriteFrame(HUDManager::getInstance()->_rankingNumSpriteFrames[((Hamster *)CharacterManager::getInstance()->_player)->_ranking-1]);

	switch (GameManager::getInstance()->_gameMode){
	case (int)GameManager::GameMode::RANKING_MODE:{
		auto finishHamsterNote = Sprite::create("hud/finish_hamster/finish_hamster_note.png");
		finishHamsterNote->setScale(0.8);
		HUDManager::getInstance()->_displayedHamsterNote = finishHamsterNote;
		this->addChild(finishHamsterNote, 1);
		finishHamsterNote->setAnchorPoint(Point(0, 0));
		finishHamsterNote->setPosition(Point(8, winSize.height - 32));
	}break;
	case (int)GameManager::GameMode::ELIMINATION_MODE:{
		auto currentSituationNote = Sprite::create("hud/current_situation/current_situation_note.png");
		currentSituationNote->setScale(0.8);
		HUDManager::getInstance()->_displayedHamsterNote = currentSituationNote;
		this->addChild(currentSituationNote, 1);
		currentSituationNote->setAnchorPoint(Point(0, 0));
		currentSituationNote->setPosition(Point(8, winSize.height - 32));

	}break;
	case (int)GameManager::GameMode::SURVIVAL_MODE:{
        auto survivalStateNote = Sprite::create("hud/survival_state/survival_state_note.png");
		survivalStateNote->setScale(0.8);
		HUDManager::getInstance()->_displayedHamsterNote = survivalStateNote;
		this->addChild(survivalStateNote, 1);
		survivalStateNote->setAnchorPoint(Point(0, 0));
		survivalStateNote->setPosition(Point(8, winSize.height - 32));
	}break;
	}

	return true;
}

void HUDLayer::update(float dt){

}
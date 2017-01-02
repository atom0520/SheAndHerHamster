#include "GameLayer.h"
#include "DataManager.h"
#include "Hamster.h"
#include "Master.h"
#include "Predator.h"
#include "GlobalEffect.h"

#include "GameManager.h"
#include "CharacterManager.h"
#include "MapManager.h"
#include "InputManager.h"
#include "HUDManager.h"
#include "QuestionManager.h"
#include "OperationManager.h"
#include "GameEffectManager.h"
#include "TimeManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define NEED_REFRESH_COMPILE 1

long GameLayer::old_clock_count = 0;

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	
	this->addPlayer();
	this->addOpponentHamsters();
    
    log("finish adding hamsters");
    
	this->addMasters();
    
	if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::SURVIVAL_MODE){
		this->addPredators();
	}
	return true;
}

void GameLayer::onEnter()
{
	Layer::onEnter();

	switch (GameManager::getInstance()->_gameMode){
	case (int)GameManager::GameMode::GUIDE_MODE:
	{
		GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
		GameManager::getInstance()->_guidePhase = 0;
		GameManager::getInstance()->_guidePhaseFinish = false;
		GameManager::getInstance()->_getReadyPhaseCounter = 0;

		//OperationManager::getInstance()->_joyStick->_listenerTouch->setEnabled(false);
		
		OperationManager::getInstance()->_speedUpBtn->setEnabled(false);
		
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_guide_game_bgm.wav", true);
		}
		else{
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_guide_game_bgm.wav", true);
		}
	}break;
	case (int)GameManager::GameMode::RANKING_MODE:
	{
	    GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
		GameManager::getInstance()->_getReadyPhaseCounter = 0;

		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_ranking_game_bgm.wav", true);
		}
		else{
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_ranking_game_bgm.wav", true);
		}
	}break;
	case (int)GameManager::GameMode::ELIMINATION_MODE:
	{
		GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
		GameManager::getInstance()->_getReadyPhaseCounter = 0;

		HUDManager::getInstance()->displayHamsterHeads();

		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_elimination_game_bgm.wav", true);
			
		}
		else{
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_elimination_game_bgm.wav", true);
			
		}
	}break;
	case (int)GameManager::GameMode::SURVIVAL_MODE:
	{
		GameManager::getInstance()->_gameState = (int)GameManager::GameState::GET_READY;
		GameManager::getInstance()->_getReadyPhaseCounter = 0;
		
		HUDManager::getInstance()->displayHamsterHeads();

		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_survival_game_bgm.wav", true);
		}
		else{
			SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mode_survival_game_bgm.wav", true);
		}
	}break;
	}
	
    this->schedule(schedule_selector(GameLayer::update), 0.03);
}

void GameLayer::onExit()
{
	Layer::onExit();
    this->unschedule(schedule_selector(GameLayer::update));
	//unscheduleUpdate();
}

void GameLayer::update(float dt){

	/*while (TimeManager::getInstance()->getCurrentTimeInMillisecond() - old_clock_count < 30);
	  old_clock_count = TimeManager::getInstance()->getCurrentTimeInMillisecond();*/
	
	GameManager::getInstance()->update();
}

void GameLayer::addPlayer(){

	if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::GUIDE_MODE){
		Character * player = Hamster::create(2, \
			(int)Hamster::ControlType::PLAYER, \
			MapManager::getInstance()->_mapWidth / 2 - 16 , \
			MapManager::getInstance()->_startLinePosY );
		CharacterManager::getInstance()->_player = (Hamster*)player;
		CharacterManager::getInstance()->_hamsters.push_back(player);

		MapManager::getInstance()->_characterLayer->addChild(player, MapManager::getInstance()->_mapHeight - player->getPositionY());
	}
	else{
		Character * player = Hamster::create(GameManager::getInstance()->_playerSelHamsterId, \
			(int)Hamster::ControlType::PLAYER, \
			MapManager::getInstance()->_mapWidth / 2 - 16 - 32 + (GameManager::getInstance()->_playerSelHamsterId - 1) % 4 * 32, \
			MapManager::getInstance()->_startLinePosY + (GameManager::getInstance()->_playerSelHamsterId - 1) / 4 * 32);
		CharacterManager::getInstance()->_player = (Hamster*)player;
		CharacterManager::getInstance()->_hamsters.push_back(player);

		MapManager::getInstance()->_characterLayer->addChild(player, MapManager::getInstance()->_mapHeight - player->getPositionY());
	}	
}

void GameLayer::addOpponentHamsters(){

	if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::GUIDE_MODE){
		
		Character * oppoHamster = Hamster::create(3, \
			(int)Hamster::ControlType::COMPUTER, \
			MapManager::getInstance()->_mapWidth / 2 + 16, \
			MapManager::getInstance()->_startLinePosY);
		CharacterManager::getInstance()->_opponentHamsters.push_back(oppoHamster);
		CharacterManager::getInstance()->_hamsters.push_back(oppoHamster);

		MapManager::getInstance()->_characterLayer->addChild(oppoHamster, MapManager::getInstance()->_mapHeight - oppoHamster->getPositionY());
		
	}
	else{
		for (int i = 1; i <= 8; i++){
			if (i != GameManager::getInstance()->_playerSelHamsterId){
				Character * oppoHamster = Hamster::create(i, \
					(int)Hamster::ControlType::COMPUTER, \
					MapManager::getInstance()->_mapWidth / 2 - 16 - 32 + (i - 1) % 4 * 32, \
					MapManager::getInstance()->_startLinePosY + (i - 1) / 4 * 32);
				CharacterManager::getInstance()->_opponentHamsters.push_back(oppoHamster);
				CharacterManager::getInstance()->_hamsters.push_back(oppoHamster);

				MapManager::getInstance()->_characterLayer->addChild(oppoHamster, MapManager::getInstance()->_mapHeight - oppoHamster->getPositionY());

			}

		}
	}

	
}

void GameLayer::addMasters(){
	

	if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::GUIDE_MODE){
		{
			int	trackTileX = MASTER_LEFT_TRACK_TILE_X;
			
			Character * playerMaster = Master::create(1, \
				(Hamster *)CharacterManager::getInstance()->_player, \
				trackTileX * 32 + 16, \
				CharacterManager::getInstance()->_player->getPositionY());

			CharacterManager::getInstance()->_masters.push_back(playerMaster);

			MapManager::getInstance()->_characterLayer->addChild(playerMaster, MapManager::getInstance()->_mapHeight - playerMaster->getPositionY());
		}

		{

			int trackTileX = MASTER_RIGHT_TRACK_TILE_X;
			
			Character * oppoHamsterMaster = Master::create(8, \
				(Hamster *)CharacterManager::getInstance()->_opponentHamsters[0], \
				trackTileX * 32 + 16, \
				CharacterManager::getInstance()->_opponentHamsters[0]->getPositionY());

			CharacterManager::getInstance()->_masters.push_back(oppoHamsterMaster);
			MapManager::getInstance()->_characterLayer->addChild(oppoHamsterMaster, MapManager::getInstance()->_mapHeight - oppoHamsterMaster->getPositionY());
		}
	}
	else{
		srand(time(NULL));
		{

			int track = rand() % 2;
			int trackTileX;
			if (track == 0){
				trackTileX = MASTER_LEFT_TRACK_TILE_X;
			}
			else{
				trackTileX = MASTER_RIGHT_TRACK_TILE_X;
			}
			Character * playerMaster = Master::create(1, \
				(Hamster *)CharacterManager::getInstance()->_player, \
				trackTileX * 32 + 16, \
				CharacterManager::getInstance()->_player->getPositionY());

			CharacterManager::getInstance()->_masters.push_back(playerMaster);

			MapManager::getInstance()->_characterLayer->addChild(playerMaster, MapManager::getInstance()->_mapHeight - playerMaster->getPositionY());
		}

		for (int i = 0; i < 7; i++){

			int track = rand() % 2;
			int trackTileX;
			if (track == 0){
				trackTileX = MASTER_LEFT_TRACK_TILE_X;
			}
			else{
				trackTileX = MASTER_RIGHT_TRACK_TILE_X;
			}
			Character * oppoHamsterMaster = Master::create(2 + i, \
				(Hamster *)CharacterManager::getInstance()->_opponentHamsters[i], \
				trackTileX * 32 + 16, \
				CharacterManager::getInstance()->_opponentHamsters[i]->getPositionY());

			CharacterManager::getInstance()->_masters.push_back(oppoHamsterMaster);
			MapManager::getInstance()->_characterLayer->addChild(oppoHamsterMaster, MapManager::getInstance()->_mapHeight - oppoHamsterMaster->getPositionY());
		}
	}

}

void GameLayer::addPredators(){
	int positionStyle = rand() % 2;
	switch (positionStyle){
	case 0:{
		Character * doraemon = Predator::create(1, \
		MapManager::getInstance()->_mapWidth / 2 - 16, \
		MapManager::getInstance()->_startLinePosY + 128);

		CharacterManager::getInstance()->_predators.push_back(doraemon);

		MapManager::getInstance()->_characterLayer->addChild(doraemon, MapManager::getInstance()->_mapHeight - doraemon->getPositionY());

		/*Character * dorami = Predator::create(2, \
		MapManager::getInstance()->_mapWidth / 2 + 16, \
		MapManager::getInstance()->_startLinePosY + 128);

		CharacterManager::getInstance()->_predators.push_back(dorami);

		MapManager::getInstance()->_characterLayer->addChild(dorami, MapManager::getInstance()->_mapHeight - doraemon->getPositionY());*/

	}
		break;
	case 1:{
		Character * doraemon = Predator::create(1, \
		MapManager::getInstance()->_mapWidth / 2 + 16, \
		MapManager::getInstance()->_startLinePosY + 128);

		CharacterManager::getInstance()->_predators.push_back(doraemon);

		MapManager::getInstance()->_characterLayer->addChild(doraemon, MapManager::getInstance()->_mapHeight - doraemon->getPositionY());
		
		/*Character * dorami = Predator::create(2, \
		MapManager::getInstance()->_mapWidth / 2 - 16, \
		MapManager::getInstance()->_startLinePosY + 128);

		CharacterManager::getInstance()->_predators.push_back(dorami);

		MapManager::getInstance()->_characterLayer->addChild(dorami, MapManager::getInstance()->_mapHeight - doraemon->getPositionY());*/
	}
		break;
	}
	

}
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

//游戏逻辑管理类
class GameManager : public Ref{
public:
	static GameManager * getInstance();
	static void destroyInstance();
	virtual bool init();
	virtual void update();
	virtual void startGame();
	/*virtual void reStartGame();*/
	virtual void winGame();
	virtual void finishRace();
	virtual void finishEliminationRound(int roundNum);

	Layer * _gameLayer;

	enum class GameMode{
		GUIDE_MODE,
		RANKING_MODE,
		ELIMINATION_MODE,
		SURVIVAL_MODE,
	};

	enum class GameState{
		PAUSE,
		GET_READY,
		IN_THE_GAME,
		END,		
	};

	int _gameState;
	int _gameMode;
	int _finishNum;
	int _playerSelHamsterId;
	int _roundNum;
	int _caughtNum;
	int _getReadyPhaseCounter;
	int _endPhaseCounter;

	int _guidePhase;
	bool _guidePhaseFinish;

	bool _playerMoveCompleteInGuide;
	bool _playerRunCompleteInGuide;
protected:
	static GameManager * _instance;

	
};

#endif
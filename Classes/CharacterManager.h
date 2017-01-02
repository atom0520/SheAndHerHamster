#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H


#include "Character.h"
#include "Hamster.h"
#include "cocos2d.h"
USING_NS_CC;

//游戏场景中角色的管理类
class CharacterManager : public Ref{
public:
	static CharacterManager * getInstance();
	static void destroyInstance();
	virtual bool init();
	virtual void update();

	Character * _player;
	//Hamster * _player;
	std::vector<Character *> _opponentHamsters;
	std::vector<Character *> _hamsters;
	std::vector<Character *> _masters;
	std::vector<Character *> _predators;

protected:
	static CharacterManager * _instance;
};

#endif
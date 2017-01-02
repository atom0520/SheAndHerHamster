#include "MapManager.h"
#include "CharacterManager.h"

//ÉùÃ÷¾²Ì¬±äÁ¿
MapManager * MapManager::_instance = nullptr;

MapManager * MapManager::getInstance(){
	if (_instance == nullptr){
		_instance = new MapManager();
		_instance->init();
	}
	return _instance;
}

void MapManager::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

bool MapManager::init(){
	_mapLayer=nullptr;
	_characterLayer = nullptr;

	_mapWidth=0;
	_mapHeight=0;
	_startLinePosY = 0;
	_finishLinePosY = 0;
	_recurrenceLineInGuidePosY = 0;

	return true;
}

void MapManager::update(){
	if (CharacterManager::getInstance()->_player != nullptr){
		updateMapView();
	}

}

void MapManager::updateMapView(){
	Size winSize = Director::getInstance()->getWinSize();

	Point playerMapPosition = CharacterManager::getInstance()->_player->getPosition();

	Point playerWinPosition = playerMapPosition + this->_mapLayer->getPosition();

	/*if (playerWinPosition.x < winSize.width / 5 * 2){
		this->_mapLayer->setPositionX(this->_mapLayer->getPositionX() + (winSize.width / 5 * 2 - playerWinPosition.x));

	}
	else if (playerWinPosition.x > winSize.width / 5 * 3){
		this->_mapLayer->setPositionX(this->_mapLayer->getPositionX() - (playerWinPosition.x - winSize.width / 5 * 3));
	}*/

	/*if (playerWinPosition.x < winSize.width / 2){
		this->_mapLayer->setPositionX(this->_mapLayer->getPositionX() + (winSize.width / 2 - playerWinPosition.x));

	}
	else if (playerWinPosition.x > winSize.width / 2){
		this->_mapLayer->setPositionX(this->_mapLayer->getPositionX() - (playerWinPosition.x - winSize.width / 2));
	}

	if (this->_mapLayer->getPositionX() > 0){
		this->_mapLayer->setPositionX(0);
	}
	else if (this->_mapLayer->getPositionX() < -(this->_mapWidth - winSize.width)){
		this->_mapLayer->setPositionX(-(this->_mapWidth - winSize.width));

	}*/
	this->_mapLayer->setPositionX(-(this->_mapWidth/2 - winSize.width/2));

	/*if (playerWinPosition.y < winSize.height / 3){
		this->_mapLayer->setPositionY(this->_mapLayer->getPositionY() + (winSize.height / 3 - playerWinPosition.y));
	}
	else if (playerWinPosition.y > winSize.height / 2){
		this->_mapLayer->setPositionY(this->_mapLayer->getPositionY() - (playerWinPosition.y - winSize.height / 2));
	}*/
	if (playerWinPosition.y < winSize.height* 1 / 4){
		this->_mapLayer->setPositionY(this->_mapLayer->getPositionY() + (winSize.height* 1 / 4 - playerWinPosition.y));
	}
	else if (playerWinPosition.y > winSize.height* 1 / 4){
		this->_mapLayer->setPositionY(this->_mapLayer->getPositionY() - (playerWinPosition.y - winSize.height* 1 / 4));
	}

	if (this->_mapLayer->getPositionY() > 0){
		this->_mapLayer->setPositionY(0);
	}
	else if (this->_mapLayer->getPositionY() < -(this->_mapHeight - winSize.height)){
		this->_mapLayer->setPositionY(-(this->_mapHeight - winSize.height));

	}
}

bool MapManager::isPassable(int x, int y, int direction){
	return true;
}
#include "DataManager.h"

//ÉùÃ÷¾²Ì¬±äÁ¿
DataManager * DataManager::_instance = nullptr;

DataManager * DataManager::getInstance(){
	if (_instance == nullptr){
		_instance = new DataManager();
		_instance->init();
	}
	return _instance;
}

void DataManager::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

bool  DataManager::init(){
	std::string configDataPath = FileUtils::getInstance()->fullPathForFilename(CONFIG_DATA_PATH);
	this->_configData = FileUtils::getInstance()->getValueMapFromFile(configDataPath);

	std::string staticDataPath = FileUtils::getInstance()->fullPathForFilename(STATIC_DATA_PATH);
	this->_staticData = FileUtils::getInstance()->getValueMapFromFile(staticDataPath);

	this->_dynamicData = UserDefault::getInstance();

	return true;
}
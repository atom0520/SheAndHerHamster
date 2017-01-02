#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

#define  CONFIG_DATA_PATH     "data/config_data.xml"
#define  STATIC_DATA_PATH     "data/static_data.xml" 
#define  DYNAMIC_DATA_PATH    "data/dynamic_data.xml"


//游戏数据管理类
class DataManager : public Ref{
public:
	static DataManager * getInstance();
	static void destroyInstance();

	virtual bool init();

	ValueMap _configData;
	ValueMap _staticData;

	UserDefault * _dynamicData;

	class Word{
	public:
		int _id;
		String * _en;
		String * _ch;
		Word(){};
		~Word(){};
		Word(int id, String * en, String * ch){
			_id = id;
			_en = en;
			_en->retain();
			_ch = ch;
			_ch->retain();
		}
	};

	std::vector<Word> _ieltsWords;
protected:
	static DataManager * _instance;
};

#endif
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

//游戏地图管理类
class MapManager : public Ref{
public:

	static MapManager * getInstance();
	static void destroyInstance();
	virtual bool init();

	virtual void update();
	void updateMapView();

	Layer * _mapLayer;
	Layer * _characterLayer;
	bool isPassable(int x, int y, int direction);

	int _mapWidth;
	int _mapHeight;

	int _startLinePosY;
	int _finishLinePosY;

	int _eliminationLinePosY[3];
	int _recurrenceLineInGuidePosY;
	int _recurrenceDistanceInGuide;
	//unsigned char * _mapMarkData;

	//enum class MapMarkDataType{
	//	RED_CHANNEL_DATA = 0,
	//	GREEN_CHANNEL_DATA,
	//	BLUE_CHANNEL_DATA,
	//	ALPHA_CHANNEL_DATA,
	//};

	//int getMapMarkData(Point markPosition, MapMarkDataType dataType);

protected:
	static MapManager * _instance;
};

#endif
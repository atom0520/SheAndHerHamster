#include "MapLayer.h"
#include "MapManager.h"
#include "DataManager.h"
#include "GameManager.h"

MapLayer::MapLayer()
{

}

MapLayer::~MapLayer()
{

}

bool MapLayer::init()
{
	if (!Layer::init()){
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();


	auto sceneryLayer = Layer::create();

	if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::GUIDE_MODE){
		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/field_3.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			MapManager::getInstance()->_recurrenceLineInGuidePosY += unitSize.height;

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/field_2.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			int unitNum = 8;
			int unitIndex;

			MapManager::getInstance()->_recurrenceLineInGuidePosY += 4*unitSize.height;
			MapManager::getInstance()->_recurrenceDistanceInGuide = unitSize.height;

			for (unitIndex = 0; unitIndex < unitNum; unitIndex++){
				auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
				sceneryLayer->addChild(unitSprite, 1);
				unitSprite->setAnchorPoint(Point(0, 0));
				unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
				MapManager::getInstance()->_mapHeight += unitSize.height;

		    }
		    MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
	    }

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/field_1.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

	

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		int startLinePosY = MapManager::getInstance()->_mapHeight - DataManager::getInstance()->_staticData\
			.at("map").asValueMap()\
			.at("start_line_off_y").asInt();
		MapManager::getInstance()->_startLinePosY = startLinePosY;

		{
			auto startLine = Sprite::create("map/start_line.png");
			sceneryLayer->addChild(startLine, 2);
			startLine->setAnchorPoint(Point(0.5, 0.5));
			startLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, startLinePosY));

			auto blackwhileLine = Sprite::create("map/blackwhite_line.png");
			sceneryLayer->addChild(blackwhileLine, 2);
			blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
			blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, startLinePosY + 32));
		}


		int finishLinePosY = DataManager::getInstance()->_staticData\
			.at("map").asValueMap()\
			.at("finish_line_off_y").asInt();
		MapManager::getInstance()->_finishLinePosY = finishLinePosY;

		{
			auto finishLine = Sprite::create("map/finish_line.png");
			sceneryLayer->addChild(finishLine, 2);
			finishLine->setAnchorPoint(Point(0.5, 0.5));
			finishLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, finishLinePosY));

			auto blackwhileLine = Sprite::create("map/blackwhite_line.png");
			sceneryLayer->addChild(blackwhileLine, 2);
			blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
			blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, finishLinePosY - 32));
			
		}
	}
	else{

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/city_2.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			int unitNum = 5;
			int unitIndex;

			for (unitIndex = 0; unitIndex < unitNum; unitIndex++){
				auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
				sceneryLayer->addChild(unitSprite, 1);
				unitSprite->setAnchorPoint(Point(0, 0));
				unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
				MapManager::getInstance()->_mapHeight += unitSize.height;

			}
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/city_1.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::ELIMINATION_MODE){
			MapManager::getInstance()->_eliminationLinePosY[2] = MapManager::getInstance()->_mapHeight + 16;
			{
				auto eliminationLine = Sprite::create("map/elimination_line_3.png");
				sceneryLayer->addChild(eliminationLine, 2);
				eliminationLine->setAnchorPoint(Point(0.5, 0.5));
				eliminationLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, MapManager::getInstance()->_mapHeight + 16));

			}
			{
				auto blackwhileLine = Sprite::create("map/blackwhite_line.png");
				sceneryLayer->addChild(blackwhileLine, 2);
				blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
				blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, MapManager::getInstance()->_mapHeight - 16));
				//MessageBox(Value(MapManager::getInstance()->_mapHeight - 16 + 32 * i).asString().c_str(), "test");
			}
		}


		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/lakeside_3.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/lakeside_2.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			int unitNum = 5;
			int unitIndex;

			for (unitIndex = 0; unitIndex < unitNum; unitIndex++){
				auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
				sceneryLayer->addChild(unitSprite, 1);
				unitSprite->setAnchorPoint(Point(0, 0));
				unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
				MapManager::getInstance()->_mapHeight += unitSize.height;

			}
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/lakeside_1.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::ELIMINATION_MODE){
			MapManager::getInstance()->_eliminationLinePosY[1] = MapManager::getInstance()->_mapHeight + 16;
			{
				auto eliminationLine = Sprite::create("map/elimination_line_2.png");
				sceneryLayer->addChild(eliminationLine, 2);
				eliminationLine->setAnchorPoint(Point(0.5, 0.5));
				eliminationLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, MapManager::getInstance()->_mapHeight + 16));

			}
			{
				auto blackwhileLine = Sprite::create("map/blackwhite_line.png");
				sceneryLayer->addChild(blackwhileLine, 2);
				blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
				blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, MapManager::getInstance()->_mapHeight - 16));
				//MessageBox(Value(MapManager::getInstance()->_mapHeight - 16 + 32 * i).asString().c_str(), "test");
			}
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/field_3.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/field_2.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			int unitNum = 5;
			int unitIndex;

			for (unitIndex = 0; unitIndex < unitNum; unitIndex++){
				auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
				sceneryLayer->addChild(unitSprite, 1);
				unitSprite->setAnchorPoint(Point(0, 0));
				unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
				MapManager::getInstance()->_mapHeight += unitSize.height;

			}
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/field_1.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		if (GameManager::getInstance()->_gameMode == (int)GameManager::GameMode::ELIMINATION_MODE){
			MapManager::getInstance()->_eliminationLinePosY[0] = MapManager::getInstance()->_mapHeight + 16;
			{
				auto eliminationLine = Sprite::create("map/elimination_line_1.png");
				sceneryLayer->addChild(eliminationLine, 2);
				eliminationLine->setAnchorPoint(Point(0.5, 0.5));
				eliminationLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, MapManager::getInstance()->_mapHeight + 16));
			
			}
			{
				auto blackwhileLine = Sprite::create("map/blackwhite_line.png");
				sceneryLayer->addChild(blackwhileLine, 2);
				blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
				blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, MapManager::getInstance()->_mapHeight - 16));
				//MessageBox(Value(MapManager::getInstance()->_mapHeight - 16 + 32 * i).asString().c_str(), "test");
			}
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/city_3.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
			sceneryLayer->addChild(unitSprite, 1);
			unitSprite->setAnchorPoint(Point(0, 0));
			unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
			MapManager::getInstance()->_mapHeight += unitSize.height;
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		{
			SpriteFrame * unitSpriteFrame = Sprite::create("map/city_2.png")->getSpriteFrame();
			auto unitSize = unitSpriteFrame->getTexture()->getContentSize();

			int unitNum = 5;
			int unitIndex;

			for (unitIndex = 0; unitIndex < unitNum; unitIndex++){
				auto unitSprite = Sprite::createWithSpriteFrame(unitSpriteFrame);
				sceneryLayer->addChild(unitSprite, 1);
				unitSprite->setAnchorPoint(Point(0, 0));
				unitSprite->setPosition(Point(0, MapManager::getInstance()->_mapHeight));
				MapManager::getInstance()->_mapHeight += unitSize.height;

			}
			MapManager::getInstance()->_mapWidth = MAX(MapManager::getInstance()->_mapWidth, unitSize.width);
		}

		int startLinePosY = MapManager::getInstance()->_mapHeight - DataManager::getInstance()->_staticData\
																.at("map").asValueMap()\
																.at("start_line_off_y").asInt();
		MapManager::getInstance()->_startLinePosY = startLinePosY;

		{
			auto startLine = Sprite::create("map/start_line.png");
			sceneryLayer->addChild(startLine, 2);
			startLine->setAnchorPoint(Point(0.5, 0.5));
			startLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, startLinePosY));

			auto blackwhileLine = Sprite::create("map/blackwhite_line.png");
			sceneryLayer->addChild(blackwhileLine, 2);
			blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
			blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, startLinePosY + 32));
		}

	
		int finishLinePosY = DataManager::getInstance()->_staticData\
			.at("map").asValueMap()\
			.at("finish_line_off_y").asInt();
		MapManager::getInstance()->_finishLinePosY = finishLinePosY;

		{
			auto finishLine = Sprite::create("map/finish_line.png");
			sceneryLayer->addChild(finishLine, 2);
			finishLine->setAnchorPoint(Point(0.5, 0.5));
			finishLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, finishLinePosY));
	    
			switch (GameManager::getInstance()->_gameMode){
			case (int)GameManager::GameMode::RANKING_MODE:
			case (int)GameManager::GameMode::SURVIVAL_MODE:{
				auto blackwhileLine = Sprite::create("map/blackwhite_line.png");
				sceneryLayer->addChild(blackwhileLine, 2);
				blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
				blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, finishLinePosY - 32));
			}break;
			case (int)GameManager::GameMode::ELIMINATION_MODE:{
				auto blackwhileLine = Sprite::create("map/champion_line.png");
				sceneryLayer->addChild(blackwhileLine, 2);
				blackwhileLine->setAnchorPoint(Point(0.5, 0.5));
				blackwhileLine->setPosition(Point(MapManager::getInstance()->_mapWidth / 2, finishLinePosY - 32));
			}break;
			
			}
		
		}

	}
	this->addChild(sceneryLayer,1);
	sceneryLayer->setAnchorPoint(Point(0, 0));
	sceneryLayer->setPosition(Point(0, 0));

	auto characterLayer = Layer::create();

	MapManager::getInstance()->_characterLayer = characterLayer;
	this->addChild(characterLayer, 2);

	/*characterLayer->setAnchorPoint(Point(0, 0));
	characterLayer->setPosition(Point(0, 0));*/

	return true;
}

void MapLayer::update(float dt)
{
	
}
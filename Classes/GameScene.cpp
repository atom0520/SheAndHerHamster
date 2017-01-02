#include "GameScene.h"
#include "MapLayer.h"
#include "GameLayer.h"
#include "HUDLayer.h"
#include "QuestionLayer.h"
#include "OperationLayer.h"

#include "MapManager.h"
#include "GameManager.h"
#include "HUDManager.h"
#include "QuestionManager.h"
#include "OperationManager.h"
#include "GameEffectManager.h"

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto gameScene = Scene::create();

	// 'layer' is an autorelease object
	auto mapLayer = MapLayer::create();
	mapLayer->setAnchorPoint(Point(0, 0));
	gameScene->addChild(mapLayer, 2);
	MapManager::getInstance()->_mapLayer = mapLayer;


	auto gameLayer = GameLayer::create();
	gameScene->addChild(gameLayer, 1);
	GameManager::getInstance()->_gameLayer = gameLayer;

	auto hudLayer = HUDLayer::create();
	gameScene->addChild(hudLayer, 3);
	HUDManager::getInstance()->_hudLayer = hudLayer;

	auto questionLayer = QuestionLayer::create();
	gameScene->addChild(questionLayer, 4);
	QuestionManager::getInstance()->_questionLayer = questionLayer;

	auto operationLayer = OperationLayer::create();
	gameScene->addChild(operationLayer, 5);
	OperationManager::getInstance()->_operationLayer = operationLayer;

	auto glEffectLayer = Layer::create();
	gameScene->addChild(glEffectLayer, 6);
	GameEffectManager::getInstance()->_glEffectLayer = glEffectLayer;

	return gameScene;
}
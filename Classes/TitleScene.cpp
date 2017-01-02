#include "TitleScene.h"
#include "TitleLayer.h"

Scene* TitleScene::createScene()
{
	auto titleScene = Scene::create();

	auto titleLayer = TitleLayer::create();

	titleScene->addChild(titleLayer, 1);

	return titleScene;
}
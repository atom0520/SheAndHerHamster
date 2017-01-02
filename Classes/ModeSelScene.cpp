#include "ModeSelScene.h"
#include "ModeSelLayer.h"

Scene* ModeSelScene::createScene()
{
	auto modeSelScene = Scene::create();

	auto  modeSelLayer = ModeSelLayer::create();

	modeSelScene->addChild(modeSelLayer, 1);

	return  modeSelScene;
}
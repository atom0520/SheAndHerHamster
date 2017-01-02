#include "HamsterSelScene.h"
#include "HamsterSelLayer.h"

Scene* HamsterSelScene::createScene()
{
	auto hamsterSelScene = Scene::create();

	auto  hamsterSelLayer= HamsterSelLayer::create();

	hamsterSelScene->addChild(hamsterSelLayer, 1);

	return  hamsterSelScene;
}
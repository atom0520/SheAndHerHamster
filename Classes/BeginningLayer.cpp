#include "BeginningLayer.h"
#include "TitleScene.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene*  BeginningLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = BeginningLayer::create();
	
	scene->addChild(layer, 1);

	return scene;
}

bool BeginningLayer::init(){
	if (!Layer::init())
	{
		return false;
	}	
	Sprite * wishSprite = Sprite::create("beginning/beginning_wish.png");
	//this->addChild(wishSprite, 1);
	wishSprite->setAnchorPoint(Point(0, 0));

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/title.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/button.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/mode_sel_scene.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/mode_guide_game_bgm.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/select_fixed.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/hamster_sel_scene.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/counter.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/cursor.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/horn.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/ready_go.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/mode_ranking_game_bgm.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/mode_elimination_game_bgm.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/good_f.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/good_m.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/cool_f.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/cool_m.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/perfect_f.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/perfect_m.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/mode_survival_game_bgm.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/error.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/win.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/lose.wav");
    /*
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_effect/game_effect_spriteframes_01.plist","game_effect/game_effect_spriteframes_01.pvr.ccz");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_effect/game_effect_spriteframes_02.plist", "game_effect/game_effect_spriteframes_02.pvr.ccz");*/

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_effect/game_effect_spriteframes.plist", "game_effect/game_effect_spriteframes.png");

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("character/character_spriteframes.plist","character/character_spriteframes.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hud/ranking/ranking_num_spriteframes.plist","hud/ranking/ranking_num_spriteframes.pvr.ccz");
    

	std::string fullPathForIELTSWordsData = FileUtils::getInstance()->fullPathForFilename("data/ielts_words_UTF-8.txt");

	std::string ieltsWordsDataStdStr = FileUtils::getInstance()->getStringFromFile(fullPathForIELTSWordsData);
		

	String * ieltsWordsDataCCStr = String::create(ieltsWordsDataStdStr);
	Array * ieltsWordsDataSet = ieltsWordsDataCCStr->componentsSeparatedByString("\n");
	
	for (unsigned int i = 0; i < ieltsWordsDataSet->count(); i++){
		String * wordDataStr = (String *)ieltsWordsDataSet->getObjectAtIndex(i);
		Array * wordDataSet = wordDataStr->componentsSeparatedByString("\t");
		/*std::string wordDataSubStdStr1 = ((String *)wordDataSet->getObjectAtIndex(1))->getCString();
		wordDataSubStdStr1.erase(wordDataSubStdStr1.size()-1);
		String * wordDataSubCCStr1 = String::create(wordDataSubStdStr1);*/

		std::string wordDataSubStdStr2 = ((String *)wordDataSet->getObjectAtIndex(2))->getCString();
		wordDataSubStdStr2.erase(wordDataSubStdStr2.size() - 1);
		String * wordDataSubCCStr2 = String::create(wordDataSubStdStr2);

		DataManager::getInstance()->_ieltsWords.push_back(DataManager::Word(i+1, \
			(String *)wordDataSet->getObjectAtIndex(1), \
			wordDataSubCCStr2));
	}

	this->scheduleUpdate();
	_counter = 0;
	return true;
}

void BeginningLayer::onEnter(){
	Layer::onEnter();


	
}

void BeginningLayer::onExit(){
	Layer::onExit();

	

}

void BeginningLayer::update(float dt){
	if (_counter > 50){
		//_counter = 0;
		Director::getInstance()->replaceScene(TransitionFade::create(2.0f, TitleScene::createScene()));
		this->unscheduleUpdate();
	}
	else{
		_counter++;
	}
	
}

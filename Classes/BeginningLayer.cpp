#include "BeginningLayer.h"
#include "TitleScene.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"
#include "Global.h"

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

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(TITLE_SCENE_BGM_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MODE_SEL_SCENE_BGM_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(HAMSTER_SEL_SCENE_BGM_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MODE_GUIDE_GAME_BGM_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MODE_RANKING_GAME_BGM_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MODE_ELIMINATION_GAME_BGM_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MODE_SURVIVAL_GAME_BGM_FILE_PATH);

	SimpleAudioEngine::getInstance()->preloadEffect(BUTTON_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(COUNTER_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(CURSOR_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(SELECT_FIXED_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(HORN_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(READY_GO_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(GOOD_FEMALE_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(GOOD_MALE_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(COOL_FEMALE_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(COOL_MALE_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(PERFECT_FEMALE_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(PERFECT_MALE_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(ERROR_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(WIN_EFFECT_FILE_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(LOSE_EFFECT_FILE_PATH);
    /*
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_effect/game_effect_spriteframes_01.plist","game_effect/game_effect_spriteframes_01.pvr.ccz");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_effect/game_effect_spriteframes_02.plist", "game_effect/game_effect_spriteframes_02.pvr.ccz");*/

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_effect/game_effect_spriteframes.plist", "game_effect/game_effect_spriteframes.png");

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("character/character_spriteframes.plist","character/character_spriteframes.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hud/ranking/ranking_num_spriteframes.plist","hud/ranking/ranking_num_spriteframes.pvr.ccz");
    

	std::string fullPathForIELTSWordsData = FileUtils::getInstance()->fullPathForFilename(IELTS_WORDS_FILE_PATH);

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
		//wordDataSubStdStr2.erase(wordDataSubStdStr2.size() - 1);
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

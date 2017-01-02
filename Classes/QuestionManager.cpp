#include "QuestionManager.h"
#include "DataManager.h"
#include "CharacterManager.h"
#include "InputManager.h"
#include "OperationManager.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

//声明静态变量
QuestionManager * QuestionManager::_instance = nullptr;

QuestionManager * QuestionManager::getInstance(){
	if (_instance == nullptr){
		_instance = new QuestionManager();
		_instance->init();
	}
	return _instance;
}

void QuestionManager::destroyInstance(){
	if (!_instance){
		return;
	}
	CC_SAFE_RELEASE_NULL(_instance->_questionPanelBgFrames[0]);
	CC_SAFE_RELEASE_NULL(_instance->_questionPanelBgFrames[1]);	

	delete _instance;
	_instance = nullptr;
}

bool QuestionManager::init(){
	
	_questionLayer=nullptr;
	_questionedWord=nullptr;
	
	_optionZText = nullptr;
	_optionXText = nullptr;
	_optionCText = nullptr;

	_optionZBtn = nullptr;
	_optionXBtn = nullptr;
	_optionCBtn = nullptr;

	_state = (int)State::PANEL_UNINIT;
	_currentKeyOptionTag = 0;
	_currentKeyWordId = 0;
	_currentQuestionReward = 20;
	_currentQuestionErrorPunishment = 20;
	_needResetQuestion = false;
	_isKeyOptionHighlighted = false;

	_questionNum = DataManager::getInstance()->getInstance()->_ieltsWords.size();
	
	_questionPanelBg = nullptr;

	_questionPanelBgFrames[0] = Sprite::create("question_panel/question_panel_bg_folded.png")->getSpriteFrame();
	_questionPanelBgFrames[0]->retain();
	_questionPanelBgFrames[1] = Sprite::create("question_panel/question_panel_bg_unfolded.png")->getSpriteFrame();
	_questionPanelBgFrames[1]->retain();

	_cdAfterError = 0;

	return true;
}

bool QuestionManager::initFoldedQuestionPanel(){
	auto winSize = Director::getInstance()->getWinSize();
	_questionPanelBg = Sprite::create();
	_questionLayer->addChild(_questionPanelBg, 1);
	_questionPanelBg->setAnchorPoint(Point(0.5, 1));
	_questionPanelBg->setPosition(Point(winSize.width / 2, winSize.height - 84));

	_questionPanelBg->setSpriteFrame(_questionPanelBgFrames[0]);

	_state = (int)State::PANEL_FOLDED;
	
	return true;
}

bool QuestionManager::initUnfoldedQuestionPanel(){
	
	auto winSize = Director::getInstance()->getWinSize();
	
	_questionPanelBg->setSpriteFrame(_questionPanelBgFrames[1]);

	_questionedWord = Label::create("", "Arial", 16);
	
	_questionedWord->setColor(Color3B(0, 0, 0));
	_questionPanelBg->addChild(_questionedWord, 1);
	_questionedWord->setAnchorPoint(Point(0, 0));
	_questionedWord->setPosition(Point(40, 146));

	auto optionMenu =Menu::create();
	
	_optionZBtn = MenuItemImage::create("question_panel/option_z_01.png",\
		"question_panel/option_z_02.png",\
		"question_panel/option_z_03.png",\
		CC_CALLBACK_1(QuestionManager::optionsCallback, this));

	_optionZBtn->setPosition(Point(34 + 18, 100 + 17));
	_optionZBtn->setAnchorPoint(Point(0.5, 0.5));
	_optionZBtn->setScale(31.0 / _optionZBtn->getContentSize().width);
	_optionZBtn->setTag(1);
	_optionZBtn->setEnabled(false);
	optionMenu->addChild(_optionZBtn, 1);

	_optionXBtn = MenuItemImage::create("question_panel/option_x_01.png",\
		"question_panel/option_x_02.png",\
		"question_panel/option_x_03.png",\
		CC_CALLBACK_1(QuestionManager::optionsCallback, this));


	optionMenu->addChild(_optionXBtn, 2);
	_optionXBtn->setPosition(Point(_optionZBtn->getPositionX(), _optionZBtn->getPositionY() - 40));
	_optionXBtn->setAnchorPoint(Point(0.5, 0.5));
	_optionXBtn->setScale(31.0 / _optionXBtn->getContentSize().width);
	_optionXBtn->setTag(2);
	_optionXBtn->setEnabled(false);

	_optionCBtn = MenuItemImage::create("question_panel/option_c_01.png",\
		"question_panel/option_c_02.png",\
		"question_panel/option_c_03.png",\
		CC_CALLBACK_1(QuestionManager::optionsCallback, this));
	//_optionCBtn = optionCBtn;

	optionMenu->addChild(_optionCBtn, 3);
	_optionCBtn->setPosition(Point(_optionZBtn->getPositionX(), _optionXBtn->getPositionY() - 40));
	_optionCBtn->setAnchorPoint(Point(0.5, 0.5));
	_optionCBtn->setScale(31.0 / _optionCBtn->getContentSize().width);
	_optionCBtn->setTag(3);
	_optionCBtn->setEnabled(false);

	_questionPanelBg->addChild(optionMenu, 1);

	optionMenu->setPosition(Point(0, 0));

	Label * optionZText = Label::create("", "Arial", 13);
	QuestionManager::getInstance()->_optionZText = optionZText;

	optionZText->setColor(Color3B(0, 0, 0));
	_questionPanelBg->addChild(optionZText, 1);
	optionZText->setAnchorPoint(Point(0, 1));
	optionZText->setPosition(Point(78, 133));
	_optionZText->setDimensions(215, 33);

	Label * optionXText = Label::create("", "Arial", 13);
	QuestionManager::getInstance()->_optionXText = optionXText;

	optionXText->setColor(Color3B(0, 0, 0));
	_questionPanelBg->addChild(optionXText, 1);
	optionXText->setAnchorPoint(Point(0, 1));
	optionXText->setPosition(Point(optionZText->getPositionX(), optionZText->getPositionY() - 40));
	_optionXText->setDimensions(215, 33);

	Label * optionCText = Label::create("", "Arial", 13);
	QuestionManager::getInstance()->_optionCText = optionCText;

	optionCText->setColor(Color3B(0, 0, 0));
	_questionPanelBg->addChild(optionCText, 1);
	optionCText->setAnchorPoint(Point(0, 1));
	optionCText->setPosition(Point(optionZText->getPositionX(), optionXText->getPositionY() - 40));
	_optionCText->setDimensions(215, 33);	

	_state = (int)State::NOTHING_ON_DISPLAY;
	return true;
}

void QuestionManager::update(){
	switch (_state){
	case (int)State::PANEL_UNINIT:{
		/*static int delay = 0;
		if (delay > 16){
			delay = 0;
			initFoldedQuestionPanel();
		}
		else{
			delay++;
		}*/
		break;
	}
	case (int)State::PANEL_FOLDED:{
		static int delay = 0;
		if (delay > 16){
			delay = 0;
			initUnfoldedQuestionPanel();
			//_needResetQuestion = true;
		}
		else{
			delay++;
		}
		break;
	}		
	case (int)State::NOTHING_ON_DISPLAY:
	{
        static int delay = 0;
		if (_needResetQuestion == true){
			if (delay > DISPLAY_QUESTION_DELAY_TIME){
				_needResetQuestion = false;
				delay = 0;
				resetQuestion();				
			}
			else{
				delay++;
			}
		}

	    break;
	}
	case (int)State::QUESTION_ON_DISPLAY:
		if (_cdAfterError > 0){
			_cdAfterError--;
			if (_cdAfterError == 0){
				_optionZBtn->setEnabled(true);
				_optionXBtn->setEnabled(true);
				_optionCBtn->setEnabled(true);
				OperationManager::getInstance()->_zBtn->setEnabled(true);
				OperationManager::getInstance()->_xBtn->setEnabled(true);
				OperationManager::getInstance()->_cBtn->setEnabled(true);
			}
		}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		else{

			if (InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_Z] >= (int)InputManager::KeyState::JUST_PRESSED\
				&& InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_X] <= (int)InputManager::KeyState::JUST_RELEASED\
				&& InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_C] <= (int)InputManager::KeyState::JUST_RELEASED){

				optionsCallback(OperationManager::getInstance()->_zBtn);
			}
			else if (InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_X] >= (int)InputManager::KeyState::JUST_PRESSED\
				&& InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_Z] <= (int)InputManager::KeyState::JUST_RELEASED\
				&& InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_C] <= (int)InputManager::KeyState::JUST_RELEASED){

				optionsCallback(OperationManager::getInstance()->_xBtn);
			}
			else if (InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_C] >= (int)InputManager::KeyState::LONG_PRESSED\

				&& InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_Z] <= (int)InputManager::KeyState::JUST_RELEASED\
				&& InputManager::getInstance()->_keyState[(int)InputManager::KeyCode::KEY_X] <= (int)InputManager::KeyState::JUST_RELEASED){

				optionsCallback(OperationManager::getInstance()->_cBtn);
			}
		}
#endif
		break;
	}
}

void QuestionManager::resetQuestion(){
	srand(time(nullptr));

	//随机抽取题号
	_currentKeyWordId = 1 + rand() % _questionNum;
	/*auto questionData = DataManager::getInstance()->_staticData\
		.at("question").asValueMap()\
		.at(Value(_currentQuestionId).asString().c_str()).asValueMap();*/
	
	//_questionedWord->setString(questionData.at("word").asString());
	_questionedWord->setString(DataManager::getInstance()->_ieltsWords[_currentKeyWordId - 1]._en->getCString());

	_currentKeyOptionTag = 1;

	int optionZTag = 1 + rand() % 3;
	_optionZBtn->setTag(optionZTag);

	int optionXTag;
	do{
		optionXTag = 1 + rand() % 3;

	} while (optionXTag == optionZTag);
	_optionXBtn->setTag(optionXTag);

	int optionCTag = 6 - optionZTag - optionXTag;
	_optionCBtn->setTag(optionCTag);

	if (optionZTag == _currentKeyOptionTag){
		_optionZText->setString(DataManager::getInstance()->_ieltsWords[_currentKeyWordId - 1]._ch->getCString());
		
		int optionXWordId;
		do{
			optionXWordId = 1 + rand() % _questionNum;

		} while (optionXWordId == _currentKeyWordId);
		_optionXText->setString(DataManager::getInstance()->_ieltsWords[optionXWordId - 1]._ch->getCString());

		int optionCWordId;
		do{
			optionCWordId = 1 + rand() % _questionNum;

		} while (optionCWordId == _currentKeyWordId || optionCWordId == optionXWordId);
		_optionCText->setString(DataManager::getInstance()->_ieltsWords[optionCWordId - 1]._ch->getCString());

	}else if (optionXTag == _currentKeyOptionTag){
		_optionXText->setString(DataManager::getInstance()->_ieltsWords[_currentKeyWordId - 1]._ch->getCString());

		int optionZWordId;
		do{
			optionZWordId = 1 + rand() % _questionNum;

		} while (optionZWordId == _currentKeyWordId);
		_optionZText->setString(DataManager::getInstance()->_ieltsWords[optionZWordId - 1]._ch->getCString());

		int optionCWordId;
		do{
			optionCWordId = 1 + rand() % _questionNum;

		} while (optionCWordId == _currentKeyWordId || optionCWordId == optionZWordId);
		_optionCText->setString(DataManager::getInstance()->_ieltsWords[optionCWordId - 1]._ch->getCString());
	}
	else if (optionCTag == _currentKeyOptionTag){
		_optionCText->setString(DataManager::getInstance()->_ieltsWords[_currentKeyWordId - 1]._ch->getCString());

		int optionZWordId;
		do{
			optionZWordId = 1 + rand() % _questionNum;

		} while (optionZWordId == _currentKeyWordId);
		_optionZText->setString(DataManager::getInstance()->_ieltsWords[optionZWordId - 1]._ch->getCString());

		int optionXWordId;
		do{
			optionXWordId = 1 + rand() % _questionNum;

		} while (optionXWordId == _currentKeyWordId || optionXWordId == optionZWordId);
		_optionXText->setString(DataManager::getInstance()->_ieltsWords[optionXWordId - 1]._ch->getCString());
	}

	_optionZBtn->setEnabled(true);
	_optionXBtn->setEnabled(true);
	_optionCBtn->setEnabled(true);
	OperationManager::getInstance()->_zBtn->setEnabled(true);
	OperationManager::getInstance()->_zBtn->setTag(_optionZBtn->getTag());
	OperationManager::getInstance()->_xBtn->setEnabled(true);
	OperationManager::getInstance()->_xBtn->setTag(_optionXBtn->getTag());
	OperationManager::getInstance()->_cBtn->setEnabled(true);
	OperationManager::getInstance()->_cBtn->setTag(_optionCBtn->getTag());

	_isKeyOptionHighlighted = false;

	_state = (int)State::QUESTION_ON_DISPLAY;
}

void QuestionManager::highlightKeyOption()
{
	if (_isKeyOptionHighlighted == true){
		return;
	}
	if (_optionZBtn->getTag() == _currentKeyOptionTag)
	{
			_optionZText->setColor(Color3B(255, 0, 0));
	}
	else if (_optionXBtn->getTag() == _currentKeyOptionTag)
	{
			_optionXText->setColor(Color3B(255, 0, 0));
	}
	else if (_optionCBtn->getTag() == _currentKeyOptionTag)
	{
			_optionCText->setColor(Color3B(255, 0, 0));
	}
	_isKeyOptionHighlighted = true;
}

void QuestionManager::clearQuestion(){
	if (_questionedWord != nullptr){
		_questionedWord->setString("");
	}
	
	if (_optionZText != nullptr){
		_optionZText->setString("");
		_optionZText->setColor(Color3B(0, 0, 0));
	}
	if (_optionXText != nullptr){
		_optionXText->setString("");
		_optionXText->setColor(Color3B(0, 0, 0));
	}
	if (_optionCText != nullptr){
		_optionCText->setString("");
		_optionCText->setColor(Color3B(0, 0, 0));
	}

	if (_optionZBtn != nullptr){
		_optionZBtn->setEnabled(false);
	}
	if (_optionXBtn != nullptr){
		_optionXBtn->setEnabled(false);
	}
	if (_optionCBtn != nullptr){
		_optionCBtn->setEnabled(false);
	}

	OperationManager::getInstance()->_zBtn->setEnabled(false);
	OperationManager::getInstance()->_xBtn->setEnabled(false);
	OperationManager::getInstance()->_cBtn->setEnabled(false);

	_isKeyOptionHighlighted = false;

	_state = (int)State::NOTHING_ON_DISPLAY;
}

void  QuestionManager::removeQuestionPanel(){
	clearQuestion();

	if (_questionedWord != nullptr){
		if (_questionedWord->getReferenceCount()>0){
			_questionedWord->removeFromParent();
			//_questionedWord->release();
			_questionedWord = nullptr;
		}
	}

	for (int i = 0; i<2; i++){
		if (_optionZText != nullptr){
			if (_optionZText->getReferenceCount()>0){
				_optionZText->removeFromParent();
				//_optionZText->release();
				_optionZText = nullptr;
			}
		}
		
		if (_optionXText != nullptr){
			if (_optionXText->getReferenceCount()>0){
				_optionXText->removeFromParent();
				//_optionXText->release();
				_optionXText = nullptr;
			}
		}
		
		if (_optionCText != nullptr){
			if (_optionCText->getReferenceCount()>0){
				_optionCText->removeFromParent();
				//_optionCText->release();
				_optionCText = nullptr;
			}
		}		
		
	}
	if (_optionZBtn != nullptr){
		if (_optionZBtn->getReferenceCount()>0){
			_optionZBtn->removeFromParent();
			//_optionZBtn->release();
			_optionZBtn = nullptr;
		}
	}
	
	if (_optionXBtn != nullptr){
		if (_optionXBtn->getReferenceCount() > 0){
			_optionXBtn->removeFromParent();
			//_optionXBtn->release();
			_optionXBtn = nullptr;
		}
	}
	if (_optionCBtn != nullptr){
		if (_optionCBtn->getReferenceCount() > 0){
			_optionCBtn->removeFromParent();
			//_optionCBtn->release();
			_optionCBtn = nullptr;
		}
	}

	if (_questionPanelBg != nullptr){
		if (_questionPanelBg->getReferenceCount()>0){
			_questionPanelBg->removeFromParent();
			
			_questionPanelBg = nullptr;
		}
	}
	

	_state = (int)State::PANEL_UNINIT;
}

void QuestionManager::optionsCallback(Ref* pSender)
{
	
	MenuItemImage * optionBtn = (MenuItemImage *)pSender;
	//MessageBox(Value(optionBtn->getTag()).asString().c_str(), "option No");

	if (optionBtn->getTag() == QuestionManager::getInstance()->_currentKeyOptionTag){
		
		((Hamster *)CharacterManager::getInstance()->_player)->_energy += _currentQuestionReward;
		QuestionManager::getInstance()->clearQuestion();
		QuestionManager::getInstance()->_needResetQuestion = true;
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		
	}
	else{
		
		((Hamster *)CharacterManager::getInstance()->_player)->_energy -= _currentQuestionErrorPunishment;
	
		_optionZBtn->setEnabled(false);
		_optionXBtn->setEnabled(false);
		_optionCBtn->setEnabled(false);
		OperationManager::getInstance()->_zBtn->setEnabled(false);
		OperationManager::getInstance()->_xBtn->setEnabled(false);
		OperationManager::getInstance()->_cBtn->setEnabled(false);

		_cdAfterError = CD_TIME_AFTER_ERROR;
		QuestionManager::getInstance()->highlightKeyOption();
		SimpleAudioEngine::getInstance()->playEffect("sound/error.wav");

	}
}
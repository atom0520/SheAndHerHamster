#ifndef QUESTION_MANAGER_H
#define QUESTION_MANAGER_H

#define DISPLAY_QUESTION_DELAY_TIME 5
#define CD_TIME_AFTER_ERROR 66

#include "cocos2d.h"
USING_NS_CC;

class QuestionManager : public Ref{
public:
	static QuestionManager * getInstance();
	static void destroyInstance();
	virtual bool init();
	virtual void update();
	virtual bool initFoldedQuestionPanel();
	virtual bool initUnfoldedQuestionPanel();

	virtual void resetQuestion();
	virtual void highlightKeyOption();
	virtual void clearQuestion();
	virtual void removeQuestionPanel();

	void optionsCallback(Ref* pSender);

	Layer * _questionLayer;
	Sprite * _questionPanelBg;
	SpriteFrame * _questionPanelBgFrames[2];
	Label * _questionedWord;

	Label * _optionZText;
	Label * _optionXText;
	Label * _optionCText;

	MenuItemImage *_optionZBtn;
	MenuItemImage *_optionXBtn;
	MenuItemImage *_optionCBtn;
	
	int _questionNum;

	int _state;
	int _currentKeyOptionTag;
	//int _currentQuestionId;
	int _currentKeyWordId;
	int _currentQuestionReward;
	int _currentQuestionErrorPunishment;

	bool _needResetQuestion;
	bool _isKeyOptionHighlighted;

	int _cdAfterError;

	enum class State{
		PANEL_UNINIT,
		PANEL_FOLDED,
		NOTHING_ON_DISPLAY,
		QUESTION_ON_DISPLAY,
	};
protected:
	static QuestionManager * _instance;
};

#endif
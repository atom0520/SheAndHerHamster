#ifndef CHARACTER_H
#define CHARACTER_H

#include "cocos2d.h"
using namespace cocos2d;

#define CHARACTER_DIRECTION_DOWN  1
#define CHARACTER_DIRECTION_LEFT  2
#define CHARACTER_DIRECTION_RIGHT 4
#define CHARACTER_DIRECTION_UP    8

class Character : public Sprite
{
public:
	Character();
	~Character();
	CREATE_FUNC(Character);

	static Character * create(int x, int y);
	virtual bool init();

	virtual void turnDown();
	virtual void turnLeft();
	virtual void turnRight();
	virtual void turnUp();

	virtual bool moveDown(bool isDirFixed = false);
	virtual bool moveLeft(bool isDirFixed = false);
	virtual bool moveRight(bool isDirFixed = false);
	virtual bool moveUp(bool isDirFixed = false);

	virtual void turnToward(Character* aim);
	virtual void turnAwayFrom(Character* aim);
	virtual void moveToward(Character* aim, bool isDirFixed = false);
	virtual void moveAwayFrom(Character* aim, bool isDirFixed = false);

	virtual void loadFramesFromDataFile(const char *framesDataKey);
	virtual void loadAllFrames();
	virtual void unloadAllFrames();

	virtual void loadAnimationFromDataFile(const char* animationDataKey);
	virtual void loadAllAnimations();
	virtual void unloadAllAnimations();

	virtual bool setCurrentAnimationId(int animationId);
	virtual bool setCurrentFrame(int animationId, int animationIndex);

	virtual void update();
	virtual void updateFrame();
	virtual void updateMove();
	virtual void updateAI();
	virtual bool isMoving();

	virtual bool canMove(int posX, int  posY, int direction);

	int _moveSpeed;

	enum class Type{
		HAMSTER,
		MASTER,
		PREDATOR,
	};

	int _id;
	int  _state;
protected:
	

	int _type;
	
	int _direction;

	std::map<int, SpriteFrame*> _frames;
	std::map<int, Point> _framesAnchorPoint;

	//ValueMap _animationsId;
	std::map<std::string, int > _animationsId;
	/*�˴���ʹ��std::map< const char *, int>���޷���Чͨ��const char*���͵�key�õ���Ӧ��value
	��Ϊ��ͬΪconst char *���͵������ִ����бȽ�ʱ��ʵ���ϱȽϵ����ִ���ָ�룬�����ִ�ʵ�ʵ�����
	�˴�Ӧ��ʹ��std::map<std::string, int > ���� ValueMap
	*/

	//ValueMap _animationsFrameIndexStart;
	std::map<std::string, int >  _animationsFrameIndexStart;
	std::map<int, int *> _animationFrameSequences;
	std::map<int, int *> _animationDurationSequences;

	int _currentAnimationId;
	int _currentAnimationIndex;
	int _animationCounter;

	int _currentFrameIndex;
	SpriteFrame * _currentFrame;
	
	int _moveTrigger;

	Point _destPosition;
};

#endif
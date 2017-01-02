#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "InputManager.h"

//声明静态变量
InputManager * InputManager::_instance = nullptr;

InputManager * InputManager::getInstance(){
	if (_instance == nullptr){
		_instance = new InputManager();
		_instance->init();
	}
	return _instance;
}

void InputManager::destroyInstance(){
	if (!_instance){
		return;
	}
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listenerKeyboard);
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listenerMouse);
	delete _instance;
	_instance = nullptr;
}

bool InputManager::init(){
	_listenerKeyboard = EventListenerKeyboard::create();
	_listenerMouse = EventListenerMouse::create();

	_listenerKeyboard->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	_listenerKeyboard->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);

	_listenerMouse->onMouseUp = CC_CALLBACK_1(InputManager::onMouseUp, this);
	_listenerMouse->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	_listenerMouse->onMouseMove = CC_CALLBACK_1(InputManager::onMouseMove, this);

	//让事件（消息）分发器把新生的监听器与本管理类绑定
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listenerKeyboard, 5);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listenerMouse, 5);

	return true;
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event){
	_isKeyPressed[(int)keyCode] = true;
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event){
	_isKeyPressed[(int)keyCode] = false;
}

void InputManager::onMouseUp(Event *event){
	_isKeyPressed[(int)InputManager::KeyCode::KEY_LEFT_MOUSE_BUTTON \
		+ ((EventMouse *)event)->getMouseButton()] = false;
}

void InputManager::onMouseDown(Event *event){
	
	_isKeyPressed[(int)InputManager::KeyCode::KEY_LEFT_MOUSE_BUTTON \
		+ ((EventMouse *)event)->getMouseButton()] = true;
}

void InputManager::onMouseMove(Event *event){
	/*MessageBox(Value(Director::getInstance()->getWinSize().height).asString().c_str(), "!winsize_height");
	MessageBox(Value(((EventMouse *)event)->getCursorY()).asString().c_str(), "!event_y");*/
	_mousePosition = Point(((EventMouse *)event)->getCursorX(),((EventMouse *)event)->getCursorY());
}

void InputManager::update(){
	
	for (int keyIndex = 0; keyIndex <= _keyCodeNum; keyIndex++){
		if (_isKeyPressed[keyIndex] == true){
			switch (_keyState[keyIndex]){
			case (int)KeyState::JUST_RELEASED:
			case (int)KeyState::LONG_RELEASED:
				_keyState[keyIndex] = (int)KeyState::JUST_PRESSED;
				break;
			case (int)KeyState::JUST_PRESSED:
				
					_keyState[keyIndex] = (int)KeyState::LONG_PRESSED;
				
				
				break;
			case (int)KeyState::LONG_PRESSED:
				break;

			}
		}
		else{
			switch (_keyState[keyIndex]){		
			case (int)KeyState::JUST_PRESSED:
			case (int)KeyState::LONG_PRESSED:

				_keyState[keyIndex] = (int)KeyState::JUST_RELEASED;
				break;
			case (int)KeyState::JUST_RELEASED:
				
					_keyState[keyIndex] = (int)KeyState::LONG_RELEASED;
				
				
				break;
			case (int)KeyState::LONG_RELEASED:
				break;
			}
		}
	}

}

#endif
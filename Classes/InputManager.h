#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define _IM_M_L 0x00 //������
#define _IM_M_M 0x01 //����м�
#define _IM_M_R 0x02 //����Ҽ�
#define _IM_K_A 0x03 //������ĸ��A
#define _IM_K_B 0x04 //������ĸ��B
#define _IM_K_C 0x05 //������ĸ��C
#define _IM_K_D 0x06 //������ĸ��D
#define _IM_K_E 0x07 //������ĸ��E
#define _IM_K_F 0x08 //������ĸ��F
#define _IM_K_G 0x09 //������ĸ��G
#define _IM_K_H 0x0A //������ĸ��H
#define _IM_K_I 0x0B //������ĸ��I
#define _IM_K_J 0x0C //������ĸ��J
#define _IM_K_K 0x0D //������ĸ��K
#define _IM_K_L 0x0E //������ĸ��L
#define _IM_K_M 0x0F //������ĸ��M
#define _IM_K_N 0x10 //������ĸ��N
#define _IM_K_O 0x11 //������ĸ��O
#define _IM_K_P 0x12 //������ĸ��P
#define _IM_K_Q 0x13 //������ĸ��Q
#define _IM_K_R 0x14 //������ĸ��R
#define _IM_K_S 0x15 //������ĸ��S
#define _IM_K_T 0x16 //������ĸ��T
#define _IM_K_U 0x17 //������ĸ��U
#define _IM_K_V 0x18 //������ĸ��V
#define _IM_K_W 0x19 //������ĸ��W
#define _IM_K_X 0x1A //������ĸ��X
#define _IM_K_Y 0x1B //������ĸ��Y
#define _IM_K_Z 0x1C //������ĸ��Z
#define _IM_K_0 0x1D //�������ּ�0
#define _IM_K_1 0x1E //�������ּ�1
#define _IM_K_2 0x1F //�������ּ�2
#define _IM_K_3 0x20 //�������ּ�3
#define _IM_K_4 0x21 //�������ּ�4
#define _IM_K_5 0x22 //�������ּ�5
#define _IM_K_6 0x23 //�������ּ�6
#define _IM_K_7 0x24 //�������ּ�7
#define _IM_K_8 0x25 //�������ּ�8
#define _IM_K_9 0x26 //�������ּ�9
#define _IM_K_F01 0x27 //���̼�F1
#define _IM_K_F02 0x28 //���̼�F2
#define _IM_K_F03 0x29 //���̼�F3
#define _IM_K_F04 0x2A //���̼�F4
#define _IM_K_F05 0x2B //���̼�F5
#define _IM_K_F06 0x2C //���̼�F6
#define _IM_K_F07 0x2D //���̼�F7
#define _IM_K_F08 0x2E //���̼�F8
#define _IM_K_F09 0x2F //���̼�F9
#define _IM_K_F10 0x30 //���̼�F10
#define _IM_K_F11 0x31 //���̼�F11
#define _GI_K_F12 0x32 //���̼�F12
#define _GI_K_ESC 0x33 //���̼�Esc
#define _GI_K_OEM_3 0x34 //���̼�~
#define _GI_K_OEM_MINUS 0x35 //���̼�_
#define _GI_K_OEM_PLUS 0x36 //���̼�+
#define _GI_K_OEM_5 0x37 //���̼�|
#define _GI_K_BACK 0x38 //���̼�Back Space
#define _GI_K_TAB 0x39 //���̼�Tab
#define _GI_K_OEM_4 0x3A //���̼�{
#define _GI_K_OEM_6 0x3B //���̼�}
#define _GI_K_RETURN 0x3C //���̼�Enter
#define _GI_K_CAPITAL_LOCK 0x3D //���̼�Caps Lock
#define _GI_K_OEM_1 0x3E //���̼�:
#define _GI_K_OEM_7 0x3F //���̼�"
#define _GI_K_L_SHIFT 0x40 //���̼���Shift
#define _GI_K_OEM_COMMA 0x41 //���̼�<
#define _GI_K_OEM_PERIOD 0x42 //���̼�>
#define _GI_K_OEM_2 0x43 //���̼�?
#define _GI_K_R_SHIFT 0x44 //���̼���Shift
#define _GI_K_L_CTRL 0x45 //���̼���Ctrl
#define _GI_K_L_ALT 0x46 //���̼���Alt
#define _GI_K_SPACE 0x47 //���̼�Spacebar
#define _GI_K_R_ALT 0x48 //���̼���Alt
#define _GI_K_R_CTRL 0x49 //���̼���Ctrl
#define _GI_K_PRINT_SCREEN 0x4A //���̼�Print Screen
#define _GI_K_SCROLL_LOCK 0x4B //���̼�Scroll Lock
#define _GI_K_INSERT 0x4C //���̼�Insert
#define _GI_K_HOME 0x4D //���̼�Home
#define _GI_K_PAGE_UP 0x4E //���̼�Page Up
#define _GI_K_DELETE 0x4F //���̼�Delete
#define _GI_K_END 0x50 //���̼�End
#define _GI_K_PAGE_DOWN 0x51 //���̼�Page Down
#define _GI_K_UP 0x52 //���̼���
#define _GI_K_DOWN 0x53 //���̼���
#define _GI_K_LEFT 0x54 //���̼���
#define _GI_K_RIGHT 0x55 //���̼���
#define _GI_NK_NUM_LOCK 0x56 //С���̼�Num Lock
#define _GI_NK_DIVIDE 0x57 //С���̼���
#define _GI_NK_MULTIPLY 0x58 //С���̼���
#define _GI_NK_ADD 0x59 //С���̼���
#define _GI_NK_SEPARATOR 0x5A //С���̼���
#define _GI_NK_RETURN _GI_K_RETURN //С���̼�Enter
#define _GI_NK_DECIMAL 0x5B //С���̼�С����
#define _GI_NK_0 0x5C //С���̼����ּ�0
#define _GI_NK_1 0x5D //С���̼����ּ�1
#define _GI_NK_2 0x5E //С���̼����ּ�2
#define _GI_NK_3 0x5F //С���̼����ּ�3
#define _GI_NK_4 0x60 //С���̼����ּ�4
#define _GI_NK_5 0x61 //С���̼����ּ�5
#define _GI_NK_6 0x62 //С���̼����ּ�6
#define _GI_NK_7 0x63 //С���̼����ּ�7
#define _GI_NK_8 0x64 //С���̼����ּ�8
#define _GI_NK_9 0x65 //С���̼����ּ�9

#define _GI_KEY_NUM (_GI_NK_9 + 1) //���̼�������

#include "cocos2d.h"
USING_NS_CC;

//�û�������Ϣ�Ĺ�����
class InputManager : public Ref{
public:
	enum class KeyState{
		LONG_RELEASED = 0,
		JUST_RELEASED,
		JUST_PRESSED,
		LONG_PRESSED,
		
	};

	const int _keyCodeNum = 169;

	enum class KeyCode
	{
		KEY_NONE = 0,
		KEY_PAUSE,
		KEY_SCROLL_LOCK,
		KEY_PRINT,
		KEY_SYSREQ,
		KEY_BREAK,
		KEY_ESCAPE,
		KEY_BACK = KEY_ESCAPE,
		KEY_BACKSPACE,
		KEY_TAB,
		KEY_BACK_TAB,
		KEY_RETURN,
		KEY_CAPS_LOCK,
		KEY_SHIFT,
		KEY_LEFT_SHIFT = KEY_SHIFT,
		KEY_RIGHT_SHIFT,
		KEY_CTRL,
		KEY_LEFT_CTRL = KEY_CTRL,
		KEY_RIGHT_CTRL,
		KEY_ALT,
		KEY_LEFT_ALT = KEY_ALT,
		KEY_RIGHT_ALT,
		KEY_MENU,
		KEY_HYPER,
		KEY_INSERT,
		KEY_HOME,
		KEY_PG_UP,
		KEY_DELETE,
		KEY_END,
		KEY_PG_DOWN,
		KEY_LEFT_ARROW,
		KEY_RIGHT_ARROW,
		KEY_UP_ARROW,
		KEY_DOWN_ARROW,
		KEY_NUM_LOCK,
		KEY_KP_PLUS,
		KEY_KP_MINUS,
		KEY_KP_MULTIPLY,
		KEY_KP_DIVIDE,
		KEY_KP_ENTER,
		KEY_KP_HOME,
		KEY_KP_UP,
		KEY_KP_PG_UP,
		KEY_KP_LEFT,
		KEY_KP_FIVE,
		KEY_KP_RIGHT,
		KEY_KP_END,
		KEY_KP_DOWN,
		KEY_KP_PG_DOWN,
		KEY_KP_INSERT,
		KEY_KP_DELETE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_SPACE,
		KEY_EXCLAM,
		KEY_QUOTE,
		KEY_NUMBER,
		KEY_DOLLAR,
		KEY_PERCENT,
		KEY_CIRCUMFLEX,
		KEY_AMPERSAND,
		KEY_APOSTROPHE,
		KEY_LEFT_PARENTHESIS,
		KEY_RIGHT_PARENTHESIS,
		KEY_ASTERISK,
		KEY_PLUS,
		KEY_COMMA,
		KEY_MINUS,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_COLON,
		KEY_SEMICOLON,
		KEY_LESS_THAN,
		KEY_EQUAL,
		KEY_GREATER_THAN,
		KEY_QUESTION,
		KEY_AT,
		KEY_CAPITAL_A,
		KEY_CAPITAL_B,
		KEY_CAPITAL_C,
		KEY_CAPITAL_D,
		KEY_CAPITAL_E,
		KEY_CAPITAL_F,
		KEY_CAPITAL_G,
		KEY_CAPITAL_H,
		KEY_CAPITAL_I,
		KEY_CAPITAL_J,
		KEY_CAPITAL_K,
		KEY_CAPITAL_L,
		KEY_CAPITAL_M,
		KEY_CAPITAL_N,
		KEY_CAPITAL_O,
		KEY_CAPITAL_P,
		KEY_CAPITAL_Q,
		KEY_CAPITAL_R,
		KEY_CAPITAL_S,
		KEY_CAPITAL_T,
		KEY_CAPITAL_U,
		KEY_CAPITAL_V,
		KEY_CAPITAL_W,
		KEY_CAPITAL_X,
		KEY_CAPITAL_Y,
		KEY_CAPITAL_Z,
		KEY_LEFT_BRACKET,
		KEY_BACK_SLASH,
		KEY_RIGHT_BRACKET,
		KEY_UNDERSCORE,
		KEY_GRAVE,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_LEFT_BRACE,
		KEY_BAR,
		KEY_RIGHT_BRACE,
		KEY_TILDE,
		KEY_EURO,
		KEY_POUND,
		KEY_YEN,
		KEY_MIDDLE_DOT,
		KEY_SEARCH,
		KEY_DPAD_LEFT,
		KEY_DPAD_RIGHT,
		KEY_DPAD_UP,
		KEY_DPAD_DOWN,
		KEY_DPAD_CENTER,
		KEY_ENTER,
		KEY_PLAY = 165,
		KEY_LEFT_MOUSE_BUTTON,
		KEY_RIGHT_MOUSE_BUTTON,
		KEY_MIDDLE_MOUSE_BUTTON = 168,
	};

	static InputManager * getInstance();
	void destroyInstance();
	virtual bool init();
	virtual void update();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
	void onMouseUp(Event *event);
	void onMouseDown(Event *event);
	void onMouseMove(Event *event);

	EventListenerKeyboard * _listenerKeyboard;
	EventListenerMouse * _listenerMouse;
	
	std::map<int, bool> _isKeyPressed;
	std::map<int, int>  _keyState;
	Point _mousePosition;

protected:
	static InputManager * _instance;
};

#endif

#endif
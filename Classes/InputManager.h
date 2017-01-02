#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define _IM_M_L 0x00 //Êó±ê×ó¼ü
#define _IM_M_M 0x01 //Êó±êÖĞ¼ü
#define _IM_M_R 0x02 //Êó±êÓÒ¼ü
#define _IM_K_A 0x03 //¼üÅÌ×ÖÄ¸¼üA
#define _IM_K_B 0x04 //¼üÅÌ×ÖÄ¸¼üB
#define _IM_K_C 0x05 //¼üÅÌ×ÖÄ¸¼üC
#define _IM_K_D 0x06 //¼üÅÌ×ÖÄ¸¼üD
#define _IM_K_E 0x07 //¼üÅÌ×ÖÄ¸¼üE
#define _IM_K_F 0x08 //¼üÅÌ×ÖÄ¸¼üF
#define _IM_K_G 0x09 //¼üÅÌ×ÖÄ¸¼üG
#define _IM_K_H 0x0A //¼üÅÌ×ÖÄ¸¼üH
#define _IM_K_I 0x0B //¼üÅÌ×ÖÄ¸¼üI
#define _IM_K_J 0x0C //¼üÅÌ×ÖÄ¸¼üJ
#define _IM_K_K 0x0D //¼üÅÌ×ÖÄ¸¼üK
#define _IM_K_L 0x0E //¼üÅÌ×ÖÄ¸¼üL
#define _IM_K_M 0x0F //¼üÅÌ×ÖÄ¸¼üM
#define _IM_K_N 0x10 //¼üÅÌ×ÖÄ¸¼üN
#define _IM_K_O 0x11 //¼üÅÌ×ÖÄ¸¼üO
#define _IM_K_P 0x12 //¼üÅÌ×ÖÄ¸¼üP
#define _IM_K_Q 0x13 //¼üÅÌ×ÖÄ¸¼üQ
#define _IM_K_R 0x14 //¼üÅÌ×ÖÄ¸¼üR
#define _IM_K_S 0x15 //¼üÅÌ×ÖÄ¸¼üS
#define _IM_K_T 0x16 //¼üÅÌ×ÖÄ¸¼üT
#define _IM_K_U 0x17 //¼üÅÌ×ÖÄ¸¼üU
#define _IM_K_V 0x18 //¼üÅÌ×ÖÄ¸¼üV
#define _IM_K_W 0x19 //¼üÅÌ×ÖÄ¸¼üW
#define _IM_K_X 0x1A //¼üÅÌ×ÖÄ¸¼üX
#define _IM_K_Y 0x1B //¼üÅÌ×ÖÄ¸¼üY
#define _IM_K_Z 0x1C //¼üÅÌ×ÖÄ¸¼üZ
#define _IM_K_0 0x1D //¼üÅÌÊı×Ö¼ü0
#define _IM_K_1 0x1E //¼üÅÌÊı×Ö¼ü1
#define _IM_K_2 0x1F //¼üÅÌÊı×Ö¼ü2
#define _IM_K_3 0x20 //¼üÅÌÊı×Ö¼ü3
#define _IM_K_4 0x21 //¼üÅÌÊı×Ö¼ü4
#define _IM_K_5 0x22 //¼üÅÌÊı×Ö¼ü5
#define _IM_K_6 0x23 //¼üÅÌÊı×Ö¼ü6
#define _IM_K_7 0x24 //¼üÅÌÊı×Ö¼ü7
#define _IM_K_8 0x25 //¼üÅÌÊı×Ö¼ü8
#define _IM_K_9 0x26 //¼üÅÌÊı×Ö¼ü9
#define _IM_K_F01 0x27 //¼üÅÌ¼üF1
#define _IM_K_F02 0x28 //¼üÅÌ¼üF2
#define _IM_K_F03 0x29 //¼üÅÌ¼üF3
#define _IM_K_F04 0x2A //¼üÅÌ¼üF4
#define _IM_K_F05 0x2B //¼üÅÌ¼üF5
#define _IM_K_F06 0x2C //¼üÅÌ¼üF6
#define _IM_K_F07 0x2D //¼üÅÌ¼üF7
#define _IM_K_F08 0x2E //¼üÅÌ¼üF8
#define _IM_K_F09 0x2F //¼üÅÌ¼üF9
#define _IM_K_F10 0x30 //¼üÅÌ¼üF10
#define _IM_K_F11 0x31 //¼üÅÌ¼üF11
#define _GI_K_F12 0x32 //¼üÅÌ¼üF12
#define _GI_K_ESC 0x33 //¼üÅÌ¼üEsc
#define _GI_K_OEM_3 0x34 //¼üÅÌ¼ü~
#define _GI_K_OEM_MINUS 0x35 //¼üÅÌ¼ü_
#define _GI_K_OEM_PLUS 0x36 //¼üÅÌ¼ü+
#define _GI_K_OEM_5 0x37 //¼üÅÌ¼ü|
#define _GI_K_BACK 0x38 //¼üÅÌ¼üBack Space
#define _GI_K_TAB 0x39 //¼üÅÌ¼üTab
#define _GI_K_OEM_4 0x3A //¼üÅÌ¼ü{
#define _GI_K_OEM_6 0x3B //¼üÅÌ¼ü}
#define _GI_K_RETURN 0x3C //¼üÅÌ¼üEnter
#define _GI_K_CAPITAL_LOCK 0x3D //¼üÅÌ¼üCaps Lock
#define _GI_K_OEM_1 0x3E //¼üÅÌ¼ü:
#define _GI_K_OEM_7 0x3F //¼üÅÌ¼ü"
#define _GI_K_L_SHIFT 0x40 //¼üÅÌ¼ü×óShift
#define _GI_K_OEM_COMMA 0x41 //¼üÅÌ¼ü<
#define _GI_K_OEM_PERIOD 0x42 //¼üÅÌ¼ü>
#define _GI_K_OEM_2 0x43 //¼üÅÌ¼ü?
#define _GI_K_R_SHIFT 0x44 //¼üÅÌ¼üÓÒShift
#define _GI_K_L_CTRL 0x45 //¼üÅÌ¼ü×óCtrl
#define _GI_K_L_ALT 0x46 //¼üÅÌ¼ü×óAlt
#define _GI_K_SPACE 0x47 //¼üÅÌ¼üSpacebar
#define _GI_K_R_ALT 0x48 //¼üÅÌ¼üÓÒAlt
#define _GI_K_R_CTRL 0x49 //¼üÅÌ¼üÓÒCtrl
#define _GI_K_PRINT_SCREEN 0x4A //¼üÅÌ¼üPrint Screen
#define _GI_K_SCROLL_LOCK 0x4B //¼üÅÌ¼üScroll Lock
#define _GI_K_INSERT 0x4C //¼üÅÌ¼üInsert
#define _GI_K_HOME 0x4D //¼üÅÌ¼üHome
#define _GI_K_PAGE_UP 0x4E //¼üÅÌ¼üPage Up
#define _GI_K_DELETE 0x4F //¼üÅÌ¼üDelete
#define _GI_K_END 0x50 //¼üÅÌ¼üEnd
#define _GI_K_PAGE_DOWN 0x51 //¼üÅÌ¼üPage Down
#define _GI_K_UP 0x52 //¼üÅÌ¼ü¡ü
#define _GI_K_DOWN 0x53 //¼üÅÌ¼ü¡ı
#define _GI_K_LEFT 0x54 //¼üÅÌ¼ü¡û
#define _GI_K_RIGHT 0x55 //¼üÅÌ¼ü¡ú
#define _GI_NK_NUM_LOCK 0x56 //Ğ¡¼üÅÌ¼üNum Lock
#define _GI_NK_DIVIDE 0x57 //Ğ¡¼üÅÌ¼ü³ı
#define _GI_NK_MULTIPLY 0x58 //Ğ¡¼üÅÌ¼ü³Ë
#define _GI_NK_ADD 0x59 //Ğ¡¼üÅÌ¼ü¼Ó
#define _GI_NK_SEPARATOR 0x5A //Ğ¡¼üÅÌ¼ü¼õ
#define _GI_NK_RETURN _GI_K_RETURN //Ğ¡¼üÅÌ¼üEnter
#define _GI_NK_DECIMAL 0x5B //Ğ¡¼üÅÌ¼üĞ¡Êıµã
#define _GI_NK_0 0x5C //Ğ¡¼üÅÌ¼üÊı×Ö¼ü0
#define _GI_NK_1 0x5D //Ğ¡¼üÅÌ¼üÊı×Ö¼ü1
#define _GI_NK_2 0x5E //Ğ¡¼üÅÌ¼üÊı×Ö¼ü2
#define _GI_NK_3 0x5F //Ğ¡¼üÅÌ¼üÊı×Ö¼ü3
#define _GI_NK_4 0x60 //Ğ¡¼üÅÌ¼üÊı×Ö¼ü4
#define _GI_NK_5 0x61 //Ğ¡¼üÅÌ¼üÊı×Ö¼ü5
#define _GI_NK_6 0x62 //Ğ¡¼üÅÌ¼üÊı×Ö¼ü6
#define _GI_NK_7 0x63 //Ğ¡¼üÅÌ¼üÊı×Ö¼ü7
#define _GI_NK_8 0x64 //Ğ¡¼üÅÌ¼üÊı×Ö¼ü8
#define _GI_NK_9 0x65 //Ğ¡¼üÅÌ¼üÊı×Ö¼ü9

#define _GI_KEY_NUM (_GI_NK_9 + 1) //¼üÅÌ¼üµÄ×ÜÊı

#include "cocos2d.h"
USING_NS_CC;

//ÓÃ»§ÊäÈëĞÅÏ¢µÄ¹ÜÀíÀà
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
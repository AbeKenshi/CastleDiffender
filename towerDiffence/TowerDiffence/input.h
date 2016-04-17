//==========================================================
/// @file
/// @brief    Inputクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _INPUT_H                // このファイルが複数の箇所でインクルードされる場合に、 
#define _INPUT_H                // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

class Input;

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "gameError.h"


// for high-definition mouse
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//--------------------------

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;     // size of key arrays

										// what values for clear(), bit flag
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

const short GAMEPAD_THUMBSTICK_DEADZONE = (short)(0.20f * 0X7FFF);    // デッドゾーンとして範囲の20%をデフォルトとする
const short GAMEPAD_TRIGGER_DEADZONE = 20;                      // トリガーの範囲は0から255まで
const DWORD MAX_CONTROLLERS = 4;                                // Maximum number of controllers supported by XInput

																// Bit corresponding to gamepad button in state.Gamepad.wButtons
const DWORD GAMEPAD_DPAD_UP = 0x0001;
const DWORD GAMEPAD_DPAD_DOWN = 0x0002;
const DWORD GAMEPAD_DPAD_LEFT = 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT = 0x0008;
const DWORD GAMEPAD_START_BUTTON = 0x0010;
const DWORD GAMEPAD_BACK_BUTTON = 0x0020;
const DWORD GAMEPAD_LEFT_THUMB = 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB = 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER = 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER = 0x0200;
const DWORD GAMEPAD_A = 0x1000;
const DWORD GAMEPAD_B = 0x2000;
const DWORD GAMEPAD_X = 0x4000;
const DWORD GAMEPAD_Y = 0x8000;

struct ControllerState
{
	XINPUT_STATE        state;
	XINPUT_VIBRATION    vibration;
	float               vibrateTimeLeft;    // mSec
	float               vibrateTimeRight;   // mSec
	bool                connected;
};

class Input
{
private:
	// 指定のキーが押されている状態の場合にtrue
	bool keysDown[inputNS::KEYS_ARRAY_LEN];
	// 指定のキーが押された場合にtrue
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];
	std::string textIn;                         // ユーザーが入力したテキスト
	char charIn;                                // 最後に入力された文字
	bool newLine;                               // 新しい行の開始時にtrue
	int  mouseX, mouseY;                        // マウスの画面座標
	int  mouseRawX, mouseRawY;                  // 高精細マウスのデータ
	int  mouseWheel;                            // 
	RAWINPUTDEVICE Rid[1];                      // 高精細マウス用
	bool mouseCaptured;                         // マウスがキャプチャされている場合にtrue
	bool mouseLButton;                          // 左マウスボタンが押されている場合にtrue
	bool mouseMButton;                          // 中央マウスボタンが押されている場合にtrue
	bool mouseRButton;                          // 右マウスボタンが押されている場合にtrue
	bool mouseX1Button;                         // X1マウスボタンが押されている場合にtrue
	bool mouseX2Button;                         // X2マウスボタンが押されている場合にtrue
	ControllerState controllers[MAX_CONTROLLERS];    // コントローラーの状態
	short thumbstickDeadzone;
	short triggerDeadzone;

public:
	// Constructor
	Input();

	// Destructor
	virtual ~Input();

	// Initialize mouse and controller input.
	// Throws GameError
	// Pre: hwnd = window handle
	//      capture = true to capture mouse.
	void initialize(HWND hwnd, bool capture);

	// Save key down state
	void keyDown(WPARAM);

	// Save key up state
	void keyUp(WPARAM);

	// Save the char just entered in textIn string
	void keyIn(WPARAM);

	// Returns true if the specified VIRTUAL KEY is down, otherwise false.
	bool isKeyDown(UCHAR vkey) const;

	// Return true if the specified VIRTUAL KEY has been pressed in the most recent frame.
	// Key presses are erased at the end of each frame.
	bool wasKeyPressed(UCHAR vkey) const;

	// Return true if any key was pressed in the most recent frame.
	// Key presses are erased at the end of each frame.
	bool anyKeyPressed() const;

	// Clear the specified key press
	void clearKeyPress(UCHAR vkey);

	// Clear specified input buffers where what is any combination of
	// KEYS_DOWN, KEYS_PRESSED, MOUSE, TEXT_IN or KEYS_MOUSE_TEXT.
	// Use OR '|' operator to combine parameters.
	void clear(UCHAR what);

	// キー、マウス、テキスト入力バッファをクリア
	void clearAll() { clear(inputNS::KEYS_MOUSE_TEXT); }

	// テキスト入力バッファをクリア
	void clearTextIn() { textIn.clear(); }

	// Clear last character entered
	void clearCharIn() { charIn = 0; }

	// Return text input as a string
	std::string getTextIn() { return textIn; }

	// Set text input string
	void setTextIn(std::string str) { textIn = str; }

	// Return last character entered
	char getCharIn() { return charIn; }

	// Reads mouse screen position into mouseX, mouseY
	void mouseIn(LPARAM);

	// Reads raw mouse data into mouseRawX, mouseRawY
	// This routine is compatible with a high-definition mouse
	void mouseRawIn(LPARAM);

	// Reads mouse wheel movement.
	void mouseWheelIn(WPARAM);

	// 左マウスボタンの状態を保存
	void setMouseLButton(bool b) { mouseLButton = b; }

	// 中央マウスボタンの状態を保存
	void setMouseMButton(bool b) { mouseMButton = b; }

	// 右マウスボタンの状態を保存
	void setMouseRButton(bool b) { mouseRButton = b; }

	// X1、X2マウスボタンの状態を保存
	void setMouseXButton(WPARAM wParam) {
		mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}

	// マウスのX位置を戻す
	int  getMouseX()        const { return mouseX; }

	// マウスのY位置を戻す
	int  getMouseY()        const { return mouseY; }

	// マウスのX位置の移動のローデータを戻す。左への移動は<0、右への移動は>0
	// 高精細マウスに対応
	int  getMouseRawX()
	{
		int rawX = mouseRawX;
		mouseRawX = 0;
		return rawX;
	}

	// マウスのY位置の移動のローデータを戻す。上への移動は<0、下への移動は>0
	// 高精細マウスに対応
	int  getMouseRawY()
	{
		int rawY = mouseRawY;
		mouseRawY = 0;
		return rawY;
	}

	// Return mouse wheel movement relative to previous position.
	// Forward is >0, Backward is <0, movement is in multiples of WHEEL_DATA (120).
	int  getMouseWheel()
	{
		int wheel = mouseWheel;
		mouseWheel = 0;
		return wheel;
	}

	// 左マウスボタンの状態を戻す
	bool getMouseLButton()  const { return mouseLButton; }

	// 中央マウスボタンの状態を戻す
	bool getMouseMButton()  const { return mouseMButton; }

	// 右マウスボタンの状態を戻す
	bool getMouseRButton()  const { return mouseRButton; }

	// X1マウスボタンの状態を戻す
	bool getMouseX1Button() const { return mouseX1Button; }

	// X2マウスボタンの状態を戻す
	bool getMouseX2Button() const { return mouseX2Button; }

	// Update connection status of game controllers.
	void checkControllers();

	// Save input from connected game controllers.
	void readControllers();

	// Set thumbstick deadzone
	void setThumbstickDeadzone(short dz) { thumbstickDeadzone = abs(dz); }

	// Set trigger deadzone
	void setTriggerDeadzone(BYTE dz) { triggerDeadzone = dz; }

	// Get thumbstick deadzone
	short getThumbstickDeadzone() { return thumbstickDeadzone; }

	// Get trigger deadzone
	BYTE getTriggerDeadzone() { return static_cast<BYTE>(triggerDeadzone); }

	// 指定のゲームコントローラーの状態を戻す
	const ControllerState* getControllerState(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return &controllers[n];
	}

	// Return connection state of specified game controller
	bool getGamepadConnected(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].connected;
	}

	// コントローラーnのボタンの状態を戻す
	const WORD getGamepadButtons(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.wButtons;
	}

	// コントローラーnの方向パッド上の状態を戻す
	bool getGamepadDPadUp(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_UP) != 0);
	}

	// コントローラーnの方向パッド下の状態を戻す
	bool getGamepadDPadDown(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_DOWN) != 0);
	}

	// コントローラーnの方向パッド左の状態を戻す
	bool getGamepadDPadLeft(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_LEFT) != 0);
	}

	// コントローラーnの方向パッド右の状態を戻す
	bool getGamepadDPadRight(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_RIGHT) != 0);
	}

	// コントローラーnのSTARTボタンの状態を戻す
	bool getGamepadStart(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_START_BUTTON) != 0);
	}

	// コントローラーnのBACKボタンの状態を戻す
	bool getGamepadBack(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_BACK_BUTTON) != 0);
	}

	// コントローラーnの左サムボタンの状態を戻す
	bool getGamepadLeftThumb(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_THUMB) != 0);
	}

	// コントローラーnの右サムボタンの状態を戻す
	bool getGamepadRightThumb(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_THUMB) != 0);
	}

	// コントローラーnの左ショルダーボタンの状態を戻す
	bool getGamepadLeftShoulder(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_SHOULDER) != 0);
	}

	// コントローラーnの右ショルダーボタンの状態を戻す
	bool getGamepadRightShoulder(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_SHOULDER) != 0);
	}

	// コントローラーnのAボタンの状態を戻す
	bool getGamepadA(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_A) != 0);
	}

	// コントローラーnのBボタンの状態を戻す
	bool getGamepadB(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_B) != 0);
	}

	// コントローラーnのXボタンの状態を戻す
	bool getGamepadX(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_X) != 0);
	}

	// コントローラーnのYボタンの状態を戻す
	bool getGamepadY(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_Y) != 0);
	}

	// コントローラーnの左トリガーの値を戻します。
	BYTE getGamepadLeftTrigger(UINT n);

	// Return value of controller n Left Trigger (0 through 255).
	// Deadzone is not applied.
	BYTE getGamepadLeftTriggerUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.bLeftTrigger;
	}

	// コントローラーnの右トリガーの値を戻します。
	BYTE getGamepadRightTrigger(UINT n);

	// Return value of controller n Right Trigger (0 through 255).
	// Deadzone is not applied.
	BYTE getGamepadRightTriggerUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.bRightTrigger;
	}

	// コントローラーnの左サムスティック、Xの値を戻します。
	SHORT getGamepadThumbLX(UINT n);

	// Return value of controller n Left Thumbstick X (-32767 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbLXUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.sThumbLX;
	}

	// コントローラーnの左サムスティック、Yの値を戻します。
	SHORT getGamepadThumbLY(UINT n);

	// Return value of controller n Left Thumbstick Y (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbLYUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.sThumbLY;
	}

	// コントローラーnの右サムスティック、Xの値を戻します。
	SHORT getGamepadThumbRX(UINT n);

	// Return value of controller n Right Thumbstick X (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbRXUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)   // if invalid controller number
			n = MAX_CONTROLLERS - 1;    // force valid
		return controllers[n].state.Gamepad.sThumbRX;
	}

	// コントローラーnの右サムスティック、Yの値を戻します。
	SHORT getGamepadThumbRY(UINT n);

	// Return value of controller n Right Thumbstick Y (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbRYUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return controllers[n].state.Gamepad.sThumbRY;
	}

	// コントローラーnの左モーターを振動させる
	// 左は低周波振動
	// speed：0=オフ、65536=100パーセント
	// sec：振動させる時間（秒）
	void gamePadVibrateLeft(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		controllers[n].vibration.wLeftMotorSpeed = speed;
		controllers[n].vibrateTimeLeft = sec;
	}

	// コントローラーnの右モーターを振動させる
	// 左は低周波振動
	// speed：0=オフ、65536=100パーセント
	// sec：振動させる時間（秒）
	void gamePadVibrateRight(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		controllers[n].vibration.wRightMotorSpeed = speed;
		controllers[n].vibrateTimeRight = sec;
	}

	// 接続されているコントローラーを振動させる
	void vibrateControllers(float frameTime);
};

#endif


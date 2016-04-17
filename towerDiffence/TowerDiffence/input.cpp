//==========================================================
/// @file
/// @brief    input.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "input.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
Input::Input()
{
	// キーが押されている状態を示す配列をクリア
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysDown[i] = false;
	// キーが押されたことを示す配列をクリア
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysPressed[i] = false;
	newLine = true;                     // 新しい行をクリア
	textIn = "";                        // textInをクリア
	charIn = 0;                         // charInをクリア

	// マウスデータ
	mouseX = 0;                         // 画面X
	mouseY = 0;                         // 画面Y
	mouseRawX = 0;                      // 高精細X
	mouseRawY = 0;                      // 高精細Y
	mouseWheel = 0;                     // mouse wheel position
	mouseLButton = false;               // 左マウスボタンが押されている場合にtrue
	mouseMButton = false;               // 中央マウスボタンが押されている場合にtrue
	mouseRButton = false;               // 右マウスボタンが押されている場合にtrue
	mouseX1Button = false;              // X1マウスボタンが押されている場合にtrue
	mouseX2Button = false;              // X2マウスボタンが押されている場合にtrue

	for (int i = 0; i<MAX_CONTROLLERS; i++)
	{
		controllers[i].vibrateTimeLeft = 0;
		controllers[i].vibrateTimeRight = 0;
	}
	thumbstickDeadzone = GAMEPAD_THUMBSTICK_DEADZONE;    // default
	triggerDeadzone = GAMEPAD_TRIGGER_DEADZONE;          // default
}

//=============================================================================
// デストラクタ
//=============================================================================
Input::~Input()
{
	if (mouseCaptured)
		ReleaseCapture();               // マウスを解放
}

//=============================================================================
// マウスとコントローラーの入力を初期化
// マウスをキャプチャする場合、capture=trueを設定
// GameErrorをスロー
//=============================================================================
void Input::initialize(HWND hwnd, bool capture)
{
	try {
		mouseCaptured = capture;

		// 高精細マウスを登録
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = hwnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

		if (mouseCaptured)
			SetCapture(hwnd);           // マウスをキャプチャ

		// コントローラーの状態をクリア
		ZeroMemory(controllers, sizeof(ControllerState) * MAX_CONTROLLERS);

		checkControllers();             // 接続されているコントローラーをチェック
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
	}
}

//=============================================================================
// このキーについて、keysDown配列とkeyPressed配列にtrueを設定
// 実行前：wParamに、仮想キーコード（0~255）が格納されている
//=============================================================================
void Input::keyDown(WPARAM wParam)
{
	// キーコードが、バッファ範囲内にあることを確認
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		keysDown[wParam] = true;    // keysDown配列を更新
		// キーが既に押されていた、clear()で消去されていた
		keysPressed[wParam] = true; // keysPressed配列を更新
	}
}

//=============================================================================
// このキーについて、keysDown配列にfalseを設定
// 実行前：wParamに、仮想キーコード（0~255）が格納されている
//=============================================================================
void Input::keyUp(WPARAM wParam)
{
	// キーコードが、バッファ範囲内にあることを確認
	if (wParam < inputNS::KEYS_ARRAY_LEN)
		// 状態テーブルを更新
		keysDown[wParam] = false;
}

//=============================================================================
// 入力された文字をtextIn文字列に保存
// 実行前：wParamに、文字が格納されている
//=============================================================================
void Input::keyIn(WPARAM wParam)
{
	if (newLine)                            // 新しい行の開始の場合
	{
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')                     // バックスペースキーの場合
	{
		if (textIn.length() > 0)             // 文字が存在する場合
			textIn.erase(textIn.size() - 1);  // 最後に入力された文字を消去
	}
	else
	{
		textIn += wParam;                   // 文字をtextInに追加
		charIn = wParam;                    // 最後の入力された文字を保存
	}

	if ((char)wParam == '\r')               // リターンキーの場合
		newLine = true;                     // 新しい行を開始
}

//=============================================================================
// 指定された仮想キーが押されている場合はtrue、それ以外の場合はfalseを戻す
//=============================================================================
bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	else
		return false;
}

//=============================================================================
// 直近フレームにおいて、指定の仮想キーが押されたことがある場合、trueを戻します。
// キーの押し下げの状態は、各フレームの終了時に消去されます。
//=============================================================================
bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	else
		return false;
}

//=============================================================================
// 直近のフレームにおいて、何らかのキーが押された場合、trueを戻します。
// キーの押し下げの状態は、各フレームの終了時に消去されます。
//=============================================================================
bool Input::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		if (keysPressed[i] == true)
			return true;
	return false;
}

//=============================================================================
// 指定されたキーの押し下げをクリア
//=============================================================================
void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

//=============================================================================
// 指定の入力バッファをクリア
// whatの値についてはinput.hを参照
//=============================================================================
void Input::clear(UCHAR what)
{
	// キーが押されているかどうかをクリアする場合
	if (what & inputNS::KEYS_DOWN)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}
	// キーが押されたかどうかをクリアする場合
	if (what & inputNS::KEYS_PRESSED)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}
	// マウスをクリアする場合
	if (what & inputNS::MOUSE)
	{
		mouseX = 0;
		mouseY = 0;
		mouseRawX = 0;
		mouseRawY = 0;
		mouseWheel = 0;
	}
	if (what & inputNS::TEXT_IN)
	{
		clearTextIn();
		clearCharIn();
	}
}

//=============================================================================
// マウスの画面位置を読み取り、mouseXとmouseYに保存
//=============================================================================
void Input::mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

//=============================================================================
// マウスからのローデータを読み取り、mouseRawXとmouseRawYに保存
// このルーチンは、高精細マウスに対応しています。
//=============================================================================
void Input::mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
		lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}

//=============================================================================
// Reads mouse wheel movement expressed in multiples of WHEEL_DELTA, which
// is 120. A positive value indicates that the wheel was rotated away from the
// user, a negative value indicates that the wheel was rotated toward the user.
//=============================================================================
void Input::mouseWheelIn(WPARAM wParam)
{
	mouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
}

//=============================================================================
// Check for connected controllers
//=============================================================================
void Input::checkControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		result = XInputGetState(i, &controllers[i].state);
		if (result == ERROR_SUCCESS)
			controllers[i].connected = true;
		else
			controllers[i].connected = false;
	}
}

//=============================================================================
// 接続されているコントローラーの状態を読み取る
//=============================================================================
void Input::readControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			result = XInputGetState(i, &controllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)    // 接続されていない場合
				controllers[i].connected = false;
		}
	}
}

//=============================================================================
// Return value of controller n Left Trigger (0 through 255).
// Trigger movement less than triggerDeadzone returns 0.
// Return value is scaled to 0 through 255
//=============================================================================
BYTE Input::getGamepadLeftTrigger(UINT n)
{
	BYTE value = getGamepadLeftTriggerUndead(n);
	if (value > triggerDeadzone)             // if > dead zone
											 //adjust magnitude relative to the end of the dead zone
		value = (value - triggerDeadzone) * 255 /
		(255 - triggerDeadzone);
	else                                    // else, < dead zone
		value = 0;
	return value;
}

//=============================================================================
// Return value of controller n Right Trigger (0 through 255).
// Trigger movement less than triggerDeadzone returns 0.
// Return value is scaled to 0 through 255
//=============================================================================
BYTE Input::getGamepadRightTrigger(UINT n)
{
	BYTE value = getGamepadRightTriggerUndead(n);
	if (value > triggerDeadzone)    // if > dead zone
									//adjust magnitude relative to the end of the dead zone
		value = (value - triggerDeadzone) * 255 /
		(255 - triggerDeadzone);
	else                                    // else, < dead zone
		value = 0;
	return value;
}

//=============================================================================
// Return value of controller n Left Thumbstick X (-32767 through 32767).
// Stick movement less than thumbstickDeadzone returns 0.
// Return value is scaled to -32768 through 32767
//=============================================================================
SHORT Input::getGamepadThumbLX(UINT n)
{
	int x = getGamepadThumbLXUndead(n);
	if (x > thumbstickDeadzone) // if +x outside dead zone
								//adjust x relative to the deadzone and scale to 0 through 32767
		x = (x - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (x < -thumbstickDeadzone)   // if -x outside dead zone
										//adjust y relative to the deadzone and scale to 0 through -32767
		x = (x + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, x inside dead zone
		x = 0;  // return 0
	return static_cast<SHORT>(x);
}

//=============================================================================
// Return value of controller n Left Thumbstick Y (-32768 through 32767).
// Stick movement less than thumbstickDeadzone returns 0.
// Return value is scaled to -32768 through 32767
//=============================================================================
SHORT Input::getGamepadThumbLY(UINT n)
{
	int y = getGamepadThumbLYUndead(n);
	if (y > thumbstickDeadzone) // if +y outside dead zone
								//adjust magnitude relative to the end of the dead zone
		y = (y - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (y < -thumbstickDeadzone)   // if -y outside dead zone
										//adjust magnitude relative to the end of the dead zone
		y = (y + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, y inside dead zone
		y = 0;  // return 0
	return static_cast<SHORT>(y);
}

//=============================================================================
// Return value of controller n Right Thumbstick X (-32768 through 32767).
// Stick movement less than thumbstickDeadzone returns 0.
// Return value is scaled to -32768 through 32767
//=============================================================================
SHORT Input::getGamepadThumbRX(UINT n)
{
	int x = getGamepadThumbRXUndead(n);
	if (x > thumbstickDeadzone) // if +x outside dead zone
								//adjust magnitude relative to the end of the dead zone
		x = (x - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (x < -thumbstickDeadzone)   // if -x outside dead zone
										//adjust magnitude relative to the end of the dead zone
		x = (x + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, x inside dead zone
		x = 0;  // return 0
	return static_cast<SHORT>(x);
}

//=============================================================================
// Return value of controller n Right Thumbstick Y (-32768 through 32767).
// Stick movement less than thumbstickDeadzone returns 0.
// Return value is scaled to -32768 through 32767
//=============================================================================
SHORT Input::getGamepadThumbRY(UINT n)
{
	int y = getGamepadThumbRYUndead(n);
	if (y > thumbstickDeadzone) // if +y outside dead zone
								//adjust magnitude relative to the end of the dead zone
		y = (y - thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else if (y < -thumbstickDeadzone)   // if -y outside dead zone
										//adjust magnitude relative to the end of the dead zone
		y = (y + thumbstickDeadzone) * 32767 /
		(32767 - thumbstickDeadzone);
	else        // else, y inside dead zone
		y = 0;  // return 0
	return static_cast<SHORT>(y);
}

//=============================================================================
// 接続されているコントローラーを振動させる
//=============================================================================
void Input::vibrateControllers(float frameTime)
{
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			controllers[i].vibrateTimeLeft -= frameTime;
			if (controllers[i].vibrateTimeLeft < 0)
			{
				controllers[i].vibrateTimeLeft = 0;
				controllers[i].vibration.wLeftMotorSpeed = 0;
			}
			controllers[i].vibrateTimeRight -= frameTime;
			if (controllers[i].vibrateTimeRight < 0)
			{
				controllers[i].vibrateTimeRight = 0;
				controllers[i].vibration.wRightMotorSpeed = 0;
			}
			XInputSetState(i, &controllers[i].vibration);
		}
	}
}


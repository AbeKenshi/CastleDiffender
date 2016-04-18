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
		mKeysDown[i] = false;
	// キーが押されたことを示す配列をクリア
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		mKeysPressed[i] = false;
	mNewLine = true;                     // 新しい行をクリア
	mTextIn = "";                        // textInをクリア
	mCharIn = 0;                         // charInをクリア

	// マウスデータ
	mMouseX = 0;                         // 画面X
	mMouseY = 0;                         // 画面Y
	mMouseRawX = 0;                      // 高精細X
	mMouseRawY = 0;                      // 高精細Y
	mMouseWheel = 0;                     // mouse wheel position
	mMouseLButton = false;               // 左マウスボタンが押されている場合にtrue
	mMouseMButton = false;               // 中央マウスボタンが押されている場合にtrue
	mMouseRButton = false;               // 右マウスボタンが押されている場合にtrue
	mMouseX1Button = false;              // X1マウスボタンが押されている場合にtrue
	mMouseX2Button = false;              // X2マウスボタンが押されている場合にtrue

	for (int i = 0; i<MAX_CONTROLLERS; i++)
	{
		mControllers[i].vibrateTimeLeft = 0;
		mControllers[i].vibrateTimeRight = 0;
	}
	mThumbstickDeadzone = GAMEPAD_THUMBSTICK_DEADZONE;    // default
	mTriggerDeadzone = GAMEPAD_TRIGGER_DEADZONE;          // default
}

//=============================================================================
// デストラクタ
//=============================================================================
Input::~Input()
{
	if (mMouseCaptured)
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
		mMouseCaptured = capture;

		// 高精細マウスを登録
		mRid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		mRid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		mRid[0].dwFlags = RIDEV_INPUTSINK;
		mRid[0].hwndTarget = hwnd;
		RegisterRawInputDevices(mRid, 1, sizeof(mRid[0]));

		if (mMouseCaptured)
			SetCapture(hwnd);           // マウスをキャプチャ

		// コントローラーの状態をクリア
		ZeroMemory(mControllers, sizeof(ControllerState) * MAX_CONTROLLERS);

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
		mKeysDown[wParam] = true;    // keysDown配列を更新
		// キーが既に押されていた、clear()で消去されていた
		mKeysPressed[wParam] = true; // keysPressed配列を更新
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
		mKeysDown[wParam] = false;
}

//=============================================================================
// 入力された文字をtextIn文字列に保存
// 実行前：wParamに、文字が格納されている
//=============================================================================
void Input::keyIn(WPARAM wParam)
{
	if (mNewLine)                            // 新しい行の開始の場合
	{
		mTextIn.clear();
		mNewLine = false;
	}

	if (wParam == '\b')                     // バックスペースキーの場合
	{
		if (mTextIn.length() > 0)             // 文字が存在する場合
			mTextIn.erase(mTextIn.size() - 1);  // 最後に入力された文字を消去
	}
	else
	{
		mTextIn += wParam;                   // 文字をtextInに追加
		mCharIn = wParam;                    // 最後の入力された文字を保存
	}

	if ((char)wParam == '\r')               // リターンキーの場合
		mNewLine = true;                     // 新しい行を開始
}

//=============================================================================
// 指定された仮想キーが押されている場合はtrue、それ以外の場合はfalseを戻す
//=============================================================================
bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return mKeysDown[vkey];
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
		return mKeysPressed[vkey];
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
		if (mKeysPressed[i] == true)
			return true;
	return false;
}

//=============================================================================
// 指定されたキーの押し下げをクリア
//=============================================================================
void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		mKeysPressed[vkey] = false;
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
			mKeysDown[i] = false;
	}
	// キーが押されたかどうかをクリアする場合
	if (what & inputNS::KEYS_PRESSED)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			mKeysPressed[i] = false;
	}
	// マウスをクリアする場合
	if (what & inputNS::MOUSE)
	{
		mMouseX = 0;
		mMouseY = 0;
		mMouseRawX = 0;
		mMouseRawY = 0;
		mMouseWheel = 0;
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
	mMouseX = GET_X_LPARAM(lParam);
	mMouseY = GET_Y_LPARAM(lParam);
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
		mMouseRawX = raw->data.mouse.lLastX;
		mMouseRawY = raw->data.mouse.lLastY;
	}
}

//=============================================================================
// Reads mouse wheel movement expressed in multiples of WHEEL_DELTA, which
// is 120. A positive value indicates that the wheel was rotated away from the
// user, a negative value indicates that the wheel was rotated toward the user.
//=============================================================================
void Input::mouseWheelIn(WPARAM wParam)
{
	mMouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
}

//=============================================================================
// Check for connected controllers
//=============================================================================
void Input::checkControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		result = XInputGetState(i, &mControllers[i].state);
		if (result == ERROR_SUCCESS)
			mControllers[i].connected = true;
		else
			mControllers[i].connected = false;
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
		if (mControllers[i].connected)
		{
			result = XInputGetState(i, &mControllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)    // 接続されていない場合
				mControllers[i].connected = false;
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
	if (value > mTriggerDeadzone)             // if > dead zone
											 //adjust magnitude relative to the end of the dead zone
		value = (value - mTriggerDeadzone) * 255 /
		(255 - mTriggerDeadzone);
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
	if (value > mTriggerDeadzone)    // if > dead zone
									//adjust magnitude relative to the end of the dead zone
		value = (value - mTriggerDeadzone) * 255 /
		(255 - mTriggerDeadzone);
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
	if (x > mThumbstickDeadzone) // if +x outside dead zone
								//adjust x relative to the deadzone and scale to 0 through 32767
		x = (x - mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
	else if (x < -mThumbstickDeadzone)   // if -x outside dead zone
										//adjust y relative to the deadzone and scale to 0 through -32767
		x = (x + mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
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
	if (y > mThumbstickDeadzone) // if +y outside dead zone
								//adjust magnitude relative to the end of the dead zone
		y = (y - mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
	else if (y < -mThumbstickDeadzone)   // if -y outside dead zone
										//adjust magnitude relative to the end of the dead zone
		y = (y + mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
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
	if (x > mThumbstickDeadzone) // if +x outside dead zone
								//adjust magnitude relative to the end of the dead zone
		x = (x - mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
	else if (x < -mThumbstickDeadzone)   // if -x outside dead zone
										//adjust magnitude relative to the end of the dead zone
		x = (x + mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
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
	if (y > mThumbstickDeadzone) // if +y outside dead zone
								//adjust magnitude relative to the end of the dead zone
		y = (y - mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
	else if (y < -mThumbstickDeadzone)   // if -y outside dead zone
										//adjust magnitude relative to the end of the dead zone
		y = (y + mThumbstickDeadzone) * 32767 /
		(32767 - mThumbstickDeadzone);
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
		if (mControllers[i].connected)
		{
			mControllers[i].vibrateTimeLeft -= frameTime;
			if (mControllers[i].vibrateTimeLeft < 0)
			{
				mControllers[i].vibrateTimeLeft = 0;
				mControllers[i].vibration.wLeftMotorSpeed = 0;
			}
			mControllers[i].vibrateTimeRight -= frameTime;
			if (mControllers[i].vibrateTimeRight < 0)
			{
				mControllers[i].vibrateTimeRight = 0;
				mControllers[i].vibration.wRightMotorSpeed = 0;
			}
			XInputSetState(i, &mControllers[i].vibration);
		}
	}
}


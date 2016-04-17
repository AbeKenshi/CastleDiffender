//==========================================================
/// @file
/// @brief    input.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "input.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
Input::Input()
{
	// �L�[��������Ă����Ԃ������z����N���A
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysDown[i] = false;
	// �L�[�������ꂽ���Ƃ������z����N���A
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysPressed[i] = false;
	newLine = true;                     // �V�����s���N���A
	textIn = "";                        // textIn���N���A
	charIn = 0;                         // charIn���N���A

	// �}�E�X�f�[�^
	mouseX = 0;                         // ���X
	mouseY = 0;                         // ���Y
	mouseRawX = 0;                      // ������X
	mouseRawY = 0;                      // ������Y
	mouseWheel = 0;                     // mouse wheel position
	mouseLButton = false;               // ���}�E�X�{�^����������Ă���ꍇ��true
	mouseMButton = false;               // �����}�E�X�{�^����������Ă���ꍇ��true
	mouseRButton = false;               // �E�}�E�X�{�^����������Ă���ꍇ��true
	mouseX1Button = false;              // X1�}�E�X�{�^����������Ă���ꍇ��true
	mouseX2Button = false;              // X2�}�E�X�{�^����������Ă���ꍇ��true

	for (int i = 0; i<MAX_CONTROLLERS; i++)
	{
		controllers[i].vibrateTimeLeft = 0;
		controllers[i].vibrateTimeRight = 0;
	}
	thumbstickDeadzone = GAMEPAD_THUMBSTICK_DEADZONE;    // default
	triggerDeadzone = GAMEPAD_TRIGGER_DEADZONE;          // default
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Input::~Input()
{
	if (mouseCaptured)
		ReleaseCapture();               // �}�E�X�����
}

//=============================================================================
// �}�E�X�ƃR���g���[���[�̓��͂�������
// �}�E�X���L���v�`������ꍇ�Acapture=true��ݒ�
// GameError���X���[
//=============================================================================
void Input::initialize(HWND hwnd, bool capture)
{
	try {
		mouseCaptured = capture;

		// �����׃}�E�X��o�^
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = hwnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

		if (mouseCaptured)
			SetCapture(hwnd);           // �}�E�X���L���v�`��

		// �R���g���[���[�̏�Ԃ��N���A
		ZeroMemory(controllers, sizeof(ControllerState) * MAX_CONTROLLERS);

		checkControllers();             // �ڑ�����Ă���R���g���[���[���`�F�b�N
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
	}
}

//=============================================================================
// ���̃L�[�ɂ��āAkeysDown�z���keyPressed�z���true��ݒ�
// ���s�O�FwParam�ɁA���z�L�[�R�[�h�i0~255�j���i�[����Ă���
//=============================================================================
void Input::keyDown(WPARAM wParam)
{
	// �L�[�R�[�h���A�o�b�t�@�͈͓��ɂ��邱�Ƃ��m�F
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		keysDown[wParam] = true;    // keysDown�z����X�V
		// �L�[�����ɉ�����Ă����Aclear()�ŏ�������Ă���
		keysPressed[wParam] = true; // keysPressed�z����X�V
	}
}

//=============================================================================
// ���̃L�[�ɂ��āAkeysDown�z���false��ݒ�
// ���s�O�FwParam�ɁA���z�L�[�R�[�h�i0~255�j���i�[����Ă���
//=============================================================================
void Input::keyUp(WPARAM wParam)
{
	// �L�[�R�[�h���A�o�b�t�@�͈͓��ɂ��邱�Ƃ��m�F
	if (wParam < inputNS::KEYS_ARRAY_LEN)
		// ��ԃe�[�u�����X�V
		keysDown[wParam] = false;
}

//=============================================================================
// ���͂��ꂽ������textIn������ɕۑ�
// ���s�O�FwParam�ɁA�������i�[����Ă���
//=============================================================================
void Input::keyIn(WPARAM wParam)
{
	if (newLine)                            // �V�����s�̊J�n�̏ꍇ
	{
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')                     // �o�b�N�X�y�[�X�L�[�̏ꍇ
	{
		if (textIn.length() > 0)             // ���������݂���ꍇ
			textIn.erase(textIn.size() - 1);  // �Ō�ɓ��͂��ꂽ����������
	}
	else
	{
		textIn += wParam;                   // ������textIn�ɒǉ�
		charIn = wParam;                    // �Ō�̓��͂��ꂽ������ۑ�
	}

	if ((char)wParam == '\r')               // ���^�[���L�[�̏ꍇ
		newLine = true;                     // �V�����s���J�n
}

//=============================================================================
// �w�肳�ꂽ���z�L�[��������Ă���ꍇ��true�A����ȊO�̏ꍇ��false��߂�
//=============================================================================
bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	else
		return false;
}

//=============================================================================
// ���߃t���[���ɂ����āA�w��̉��z�L�[�������ꂽ���Ƃ�����ꍇ�Atrue��߂��܂��B
// �L�[�̉��������̏�Ԃ́A�e�t���[���̏I�����ɏ�������܂��B
//=============================================================================
bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	else
		return false;
}

//=============================================================================
// ���߂̃t���[���ɂ����āA���炩�̃L�[�������ꂽ�ꍇ�Atrue��߂��܂��B
// �L�[�̉��������̏�Ԃ́A�e�t���[���̏I�����ɏ�������܂��B
//=============================================================================
bool Input::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		if (keysPressed[i] == true)
			return true;
	return false;
}

//=============================================================================
// �w�肳�ꂽ�L�[�̉����������N���A
//=============================================================================
void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

//=============================================================================
// �w��̓��̓o�b�t�@���N���A
// what�̒l�ɂ��Ă�input.h���Q��
//=============================================================================
void Input::clear(UCHAR what)
{
	// �L�[��������Ă��邩�ǂ������N���A����ꍇ
	if (what & inputNS::KEYS_DOWN)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}
	// �L�[�������ꂽ���ǂ������N���A����ꍇ
	if (what & inputNS::KEYS_PRESSED)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}
	// �}�E�X���N���A����ꍇ
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
// �}�E�X�̉�ʈʒu��ǂݎ��AmouseX��mouseY�ɕۑ�
//=============================================================================
void Input::mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

//=============================================================================
// �}�E�X����̃��[�f�[�^��ǂݎ��AmouseRawX��mouseRawY�ɕۑ�
// ���̃��[�`���́A�����׃}�E�X�ɑΉ����Ă��܂��B
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
// �ڑ�����Ă���R���g���[���[�̏�Ԃ�ǂݎ��
//=============================================================================
void Input::readControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			result = XInputGetState(i, &controllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)    // �ڑ�����Ă��Ȃ��ꍇ
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
// �ڑ�����Ă���R���g���[���[��U��������
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


//==========================================================
/// @file
/// @brief    Input�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _INPUT_H                // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA 
#define _INPUT_H                // ���d�ɒ�`����邱�Ƃ�h���܂��B
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

// Input�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;     // �L�[�z��̒���

	// what values for clear(), bit flag
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

const short GAMEPAD_THUMBSTICK_DEADZONE = (short)(0.20f * 0X7FFF);    // �f�b�h�]�[���Ƃ��Ĕ͈͂�20%���f�t�H���g�Ƃ���
const short GAMEPAD_TRIGGER_DEADZONE = 20;                      // �g���K�[�͈̔͂�0����255�܂�
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
	// �w��̃L�[��������Ă����Ԃ̏ꍇ��true
	bool mKeysDown[inputNS::KEYS_ARRAY_LEN];
	// �w��̃L�[�������ꂽ�ꍇ��true
	bool mKeysPressed[inputNS::KEYS_ARRAY_LEN];
	std::string mTextIn;                         // ���[�U�[�����͂����e�L�X�g
	char mCharIn;                                // �Ō�ɓ��͂��ꂽ����
	bool mNewLine;                               // �V�����s�̊J�n����true
	int  mMouseX, mMouseY;                       // �}�E�X�̉�ʍ��W
	int  mMouseRawX, mMouseRawY;                 // �����׃}�E�X�̃f�[�^
	int  mMouseWheel;                            // 
	RAWINPUTDEVICE mRid[1];                      // �����׃}�E�X�p
	bool mMouseCaptured;                         // �}�E�X���L���v�`������Ă���ꍇ��true
	bool mMouseLButton;                          // ���}�E�X�{�^����������Ă���ꍇ��true
	bool mMouseMButton;                          // �����}�E�X�{�^����������Ă���ꍇ��true
	bool mMouseRButton;                          // �E�}�E�X�{�^����������Ă���ꍇ��true
	bool mMouseX1Button;                         // X1�}�E�X�{�^����������Ă���ꍇ��true
	bool mMouseX2Button;                         // X2�}�E�X�{�^����������Ă���ꍇ��true
	ControllerState mControllers[MAX_CONTROLLERS];    // �R���g���[���[�̏��
	short mThumbstickDeadzone;
	short mTriggerDeadzone;

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

	// �L�[�A�}�E�X�A�e�L�X�g���̓o�b�t�@���N���A
	void clearAll() { clear(inputNS::KEYS_MOUSE_TEXT); }

	// �e�L�X�g���̓o�b�t�@���N���A
	void clearTextIn() { mTextIn.clear(); }

	// Clear last character entered
	void clearCharIn() { mCharIn = 0; }

	// Return text input as a string
	std::string getTextIn() { return mTextIn; }

	// Set text input string
	void setTextIn(std::string str) { mTextIn = str; }

	// Return last character entered
	char getCharIn() { return mCharIn; }

	// Reads mouse screen position into mouseX, mouseY
	void mouseIn(LPARAM);

	// Reads raw mouse data into mouseRawX, mouseRawY
	// This routine is compatible with a high-definition mouse
	void mouseRawIn(LPARAM);

	// Reads mouse wheel movement.
	void mouseWheelIn(WPARAM);

	// ���}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseLButton(bool b) { mMouseLButton = b; }

	// �����}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseMButton(bool b) { mMouseMButton = b; }

	// �E�}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseRButton(bool b) { mMouseRButton = b; }

	// X1�AX2�}�E�X�{�^���̏�Ԃ�ۑ�
	void setMouseXButton(WPARAM wParam) {
		mMouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		mMouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}

	// �}�E�X��X�ʒu��߂�
	int  getMouseX()        const { return mMouseX; }

	// �}�E�X��Y�ʒu��߂�
	int  getMouseY()        const { return mMouseY; }

	// �}�E�X��X�ʒu�̈ړ��̃��[�f�[�^��߂��B���ւ̈ړ���<0�A�E�ւ̈ړ���>0
	// �����׃}�E�X�ɑΉ�
	int  getMouseRawX()
	{
		int rawX = mMouseRawX;
		mMouseRawX = 0;
		return rawX;
	}

	// �}�E�X��Y�ʒu�̈ړ��̃��[�f�[�^��߂��B��ւ̈ړ���<0�A���ւ̈ړ���>0
	// �����׃}�E�X�ɑΉ�
	int  getMouseRawY()
	{
		int rawY = mMouseRawY;
		mMouseRawY = 0;
		return rawY;
	}

	// Return mouse wheel movement relative to previous position.
	// Forward is >0, Backward is <0, movement is in multiples of WHEEL_DATA (120).
	int  getMouseWheel()
	{
		int wheel = mMouseWheel;
		mMouseWheel = 0;
		return wheel;
	}

	// ���}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseLButton()  const { return mMouseLButton; }

	// �����}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseMButton()  const { return mMouseMButton; }

	// �E�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseRButton()  const { return mMouseRButton; }

	// X1�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseX1Button() const { return mMouseX1Button; }

	// X2�}�E�X�{�^���̏�Ԃ�߂�
	bool getMouseX2Button() const { return mMouseX2Button; }

	// Update connection status of game controllers.
	void checkControllers();

	// Save input from connected game controllers.
	void readControllers();

	// Set thumbstick deadzone
	void setThumbstickDeadzone(short dz) { mThumbstickDeadzone = abs(dz); }

	// Set trigger deadzone
	void setTriggerDeadzone(BYTE dz) { mTriggerDeadzone = dz; }

	// Get thumbstick deadzone
	short getThumbstickDeadzone() { return mThumbstickDeadzone; }

	// Get trigger deadzone
	BYTE getTriggerDeadzone() { return static_cast<BYTE>(mTriggerDeadzone); }

	// �w��̃Q�[���R���g���[���[�̏�Ԃ�߂�
	const ControllerState* getControllerState(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return &mControllers[n];
	}

	// Return connection state of specified game controller
	bool getGamepadConnected(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return mControllers[n].connected;
	}

	// �R���g���[���[n�̃{�^���̏�Ԃ�߂�
	const WORD getGamepadButtons(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return mControllers[n].state.Gamepad.wButtons;
	}

	// �R���g���[���[n�̕����p�b�h��̏�Ԃ�߂�
	bool getGamepadDPadUp(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((mControllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_UP) != 0);
	}

	// �R���g���[���[n�̕����p�b�h���̏�Ԃ�߂�
	bool getGamepadDPadDown(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((mControllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_DOWN) != 0);
	}

	// �R���g���[���[n�̕����p�b�h���̏�Ԃ�߂�
	bool getGamepadDPadLeft(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return ((mControllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_LEFT) != 0);
	}

	// �R���g���[���[n�̕����p�b�h�E�̏�Ԃ�߂�
	bool getGamepadDPadRight(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_RIGHT) != 0);
	}

	// �R���g���[���[n��START�{�^���̏�Ԃ�߂�
	bool getGamepadStart(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_START_BUTTON) != 0);
	}

	// �R���g���[���[n��BACK�{�^���̏�Ԃ�߂�
	bool getGamepadBack(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_BACK_BUTTON) != 0);
	}

	// �R���g���[���[n�̍��T���{�^���̏�Ԃ�߂�
	bool getGamepadLeftThumb(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_THUMB) != 0);
	}

	// �R���g���[���[n�̉E�T���{�^���̏�Ԃ�߂�
	bool getGamepadRightThumb(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_THUMB) != 0);
	}

	// �R���g���[���[n�̍��V�����_�[�{�^���̏�Ԃ�߂�
	bool getGamepadLeftShoulder(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_SHOULDER) != 0);
	}

	// �R���g���[���[n�̉E�V�����_�[�{�^���̏�Ԃ�߂�
	bool getGamepadRightShoulder(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_SHOULDER) != 0);
	}

	// �R���g���[���[n��A�{�^���̏�Ԃ�߂�
	bool getGamepadA(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_A) != 0);
	}

	// �R���g���[���[n��B�{�^���̏�Ԃ�߂�
	bool getGamepadB(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_B) != 0);
	}

	// �R���g���[���[n��X�{�^���̏�Ԃ�߂�
	bool getGamepadX(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_X) != 0);
	}

	// �R���g���[���[n��Y�{�^���̏�Ԃ�߂�
	bool getGamepadY(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return bool((mControllers[n].state.Gamepad.wButtons&GAMEPAD_Y) != 0);
	}

	// �R���g���[���[n�̍��g���K�[�̒l��߂��܂��B
	BYTE getGamepadLeftTrigger(UINT n);

	// Return value of controller n Left Trigger (0 through 255).
	// Deadzone is not applied.
	BYTE getGamepadLeftTriggerUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return mControllers[n].state.Gamepad.bLeftTrigger;
	}

	// �R���g���[���[n�̉E�g���K�[�̒l��߂��܂��B
	BYTE getGamepadRightTrigger(UINT n);

	// Return value of controller n Right Trigger (0 through 255).
	// Deadzone is not applied.
	BYTE getGamepadRightTriggerUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return mControllers[n].state.Gamepad.bRightTrigger;
	}

	// �R���g���[���[n�̍��T���X�e�B�b�N�AX�̒l��߂��܂��B
	SHORT getGamepadThumbLX(UINT n);

	// Return value of controller n Left Thumbstick X (-32767 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbLXUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return mControllers[n].state.Gamepad.sThumbLX;
	}

	// �R���g���[���[n�̍��T���X�e�B�b�N�AY�̒l��߂��܂��B
	SHORT getGamepadThumbLY(UINT n);

	// Return value of controller n Left Thumbstick Y (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbLYUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return mControllers[n].state.Gamepad.sThumbLY;
	}

	// �R���g���[���[n�̉E�T���X�e�B�b�N�AX�̒l��߂��܂��B
	SHORT getGamepadThumbRX(UINT n);

	// Return value of controller n Right Thumbstick X (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbRXUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)   // if invalid controller number
			n = MAX_CONTROLLERS - 1;    // force valid
		return mControllers[n].state.Gamepad.sThumbRX;
	}

	// �R���g���[���[n�̉E�T���X�e�B�b�N�AY�̒l��߂��܂��B
	SHORT getGamepadThumbRY(UINT n);

	// Return value of controller n Right Thumbstick Y (-32768 through 32767).
	// Deadzone is not applied.
	SHORT getGamepadThumbRYUndead(UINT n)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		return mControllers[n].state.Gamepad.sThumbRY;
	}

	// �R���g���[���[n�̍����[�^�[��U��������
	// ���͒���g�U��
	// speed�F0=�I�t�A65536=100�p�[�Z���g
	// sec�F�U�������鎞�ԁi�b�j
	void gamePadVibrateLeft(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		mControllers[n].vibration.wLeftMotorSpeed = speed;
		mControllers[n].vibrateTimeLeft = sec;
	}

	// �R���g���[���[n�̉E���[�^�[��U��������
	// ���͒���g�U��
	// speed�F0=�I�t�A65536=100�p�[�Z���g
	// sec�F�U�������鎞�ԁi�b�j
	void gamePadVibrateRight(UINT n, WORD speed, float sec)
	{
		if (n > MAX_CONTROLLERS - 1)
			n = MAX_CONTROLLERS - 1;
		mControllers[n].vibration.wRightMotorSpeed = speed;
		mControllers[n].vibrateTimeRight = sec;
	}

	// �ڑ�����Ă���R���g���[���[��U��������
	void vibrateControllers(float frameTime);
};

#endif


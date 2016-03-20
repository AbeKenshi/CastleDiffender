#ifndef _CONSTANTS_H            // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _CONSTANTS_H            // ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
//                  �萔
//=============================================================================

// �E�B���h�E�Ɋւ���萔
const char CLASS_NAME[] = "TowerDiffence";
const char GAME_TITLE[] = "TowerDiffence ver0.1";
const bool FULLSCREEN = false;							// �t���X�N���[���̏ꍇtrue
const UINT GAME_WIDTH = 1280;							// �Q�[����ʂ̕��i�s�N�Z���P�ʁj
const UINT GAME_HEIGHT = 720;							// �Q�[����ʂ̍����i�s�N�Z���P�ʁj

// �Q�[�����̒萔
const double PI = 3.14159265;							// �~����
const float FRAME_RATE = 60.0f;						// �t���[�����[�g (frames/sec)
const float MIN_FRAME_RATE = 10.0f;						// �ŏ��̃t���[�����[�g
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;			// 1�t���[���ɗv����ŏ��̎���
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;		// 1�t���[���ɗv����ő�̎���

// �摜
const char MENU_IMAGE[] = "pictures\\menu.png";				// ���j���[�摜
const char BRAVE_MOVE_IMAGE[] = "pictures\\alex\\move_atack.png";	// �E�҂̕��s�摜

// ����
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\waveBank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\soundBank.xsb";
// audio cues


// �L�[�}�b�v
const UCHAR CONSOLE_KEY = '`';			// `�L�[
const UCHAR ESC_KEY = VK_ESCAPE;		// Esc�L�[
const UCHAR ALT_KEY = VK_MENU;			// Alt�L�[
const UCHAR ENTER_KEY = VK_RETURN;		// Enter�L�[
const UCHAR BRAVE_LEFT_KEY = VK_LEFT;	// ���ړ��L�[
const UCHAR BRAVE_RIGHT_KEY = VK_RIGHT;	// �E�ړ��L�[
const UCHAR BRAVE_UP_KEY = VK_UP;		// ��ړ��L�[
const UCHAR BRAVE_DOWN_KEY = VK_DOWN;	// ���ړ��L�[
const UCHAR BRAVE_ATTACK_KEY = VK_RETURN;// �U���L�[

// weapon types
enum WEAPON { TORPEDO, SHIP, PLANET };

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
	if (ptr)
		ptr->onLostDevice();
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
	if (ptr)
		ptr->onResetDevice();
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif
